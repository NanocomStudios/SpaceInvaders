#include <windows.h>

#include "audio.h"
#include <windows.h>
#include <iostream>
#pragma comment(lib, "Winmm.lib")

using namespace std;
//https://stackoverflow.com/questions/22253074/how-to-play-or-open-mp3-or-wav-sound-file-in-c-program
void playGameAudio() {
	mciSendString("open \"song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	mciSendString("play mp3", NULL, 0, NULL);
}