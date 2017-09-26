/*
 * MapTile.h
 *
 *  Created on: 2017Äê9ÔÂ18ÈÕ
 *      Author: Wenzheng Xu
 */

#ifndef MAPTILE_H_
#define MAPTILE_H_

#include <FL/Fl_PNG_Image.H>
#include "MapUtil.h"
#include "Downloader.h"

class MapTile {
public:
	MapTile(unsigned int tileZoom,long tileX ,long tileY) ;
	virtual ~MapTile();
	bool ReloadImg();

public:
	long m_nTileX;
	long m_nTileY;
	unsigned int m_nTileZoom;
	Fl_PNG_Image* m_Data;
	bool m_bIsLoaded;
};

#endif /* MAPTILE_H_ */
