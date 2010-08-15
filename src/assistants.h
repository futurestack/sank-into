/*
 *  assistants.h
 *  sank-into
 *
 *  Created by hornet on 8/15/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ASSISTANTS_H_
#define ASSISTANTS_H_

#include "fsPoint2i.h"
#include <vector>
static fsPoint2i findCenter( const std::vector<fsPoint2i>& points);
static std::vector<fsPoint2i> normalizePoints( const std::vector<fsPoint2i>& points );

static std::vector<fsPoint2i> normalizePoints( const std::vector<fsPoint2i>& points )
{
	std::vector<fsPoint2i> newPoints;
	fsPoint2i center = findCenter( points );
	for( unsigned int i = 0; i < points.size() ; ++i )
	{
		newPoints.push_back( fsPoint2i( points[i].x - center.x, points[i].y - center.y ) );
	}
	return newPoints;
}


static fsPoint2i findCenter( const std::vector<fsPoint2i>& points)
{
	int avgx , avgy;
	avgx = avgy = 0;
	
	int num = points.size();
	for(  int i = 0; i < num ; ++i )
	{
		avgx += points[i].x;
		avgy += points[i].y;
	}
    
	if( num == 0 ) return fsPoint2i(0,0);
    
	avgx /= num;
	avgy /= num;
    
	return fsPoint2i( avgx, avgy);
	
}

#endif
