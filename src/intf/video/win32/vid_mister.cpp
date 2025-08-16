#include "groovymister.h"
#include "burner.h"
#include "vid_softfx.h"
#include "display.h"
#include "modeline.h"
#include "switchres.h"

static GroovyMister *mister;
static switchres_manager *switchres;

// Windows includes
static FILE* file = nullptr;
void MisterLog(char *message, ...) {
    // Use Windows API to open a file for logging
    if (file == nullptr) {
        file = fopen("mister_log.txt", "w");
        if (file == nullptr) {
            MessageBox(NULL, _T("Failed to open log file"), _T("Error"), MB_OK | MB_ICONERROR);
            return;
        }
    }

    va_list args;
    va_start(args, message);
    if (file) {
        vfprintf(file, message, args);
        fprintf(file, "\n");
        fflush(file);
    }
    va_end(args);
}

INT32 nGameWidth;
INT32 nGameHeight;

INT32 nGameImageWidth;
INT32 nGameImageHeight;

static int misterExit();

static int misterTextureInit()
{
    nVidImageWidth = nGameWidth;
    nVidImageHeight = nGameHeight;

    nGameImageWidth = nVidImageWidth;
    nGameImageHeight = nVidImageHeight;

    //nVidImageDepth = nVidScrnDepth;
    nVidImageDepth = 16;

    nVidImageBPP = (nVidImageDepth + 7) >> 3;
    nBurnBpp = nVidImageBPP;	// Set Burn library Bytes per pixel

    // Use our callback to get colors:
    SetBurnHighCol(nVidImageDepth);

    // Make the normal memory buffer
    if (VidSAllocVidImage()) {
        misterExit();
        return 1;
    }

    return 0;
}

static int misterInit()
{
    // TODO: Remove window and allow console only?
    if (hScrnWnd == NULL) {
        return 1;
    }
    hVidWnd = hScrnWnd;

    MisterLog("Initializing Mister video output...");
    mister = new GroovyMister();
    MisterLog("GroovyMister instance created");

    switchres = new switchres_manager;
    display_manager* df = switchres->display_factory();
    df->set_monitor("arcade_15");
    df->set_doublescan(false);
    df->set_screen("dummy");
    display_manager *display = switchres->add_display();

    int rgbMode = 2;
    // Never initialized at this point
    if (nVidImageDepth == 32) {
        rgbMode = 1;
    }
    else if (nVidImageDepth == 16) {
        rgbMode = 2;
    }

    MisterLog("Initializing Mister with RGB mode: %d", rgbMode);
    int ret = mister->CmdInit("192.168.1.21", 32100, 0, 0, 0, 0, rgbMode);
    if (!ret) {
        FBAPopupAddText(PUF_TEXT_DEFAULT, _T("Mister init failed"));
        FBAPopupDisplay(PUF_TYPE_ERROR);

        return 1;
    }
    MisterLog("Mister initialized successfully");

    nGameWidth = 640;
    nGameHeight = 480;
    if (bDrvOkay) {
        // Get the game screen size
        BurnDrvGetVisibleSize(&nGameWidth, &nGameHeight);
    }
    else {
        return 0;
    }

    if (misterTextureInit()) {
        return 1;
    }

    modeline *modeline = display->get_mode(nGameWidth, nGameHeight, 60, 0);
    if (modeline == NULL) {
        MisterLog("Failed to get modeline for game resolution %dx%d", nGameWidth, nGameHeight);
        return 1;
    }

    MisterLog("Game width: %d, Game height: %d", nGameWidth, nGameHeight);
    mister->CmdSwitchres(((double) modeline->pclock) / 1000000.0, modeline->hactive, modeline->hbegin, modeline->hend, modeline->htotal, modeline->vactive, modeline->vbegin, modeline->vend, modeline->vtotal, modeline->interlace ? 1 : 0);
    MisterLog("Mister switchres called with width: %d, height: %d", nGameWidth, nGameHeight);

    MisterLog("Le pointeur la: %p", mister->pBufferBlit);

    return 0;
}

static int misterExit()
{
    MisterLog("Exiting Mister video output...");

    VidSFreeVidImage();

    if (mister) {
        mister->CmdClose();
        mister = nullptr;
    }

    return 0;
}

static INT32 misterFrameCount = 0;

// Run one frame and render the screen
static int misterFrame(bool bRedraw)	// bRedraw = 0
{
    if (pVidImage == NULL) {
        return 1;
    }

    if (bDrvOkay) {
        if (bRedraw) {				// Redraw current frame
            if (BurnDrvRedraw()) {
                BurnDrvFrame();		// No redraw function provided, advance one frame
                misterFrameCount++;
            }
        }
        else {
            BurnDrvFrame();			// Run one frame and draw the screen
            misterFrameCount++;
        }

        if ((BurnDrvGetFlags() & BDF_16BIT_ONLY) && pVidTransCallback)
            pVidTransCallback();
    }

    return 0;
}

// Paint the BlitFX surface onto the primary surface
static int misterPaint(int bValidate)
{
    MisterLog("Painting Mister video output...");
    if (!bDrvOkay) {
        return 0;
    }

    unsigned char* ps = pVidImage + nVidImageLeft * nVidImageBPP;
    int s = nVidImageWidth * nVidImageBPP;

    MisterLog("Native: %d Left: %d BPP: %d W: %d H: %d", nVidImageDepth, nVidImageLeft, nVidImageBPP, nVidImageWidth, nVidImageHeight);
    if (mister) {
        memcpy(mister->pBufferBlit, pVidImage, nVidImageWidth * nVidImageHeight * nVidImageBPP);
        if (kNetLua) {
            FBA_LuaGui((unsigned char *) mister->pBufferBlit, nVidImageWidth, nVidImageHeight, nVidImageBPP, s);
        }
        mister->CmdBlit(misterFrameCount, 0, 0);
    }

    return 0;
}

static int misterScale(RECT* rect, int width, int height)
{
    MisterLog("Scaling Mister video output...");
    // mister.CmdSwitchres(0, width, 0, 0, 0, height, 0, 0, 0, 0);

    return 0;
}

static int misterGetSettings(InterfaceInfo* pInfo)
{
    MisterLog("Getting Mister video output settings...");
    if (bDrvOkay) {
        IntInfoAddStringModule(pInfo, _T("Yes hello Adamaq01"));
    }

    return 0;
}

// The Video Output plugin:
struct VidOut VidOutMister = { misterInit, misterExit, misterFrame, misterPaint, misterScale, misterGetSettings, _T("Mister video output") };
