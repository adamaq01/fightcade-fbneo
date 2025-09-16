#include "mister.h"

#include <cstdint>
#include "switchres.h"
#include "tchar.h"

GroovyMister *pMister = nullptr;
INT32 misterFrameCount = 0;
switchres_manager *switchres = nullptr;

struct change_res {
    int width;
    int height;
    float refreshRate;
};

change_res current_res = {0, 0, 0.0f};
change_res *pSetRes = nullptr;

struct change_audio {
    uint32_t sampleRate;
    uint16_t channels;
};

change_audio current_audio = {0, 0};

bool bInitInput = false;

char misterHost[256] = {0};
TCHAR szMisterHost[MAX_PATH] = _T("");
INT32 nMisterLz4Frames = 0;

HANDLE waitSyncThread = nullptr;
HANDLE waitSyncEvent = nullptr;
HANDLE waitSyncEvent2 = nullptr;

void waitSyncProc(void *param) {
    HANDLE event = (HANDLE) param;
    while (true) {
        WaitForSingleObject(event, INFINITE);
        if (pMister) {
            pMister->WaitSync();
        }
        ResetEvent(event);
        SetEvent(waitSyncEvent2);
    }
}

int MisterInit() {
    if (pMister) {
        return 0; // Already initialized
    }

    if (!switchres) {
        switchres = new switchres_manager;
        switchres->display()->set_monitor("arcade_15");
        switchres->display()->set_doublescan(false);
        switchres->display()->set_screen("dummy");
        switchres->add_display();
    }

    auto *mister = new GroovyMister();

    // Convert TCHAR to char for misterHost
#ifdef _UNICODE
    size_t convertedChars = 0;
    wcstombs_s(&convertedChars, misterHost, szMisterHost, sizeof(misterHost));
#else
    strncpy_s(misterHost, szMisterHost, sizeof(misterHost));
#endif

    // Initialize inputs before CmdInit if requested, if done after it will be ignored
    if (bInitInput) {
        mister->BindInputs(misterHost, 32101);
    }

    int ret = mister->CmdInit(misterHost, 32100, nMisterLz4Frames, current_audio.sampleRate, current_audio.channels, 2,
                              0);
    if (ret) {
        delete mister;
        mister = nullptr;
        delete switchres;
        switchres = nullptr;
        return 1; // Initialization failed
    }

    if (pSetRes) {
        modeline *modeline = switchres->display()->get_mode(pSetRes->width, pSetRes->height,
                                                            pSetRes->refreshRate, 0);
        if (modeline) {
            mister->CmdSwitchres(((double) modeline->pclock) / 1000000.0, modeline->hactive, modeline->hbegin,
                                 modeline->hend, modeline->htotal, modeline->vactive, modeline->vbegin, modeline->vend,
                                 modeline->vtotal, modeline->interlace ? 1 : 0);
        }
    }

    if (!waitSyncThread) {
        waitSyncEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        waitSyncEvent2 = CreateEvent(NULL, TRUE, FALSE, NULL);
        waitSyncThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) waitSyncProc, waitSyncEvent, 0, NULL);
    }

    pSetRes = &current_res;
    pMister = mister;
    misterFrameCount = 0;
    return 0; // Success
}

int MisterReset() {
    if (pMister) {
        MisterExit();
        return MisterInit();
    }

    return 0;
}

void MisterSwitchres(int nGameWidth, int nGameHeight, float refreshRate) {
    change_res res = {nGameWidth, nGameHeight, refreshRate};
    if (current_res.width == res.width && current_res.height == res.height &&
        current_res.refreshRate == res.refreshRate) {
        return;
    }
    current_res = res;

    if (pMister && switchres) {
        modeline *modeline = switchres->display()->get_mode(nGameWidth, nGameHeight, refreshRate, 0);
        if (modeline) {
            pMister->CmdSwitchres(((double) modeline->pclock) / 1000000.0, modeline->hactive, modeline->hbegin,
                                  modeline->hend, modeline->htotal, modeline->vactive, modeline->vbegin, modeline->vend,
                                  modeline->vtotal, modeline->interlace ? 1 : 0);
        }
    }
    pSetRes = &current_res;
}

char *MisterGetBufferBlit() {
    if (pMister) {
        return pMister->getPBufferBlit(0);
    }
    return nullptr;
}

void MisterBlit(int vCountSync, int margin) {
    if (pMister) {
        pMister->CmdBlit(misterFrameCount, 0, vCountSync, margin, 0);
    }
}

int MisterSetAudio(uint32_t sampleRate, uint16_t channels) {
    if (current_audio.sampleRate == sampleRate && current_audio.channels == channels) {
        return 0;
    }
    current_audio = {sampleRate, channels};

    return MisterReset();
}

char *MisterGetBufferAudio() {
    if (pMister) {
        return pMister->getPBufferAudio();
    }
    return nullptr;
}

void MisterSendAudio(uint16_t soundSize) {
    if (pMister) {
        pMister->CmdAudio(soundSize);
    }
}

void MisterExit() {
    if (pMister) {
        pMister->CmdClose();
        delete pMister;
        pMister = nullptr;

        TerminateThread(waitSyncThread, 0);
        WaitForSingleObject(waitSyncThread, INFINITE);
        CloseHandle(waitSyncThread);
        waitSyncThread = nullptr;
        CloseHandle(waitSyncEvent);
        waitSyncEvent = nullptr;
        CloseHandle(waitSyncEvent2);
        waitSyncEvent2 = nullptr;
    }
}

void MisterFrame() {
    misterFrameCount++;
}

bool MisterIsReady() {
    return pMister != nullptr;
}

int MisterWaitSync() {
    if (pMister && waitSyncThread && waitSyncEvent && waitSyncEvent2) {
        SetEvent(waitSyncEvent);
        if (WaitForSingleObject(waitSyncEvent2, 300) != WAIT_OBJECT_0) {
            ResetEvent(waitSyncEvent2);
            ResetEvent(waitSyncEvent);
            return MisterReset();
        }
        ResetEvent(waitSyncEvent2);
    } else {
        MisterExit();
        return MisterInit();
    }

    return 0;
}

int MisterUseInput(bool bSetup) {
    bInitInput = bSetup;
    if (pMister) {
        MisterExit();
        return MisterInit();
    }

    return 0;
}

void MisterInputPoll() {
    if (pMister) {
        pMister->PollInputs();
    }
}

fpgaJoyInputs MisterInputJoyGet() {
    if (pMister) {
        return pMister->joyInputs;
    }
    return {};
}

fpgaPS2Inputs MisterInputKeyGet() {
    if (pMister) {
        return pMister->ps2Inputs;
    }
    return {};
}
