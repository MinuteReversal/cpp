// https://learn.microsoft.com/en-us/windows/uwp/cpp-and-winrt-apis/get-started
// https://github.com/microsoft/cppwinrt/issues/532
#ifndef _SILENCE_CLANG_COROUTINE_MESSAGE
#define _SILENCE_CLANG_COROUTINE_MESSAGE
#include <winrt/Windows.Foundation.Collections.h>
#endif

#include <iostream>
#include <string>
#include <winrt/Windows.Web.Syndication.h>

#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "kernel32.lib")

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;

int main() {
  winrt::init_apartment();

  Uri rssFeedUri{L"https://blogs.windows.com/feed"};
  SyndicationClient syndicationClient;
  SyndicationFeed syndicationFeed =
      syndicationClient.RetrieveFeedAsync(rssFeedUri).get();
  for (const SyndicationItem syndicationItem : syndicationFeed.Items()) {
    winrt::hstring titleAsHstring = syndicationItem.Title().Text();
    std::wcout << titleAsHstring.c_str() << std::endl;
  }
  return 0;
}