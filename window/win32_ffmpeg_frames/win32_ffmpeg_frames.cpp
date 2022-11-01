// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
// https://blogs.windows.com/windowsdeveloper/2015/06/05/using-ffmpeg-in-windows-applications/
// https://github.com/Microsoft/FFmpegInterop
// https://stackoverflow.com/questions/2401764/can-ffmpeg-be-used-as-a-library-instead-of-a-standalone-program
// https://trac.ffmpeg.org/wiki/Projects
// https://www.cnblogs.com/judgeou/p/14724951.html
// https://github.com/BtbN/FFmpeg-Builds/releases
// https://www.jianshu.com/p/3ea9ef713211
#ifndef UNICODE
#define UNICODE
#endif

#include <string.h>
#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <vector>
#include <stdint.h>
#include <atlbase.h>
#include <atlconv.h>
#include <thread>
#include <chrono>

#pragma comment(linker, "/subsystem:windows") /// SUBSYSTEM:CONSOLE

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ComDlg32.Lib")

extern "C" {
#include <libavcodec/codec.h>
#include <libavcodec/packet.h>
#include <libavutil/avutil.h>
#include <libavutil/error.h>
#include <libavutil/frame.h>

#include <libavcodec/avcodec.h>
#pragma comment(lib, "avcodec.lib")

#include <libavformat/avformat.h>
#pragma comment(lib, "avformat.lib")

#include <libavutil/imgutils.h>
#pragma comment(lib, "avutil.lib")

#include <libswscale/swscale.h>
#pragma comment(lib, "swscale.lib")
}

#define IDM_MENU_PICK_FILE 4001

typedef struct ColorRGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} ColorRGB;

typedef struct DecoderParam {
  AVFormatContext* fmtCtx = nullptr;
  AVCodecContext* vcodecCtx = nullptr;
  int width;
  int height;
  int videoStreamIndex;
} DecoderParam, *PDecoderParam;

HWND hWnd;
HMENU hMenu = NULL;
HMENU mSubMenu = NULL;
DecoderParam decoderParam;
SwsContext* swsCtx = nullptr;
std::vector<ColorRGB> buffer;
auto currentTime = std::chrono::system_clock::now();

void InitDecoder(const char* filePath, DecoderParam& param) {
  AVFormatContext* fmtCtx = nullptr;
  avformat_open_input(&fmtCtx, filePath, NULL, NULL);
  avformat_find_stream_info(fmtCtx, NULL);

  AVCodecContext* vcodecCtx = nullptr;
  for (int i = 0; i < fmtCtx->nb_streams; i++) {
    AVStream* stream = fmtCtx->streams[i];
    const AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
    if (codec->type == AVMEDIA_TYPE_VIDEO) {
      param.videoStreamIndex = i;
      vcodecCtx = avcodec_alloc_context3(codec);
      avcodec_parameters_to_context(vcodecCtx, fmtCtx->streams[i]->codecpar);
      avcodec_open2(vcodecCtx, codec, NULL);
    }
  }

  param.fmtCtx = fmtCtx;
  param.vcodecCtx = vcodecCtx;
  param.width = vcodecCtx->width;
  param.height = vcodecCtx->height;
}

AVFrame* RequestFrame(DecoderParam& param) {
  auto& fmtCtx = param.fmtCtx;
  auto& vcodecCtx = param.vcodecCtx;
  auto& videoStreamIndex = param.videoStreamIndex;
  AVFrame* frame = nullptr;
  while (TRUE) {
    AVPacket* packet = av_packet_alloc();
    int ret = av_read_frame(fmtCtx, packet);
    if (ret == 0 && packet->stream_index == videoStreamIndex) {
      ret = avcodec_send_packet(vcodecCtx, packet);
      if (ret == 0) {
        frame = av_frame_alloc();
        ret = avcodec_receive_frame(vcodecCtx, frame);
        if (ret == 0) {
          av_packet_unref(packet);
          break;
        } else if (ret == AVERROR(EAGAIN)) {
          av_frame_unref(frame);
          continue;
        }
      }
    }
    av_packet_unref(packet);
  }
  return frame;
}

AVFrame* GetFirstFrame(DecoderParam& param) {
  auto& fmtCtx = param.fmtCtx;
  auto& vcodecCtx = param.vcodecCtx;
  auto& videoStreamIndex = param.videoStreamIndex;

  AVFrame* frame = nullptr;
  while (TRUE) {
    AVPacket* packet = av_packet_alloc();
    int ret = av_read_frame(fmtCtx, packet);
    if (ret == 0 && packet->stream_index == videoStreamIndex) {
      ret = avcodec_send_packet(vcodecCtx, packet);
      if (ret == 0) {
        frame = av_frame_alloc();
        ret = avcodec_receive_frame(vcodecCtx, frame);
        if (ret == 0) {
          av_packet_unref(packet);
          avcodec_free_context(&vcodecCtx);
          avformat_close_input(&fmtCtx);
          break;
        } else if (ret == AVERROR(EAGAIN)) {
          av_frame_unref(frame);
          continue;
        }
      }
    }
    av_packet_unref(packet);
  }
  return frame;
}

std::vector<ColorRGB> GetRGBPixels(AVFrame* frame,
                                   std::vector<ColorRGB>& buffer) {
  swsCtx = sws_getCachedContext(swsCtx, frame->width, frame->height,
                                (AVPixelFormat)frame->format, frame->width,
                                frame->height, AVPixelFormat::AV_PIX_FMT_BGR24,
                                NULL, NULL, NULL, 0L);

  uint8_t* data[] = {(uint8_t*)&buffer[0]};
  int linesize[] = {frame->width * 3};

  sws_scale(swsCtx, frame->data, frame->linesize, 0, frame->height, data,
            linesize);

  return buffer;
}

void StrecthBits(HWND hWnd, const std::vector<ColorRGB>& bits, int width,
                 int height) {
  HDC hdc = GetDC(hWnd);
  BITMAPINFO bitinfo = {};
  BITMAPINFOHEADER& bmiHeader = bitinfo.bmiHeader;
  bmiHeader.biSize = sizeof(bitinfo.bmiHeader);
  bmiHeader.biWidth = width;
  bmiHeader.biHeight = -height;
  bmiHeader.biPlanes = 1;
  bmiHeader.biBitCount = 24;
  bmiHeader.biCompression = BI_RGB;
  StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, &bits[0],
                &bitinfo, DIB_RGB_COLORS, SRCCOPY);
  ReleaseDC(hWnd, hdc);
}

void RenderFrame(DecoderParam& decoderParam) {
  int width = decoderParam.width;
  int height = decoderParam.height;
  auto& fmtCtx = decoderParam.fmtCtx;
  auto& vcodecCtx = decoderParam.vcodecCtx;
  AVFrame* frame = RequestFrame(decoderParam);

  std::vector<ColorRGB> pixels = GetRGBPixels(frame, buffer);
  av_frame_free(&frame);

  double frameRate =
      (double)vcodecCtx->framerate.den / vcodecCtx->framerate.num;
  std::this_thread::sleep_until(
      currentTime + std::chrono::milliseconds((int)(frameRate * 1000)));
  currentTime = std::chrono::system_clock::now();
  StrecthBits(hWnd, pixels, width, height);
  Sleep(frameRate * 1000);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    hMenu = CreateMenu();
    mSubMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_PICK_FILE,
               TEXT("Pick mp4 File"));

    SetMenu(hWnd, hMenu);
  }
  case WM_COMMAND:
    switch (wParam) {
    case IDM_MENU_PICK_FILE:
      wchar_t szPath[MAX_PATH] = {'\0'};
      OPENFILENAME ofn = {sizeof(ofn)}; // common dialog box structure
      ofn.hwndOwner = hWnd;
      ofn.lpstrFilter = L"All Files\0*.*\0";
      ofn.lpstrFile = szPath;
      ofn.nMaxFile = ARRAYSIZE(szPath);

      BOOL fOk = GetOpenFileName(&ofn);
      if (fOk) {
        char* filePath = ATL::CW2A(szPath);
        InitDecoder(filePath, decoderParam);
        auto buf =
            std::vector<ColorRGB>(decoderParam.width * decoderParam.height);
        buffer = buf;
        RenderFrame(decoderParam);
      }
      break;
    }
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_PAINT: {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hWnd, &ps);
  }
    return 0;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  // Register the window class.
  const wchar_t CLASS_NAME[] = L"Sample Window Class";

  WNDCLASS wc = {};

  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = CLASS_NAME;

  RegisterClass(&wc);

  // Create the window.

  hWnd =
      CreateWindowEx(0,          // Optional window styles.
                     CLASS_NAME, // Window class
                     L"Learn Win32 To Program Windows", // Window text
                     WS_OVERLAPPEDWINDOW,               // Window style

                     // Size and position
                     CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

                     NULL,      // Parent window
                     NULL,      // Menu
                     hInstance, // Instance handle
                     NULL       // Additional application data
      );

  if (hWnd == NULL) {
    return 0;
  }

  ShowWindow(hWnd, nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (TRUE) {
    BOOL hasMSG = PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
    if (hasMSG) {
      if (msg.message == WM_QUIT) {
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      if (decoderParam.vcodecCtx != nullptr) {
        RenderFrame(decoderParam);
      }
    }
  }

  return 0;
}
