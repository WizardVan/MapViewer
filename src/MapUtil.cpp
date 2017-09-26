/*
 * MapUtil.cpp
 *
 *  Created on: 2017Äê9ÔÂ18ÈÕ
 *      Author: Wenzheng Xu
 */

#include "MapUtil.h"


MapUtil::MapUtil() {
	// TODO Auto-generated constructor stub

}

MapUtil::~MapUtil() {
	// TODO Auto-generated destructor stub
}

long MapUtil::lat2tiley(double lat, unsigned int zoom)
{
    double lata = lat*M_PI/180;
    long z = pow(2,zoom) * 256;
    return (long)((1 - log(tan(lata) + 1/cos(lata))/M_PI)/2 * z );
}


long MapUtil::lon2tilex(double lon, unsigned int zoom)
{
	long z = pow(2,zoom)* 256;
	return (long)((lon+180)/360 * z);
}

double MapUtil::tiley2lat(long tiley,unsigned int zoom)
{
	long z = pow(2,zoom)* 256;
	double lat_rad = atan(sinh(M_PI * (1 - 2.0 * tiley / z)));
	return  (double)(lat_rad * 180.0 / M_PI);
}

double MapUtil::tilex2lon(long tilex,unsigned int zoom)
{
	long z = pow(2,zoom)* 256;
	return (double)(tilex * 360.0 / z  - 180.0);
}

//string MapUtil::tile2path(MapTile *tile)
//{
//	char buffer[256];
//	sprintf(buffer,"map\\%d\\%d\\%d\.png",tile->m_nTileZoom,tile->m_nTileX,tile->m_nTileY);
//	return string(buffer);
//    //return string("map\\") + string(tile->m_nTileZoom) + string("\\") + string(tile->m_nTileX) + string("\\") +string(tile->m_nTileY) + string(".png");
//}

string MapUtil::tile2path(unsigned int tileZoom , long tileX , long tileY)
{
	char buffer[256];
	sprintf(buffer,"map\\%d\\%d\\%d\.png",tileZoom,tileX,tileY);
	return string(buffer);
	//return ("map" + "\\" + string(tileZoom) + "\\" + string(tileX) + "\\" +string(tileY) + ".png");
}

string MapUtil::tile2folder(unsigned int tileZoom , long tileX , long tileY)
{
	char buffer[256];
	sprintf(buffer,"map\\%d\\%d\\",tileZoom,tileX);
	return string(buffer);
	//return ("map" + "\\" + string(tileZoom) + "\\" + string(tileX) + "\\" +string(tileY) + ".png");
}

string MapUtil::tile2filename(unsigned int tileZoom , long tileX , long tileY)
{
	char buffer[256];
	sprintf(buffer,"%d\.png",tileY);
	return string(buffer);
	//return ("map" + "\\" + string(tileZoom) + "\\" + string(tileX) + "\\" +string(tileY) + ".png");
}

string MapUtil::tile2url(unsigned int tileZoom , long tileX , long tileY)
{
	char buffer[256];
	sprintf(buffer,"http://a.tile.openstreetmap.org/%d/%d/%d\.png",tileZoom,tileX,tileY);
	return string(buffer);
	//return ("map" + "\\" + string(tileZoom) + "\\" + string(tileX) + "\\" +string(tileY) + ".png");
}


