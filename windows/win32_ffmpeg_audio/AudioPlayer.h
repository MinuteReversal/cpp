// AudioPlayer.h

#pragma once
#include <Windows.h>
#include <atlcomcli.h>
#include <mmdeviceapi.h>
#include <Audioclient.h>
#include <audiopolicy.h>

namespace nv {
  class AudioPlayer {
    public:
      AudioPlayer(WORD nChannels_, DWORD nSamlesPerSec_);
      HRESULT Start();
      HRESULT Stop();
      BYTE* GetBuffer(UINT32 wantFrames);
      HRESULT ReleaseBuffer(UINT32 writtenFrames);
      HRESULT WriteFLTP(float* left, float* right, UINT32 sampleCount);
      HRESULT PlaySinWave(int nb_samples);
      HRESULT SetVolume(float v);
      ~AudioPlayer() {}

    private:
      WORD nChannels;
      DWORD nSamplesPerSec;
      int maxSampleCount;

      WAVEFORMATEX* pwfx;
      CComPtr<IMMDeviceEnumerator> pEnumerator;
      CComPtr<IMMDevice> pDevice;
      CComPtr<IAudioClient> pAudioClient;
      CComPtr<IAudioRenderClient> pRenderClient;
      CComPtr<ISimpleAudioVolume> pSimpleAudioVolume;
      DWORD flags = 0;
      HRESULT Init();
  };
} // namespace nv