/*
 *  assistants.h
 *  sank-into
 *
 *  Created by futurestack on 8/15/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef ASSISTANTS_H_
#define ASSISTANTS_H_

#include "fsPoint2i.h"
#include "fsPoint2f.h"
#include <vector>
#include <math.h>

typedef unsigned long long int Ullong;
typedef unsigned int Uint;


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


class fsRan
    {
        public:
        Ullong u;
        Ullong v;
        Ullong w;
        fsRan(Ullong j) : v(4101842887655102017LL), w( 1 )
        {
            u = j ^ v; int64();
            v = u; int64();
            w = v; int64();
        }
        /*
         Ran() : v(4101842887655102017LL), w( 1 ) 
         {
         Ullong j = fsMillis();
         u = j ^ v; int64();
         v = u; int64();
         w = v; int64();
         }
         */
        
        inline Ullong int64() {
            u = u * 2862933555777941757LL + 7046029254386353087LL;
            v ^= v >> 17; v ^= v << 31; v ^= v >> 8;
            w = 4294957665U*(w & 0xffffffff) + (w >> 32);
            Ullong x = u ^ (u << 21 ); x ^= x >> 35; x ^= x << 4;
            return ( x + v) ^ w;
        }
        inline double doub() { return 5.4210108624275221E-20 * int64(); }
        inline Uint int32() { return (Uint)int64(); } 
};


static inline float dist2d( float x1, float y1, float x2, float y2)
{
	return sqrt( (fabs( x1 - x2)) * (fabs( x1 - x2)) + 
				(fabs( y1 - y2)) * (fabs( y1 - y2)) );
}

static inline float dist2d( fsPoint2i p1, fsPoint2i p2)
{
	return sqrt( (fabs( p1.x - p2.x)) * (fabs( p1.x - p2.x)) + 
				(fabs( p1.y - p2.y)) * (fabs( p1.y - p2.y)) );
}

static inline float dist2d( fsPoint2f p1, fsPoint2f p2 )
{
	return sqrt( (fabs( p1.x - p2.x)) * (fabs( p1.x - p2.x)) + 
				(fabs( p1.y - p2.y)) * (fabs( p1.y - p2.y)) );
}


#endif
