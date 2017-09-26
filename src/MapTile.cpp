/*
 * MapTile.cpp
 *
 *  Created on: 2017Äê9ÔÂ18ÈÕ
 *      Author: Wenzheng Xu
 */

#include "MapTile.h"


MapTile::MapTile(unsigned int tileZoom,long tileX ,long tileY) {
	// TODO Auto-generated constructor stub
	m_nTileX = tileX;
	m_nTileY = tileY;
	m_nTileZoom = tileZoom;
	m_Data = new Fl_PNG_Image(MapUtil::tile2path(tileZoom,tileX,tileY).c_str());
	m_bIsLoaded = !(m_Data->fail()==Fl_PNG_Image::ERR_FILE_ACCESS || m_Data->fail()==Fl_PNG_Image::ERR_FORMAT || m_Data->fail()==Fl_PNG_Image::ERR_NO_IMAGE);
	if(!m_bIsLoaded)
		Downloader::instance()->download(MapUtil::tile2url(tileZoom,tileX,tileY).c_str(), MapUtil::tile2folder(tileZoom,tileX,tileY).c_str());
}

MapTile::~MapTile() {
	delete m_Data;
}

bool MapTile::ReloadImg()
{
	delete m_Data;
	m_Data = new Fl_PNG_Image(MapUtil::tile2path(this->m_nTileZoom,this->m_nTileX,this->m_nTileY).c_str());
	m_bIsLoaded = !(m_Data->fail()==Fl_PNG_Image::ERR_FILE_ACCESS || m_Data->fail()==Fl_PNG_Image::ERR_FORMAT || m_Data->fail()==Fl_PNG_Image::ERR_NO_IMAGE);
    return m_bIsLoaded;
}

