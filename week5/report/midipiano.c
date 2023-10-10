#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")
#pragma pack(push, 1)

#define NKEY        29
#define NINSTRUMENT 128
#define NNOTE       128  
#define NVOLUME     128

typedef struct {
    BYTE byteState;
    BYTE byteNote;
    BYTE byteVelocity;
    BYTE byteNULL;
} MIDIShortMSG_ST;

typedef union {
    DWORD dwMIDIdata;
    MIDIShortMSG_ST stMIDIData;
} MIDIShortMSG;

#pragma pack(pop)

void CALLBACK MidiOutProc(HMIDIOUT hmMidiDevice, UINT umsg, DWORD Instance, DWORD Param1, DWORD Param2) {
}

void MIDIOutputError(MMRESULT mmResult) {
    char szErrMsg[129];
    midiInGetErrorText(mmResult, (char*)szErrMsg, sizeof(szErrMsg));
    MessageBox(0, szErrMsg, "Midi Error!", MB_OK);
}

long MIDIGetDevID(HMIDIOUT hMidiDevice) {
    UINT uDeviceID;
    MMRESULT mmResult = midiOutGetID(hMidiDevice, &uDeviceID);

    if (mmResult != MMSYSERR_NOERROR) {
        MIDIOutputError(mmResult);
        return -1;
    }

    return (long)uDeviceID;
}

void MIDIGetDevCaps(HMIDIOUT hMidiDevice, MIDIOUTCAPS* Caps) {
    long lDeviceID;
    MMRESULT mmResult;
    lDeviceID = MIDIGetDevID(hMidiDevice);
    if (lDeviceID < 0)
        return;

    mmResult = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));

    if (mmResult != MMSYSERR_NOERROR) {
        MIDIOutputError(mmResult);
    }
}

HMIDIOUT MIDIOpen(WORD wMidiNum) {

    WORD wMidiMax = 0;
    MMRESULT mmResult = 0;
    HMIDIOUT hMidiDevice = NULL;

    wMidiMax = midiInGetNumDevs();

    if (wMidiNum >= wMidiMax) wMidiNum = 0;

    mmResult = midiOutOpen(&hMidiDevice, wMidiNum, (DWORD_PTR)(MidiOutProc), (DWORD)NULL, CALLBACK_FUNCTION);

    if (mmResult != MMSYSERR_NOERROR) {
        MIDIOutputError(mmResult);
        return NULL;
    }

    return hMidiDevice;
}

LRESULT MIDIClose(HMIDIOUT hMidiDevice) {
    MMRESULT mmResult;
    mmResult = midiOutClose(hMidiDevice);

    if (mmResult != MMSYSERR_NOERROR) {
        MIDIOutputError(mmResult);
        return FALSE;
    }

    return TRUE;
}

void MIDISendShortMsg(HMIDIOUT hMidiDevice, BYTE byteState, BYTE byteNote, BYTE byteValo) {
    MIDIShortMSG sMsg;

    sMsg.stMIDIData.byteVelocity = byteValo;
    sMsg.stMIDIData.byteNote = byteNote;
    sMsg.stMIDIData.byteState = byteState;
    sMsg.stMIDIData.byteNULL = 0;

    midiOutShortMsg(hMidiDevice, sMsg.dwMIDIdata);
}

void MIDIALLChannelSoundOff(HMIDIOUT hMidiDevice) {
    BYTE channel;

    for (channel = 0; channel < 16; channel++) {
        MIDISendShortMsg(hMidiDevice, (BYTE)(0xB0 + channel), 0x78, 0);
    }
}

void gotoxy(int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(unsigned short text, unsigned short back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}

int main() {
    int loop;
    BYTE key = 0;
    BYTE instrument = 0;
    BYTE volume = 127;
    BYTE octave = 48;
    BYTE velocity = 120;

    HMIDIOUT hMidiDevice;

    BYTE pianoKey[NKEY] = {
        0x5A, 0x53, 0x58, 0x44, 0x43,
        0x56, 0x47, 0x42, 0x48, 0x4E, 0x4A, 0x4D,
        0x51, 0x32, 0x57, 0x33, 0x45,
        0x52, 0x35, 0x54, 0x36, 0x59, 0x37, 0x55,
        0x49, 0x39, 0x4F, 0x30, 0x50
    };

    BYTE pianoKeyOnOff[NKEY] = { 0 };

    char instName[][NINSTRUMENT] = {
    "Acoustic Grand", "Bright Acoustic", "Electric Grand", "Honky-Tonk", "Electric Piano 1", "Electric Piano 2", "Harpsichord", "Clav", "Celesta", "Glockenspiel",
    "Music Box", "Vibraphone", "Marimba", "Xylophone", "Tubular Bells", "Dulcimer", "Drawbar Organ", "Percussive Organ", "Rock Organ", "Church Organ", "Reed Organ", "Accodion",
    "Harmonica", "Tango Accordion" "Acoustic Guitar(nylon)", "Acoustic Guitar(steel)", "Electric Guitar(jazz)", "Electric Guitar(clean)", "..." };

    hMidiDevice = MIDIOpen(0);

    if (hMidiDevice == NULL) {
        return 0;
    }

    printf("\n");
    setColor(16, 15);
    printf("좌우 키를 누르면 악기가 바뀝니다.                                   \n");
    printf("상하 키를 누르면 옥타브가 바뀝니다.                                 \n");
    printf("+ 키를 누르면 볼륨이 오릅니다.                                      \n");
    printf("-키를 누르면 볼륨이 줄어듭니다.                                     \n");
    gotoxy(0, 5);
    printf("                                                                 ");
    gotoxy(1, 5);
    printf("INSTRUMENT : %-24s	OCTAVE : %03d	VOLUME : %03d\n", instName[0], octave, volume);
    //setColor(16, 15);
    puts("┌―┬――┬┬――┬―┬―┬――┬┬――┬┬――┬――┬―┬――┬┬――┬―┬―┬――┬┬――┬┬――┬――┬―┬――┬┬――┬―┐  ");
    puts("│ │  ││  │ │ │  ││  ││  │  │ │  ││  │ │ │  ││  ││  │  │ │  ││  │ │  ");
    puts("│ │  ││  │ │ │  ││  ││  │  │ │  ││  │ │ │  ││  ││  │  │ │  ││  │ │  ");
    puts("│ │S ││D │ │ │G ││H ││J │  │ │2 ││3 │ │ │5 ││6 ││7 │  │ │9 ││0 │ │  ");
    puts("│ │  ││  │ │ │  ││  ││  │  │ │  ││  │ │ │  ││  ││  │  │ │  ││  │ │  ");
    puts("│ └―┬┘└―┬┘ │ └―┬┘└―┬┘└―┬┘  │ └―┬┘└―┬┘ │ └―┬┘└―┬┘└―┬┘  │ └―┬┘└―┬┘ │  ");
    puts("│ Z │ X │C │ V │ B │ N │ M │ Q │ W │E │ R │ T │ Y │ U │ I │ O │P │  ");
    puts("└―――┴―――┴――┴―――┴―――┴―――┴―――┴―――┴―――┴――┴―――┴―――┴―――┴―――┴―――┴―――┴――┘  ");
    puts("ESC 버튼을 누르면 종료됩니다.                                       \n");

    MIDIALLChannelSoundOff(hMidiDevice);

    MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);

    loop = 1;
    while (loop) {
        if (GetKeyState(VK_ESCAPE) < 0)
            loop = 0;
        else if (GetKeyState(VK_RIGHT) < 0) {
            if (instrument < (NINSTRUMENT - 1)) {
                instrument += 1;

                MIDISendShortMsg(hMidiDevice, 0xC0, instrument, 0);
                gotoxy(1, 5);
                printf("INSTRUMENT : %-24s", instName[instrument]);
                Sleep(200);
            }
        }
        else if (GetKeyState(VK_LEFT) < 0) {
            if (instrument != 0)
                instrument -= 1;

            MIDISendShortMsg(hMidiDevice, 0xC0, instrument, 0);
            gotoxy(1, 5);
            printf("INSTRUMENT : %-25s", instName[instrument]);
            Sleep(200);
        }
        else if (GetKeyState(VK_UP) < 0) {
            if (octave < (NNOTE - NKEY))
                octave += 12;

            gotoxy(40, 5);
            printf("OCTAVE : %03d", octave);
            Sleep(200);
        }
        else if (GetKeyState(VK_DOWN) < 0) {
            if (octave != 0)
                octave -= 12;

            gotoxy(40, 5);
            printf("OCTAVE : %03d", octave);
            Sleep(200);
        }
        else if (GetKeyState(VK_OEM_PLUS) < 0) {
            if (volume < (NVOLUME - 1))
                volume += 5;

            MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);
            gotoxy(58, 5);
            printf("VOLUME : %03d", volume);
            Sleep(30);
        }
        else if (GetKeyState(VK_OEM_MINUS) < 0) {
            if (volume != 0)
                volume -= 5;

            MIDISendShortMsg(hMidiDevice, 0xB0, 7, volume);
            gotoxy(58, 5);
            printf("VOLUME : %03d", volume);
            Sleep(30);
        }
        else {
            for (key = 0; key < NKEY; key++) {
                if (GetKeyState(pianoKey[key]) < 0) {
                    if (pianoKeyOnOff[key] == 0) {
                        if (pianoKeyOnOff[key] == 0) {
                            pianoKeyOnOff[key] = 1;
                            MIDISendShortMsg(hMidiDevice, 0x90, (BYTE)(octave + key), velocity);
                        }
                    }
                }
            }
        }
        for (key = 0; key < NKEY; key++) {
            if (!(GetKeyState(pianoKey[key]) < 0)) {
                if (pianoKeyOnOff[key] != 0) {
                    pianoKeyOnOff[key] = 0;
                    MIDISendShortMsg(hMidiDevice, 0x80, (BYTE)(octave + key), velocity);
                }
            }
        }
    }

    for (key = 0; key < NKEY; key++) {
        if (!(GetKeyState(pianoKey[key]) < 0)) {
            if (pianoKeyOnOff[key] != 0) {
                pianoKeyOnOff[key] = 0;
                MIDISendShortMsg(hMidiDevice, 0x80, (BYTE)(octave + key), velocity);
            }
        }
    }

    MIDIALLChannelSoundOff(hMidiDevice);
    MIDIClose(hMidiDevice);

    return 0;
}
