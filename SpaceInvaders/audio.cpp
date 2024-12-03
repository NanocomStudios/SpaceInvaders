#include <windows.h>
#include <time.h>
#include "audio.h"
#include <iostream>
#pragma comment(lib, "Winmm.lib")

using namespace std;

LPCWSTR toLPCWSTR(string str) {
	wstring temp = wstring(str.begin(), str.end());
	LPCWSTR wideString = temp.c_str();
	return wideString;
}

//https://stackoverflow.com/questions/22253074/how-to-play-or-open-mp3-or-wav-sound-file-in-c-program
void playGameAudio() {
	//mciSendString("open \"song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	//mciSendString("play mp3 from 0", NULL, 0, NULL);
	//Sleep(1000);
	//mciSendString("stop mp3", NULL, 0, NULL);
}

void playBlasterAudio() {
	mciSendString("open \"blaster.mp3\" type mpegvideo alias blaster", NULL, 0, NULL);
	mciSendString("play blaster from 0 wait", NULL, 0, NULL);
	mciSendString("close blaster", NULL,0,0);
}

void playExplosionAudio() {
	mciSendString("open \"explosion.mp3\" type mpegvideo alias explosion", NULL, 0, NULL);
	mciSendString("play explosion from 0 wait", NULL, 0, NULL);
	mciSendString("close explosion", NULL, 0, 0);
	
}

