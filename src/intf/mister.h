#ifndef MISTER_H
#define MISTER_H

#include "groovymister.h"

int MisterInit();
void MisterFrame();
bool MisterIsReady();
int MisterWaitSync();
void MisterExit();
int MisterReset();

void MisterSwitchres(int nGameWidth, int nGameHeight, float refreshRate);
char *MisterGetBufferBlit();
void MisterBlit(int vCountSync, int margin);

int MisterSetAudio(uint32_t sampleRate, uint16_t channels);
char *MisterGetBufferAudio();
void MisterSendAudio(uint16_t soundSize);

int MisterUseInput(bool bSetup);
void MisterInputPoll();
fpgaJoyInputs MisterInputJoyGet();
fpgaPS2Inputs MisterInputKeyGet();

#endif /* MISTER_H */
