/*
 *  fsPoint2i.h
 *  fsGui
 *
 *  Created by futurestack on 2/23/09.
 *  Copyright 2009 st4tic_software. All rights reserved.
 *
 */

#ifndef FS_GEOM_POINT2I_H_
#define	FS_GEOM_POINT2I_H_

//#include "fsPoint2f.h"
class fsPoint2f;

struct fsPoint2i
{
public:
	
	fsPoint2i ();
	fsPoint2i (int x, int y);
	~fsPoint2i();
	
	fsPoint2i(const fsPoint2i& rhs);
	fsPoint2i(const fsPoint2f& rhs);

	
	
	void swap(fsPoint2i& rhs) throw();
	fsPoint2i& operator -(const fsPoint2i& rhs);
	fsPoint2i& operator +(const fsPoint2i& rhs);	
	fsPoint2i& operator /(const fsPoint2i& rhs);
	fsPoint2i& operator =(const fsPoint2i& rhs);
	fsPoint2i& operator+=(const fsPoint2i& rhs);
	fsPoint2i& operator-=(const fsPoint2i& rhs);
	fsPoint2i& operator*=(const fsPoint2i& rhs);
	fsPoint2i& operator/=(const fsPoint2i& rhs);
	fsPoint2i& operator/=(const int val);
	bool operator==(const fsPoint2i& rhs);
	bool operator!=(const fsPoint2i& rhs);
	
	
	int x,y;
	
	
};

#endif
