/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-09-22
 *
 * @copyright Copyright (c) 2022
 * https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/using-the-xaml-hosting-api
 * https://github.com/microsoft/Xaml-Islands-Samples/tree/master/Samples/Win32
 * https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/xaml-islands
 */
#include <shobjidl.h>
#include <stdlib.h>
#include <windows.h>
#include <windows.ui.xaml.hosting.desktopwindowxamlsource.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.system.h>
#include <winrt/Windows.ui.xaml.media.h>
#include <winrt/windows.ui.xaml.controls.h>
#include <winrt/windows.ui.xaml.hosting.h>

using namespace winrt;
using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI::Xaml::Controls;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine,
                      _In_ int nCmdShow) {
  winrt::init_apartment(winrt::apartment_type::single_threaded);
  
  // The DesktopWindowXamlSource object creates the Xaml Island
  winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource desktopSource;

  // Get handle to corewindow

  return EXIT_SUCCESS;
}