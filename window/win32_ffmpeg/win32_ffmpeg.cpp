// https://learn.microsoft.com/zh-tw/windows/win32/learnwin32/your-first-windows-program
// https://blogs.windows.com/windowsdeveloper/2015/06/05/using-ffmpeg-in-windows-applications/
// https://github.com/Microsoft/FFmpegInterop
// https://stackoverflow.com/questions/2401764/can-ffmpeg-be-used-as-a-library-instead-of-a-standalone-program
// https://trac.ffmpeg.org/wiki/Projects
// https://blog.csdn.net/weixin_45032957/article/details/116447520?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-116447520-blog-79367721.pc_relevant_3mothn_strategy_and_data_recovery&spm=1001.2101.3001.4242.1&utm_relevant_index=3
// https://github.com/BtbN/FFmpeg-Builds/releases
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <winuser.h>
#include <wingdi.h>
#include <vector>
#include "libavcodec/codec.h"
#include "libavcodec/packet.h"
#include "libavutil/avutil.h"
#include "libavutil/error.h"
#include "libavutil/frame.h"
#include <stdint.h>

#pragma comment(linker, "/subsystem:windows") /// SUBSYSTEM:CONSOLE

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "ComDlg32.Lib")

extern "C" {
#include <libavcodec/avcodec.h>
#pragma comment(lib, "avcodec.lib")

#include <libavformat/avformat.h>
#pragma comment(lib, "avformat.lib")

#include <libavutil/imgutils.h>
#pragma comment(lib, "avutil.lib")
}

#define IDM_MENU_SUB 4001

typedef struct ColorRGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} ColorRGB;

HWND hWnd;
HMENU hMenu = NULL;
HMENU mSubMenu = NULL;

AVFrame* getFirstFrame(const char* filePath) {
  AVFormatContext* fmtCtx = nullptr;
  avformat_open_input(&fmtCtx, filePath, NULL, NULL);
  avformat_find_stream_info(fmtCtx, NULL);

  int videoStreamIndex;
  AVCodecContext* vcodecCtx = nullptr;
  for (int i = 0; i < fmtCtx->nb_streams; i++) {
    AVStream* stream = fmtCtx->streams[i];
    if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
      const AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
      videoStreamIndex = i;
      vcodecCtx = avcodec_alloc_context3(codec);
      avcodec_parameters_to_context(vcodecCtx, fmtCtx->streams[i]->codecpar);
      avcodec_open2(vcodecCtx, codec, NULL);
    }
  }

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

void StrecthBits(HWND hWnd, const std::vector<ColorRGB>& bits, int width,
                 int height) {
  HDC hdc = GetDC(hWnd);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      const ColorRGB& pixel = bits[x + y * width];
      SetPixel(hdc, x, y, RGB(pixel.r, pixel.g, pixel.b));
    }
  }
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    hMenu = CreateMenu();
    mSubMenu = CreateMenu();

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)mSubMenu, TEXT("Menu"));
    AppendMenu(mSubMenu, MF_STRING, (UINT_PTR)IDM_MENU_SUB, TEXT("Sub Menu"));

    SetMenu(hWnd, hMenu);
  }
  case WM_COMMAND:
    switch (wParam) {
    case IDM_MENU_SUB:
      wchar_t szPath[MAX_PATH] = {'\0'};
      OPENFILENAME ofn = {sizeof(ofn)}; // common dialog box structure
      ofn.hwndOwner = hWnd;
      ofn.lpstrFilter = L"All Files\0*.*\0";
      ofn.lpstrFile = szPath;
      ofn.nMaxFile = ARRAYSIZE(szPath);

      BOOL fOk = GetOpenFileName(&ofn);
      if (fOk) {
        AVFrame* firstFrame = getFirstFrame("");
        int width = firstFrame->width;
        int height = firstFrame->height;

        std::vector<ColorRGB> pixels(width * height);
        for (int i = 0; i < pixels.size(); i++) {
          uint8_t r = firstFrame->data[0][i];
          uint8_t g = r;
          uint8_t b = r;
          pixels[i] = {r, g, b};
        }

        StrecthBits(hWnd, pixels, width, height);
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
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}
