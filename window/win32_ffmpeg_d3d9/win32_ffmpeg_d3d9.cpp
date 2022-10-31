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
#include <wrl.h>

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

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
}

using Microsoft::WRL::ComPtr;
ComPtr<IDirect3D9> d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
ComPtr<IDirect3DDevice9> d3d9Device;
D3DPRESENT_PARAMETERS d3dParams = {};

#define IDM_MENU_PICK_FILE 4001

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
std::vector<uint8_t> buffer;
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
  // 启动硬件解码器
  AVBufferRef* hwDeviceCtx = nullptr;
  av_hwdevice_ctx_create(&hwDeviceCtx, AVHWDeviceType::AV_HWDEVICE_TYPE_D3D11VA,
                         NULL, NULL, 0);
  vcodecCtx->hw_device_ctx = hwDeviceCtx;

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

void GetRGBPixels(AVFrame* frame, std::vector<uint8_t>& buffer,
                  AVPixelFormat pixelFormat, int byteCount) {

  AVFrame* swFrame = av_frame_alloc();
  av_hwframe_transfer_data(swFrame, frame, 0);
  frame = swFrame;

  swsCtx = sws_getCachedContext(swsCtx, frame->width, frame->height,
                                (AVPixelFormat)frame->format, frame->width,
                                frame->height, pixelFormat,
                                NULL, NULL, NULL, 0L);
  uint8_t* data[] = {&buffer[0]};
  int linesize[] = {frame->width * byteCount};

  sws_scale(swsCtx, frame->data, frame->linesize, 0, frame->height, data,
            linesize);

  av_frame_free(&swFrame);
}

void StrecthBits(IDirect3DDevice9* device, const std::vector<uint8_t>& bits,
                 int width, int height) {
  ComPtr<IDirect3DSurface9> surface;
  device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, surface.GetAddressOf());

  D3DLOCKED_RECT lockRect;
  surface->LockRect(&lockRect, NULL, D3DLOCK_DISCARD);

  memcpy(lockRect.pBits, &bits[0], bits.size());
  surface->UnlockRect();
  device->Present(NULL, NULL, NULL, NULL);
}

void RenderFrame(DecoderParam& decoderParam) {
  int width = decoderParam.width;
  int height = decoderParam.height;
  auto& fmtCtx = decoderParam.fmtCtx;
  auto& vcodecCtx = decoderParam.vcodecCtx;
  AVFrame* frame = RequestFrame(decoderParam);

  GetRGBPixels(frame, buffer, AVPixelFormat::AV_PIX_FMT_BGRA, 4);
  av_frame_free(&frame);

  double framerate =
      (double)vcodecCtx->framerate.den / vcodecCtx->framerate.num;
  std::this_thread::sleep_until(
      currentTime + std::chrono::milliseconds((int)(framerate * 1000)));
  currentTime = std::chrono::system_clock::now();

  StrecthBits(d3d9Device.Get(), buffer, width, height);
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

        buffer =
            std::vector<uint8_t>(decoderParam.width * decoderParam.height * 4);

        d3dParams.Windowed = TRUE;
        d3dParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dParams.BackBufferFormat = D3DFORMAT::D3DFMT_X8R8G8B8;
        d3dParams.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
        d3dParams.BackBufferWidth = decoderParam.width;
        d3dParams.BackBufferHeight = decoderParam.height;
        d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                           D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dParams,
                           d3d9Device.GetAddressOf());

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
