//#include <pthread.h>
#include <process.h>
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/math.h>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <windows.h>
#include <iostream>
#include "MapViewer.h"
#include "Downloader.h"

HANDLE ghCommandThread;
bool gExit;
UINT WINAPI CommandThread(void* pParam);
int main(int argc, char *argv[]) {

	UINT threadId;
	//Fl::visual(FL_RGB);         // prevents dithering on some systems
	fl_register_images();
	MapViewer *win = new MapViewer(0, 0, 800, 600, "MapViewer");
	win->SetZoomLevel(12);
	win->SetCenterPos(120.2,31.1);
	win->show();
	gExit = false;
	ghCommandThread = (HANDLE) _beginthreadex(NULL, 0, CommandThread, win, 0,&threadId);
	return (Fl::run());
}

UINT WINAPI CommandThread(void* pParam) {
	MapViewer *pMV = reinterpret_cast<MapViewer*>(pParam);
	while (!gExit) {
		cout << "Enter Command:" << endl;
		string sCommand;
		cin >> sCommand;
		if (sCommand == "Exit") {
			gExit = true;
			return 0;
		}
	}
	return 0;
}
