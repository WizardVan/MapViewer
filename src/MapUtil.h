/*
 * MapUtil.h
 *
 *  Created on: 2017Äê9ÔÂ18ÈÕ
 *      Author: Wenzheng Xu
 */

#ifndef MAPUTIL_H_
#define MAPUTIL_H_

#include <math.h>
#include <string>
#include <stdio.h>
#include "MapTile.h"

using namespace std;
#define M_PI 3.1415926535897932384626
//#define WIN32

class MapUtil {
public:
	MapUtil();
	virtual ~MapUtil();
    static long lat2tiley(double lat, unsigned int zoom);
    static long lon2tilex(double lon, unsigned int zoom);
    static double tiley2lat(long tiley,unsigned int zoom);
    static double tilex2lon(long tilex,unsigned int zoom);
    //static string tile2path(MapTile *tile);
    static string tile2path(unsigned int tileZoom , long tileX , long tileY);
    static string tile2folder(unsigned int tileZoom , long tileX , long tileY);
    static string tile2filename(unsigned int tileZoom , long tileX , long tileY);
    static string tile2url(unsigned int tileZoom , long tileX , long tileY);
    static double lat2resolution(double lat,unsigned int tileZoom);
};

#endif /* MAPUTIL_H_ */
