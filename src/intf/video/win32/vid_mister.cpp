// Direct3D9 video output with Mister support
// rewritten by regret (Motion Blur source from VBA-M)
// Mister support by Adamaq01

#include "burner.h"
#include "vid_softfx.h"
#include "vid_overlay.h"
#include "vid_effect.h"

//#ifdef _MSC_VER
#pragma comment(lib, "d3d9")
#pragma comment(lib, "d3dx9")

#include <InitGuid.h>
#define DIRECT3D_VERSION 0x0900							// Use this Direct3D version
#define D3D_OVERLOADS
#include <d3d9.h>
#include <d3dx9effect.h>

#include "display.h"

#include "mister.h"
#include "display.h"
#include "modeline.h"
#include "switchres.h"

static IDirect3D9Ex* pD3D;							// Direct3D interface
static D3DPRESENT_PARAMETERS d3dpp;
static IDirect3DDevice9Ex* pD3DDevice;
static int nTextureWidth, nTextureHeight;

static ID3DXEffect* pEffect;
static VidEffect* pVidEffect;
static int nDX9HardFX;

static int nGameWidth, nGameHeight;				// Game screen size
static int nGameImageWidth, nGameImageHeight;

static int nRotateGame;
static int nImageWidth, nImageHeight;

static RECT Dest;

static unsigned int nD3DAdapter;

static int GetTextureSize(int nSize)
{
    int nTextureSize = 128;

    while (nTextureSize < nSize) {
        nTextureSize <<= 1;
    }

    return nTextureSize;
}

static UINT dx9GetAdapter(wchar_t* name)
{
    for (int a = pD3D->GetAdapterCount() - 1; a >= 0; a--)
    {
        D3DADAPTER_IDENTIFIER9 identifier;

        pD3D->GetAdapterIdentifier(a, 0, &identifier);
        if (identifier.DeviceName[11] == name[11]) {
            return a;
        }
    }

    return 0;
}

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

struct d3dvertex {
    float x, y, z, rhw;	//screen coords
    float u, v;			//texture coords
};

struct transp_vertex {
    float x, y, z, rhw;
    D3DCOLOR color;
    float u, v;
};

extern char *HardFXFilenames[];

#undef D3DFVF_LVERTEX2
#define D3DFVF_LVERTEX2 (D3DFVF_XYZRHW | D3DFVF_TEX1)

extern IDirect3DTexture9* emuTexture;
static d3dvertex vertex[4];
static transp_vertex transpVertex[4];

extern D3DFORMAT textureFormat;

static int nPreScale = 0;
static int nPreScaleZoom = 0;
static int nPreScaleEffect = 0;

static int misterScale(RECT* rect, int width, int height);

// Select optimal full-screen resolution
static int misterSelectFullscreenMode(VidSDisplayScoreInfo* pScoreInfo)
{
    if (bVidArcaderes) {
        if (!VidSGetArcaderes((int*)&(pScoreInfo->nBestWidth), (int*)&(pScoreInfo->nBestHeight))) {
            return 1;
        }
    }
    else {
        pScoreInfo->nBestWidth = nVidWidth;
        pScoreInfo->nBestHeight = nVidHeight;
    }

    if (!bDrvOkay && (pScoreInfo->nBestWidth < 640 || pScoreInfo->nBestHeight < 480)) {
        return 1;
    }

    return 0;
}

static void misterReleaseTexture()
{
    RELEASE(emuTexture)
}

static int misterExit()
{
    VidSoftFXExit();

    misterReleaseTexture();

    VidOverlayEnd();
    VidSFreeVidImage();

    if (pVidEffect) {
        delete pVidEffect;
        pVidEffect = NULL;
    }

    RELEASE(pEffect)
    RELEASE(pD3DDevice)
    RELEASE(pD3D)

    nRotateGame = 0;

    MisterExit();

    return 0;
}

static int misterResize(int width, int height)
{
    if (!emuTexture) {
        if (FAILED(pD3DDevice->CreateTexture(width, height, 1, D3DUSAGE_DYNAMIC, textureFormat, D3DPOOL_DEFAULT, &emuTexture, NULL))) {
            return 1;
        }
    }

    return 0;
}

static int misterTextureInit()
{
    if (nRotateGame & 1) {
        nVidImageWidth = nGameHeight;
        nVidImageHeight = nGameWidth;
    }
    else {
        nVidImageWidth = nGameWidth;
        nVidImageHeight = nGameHeight;
    }

    nGameImageWidth = nVidImageWidth;
    nGameImageHeight = nVidImageHeight;

    //nVidImageDepth = nVidScrnDepth;
    nVidImageDepth = 16;

    // Determine if we should use a texture format different from the screen format
    if ((bDrvOkay && VidSoftFXCheckDepth(nPreScaleEffect, 32) != 32) || (bDrvOkay && bVidForce16bitDx9Alt)) {
        nVidImageDepth = 16;
    }

    switch (nVidImageDepth) {
        case 32:
            textureFormat = D3DFMT_X8R8G8B8;
            break;
        case 24:
            textureFormat = D3DFMT_R8G8B8;
            break;
        case 16:
            textureFormat = D3DFMT_R5G6B5;
            break;
        case 15:
            textureFormat = D3DFMT_X1R5G5B5;
            break;
    }

    nVidImageBPP = (nVidImageDepth + 7) >> 3;
    nBurnBpp = nVidImageBPP;	// Set Burn library Bytes per pixel

    // Use our callback to get colors:
    SetBurnHighCol(nVidImageDepth);

    // Make the normal memory buffer
    if (VidSAllocVidImage()) {
        misterExit();
        return 1;
    }

    nTextureWidth = GetTextureSize(nGameImageWidth * nPreScaleZoom);
    nTextureHeight = GetTextureSize(nGameImageHeight * nPreScaleZoom);

    if (misterResize(nTextureWidth, nTextureHeight)) {
        return 1;
    }

    return 0;
}

// Vertex format:
//
// 0---------1
// |        /|
// |      /  |
// |    /    |
// |  /      |
// |/        |
// 2---------3
//
// (x,y) screen coords, in pixels
// (u,v) texture coords, betweeen 0.0 (top, left) to 1.0 (bottom, right)
static int misterSetVertex(unsigned int px, unsigned int py, unsigned int pw, unsigned int ph, unsigned int tw, unsigned int th, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
    // configure triangles
    // -0.5f is necessary in order to match texture alignment to display pixels
    float diff = -0.5f;
    if (nRotateGame & 1) {
        if (nRotateGame & 2) {
            vertex[2].x = vertex[3].x = (float)(y)+diff;
            vertex[0].x = vertex[1].x = (float)(y + h) + diff;
            vertex[1].y = vertex[3].y = (float)(x + w) + diff;
            vertex[0].y = vertex[2].y = (float)(x)+diff;
        } else {
            vertex[0].x = vertex[1].x = (float)(y)+diff;
            vertex[2].x = vertex[3].x = (float)(y + h) + diff;
            vertex[1].y = vertex[3].y = (float)(x)+diff;
            vertex[0].y = vertex[2].y = (float)(x + w) + diff;
        }
    }
    else {
        if (nRotateGame & 2) {
            vertex[1].x = vertex[3].x = (float)(y)+diff;
            vertex[0].x = vertex[2].x = (float)(y + h) + diff;
            vertex[2].y = vertex[3].y = (float)(x)+diff;
            vertex[0].y = vertex[1].y = (float)(x + w) + diff;
        } else {
            vertex[0].x = vertex[2].x = (float)(x)+diff;
            vertex[1].x = vertex[3].x = (float)(x + w) + diff;
            vertex[0].y = vertex[1].y = (float)(y)+diff;
            vertex[2].y = vertex[3].y = (float)(y + h) + diff;
        }
    }

    float rw = (float)w / (float)pw * (float)tw;
    float rh = (float)h / (float)ph * (float)th;
    vertex[0].u = vertex[2].u = (float)(px) / rw;
    vertex[1].u = vertex[3].u = (float)(px + w) / rw;
    vertex[0].v = vertex[1].v = (float)(py) / rh;
    vertex[2].v = vertex[3].v = (float)(py + h) / rh;

    // Z-buffer and RHW are unused for 2D blit, set to normal values
    vertex[0].z = vertex[1].z = vertex[2].z = vertex[3].z = 0.0f;
    vertex[0].rhw = vertex[1].rhw = vertex[2].rhw = vertex[3].rhw = 1.0f;

    // configure semi-transparent triangles
    if (bVidMotionBlur) {
        D3DCOLOR semiTrans = D3DCOLOR_ARGB(0x7F, 0xFF, 0xFF, 0xFF);
        transpVertex[0].x = vertex[0].x;
        transpVertex[0].y = vertex[0].y;
        transpVertex[0].z = vertex[0].z;
        transpVertex[0].rhw = vertex[0].rhw;
        transpVertex[0].color = semiTrans;
        transpVertex[0].u = vertex[0].u;
        transpVertex[0].v = vertex[0].v;
        transpVertex[1].x = vertex[1].x;
        transpVertex[1].y = vertex[1].y;
        transpVertex[1].z = vertex[1].z;
        transpVertex[1].rhw = vertex[1].rhw;
        transpVertex[1].color = semiTrans;
        transpVertex[1].u = vertex[1].u;
        transpVertex[1].v = vertex[1].v;
        transpVertex[2].x = vertex[2].x;
        transpVertex[2].y = vertex[2].y;
        transpVertex[2].z = vertex[2].z;
        transpVertex[2].rhw = vertex[2].rhw;
        transpVertex[2].color = semiTrans;
        transpVertex[2].u = vertex[2].u;
        transpVertex[2].v = vertex[2].v;
        transpVertex[3].x = vertex[3].x;
        transpVertex[3].y = vertex[3].y;
        transpVertex[3].z = vertex[3].z;
        transpVertex[3].rhw = vertex[3].rhw;
        transpVertex[3].color = semiTrans;
        transpVertex[3].u = vertex[3].u;
        transpVertex[3].v = vertex[3].v;
    }

    return 0;
}

static void misterDrawOSD()
{
    extern bool bEditActive;
    if (bEditActive) {
        VidOverlaySetChatInput(EditText);
    }

    VidOverlayRender(Dest, nGameWidth, nGameHeight, bVidDX9Scanlines ? (nVidScanIntensity & 0xFF) : 0.f);
}

static int misterSetHardFX(int nHardFX)
{
    // cutre reload
    //static bool reload = true; if (GetAsyncKeyState(VK_CONTROL)) { if (reload) { nDX9HardFX = 0; reload = false; } } else reload = true;

    if (nHardFX == nDX9HardFX)
    {
        return 0;
    }


    nDX9HardFX = nHardFX;

    if (pVidEffect) {
        delete pVidEffect;
        pVidEffect = NULL;
    }

    if (nDX9HardFX == 0)
    {
        return 0;
    }

    // HardFX
    pVidEffect = new VidEffect(pD3DDevice);
    int r = pVidEffect->Load(HardFXFilenames[nHardFX - 1]);

    if (r == 0)
    {
        // common parameters
        pVidEffect->SetParamFloat2("texture_size", nTextureWidth, nTextureHeight);
        pVidEffect->SetParamFloat2("video_size", (nRotateGame ? nGameHeight : nGameWidth) + 0.5f, nRotateGame ? nGameWidth : nGameHeight + 0.5f);
    }

    return r;
}

static int misterInit()
{
    if (hScrnWnd == NULL) {
        return 1;
    }

    hVidWnd = hScrnWnd;

    // Get pointer to Direct3D
    if (bVidDX9LegacyRenderer) {
        pD3D = (IDirect3D9Ex *)Direct3DCreate9(D3D_SDK_VERSION);
    }
    else {
        Direct3DCreate9Ex(D3D_SDK_VERSION, &pD3D);
    }
    if (pD3D == NULL) {
        misterExit();
        return 1;
    }

    nRotateGame = 0;
    nGameWidth = 640;
    nGameHeight = 480;
    if (bDrvOkay) {
        if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) {
            if (nVidRotationAdjust & 1) {
                nRotateGame |= (nVidRotationAdjust & 2);
            }
            else {
                nRotateGame |= 1;
            }
        }

        if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED) {
            nRotateGame ^= 2;
        }

        // Get the game screen size
        BurnDrvGetVisibleSize(&nGameWidth, &nGameHeight);
    }
    else {
        return 0;
    }

    nD3DAdapter = D3DADAPTER_DEFAULT;
    if (nRotateGame & 1 && VerScreen[0]) {
        nD3DAdapter = dx9GetAdapter(VerScreen);
    }
    else {
        if (HorScreen[0]) {
            nD3DAdapter = dx9GetAdapter(HorScreen);
        }
    }

    // check selected adapter
    D3DDISPLAYMODE dm;
    pD3D->GetAdapterDisplayMode(nD3DAdapter, &dm);

    memset(&d3dpp, 0, sizeof(d3dpp));
    if (nVidFullscreen) {
        VidSDisplayScoreInfo ScoreInfo;
        if (misterSelectFullscreenMode(&ScoreInfo)) {
            misterExit();
            return 1;
        }
        d3dpp.BackBufferWidth = ScoreInfo.nBestWidth;
        d3dpp.BackBufferHeight = ScoreInfo.nBestHeight;
        d3dpp.BackBufferFormat = (nVidDepth == 16) ? D3DFMT_R5G6B5 : D3DFMT_X8R8G8B8;
        d3dpp.SwapEffect = D3DSWAPEFFECT_FLIP;
        d3dpp.BackBufferCount = bVidTripleBuffer ? 2 : 1;
        d3dpp.hDeviceWindow = hVidWnd;
        d3dpp.Windowed = bVidDX9WinFullscreen;
        d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
        d3dpp.PresentationInterval = bVidVSync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;
        if (bVidDX9WinFullscreen) {
            d3dpp.SwapEffect = bVidVSync || bVidDX9LegacyRenderer ? D3DSWAPEFFECT_COPY : D3DSWAPEFFECT_FLIPEX;
            MoveWindow(hScrnWnd, 0, 0, d3dpp.BackBufferWidth, d3dpp.BackBufferHeight, TRUE);
        }
    } else {
        RECT rect;
        GetClientRect(hVidWnd, &rect);
        d3dpp.BackBufferWidth = rect.right - rect.left;
        d3dpp.BackBufferHeight = rect.bottom - rect.top;
        d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
        d3dpp.SwapEffect = bVidVSync || bVidDX9LegacyRenderer ? D3DSWAPEFFECT_COPY : D3DSWAPEFFECT_FLIPEX;
        d3dpp.BackBufferCount = 1;
        d3dpp.hDeviceWindow = hVidWnd;
        d3dpp.Windowed = TRUE;
        d3dpp.PresentationInterval = bVidVSync ? D3DPRESENT_INTERVAL_DEFAULT : D3DPRESENT_INTERVAL_IMMEDIATE;
    }

    D3DDISPLAYMODEEX dmex;
    dmex.Format = d3dpp.BackBufferFormat;
    dmex.Width = d3dpp.BackBufferWidth;
    dmex.Height = d3dpp.BackBufferHeight;
    dmex.RefreshRate = d3dpp.FullScreen_RefreshRateInHz;
    dmex.ScanLineOrdering = D3DSCANLINEORDERING_UNKNOWN;
    dmex.Size = sizeof(D3DDISPLAYMODEEX);

    DWORD dwBehaviorFlags = D3DCREATE_FPU_PRESERVE;
    dwBehaviorFlags |= bVidHardwareVertex ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;
#ifdef _DEBUG
    dwBehaviorFlags |= D3DCREATE_DISABLE_DRIVER_MANAGEMENT;
#endif

    HRESULT hRet;
    if (bVidDX9LegacyRenderer) {
        hRet = pD3D->CreateDevice(nD3DAdapter, D3DDEVTYPE_HAL, hVidWnd, dwBehaviorFlags, &d3dpp, (IDirect3DDevice9 **)&pD3DDevice);
    } else {
        hRet = pD3D->CreateDeviceEx(nD3DAdapter, D3DDEVTYPE_HAL, hVidWnd, dwBehaviorFlags, &d3dpp, d3dpp.Windowed ? NULL : &dmex, &pD3DDevice);
    }

    if (FAILED(hRet)) {
        if (nVidFullscreen) {
            FBAPopupAddText(PUF_TEXT_DEFAULT, MAKEINTRESOURCE(IDS_ERR_UI_FULL_PROBLEM), d3dpp.BackBufferWidth, d3dpp.BackBufferHeight, d3dpp.BackBufferFormat, d3dpp.FullScreen_RefreshRateInHz);
            if (bVidArcaderes && (d3dpp.BackBufferWidth != 320 && d3dpp.BackBufferHeight != 240)) {
                FBAPopupAddText(PUF_TEXT_DEFAULT, MAKEINTRESOURCE(IDS_ERR_UI_FULL_CUSTRES));
            }
            FBAPopupDisplay(PUF_TYPE_ERROR);
        }

        misterExit();
        return 1;
    }

    {
        nVidScrnWidth = d3dpp.BackBufferWidth;
        nVidScrnHeight = d3dpp.BackBufferHeight;
        nVidScrnDepth = (dm.Format == D3DFMT_R5G6B5) ? 16 : 32;
    }

    nRotateGame = 0;
    nDX9HardFX = -1;

    if (bDrvOkay) {
        // Get the game screen size
        BurnDrvGetVisibleSize(&nGameWidth, &nGameHeight);

        if (BurnDrvGetFlags() & BDF_ORIENTATION_VERTICAL) {
            if (nVidRotationAdjust & 1) {
                int n = nGameWidth;
                nGameWidth = nGameHeight;
                nGameHeight = n;
                nRotateGame |= (nVidRotationAdjust & 2);
            }
            else {
                nRotateGame |= 1;
            }
        }

        if (BurnDrvGetFlags() & BDF_ORIENTATION_FLIPPED) {
            nRotateGame ^= 2;
        }
    }

    // enable vertex alpha blending
    pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
    pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    // apply vertex alpha values to texture
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

    // for filter
    nPreScale = 3;
    nPreScaleZoom = 2;
    nPreScaleEffect = 0;
    if (bDrvOkay) {
        nPreScaleEffect = nVidBlitterOpt[nVidSelect] & 0xFF;
        nPreScaleZoom = VidSoftFXGetZoom(nPreScaleEffect);
    }

    // Initialize the buffer surfaces
    if (misterTextureInit()) {
        misterExit();
        return 1;
    }

    if (nPreScaleEffect) {
        if (VidSoftFXInit(nPreScaleEffect, 0)) {
            misterExit();
            return 1;
        }
    }

    nImageWidth = 0;
    nImageHeight = 0;

    pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
    pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

    // Overlay
    VidOverlayInit(pD3DDevice);

    // Mister
    if (MisterInit()) {
        FBAPopupAddText(PUF_TEXT_DEFAULT, _T("Mister init failed"));
        FBAPopupDisplay(PUF_TYPE_ERROR);

        return 1;
    }
    MisterSwitchres(nGameWidth, nGameHeight, ((float) nBurnFPS) / 100.0f);

    return 0;
}

static int misterReset()
{
    misterReleaseTexture();

    if (FAILED(pD3DDevice->Reset(&d3dpp))) {
        return 1;
    }

    pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
    pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    // apply vertex alpha values to texture
    pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);

    misterTextureInit();

    nImageWidth = 0;
    nImageHeight = 0;

    MisterSwitchres(nGameWidth, nGameHeight, ((float) nBurnFPS) / 100.0f);

    return 0;
}

static int misterScale(RECT* rect, int width, int height)
{
    if (nVidBlitterOpt[nVidSelect] & 0x0100) {
        return VidSoftFXScale(rect, width, height);
    }
    return VidSScaleImage(rect, width, height, bVidScanRotate);
}

static void VidSCpyImg32(unsigned char* dst, unsigned int dstPitch, unsigned char *src, unsigned int srcPitch, unsigned short width, unsigned short height)
{
    // fast, iterative C version
    // copies an width*height array of visible pixels from src to dst
    // srcPitch and dstPitch are the number of garbage bytes after a scanline
    register unsigned short lineSize = width << 2;

    while (height--) {
        memcpy(dst, src, lineSize);
        src += srcPitch;
        dst += dstPitch;
    }
}

static void VidSCpyImg16(unsigned char* dst, unsigned int dstPitch, unsigned char *src, unsigned int srcPitch, unsigned short width, unsigned short height)
{
    register unsigned short lineSize = width << 1;

    while (height--) {
        memcpy(dst, src, lineSize);
        src += srcPitch;
        dst += dstPitch;
    }
}

// Copy BlitFXsMem to pddsBlitFX
static int misterRender()
{
    GetClientRect(hVidWnd, &Dest);

    if (bVidArcaderes) {
        Dest.left = (Dest.right + Dest.left) / 2;
        Dest.left -= nGameWidth / 2;
        Dest.right = Dest.left + nGameWidth;

        Dest.top = (Dest.top + Dest.bottom) / 2;
        Dest.top -= nGameHeight / 2;
        Dest.bottom = Dest.top + nGameHeight;
    }
    else {
        misterScale(&Dest, nGameWidth, nGameHeight);
    }

    {
        int nNewImageWidth = nRotateGame ? (Dest.bottom - Dest.top) : (Dest.right - Dest.left);
        int nNewImageHeight = nRotateGame ? (Dest.right - Dest.left) : (Dest.bottom - Dest.top);

        if (nImageWidth != nNewImageWidth || nImageHeight != nNewImageHeight) {
            nImageWidth = nNewImageWidth;
            nImageHeight = nNewImageHeight;

            int nWidth = nGameImageWidth;
            int nHeight = nGameImageHeight;

            if (nPreScaleEffect) {
                if (nPreScale & 1) {
                    nWidth *= nPreScaleZoom;
                }
                if (nPreScale & 2) {
                    nHeight *= nPreScaleZoom;
                }
            }

            misterSetVertex(0, 0, nWidth, nHeight, nTextureWidth, nTextureHeight, nRotateGame ? Dest.top : Dest.left, nRotateGame ? Dest.left : Dest.top, nImageWidth, nImageHeight);

            if (pVidEffect && pVidEffect->IsValid())
                pVidEffect->SetParamFloat2("output_size", nImageWidth, nImageHeight);
        }
    }

    {
        // Copy the game image onto a texture for rendering
        D3DLOCKED_RECT d3dlr;
        emuTexture->LockRect(0, &d3dlr, 0, 0);
        if (d3dlr.pBits) {
            int pitch = d3dlr.Pitch;
            unsigned char* pd = (unsigned char*)d3dlr.pBits;

            if (nPreScaleEffect) {
                if (MisterIsReady()) {
                    unsigned char* ps = pVidImage + nVidImageLeft * nVidImageBPP;
                    int s = nVidImageWidth * nVidImageBPP;
                    memcpy(MisterGetBufferBlit(), ps, nVidImageWidth * nVidImageHeight * nVidImageBPP);
                    MisterBlit(0, 0);
                }
                VidFilterApplyEffect(pd, pitch);
            }
            else {
                unsigned char* ps = pVidImage + nVidImageLeft * nVidImageBPP;
                int s = nVidImageWidth * nVidImageBPP;

                switch (nVidImageDepth) {
                    case 32:
                        VidSCpyImg32(pd, pitch, ps, s, nVidImageWidth, nVidImageHeight);
                        break;
                    case 16:
                        VidSCpyImg16(pd, pitch, ps, s, nVidImageWidth, nVidImageHeight);
                        break;
                }
                if (MisterIsReady()) {
                    memcpy(MisterGetBufferBlit(), pVidImage, nVidImageWidth * nVidImageHeight * nVidImageBPP);
                    if (kNetLua) {
                        FBA_LuaGui((unsigned char *) MisterGetBufferBlit(), nVidImageWidth, nVidImageHeight, nVidImageBPP, s);
                    }
                    MisterBlit(0, 0);
                }
            }

            if (kNetLua) {
                FBA_LuaGui(pd, nVidImageWidth, nVidImageHeight, nVidImageBPP, pitch);
            }

            emuTexture->UnlockRect(0);
        }
    }

    pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, bVidDX9Bilinear ? D3DTEXF_LINEAR : D3DTEXF_POINT);
    pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, bVidDX9Bilinear ? D3DTEXF_LINEAR : D3DTEXF_POINT);

    // draw the current frame to the screen
    pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0.0f, 0);

    pD3DDevice->BeginScene();
    {
        pD3DDevice->SetTexture(0, emuTexture);
        pD3DDevice->SetFVF(D3DFVF_LVERTEX2);
        if (pVidEffect && pVidEffect->IsValid()) {
            pVidEffect->Begin();
            pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(d3dvertex));
            pVidEffect->End();
        }
        else {
            pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(d3dvertex));
        }
        misterDrawOSD();
    }
    pD3DDevice->EndScene();

    misterSetHardFX(nVidDX9HardFX);

    MisterWaitSync();

    return 0;
}

// Run one frame and render the screen
static int misterFrame(bool bRedraw)	// bRedraw = 0
{
    if (pVidImage == NULL) {
        return 1;
    }

    HRESULT nCoopLevel = pD3DDevice->TestCooperativeLevel();
    if (nCoopLevel != D3D_OK) {		// We've lost control of the screen
        if (nCoopLevel != D3DERR_DEVICENOTRESET) {
            return 1;
        }

        if (misterReset()) {
            return 1;
        }

        return 1;            // Skip this frame, pBurnDraw pointer not valid (misterReset() -> misterTextureInit() -> VidSAllocVidImage())
    }

    if (bDrvOkay) {
        if (bRedraw) {				// Redraw current frame
            if (BurnDrvRedraw()) {
                BurnDrvFrame();		// No redraw function provided, advance one frame
                MisterFrame();
            }
        }
        else {
            BurnDrvFrame();			// Run one frame and draw the screen
            MisterFrame();
        }

        if ((BurnDrvGetFlags() & BDF_16BIT_ONLY) && pVidTransCallback)
            pVidTransCallback();
    }

    return 0;
}

// Paint the BlitFX surface onto the primary surface
static int misterPaint(int bValidate)
{
    if (!bDrvOkay) {
        return 0;
    }

    if (pD3DDevice->TestCooperativeLevel()) {	// We've lost control of the screen
        return 1;
    }

    misterRender();

    pD3DDevice->Present(NULL, NULL, NULL, NULL);

    return 0;
}

static int misterGetSettings(InterfaceInfo* pInfo)
{
    if (nVidFullscreen) {
        if (bVidTripleBuffer) {
            IntInfoAddStringModule(pInfo, _T("Using a triple buffer"));
        }
        else {
            IntInfoAddStringModule(pInfo, _T("Using a double buffer"));
        }
    }

    if (bDrvOkay) {
        TCHAR szString[MAX_PATH] = _T("");

        _sntprintf(szString, MAX_PATH, _T("Prescaling using %s (%ix zoom)"), VidSoftFXGetEffect(nPreScaleEffect), nPreScaleZoom);
        IntInfoAddStringModule(pInfo, szString);
    }

    if (bVidDX9Bilinear) {
        IntInfoAddStringModule(pInfo, _T("Applying linear filter"));
    }
    else {
        IntInfoAddStringModule(pInfo, _T("Applying point filter"));
    }

    if (bVidMotionBlur) {
        IntInfoAddStringModule(pInfo, _T("Applying motion blur effect"));
    }

    if (bVidDX9Scanlines) {
        IntInfoAddStringModule(pInfo, _T("Drawing scanlines"));
    }

    return 0;
}

// The Video Output plugin:
struct VidOut VidOutMister = { misterInit, misterExit, misterFrame, misterPaint, misterScale, misterGetSettings, _T("DirectX9 Alternate (Mister) video output") };
