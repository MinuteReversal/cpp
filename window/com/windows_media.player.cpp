/**
 * @file windows_media.player.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-15
 * 
 * @copyright Copyright (c) 2022
 * [docs.microsoft.com](https://docs.microsoft.com/en-us/windows/win32/wmp/using-the-windows-media-player-control-in-a-console-application)
 */
#include "atlbase.h"
#include "atlwin.h"
#include "wmp.h"

int _tmain(int argc, _TCHAR *argv[]) {
  CoInitialize(NULL);

  HRESULT hr = S_OK;
  CComBSTR bstrVersionInfo;     // Contains the version string.
  CComPtr<IWMPPlayer> spPlayer; // Smart pointer to IWMPPlayer interface.

  hr = spPlayer.CoCreateInstance(__uuidof(WindowsMediaPlayer), 0,
                                 CLSCTX_INPROC_SERVER);

  if (SUCCEEDED(hr)) {
    hr = spPlayer->get_versionInfo(&bstrVersionInfo);
  }

  if (SUCCEEDED(hr)) {
    // Show the version in a message box.
    COLE2T pStr(bstrVersionInfo);
    MessageBox(NULL, (LPCSTR)pStr, _T("Windows Media Player Version"), MB_OK);
  }

  // Clean up.
  spPlayer.Release();
  CoUninitialize();

  return 0;
}