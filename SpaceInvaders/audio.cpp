#include <windows.h>

#include "audio.h"
#include <windows.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

using namespace std;

void playGameAudio() {
	mciSendString("open \"song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);
}