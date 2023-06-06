#include <sapi.h>
#include <Shlwapi.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "sapi.lib")
#pragma comment(lib, "Ole32.lib")
#pragma comment(lib,"Shlwapi.lib")

int main()
{
    CoInitialize(NULL);

    // create an instance of the speech synthesis engine
    ISpVoice* pVoice = NULL;
    HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);
    if (FAILED(hr))
    {
        // handle error
        CoUninitialize();
        return 1;
    }

    // create a stream for the output file
    auto filename = "output.wav";
    IStream* pStream = NULL;
    hr = SHCreateStreamOnFile(filename, SPFM_CREATE_ALWAYS, &pStream);
    if (FAILED(hr))
    {
        // handle error
        pVoice->Release();
        CoUninitialize();
        return 1;
    }

    // set the output format of the stream to PCM WAV
    WAVEFORMATEX waveFormat;
    memset(&waveFormat, 0, sizeof(waveFormat));
// write the WAVEFORMATEX structure to the stream
    ULONG bytesWritten = 0;
    waveFormat.wFormatTag = WAVE_FORMAT_PCM;
    waveFormat.nChannels = 1;
    waveFormat.nSamplesPerSec = 16000;
    waveFormat.wBitsPerSample = 16;
    waveFormat.nBlockAlign = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
    waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
    hr = pStream->Write(&waveFormat, sizeof(waveFormat), &bytesWritten);
    if (FAILED(hr))
    {
        // handle error
        pStream->Release();
        pVoice->Release();
        CoUninitialize();
        return 1;
    }

    // set the output of the speech synthesis engine to the stream
    hr = pVoice->SetOutput(pStream, TRUE);
    if (FAILED(hr))
    {
        // handle error
        pStream->Release();
        pVoice->Release();
        CoUninitialize();
        return 1;
    }

    // speak the text
    WCHAR* text = L"Hello, world! This is a test.";
    hr = pVoice->Speak(text, 0, NULL);
    if (FAILED(hr))
    {
        // handle error
    }

    // cleanup
    pStream->Release();
    pVoice->Release();
    CoUninitialize();

    return 0;
}
