/*
 * MapViewer.cpp
 *
 *  Created on: 2017Äê9ÔÂ18ÈÕ
 *      Author: Wenzheng Xu
 */

#include "MapViewer.h"
#include <GL/gl.h>
#include "glext.h"

MapViewer::MapViewer(int x, int y, int w, int h, const char *name) :
Fl_Double_Window(x, y, w, h, name) {

	InitializeCriticalSection(&m_csMapSync);
	m_fCenterLat = 0.0;
	m_fCenterLon = 0.0;
	m_nZoomLevel = 1;
	m_nViewerHeight = h;
	m_nViewerWidth = w;
	m_nCenterTileX = 0;
	m_nCenterTileY = 0;
	m_nCenterOffsetX = 0;
	m_nCenterOffsetY = 0;
}

MapViewer::~MapViewer() {
	DeleteCriticalSection(&m_csMapSync);
	// TODO Auto-generated destructor stub
}

void MapViewer::SetCenterPos(double longtitude, double latitude) {
	long tilepX = MapUtil::lon2tilex(longtitude, m_nZoomLevel);
	cout << "tilepX" <<tilepX << endl;
	m_nCenterTileX = tilepX / 256;
	m_nCenterOffsetX = tilepX % 256;
	long tilepY = MapUtil::lat2tiley(latitude, m_nZoomLevel);
	m_nCenterTileY = tilepY / 256;
	m_nCenterOffsetY = tilepY % 256;
	//if(IsNeedReload())ReloadTiles();

}
void MapViewer::SetZoomLevel(unsigned int zoomlevel) {
	m_nZoomLevel = zoomlevel < 1 ? 1 : zoomlevel;
	m_nZoomLevel = zoomlevel > 20 ? 20 : zoomlevel;
	long tilepX = MapUtil::lon2tilex(m_fCenterLon, m_nZoomLevel);
	m_nCenterTileX = tilepX / 256;
	m_nCenterOffsetX = tilepX % 256;
	long tilepY = MapUtil::lat2tiley(m_fCenterLat, m_nZoomLevel);
	m_nCenterTileY = tilepY / 256;
	m_nCenterOffsetY = tilepY % 256;
	//if(IsNeedReload())ReloadTiles();
}

void MapViewer::draw() {
	Fl_Double_Window::draw();

	if(IsNeedReload())ReloadTiles();
	long tileXCount = m_nViewerWidth / 256 + 2;
	long tileYCount = m_nViewerHeight / 256 + 2;
	long nCenterX = m_nViewerWidth/2;
	long nCenterY = m_nViewerHeight/2;
	long tileXStart = m_nCenterTileX - tileXCount / 2;
	long tileYStart = m_nCenterTileY - tileYCount / 2;

	list<MapTile*>::iterator itMT;
	//cout << "Size:" << m_lpMapTiles.size()<<endl;
	for(itMT = m_lpMapTiles.begin();itMT!=m_lpMapTiles.end();itMT++)
	{
		long nTileX = (*itMT)->m_nTileX - m_nCenterTileX;
		long nTileY = (*itMT)->m_nTileY - m_nCenterTileY;
		//cout << "X:" <<(*itMT) -> m_nTileX << " Y:" <<  (*itMT) -> m_nTileY << " Zoom:" << (*itMT)->m_nTileZoom << " IsLoaded" <<(*itMT)->m_bIsLoaded << endl;
		if((*itMT)->m_bIsLoaded == true)
		{
			//cout << "Draw at :" << nTileX * 256 + nCenterX - m_nCenterOffsetX << " " <<nTileY * 256 + nCenterY - m_nCenterOffsetY << endl;
			//cout << "Draw w h:" << (*itMT)->m_Data->w() << " " <<  (*itMT)->m_Data->h()<< endl;
			//cout << "IsFail" << (*itMT)->m_Data->fail()<<endl;
			//(*itMT)->m_Data->draw(nTileX * 256 + nCenterX - m_nCenterOffsetX,nTileY * 256 + nCenterY - m_nCenterOffsetY);
            //cout << "Image D:" << (*itMT)->m_Data->d()<< endl;
            //cout << "Image LD:" << (*itMT)->m_Data->ld()<<endl;
			fl_draw_image((unsigned char *)(*itMT)->m_Data->data()[0],(int)(nTileX * 256 + nCenterX - m_nCenterOffsetX),(int)(nTileY * 256 + nCenterY - m_nCenterOffsetY),256,256);
		}
		else
		{
			fl_color(FL_RED);
			fl_rect(nTileX * 256 + nCenterX - m_nCenterOffsetX,nTileY * 256 + nCenterY - m_nCenterOffsetY,256,256);
		}
	}


//
//
//	glClearColor(100,100,100,0.0);
//	glClear(GL_COLOR_BUFFER_BIT);
//	glViewport(0, 0, w(), h());
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, w(), 0, h(), -1 ,1);
//
//
//	glEnable(GL_TEXTURE_2D);
//
//	  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//
//	  if(!m_texture_init) {
//	    glGenTextures(1, m_textures);
//	    m_texture_init = true;
//	  }
//
//	  glBindTexture(GL_TEXTURE_2D, m_textures[0]);
//		if(!m_is_sameimg)
//	{
//			unsigned char *img_data;
//			unsigned int img_width;
//			unsigned int img_height;
//
//		  img_data = m_back_img.get_img_data();
//		  img_width  = m_back_img.get_img_pix_width();
//		  img_height = m_back_img.get_img_pix_height();
//
//
//		    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
//				 img_width, img_height, 0,
//				 GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV,
//				 (unsigned char *)img_data);
//
//		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//			m_is_sameimg = true;
//		}


	//EnterCriticalSection(&m_csMapSync);
	//LeaveCriticalSection(&m_csMapSync);
}

void MapViewer::close() {
	DeleteCriticalSection(&m_csMapSync);
	list<MapTile*>::iterator itMT;
		for (itMT = m_lpMapTiles.begin(); itMT != m_lpMapTiles.end();itMT++)delete (*itMT);

}

int MapViewer::handle(int ev) {
	static int nStartx = 0;
	static int nStarty = 0;
	static int nStartxOffset = 0;
	static int nStartyOffset = 0;
	static int nZoomCount = 0;

	switch (ev) {
	case (FL_PUSH):
		nStartx = Fl::event_x();
		nStarty = Fl::event_y();
		nStartxOffset = m_nCenterOffsetX;
		nStartyOffset = m_nCenterOffsetY;
		return 1;
		break;

	case (FL_DRAG):
		m_nCenterOffsetX = nStartxOffset - Fl::event_x() + nStartx;
	    m_nCenterOffsetY = nStartyOffset - Fl::event_y() + nStarty;
		redraw();
		flush();
		break;
	case (FL_MOUSEWHEEL):
		cout << Fl::event_dx() << " " << Fl::event_dy() << endl;
	    //if(Fl::event_dy())
		//if (sideLength - Fl::event_dy() * 10 > 0) {
		//	sideLength -= Fl::event_dy() * 10;
		//	MxOffset += Fl::event_dy() * 5;
		//	MyOffset += Fl::event_dy() * 5;
		//}
	    nZoomCount -= Fl::event_dy();
	    if(abs(nZoomCount) >= 2)
	    {
	    	SetZoomLevel(m_nZoomLevel + nZoomCount/abs(nZoomCount));
	    	nZoomCount = 0;

	    }

		redraw();
        flush();
		break;
	case (FL_RELEASE):
        ReCalculateCenterPos();
    	//if(IsNeedReload())ReloadTiles();
		redraw();
		flush();
		break;
	case (FL_CLOSE):
		close();
		break;
	default:
		return (Fl_Window::handle(ev));
	}
	return 0;
}

void MapViewer::resize(int X, int Y, int W, int H) {
	Fl_Double_Window::resize(X, Y, W, H);
	redraw();
}

bool MapViewer::ReloadTiles() {
	long tileXCount = m_nViewerWidth / 256 + 4;
	long tileYCount = m_nViewerHeight / 256 + 4;
	long tileXStart = m_nCenterTileX - tileXCount / 2;
	long tileYStart = m_nCenterTileY - tileYCount / 2;

	int *isLoaded = new int[(tileXCount + 1) * (tileYCount + 1)];
	memset(isLoaded, 0, (tileXCount + 1) * (tileYCount + 1));
	list<MapTile*>::iterator itMT;
	cout << "Reloading......" << endl;
	for (itMT = m_lpMapTiles.begin(); itMT != m_lpMapTiles.end();) {
		if ((*itMT)->m_nTileZoom != m_nZoomLevel || (*itMT)->m_nTileX < tileXStart
				|| (*itMT)->m_nTileX > tileXStart + tileXCount
				|| (*itMT)->m_nTileY < tileYStart
				|| (*itMT)->m_nTileY > tileYStart + tileYCount) {
			delete (*itMT);
			itMT = m_lpMapTiles.erase(itMT);
		} else {
			isLoaded[((*itMT)->m_nTileX - tileXStart) * (tileYCount + 1)
					+ ((*itMT)->m_nTileY - tileYStart)] = 1;
			itMT++;
		}
	}
	for (long i = 0; i <= tileXCount; i++) {
		for (long j = 0; j <= tileYCount; j++) {
			if (isLoaded[i * (tileYCount+1) + j] == 0) {
				MapTile* pTmpTile =new MapTile(m_nZoomLevel, tileXStart + i, tileYStart + j);
				m_lpMapTiles.push_back(pTmpTile);
			}
		}
	}

	delete isLoaded;
	return true;
}
bool MapViewer::IsNeedReload() {
	long tileXCount = m_nViewerWidth / 256 + 4;
	long tileYCount = m_nViewerHeight / 256 + 4;
	//cout << "tileXCount:" << tileXCount <<" tileYCount"<<tileYCount<<endl;
	long tileXStart = m_nCenterTileX - tileXCount / 2;
	long tileYStart = m_nCenterTileY - tileYCount / 2;
	//cout << "tileXStart:" << tileXStart <<" tileYStart"<<tileYStart<<endl;
	int *isLoaded = new int[(tileXCount + 1) * (tileYCount + 1)];
	memset(isLoaded, 0, (tileXCount + 1) * (tileYCount + 1));
	list<MapTile*>::iterator itMT;
	for (itMT = m_lpMapTiles.begin(); itMT != m_lpMapTiles.end(); itMT++) {
		if ((*itMT)->m_nTileZoom == m_nZoomLevel && (*itMT)->m_nTileX >= tileXStart
				&& (*itMT)->m_nTileX <= tileXStart + tileXCount
				&& (*itMT)->m_nTileY >= tileYStart
				&& (*itMT)->m_nTileY <= tileYStart + tileYCount) {
			isLoaded[((*itMT)->m_nTileX - tileXStart) * (tileYCount + 1)
					+ ((*itMT)->m_nTileY - tileYStart)] = 1;
		}
	}

	for (long i = 0; i <= tileXCount; i++) {
		for (long j = 0; j <= tileYCount; j++) {
			//cout << "i:" << i << " j:" << j <<" "<<  isLoaded[j * tileXCount + i] <<endl;
			if (isLoaded[i * (tileYCount+1) + j] == 0) {
				return true;
			}
		}
	}

	return false;

}

void MapViewer::ReCalculateCenterPos()
{
	while(m_nCenterOffsetX >= 256)
	{
		m_nCenterOffsetX -= 256;
		m_nCenterTileX += 1;
	}
	while(m_nCenterOffsetY >= 256)
	{
		m_nCenterOffsetY -= 256;
		m_nCenterTileY += 1;
	}
	while(m_nCenterOffsetX <= -256)
	{
		m_nCenterOffsetX += 256;
		m_nCenterTileX -= 1;
	}
	while(m_nCenterOffsetY <= -256)
	{
		m_nCenterOffsetY += 256;
		m_nCenterTileY -= 1;
	}
	m_fCenterLat = MapUtil::tiley2lat(m_nCenterTileY*256+m_nCenterOffsetY , m_nZoomLevel);
	cout << "m_fCenterLat" << m_fCenterLat;
	m_fCenterLon= MapUtil::tilex2lon(m_nCenterTileX*256+m_nCenterOffsetX , m_nZoomLevel);
	cout << "m_fCenterLon" << m_fCenterLon;

}
