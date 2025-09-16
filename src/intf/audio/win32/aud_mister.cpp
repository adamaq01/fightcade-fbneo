#include "burner.h"
#include "aud_dsp.h"
#include <audioclient.h>
#include "mister.h"

int MisterBlankSound()
{
	// Also blank the nAudNextSound buffer
	if (nAudNextSound) {
		AudWriteSilence();
	}

	return 0;
}

static int MisterSoundInit()
{
	if (nAudSampleRate[3] <= 0) {
		return 1;
	}

	// Calculate the Seg Length and Loop length (round to nearest sample)
	nAudSegLen = (nAudSampleRate[3] * 100 + (nAppVirtualFps >> 1)) / nAppVirtualFps;
	nAudAllocSegLen = nAudSegLen << 2; // 16 bit, 2 channels

	MisterSetAudio(nAudSampleRate[3], 2);

	// the next sound frame to put in the stream
	nAudNextSound = (short*)malloc(nAudAllocSegLen);
	if (nAudNextSound == NULL) {
		return 1;
	}

	DspInit();

	return 0;
}

static int MisterSoundExit()
{
	DspExit();

	if (nAudNextSound) {
		free(nAudNextSound);
		nAudNextSound = NULL;
	}

	MisterSetAudio(0, 0);

	return 0;
}

static int MisterSoundCheck()
{
	return 0;
}

static int MisterSoundFrame()
{
	// apply DSP to recent frame
	if (nAudDSPModule[3]) {
		DspDo(nAudNextSound, nAudSegLen);
	}

	if (MisterIsReady()) {
		memcpy(MisterGetBufferAudio(), nAudNextSound, nAudAllocSegLen);
		MisterSendAudio(nAudAllocSegLen);
	}

	return 0;
}

static int MisterSoundPlay()
{
	MisterBlankSound();

	return 0;
}

static int MisterSoundStop()
{
	return 0;
}

static int MisterSoundSetVolume()
{
	/*if (pSoundVolume) {
		pSoundVolume->SetMasterVolume(nAudVolume / 10000.0f, 0);
	}*/

	return 0;
}

static int MisterGetSettings(InterfaceInfo* pInfo)
{
	TCHAR szString[MAX_PATH] = _T("");
	_sntprintf(szString, MAX_PATH, _T("Audio is delayed by approx. %ims"), int(100000.0 / (60.0 / (nAudSegCount[3] - 1.0))));
	IntInfoAddStringModule(pInfo, szString);

	return 0;
}

struct AudOut AudOutMister = { MisterBlankSound, MisterSoundInit, MisterSoundExit, MisterSoundCheck, MisterSoundFrame, MisterSoundPlay, MisterSoundStop, MisterSoundSetVolume, MisterGetSettings, _T("Mister audio output") };
