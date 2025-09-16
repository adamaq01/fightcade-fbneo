// Module for input
#include "burner.h"

#include "mister.h"
#include "inp_keys.h"

static fpgaJoyInputs joystickInput = {0};
static unsigned char bJoystickRead = 0;
static int *JoyPrevAxes = NULL;

static fpgaPS2Inputs keyboardMouseInput = {0};
static unsigned char bKeyboardRead = 0;

int MisterinpInit() {
    int nSize = 2 * 8 * sizeof(int);
    if ((JoyPrevAxes = (int *) malloc(nSize)) == NULL) {
        return 1;
    }
    memset(JoyPrevAxes, 0, nSize);

    if (MisterUseInput(true)) {
        free(JoyPrevAxes);
        JoyPrevAxes = NULL;
        return 1;
    }

    return 0;
}

int MisterinpExit() {
    free(JoyPrevAxes);
    JoyPrevAxes = NULL;

    if (MisterUseInput(false)) {
        return 1;
    }

    return 0;
}

int MisterinpSetCooperativeLevel(bool bExclusive, bool /*bForeGround*/) {
    return 0;
}

int MisterInpNewFrame() {
    MisterInputPoll();
    bJoystickRead = 0;
    bKeyboardRead = 0;
    joystickInput = {};
    keyboardMouseInput = {};

    return 0;
}

// Read one of the joysticks
static int ReadJoystick() {
    if (bJoystickRead) {
        return 0;
    }

    joystickInput = MisterInputJoyGet();

    // All joysticks have been Read this frame
    bJoystickRead = 1;

    return 0;
}

// Read the keyboard and mouse
static int ReadKeyboardMouse() {
    if (bKeyboardRead) {
        return 0;
    }

    keyboardMouseInput = MisterInputKeyGet();

    // The keyboard has been successfully Read this frame
    bKeyboardRead = 1;

    return 0;
}

// Check a subcode (the 40xx bit in 4001, 4102 etc) for a joystick input code
static int JoystickState(int i, int nSubCode) {
    if (i < 0 || i >= 2) {
        return 0;
    }

    if (ReadJoystick() != 0) {
        return 0;
    }

    if (nSubCode < 0x10) {                                        // Joystick directions
        const char DEADZONE = 0x40;

        switch (nSubCode) {
            case 0x00:
                return (i == 0 ? joystickInput.joy1LXAnalog : joystickInput.joy2LXAnalog) < -DEADZONE; // 0
            case 0x01:
                return (i == 0 ? joystickInput.joy1LXAnalog : joystickInput.joy2LXAnalog) > DEADZONE;
            case 0x02:
                return (i == 0 ? joystickInput.joy1LYAnalog : joystickInput.joy2LYAnalog) < -DEADZONE; // 1
            case 0x03:
                return (i == 0 ? joystickInput.joy1LYAnalog : joystickInput.joy2LYAnalog) > DEADZONE;
            case 0x06:
                return (i == 0 ? joystickInput.joy1RXAnalog : joystickInput.joy2RXAnalog) < -DEADZONE; // 3
            case 0x07:
                return (i == 0 ? joystickInput.joy1RXAnalog : joystickInput.joy2RXAnalog) > DEADZONE;
            case 0x08:
                return (i == 0 ? joystickInput.joy1RYAnalog : joystickInput.joy2RYAnalog) < -DEADZONE; // 4
            case 0x09:
                return (i == 0 ? joystickInput.joy1RYAnalog : joystickInput.joy2RYAnalog) > DEADZONE;
            default:
                return 0;
        }
    }

    uint16_t buttons = (i == 0 ? joystickInput.joy1 : joystickInput.joy2);

    if (nSubCode < 0x20) {                                        // POV hat controls
        switch (nSubCode & 3) {
            case 0:                                                // Left
                return buttons & GM_JOY_LEFT;
            case 1:                                                // Right
                return buttons & GM_JOY_RIGHT;
            case 2:                                                // Up
                return buttons & GM_JOY_UP;
            case 3:                                                // Down
                return buttons & GM_JOY_DOWN;
        }

        return 0;
    }

    if (nSubCode < 0x80) {                                        // Undefined
        return 0;
    }

    if (nSubCode < 0x80 + 10) {    // Joystick buttons
        int button = nSubCode & 0x7F;
        return buttons & (1 << (button + 4));
    }

    return 0;
}

// Check a subcode (the 80xx bit in 8001, 8102 etc) for a mouse input code
static int CheckMouseState(unsigned int nSubCode) {
    switch (nSubCode & 0x7F) {
        case 0:
            // First bit
            return keyboardMouseInput.ps2Mouse & 0x1; // Left button
        case 1:
            // Second bit
            return keyboardMouseInput.ps2Mouse & 0x2; // Right button
        case 2:
            // Third bit
            return keyboardMouseInput.ps2Mouse & 0x4; // Middle button
    }

    return 0;
}

int fbk_to_ps2(int fbk_code);

// Get the state (pressed = 1, not pressed = 0) of a particular input code
int MisterInpState(int nCode) {
    if (nCode < 0) {
        return 0;
    }

    if (nCode < 0x100) {
        if (nCode >> 8) { // System Mouse
            return 0;
        }
        if (ReadKeyboardMouse() != 0) {
            return 0;
        }
        int ps2code = fbk_to_ps2(nCode);
        return (keyboardMouseInput.ps2Keys[ps2code / 8] & (1 << (ps2code % 8))) ? 1 : 0;
    }

    if (nCode < 0x4000) {
        return 0;
    }

    if (nCode < 0x8000) {
        // Codes 4000-8000 = Joysticks
        int nJoyNumber = (nCode - 0x4000) >> 8;
        return JoystickState(nJoyNumber, nCode & 0xFF);
    }

    if (nCode < 0xC000) {
        // Codes 8000-C000 = Mouse
        if ((nCode - 0x8000) >> 8) { // System Mouse
            return 0;
        }
        if (ReadKeyboardMouse() != 0) {
            return 0;
        }
        return CheckMouseState(nCode & 0xFF);
    }

    return 0;
}

// Read one joystick axis
int MisterinpJoyAxis(int i, int nAxis) {
    if (i < 0 || i >= 2) {
        return 0;
    }

    if (ReadJoystick() != 0) {
        return 0;
    }

    switch (nAxis) {
        case 0:
            return (i == 0 ? joystickInput.joy1LXAnalog : joystickInput.joy2LXAnalog);
        case 1:
            return (i == 0 ? joystickInput.joy1LYAnalog : joystickInput.joy2LYAnalog);
        case 3:
            return (i == 0 ? joystickInput.joy1RXAnalog : joystickInput.joy2RXAnalog);
        case 4:
            return (i == 0 ? joystickInput.joy1RYAnalog : joystickInput.joy2RYAnalog);
        default:
            return 0;
    }
}

// Read one mouse axis
int MisterinpMouseAxis(int i, int nAxis) {
    if (i < 0 || i >= 1) {
        return 0;
    }

    switch (nAxis) {
        case 0:
            return keyboardMouseInput.ps2MouseX * (keyboardMouseInput.ps2Mouse & 0x10 ? -1 : 1);
        case 1:
            return keyboardMouseInput.ps2MouseY * (keyboardMouseInput.ps2Mouse & 0x20 ? -1 : 1);
        default:
            return 0;
    }
}

// This function finds which key is pressed, and returns its code
int MisterinpFind(bool CreateBaseline) {
    int nRetVal = -1;

    // check if any keyboard keys are pressed
    if (ReadKeyboardMouse() == 0) {
        for (int i = 0; i < 0x100; i++) {
            int ps2code = fbk_to_ps2(i);
            if (keyboardMouseInput.ps2Keys[ps2code / 8] & (1 << (ps2code % 8))) {
                nRetVal = i;
                goto End;
            }
        }
    }

    // Now check all the connected joysticks
    for (int i = 0; i < 2; i++) {
        int j;
        if (ReadJoystick() != 0) {
            continue;
        }

        for (j = 0; j < 0x10; j++) {                        // Axes
            int nDelta = JoyPrevAxes[(i << 3) + (j >> 1)] - MisterinpJoyAxis(i, (j >> 1));
            if (nDelta < -0x40 || nDelta > 0x40) {
                if (JoystickState(i, j)) {
                    nRetVal = 0x4000 | (i << 8) | j;
                    goto End;
                }
            }
        }

        for (j = 0x10; j < 0x20; j++) {                        // POV hats
            if (JoystickState(i, j)) {
                nRetVal = 0x4000 | (i << 8) | j;
                goto End;
            }
        }

        for (j = 0x80; j < 0x80 + 10; j++) {
            if (JoystickState(i, j)) {
                nRetVal = 0x4000 | (i << 8) | j;
                goto End;
            }
        }
    }

    if (ReadKeyboardMouse() == 0) {
        int nDeltaX, nDeltaY;

        for (unsigned int j = 0x80; j < 0x80 + 0x80; j++) {
            if (CheckMouseState(j)) {
                nRetVal = 0x8000 | j;
                goto End;
            }
        }

        nDeltaX = MisterinpMouseAxis(0, 0);
        nDeltaY = MisterinpMouseAxis(0, 1);
        if (abs(nDeltaX) < abs(nDeltaY)) {
            if (nDeltaY != 0) {
                nRetVal = 0x8000 | 1;
                goto End;
            }
        } else {
            if (nDeltaX != 0) {
                nRetVal = 0x8000 | 0;
                goto End;
            }
        }
    }

    End:

    if (CreateBaseline) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 8; j++) {
                JoyPrevAxes[(i << 3) + j] = MisterinpJoyAxis(i, j);
            }
        }
    }

    return nRetVal;
}

int MisterinpGetControlName(int nCode, TCHAR *pszDeviceName, TCHAR *pszControlName) {
    if (pszDeviceName) {
        pszDeviceName[0] = _T('\0');
    }
    if (pszControlName) {
        pszControlName[0] = _T('\0');
    }

    switch (nCode & 0xC000) {
        case 0x0000: {
            int i = (nCode >> 8) & 0x3F;

            if (i >= 1) {
                return 0;
            }

            _tcscpy(pszDeviceName, _T("Mister keyboard"));

            break;
        }
        case 0x4000: {
            int i = (nCode >> 8) & 0x3F;

            if (i >= 2) {
                return 0;
            }
            _stprintf(pszDeviceName, _T("Mister joystick %d"), i);

            break;
        }
        case 0x8000: {
            int i = (nCode >> 8) & 0x3F;

            if (i >= 1) {
                return 0;
            }
            _tcscpy(pszDeviceName, _T("Mister mouse"));

            break;
        }
    }

    return 0;
}

struct InputInOut InputInOutMister = {MisterinpInit, MisterinpExit, MisterinpSetCooperativeLevel, MisterInpNewFrame,
                                      MisterInpState, MisterinpJoyAxis, MisterinpMouseAxis, MisterinpFind,
                                      MisterinpGetControlName, NULL, _T("Mister input")};

int fbk_to_ps2(int fbk_code) {
    switch (fbk_code) {
        case FBK_ESCAPE:
            return 0x76; // E
        case FBK_1:
            return 0x16; // 1
        case FBK_2:
            return 0x1E; // 2
        case FBK_3:
            return 0x26; // 3
        case FBK_4:
            return 0x25; // 4
        case FBK_5:
            return 0x2E; // 5
        case FBK_6:
            return 0x36; // 6
        case FBK_7:
            return 0x3D; // 7
        case FBK_8:
            return 0x3E; // 8
        case FBK_9:
            return 0x46; // 9
        case FBK_0:
            return 0x45; // 0
        case FBK_MINUS:
            return 0x4E; // -d
        case FBK_EQUALS:
            return 0x55; // =
        case FBK_Q:
            return 0x15; // Q
        case FBK_W:
            return 0x1D; // W
        case FBK_E:
            return 0x24; // E
        case FBK_R:
            return 0x2D; // R
        case FBK_T:
            return 0x2C; // T
        case FBK_Y:
            return 0x35; // Y
        case FBK_U:
            return 0x3C; // U
        case FBK_I:
            return 0x44; // I
        case FBK_O:
            return 0x4D; // O
        case FBK_P:
            return 0x54; // P
        case FBK_LBRACKET:
            return 0x5B; // [
        case FBK_RBRACKET:
            return 0x5D; // ]
        case FBK_RETURN:
            return 0x5A; // Enter
        case FBK_LCONTROL:
            return 0x14; // Left Ctrl
        case FBK_A:
            return 0x1C; // A
        case FBK_S:
            return 0x1B; // S
        case FBK_D:
            return 0x23; // D
        case FBK_F:
            return 0x2B; // F
        case FBK_G:
            return 0x34; // G
        case FBK_H:
            return 0x33; // H
        case FBK_J:
            return 0x3B; // J
        case FBK_K:
            return 0x42; // K
        case FBK_L:
            return 0x4B; // L
        case FBK_SEMICOLON:
            return 0x4C; // ;
        case FBK_APOSTROPHE:
            return 0x52; // '
        case FBK_GRAVE:
            return 0x0E; // ` (accent
        case FBK_LSHIFT:
            return 0x12; // Left Shift
        case FBK_BACKSLASH:
            return 0x5D; // \ (
        case FBK_Z:
            return 0x1A; // Z
        case FBK_X:
            return 0x22; // X
        case FBK_C:
            return 0x21; // C
        case FBK_V:
            return 0x2A; // V
        case FBK_B:
            return 0x30; // B
        case FBK_N:
            return 0x31; // N
        case FBK_M:
            return 0x3A; // M
        case FBK_COMMA:
            return 0x41; // ,
        case FBK_PERIOD:
            return 0x49; // .
        case FBK_SLASH:
            return 0x4A; // /
        case FBK_RSHIFT:
            return 0x59; // Right Shift
        case FBK_MULTIPLY:
            return 0x7C; // * on
        case FBK_LALT:
            return 0x11; // Left Alt
        case FBK_SPACE:
            return 0x29; // Space
        case FBK_CAPITAL:
            return 0x58; // Caps Lock
        case FBK_F1:
            return 0x05; // F1
        case FBK_F2:
            return 0x06; // F2
        case FBK_F3:
            return 0x04; // F3
        case FBK_F4:
            return 0x0C; // F4
        case FBK_F5:
            return 0x03; // F5
        case FBK_F6:
            return 0x0B; // F6
        case FBK_F7:
            return 0x83; // F7
        case FBK_F8:
            return 0x0A; // F8
        case FBK_F9:
            return 0x01; // F9
        case FBK_F10:
            return 0x09; // F10
        case FBK_NUMLOCK:
            return 0x77; // Num Lock
        case FBK_SCROLL:
            return 0x7E; // Scroll Lock
        case FBK_NUMPAD7:
            return 0x70; // Numpad
        case FBK_NUMPAD8:
            return 0x69; // Numpad 8
        case FBK_NUMPAD9:
            return 0x72; // Numpad
        case FBK_SUBTRACT:
            return 0x7B; // Numpad -
        case FBK_NUMPAD4:
            return 0x6B; // Nump
        case FBK_NUMPAD5:
            return 0x73; // Numpad 5
        case FBK_NUMPAD6:
            return 0x74; // Numpad
        case FBK_ADD:
            return 0x79; // Numpad +
        case FBK_NUMPAD1:
            return 0x69; // Numpad
        case FBK_NUMPAD2:
            return 0x72; // Numpad
        case FBK_NUMPAD3:
            return 0x7A; // Nump
        case FBK_NUMPAD0:
            return 0x7D; // Numpad 0
        case FBK_DECIMAL:
            return 0x71; // Numpad .
        case FBK_OEM_102:
            return 0x5D; // <
        case FBK_F11:
            return 0x78; // F11
        case FBK_F12:
            return 0x07; // F12
        case FBK_F13:
            return 0x64; // F13 (NE
        case FBK_F14:
            return 0x65; // F14 (NEC PC98)
        case FBK_F15:
            return 0x66; // F15 (NE
        case FBK_KANA:
            return 0x70; // (Japanese keyboard)
        case FBK_ABNT_C1:
            return 0x73; // / ?
        case FBK_CONVERT:
            return 0x79; // (Japanese keyboard)
        case FBK_NOCONVERT:
            return 0x7B; // (
        case FBK_YEN:
            return 0x7D; // (Japanese keyboard)
        case FBK_ABNT_C2:
            return 0x7E; // N
        case FBK_NUMPADEQUALS:
            return 0x8D; // = on numeric keypad (NEC PC98)
        case FBK_PREVTRACK:
            return 0x90; // Previous Track (
        case FBK_AT:
            return 0x91; // (NEC PC98)
        case FBK_COLON:
            return 0x92; // (NEC PC
        case FBK_UNDERLINE:
            return 0x93; // (NEC PC98)
        case FBK_KANJI:
            return 0x94; // (Japanese keyboard
        case FBK_STOP:
            return 0x95; // (NEC PC98
        case FBK_AX:
            return 0x96; // (Japan AX)
        case FBK_UNLABELED:
            return 0x97; // (J
        case FBK_NEXTTRACK:
            return 0x99; // Next Track
        case FBK_NUMPADENTER:
            return 0x9C; // Enter on
        case FBK_RCONTROL:
            return 0x9D; // Right Ctrl
        case FBK_MUTE:
            return 0xA0; // Mute
        case FBK_CALCULATOR:
            return 0xA1; // Calculator
        case FBK_PLAYPAUSE:
            return 0xA2; // Play /
        case FBK_MEDIASTOP:
            return 0xA4; // Media Stop
        case FBK_VOLUMEDOWN:
            return 0xAE; // Volume -
        case FBK_VOLUMEUP:
            return 0xB0; // Volume +
        case FBK_WEBHOME:
            return 0xB2; // Web home
        case FBK_NUMPADCOMMA:
            return 0xB3; // ,
        case FBK_DIVIDE:
            return 0xB5; // / on numeric keypad
        case FBK_SYSRQ:
            return 0xB7; // SysRq
        case FBK_RALT:
            return 0xB8; // Right Alt
        case FBK_PAUSE:
            return 0xC5; // Pause
        case FBK_HOME:
            return 0xC7; // Home on arrow keypad
        case FBK_UPARROW:
            return 0xC8; // UpArrow
        case FBK_PRIOR:
            return 0xC9; // PgUp on arrow keypad
        case FBK_LEFTARROW:
            return 0xCB; // LeftArrow on
        case FBK_RIGHTARROW:
            return 0xCD; // RightArrow on arrow keypad
        case FBK_END:
            return 0xCF; // End on arrow keypad
        case FBK_DOWNARROW:
            return 0xD0; // DownArrow
        case FBK_NEXT:
            return 0xD1; // PgDn on arrow keypad
        case FBK_INSERT:
            return 0xD2; // Insert on arrow keypad
        case FBK_DELETE:
            return 0xD3; // Delete on arrow keypad
        case FBK_LWIN:
            return 0xDB; // Left Windows key
        case FBK_RWIN:
            return 0xDC; // Right Windows key
        case FBK_APPS:
            return 0xDD; // AppMenu key
        case FBK_POWER:
            return 0xDE; // System Power
        case FBK_SLEEP:
            return 0xDF; // System Sleep
        case FBK_WAKE:
            return 0xE3; // System Wake
        case FBK_WEBSEARCH:
            return 0xE5; // Web Search
        case FBK_WEBFAVORITES:
            return 0xE6; // Web
        case FBK_WEBREFRESH:
            return 0xE7; // Web Refresh
        case FBK_WEBSTOP:
            return 0xE8; // Web Stop
        case FBK_WEBFORWARD:
            return 0xE9; // Web Forward
        case FBK_WEBBACK:
            return 0xEA; // Web Back
        case FBK_MYCOMPUTER:
            return 0xEB; // My Computer
        case FBK_MAIL:
            return 0xEC; // Mail
        case FBK_MEDIASELECT:
            return 0xED; // Media Select
        default:
            return -1; // Unknown key
    }
}
