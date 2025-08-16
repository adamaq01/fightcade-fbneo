#include "mister.h"

#include <cstdint>
#include "switchres.h"

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
bool bSetAudio = false;

bool bInitInput = false;

int MisterInit() {
    if (pMister) {
        if (bSetAudio) {
            MisterExit();
            bSetAudio = false; // Reset audio settings
            return MisterInit(); // Reinitialize if audio settings have changed
        }

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
    int ret = mister->CmdInit("192.168.1.21", 32100, 0, current_audio.sampleRate, current_audio.channels, 2, 0);
    if (!ret) {
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

    if (bInitInput) {
        mister->BindInputs("192.168.1.21", 32101);
    }

    pSetRes = &current_res;
    pMister = mister;
    misterFrameCount = 0;
    return 0; // Success
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
    } else {
        pSetRes = &current_res;
    }
}

char *MisterGetBufferBlit() {
    if (pMister) {
        return pMister->pBufferBlit;
    }
    return nullptr;
}

void MisterBlit(int vCountSync, int margin) {
    if (pMister) {
        pMister->CmdBlit(misterFrameCount, vCountSync, margin);
    }
}

void MisterSetAudio(uint32_t sampleRate, uint16_t channels) {
    if (current_audio.sampleRate == sampleRate && current_audio.channels == channels) {
        return;
    }
    current_audio = {sampleRate, channels};

    if (pMister) {
        bSetAudio = true;
    }
}

char *MisterGetBufferAudio() {
    if (pMister) {
        return pMister->pBufferAudio;
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
        bInitInput = false; // Reset input initialization state
    }
}

void MisterFrame() {
    misterFrameCount++;
}

bool MisterIsReady() {
    return pMister != nullptr;
}

void MisterWaitSync() {
    if (pMister) {
        pMister->WaitSync();
    }
}

void MisterInputInit() {
    if (bInitInput) {
        return; // Already initialized
    }
    bInitInput = true;
    if (pMister) {
        pMister->BindInputs("192.168.1.21", 32101);
    }
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
