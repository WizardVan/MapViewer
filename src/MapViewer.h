/*
 * MapViewer.h
 *
 *  Created on: 2017年9月18日
 *      Author: Wenzheng Xu
 */

#ifndef MAPVIEWER_H_
#define MAPVIEWER_H_


//#include <stdio.h>
#include <list>
#include <iostream>
#include <algorithm>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_GL_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/fl_draw.H>
#include <FL/gl.h>
#include <cstring>
#include "MapUtil.h"
#include <GL/gl.h>
#include "glext.h"

#define UPDATE_RATE 0.1     // update rate in seconds

using namespace std;

class MapViewer: public Fl_Gl_Window {
public:
	MapViewer(int x, int y, int w, int h, const char *name);
	~MapViewer();
	void draw();
	//void PlotPixel(int x, int y, unsigned char r, unsigned char g,unsigned char b);
	//void RenderImage();
	void close();
	void resize(int X, int Y, int W, int H);
	void SetCenterPos(double longtitude , double latitude);
	void SetZoomLevel(unsigned int zoomlevel);
	static void RefreshMap(void *userdata);
	//static void RenderImage_CB(void *userdata);
	//void RenderImage(TSImage* showImage, double stopPoint_x, double stopPoint_y,double range_text, double range);
	//void ClearImage();

	//static void UpdateThread(void* pParam);


private:
	int handle(int ev);
	bool IsNeedReload();
	bool ReloadTiles();
	void ReCalculateCenterPos();
//	bool adjustsize(int width, int height);
	double m_fCenterLat;
	double m_fCenterLon;
	int m_nZoomLevel;
	int m_nViewerHeight;
	int m_nViewerWidth;
	long m_nCenterTileX;
	long m_nCenterTileY;
	int m_nCenterOffsetX;
	int m_nCenterOffsetY;
	int m_nTileSide;
	list<MapTile*> m_lpMapTiles;
	GLuint  m_gluTextures[1];


	/** 同步互斥,临界区保护 */
	CRITICAL_SECTION m_csMapSync;       //!< 互斥操作串口

};


#endif /* MAPVIEWER_H_ */
