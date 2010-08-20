/*
 *  fsPoint2f.h
 *  fsGui
 *
 *  Created by futurestack on 2/23/09.
 *  Copyright 2009 st4tic_software. All rights reserved.
 *
 */

#ifndef FS_GEOM_POINT2F_H_
#define	FS_GEOM_POINT2F_H_

class fsPoint2i;

struct fsPoint2f
{
public:
	
	fsPoint2f ();
	fsPoint2f (float x, float y);
	~fsPoint2f();
	
	fsPoint2f(const fsPoint2f& rhs);
	fsPoint2f(const fsPoint2i& rhs);
	
	void swap(fsPoint2f& rhs) throw();
	fsPoint2f& operator -(const fsPoint2f& rhs);
	fsPoint2f& operator -(const float val);
	fsPoint2f& operator +(const fsPoint2f& rhs);	
	fsPoint2f& operator /(const fsPoint2f& rhs);
	fsPoint2f& operator =(const fsPoint2f& rhs);
	fsPoint2f& operator =(const float val);
	fsPoint2f& operator+=(const fsPoint2f& rhs);
	fsPoint2f& operator-=(const fsPoint2f& rhs);
	fsPoint2f& operator-=(const float val);
	fsPoint2f& operator*=(const fsPoint2f& rhs);
	fsPoint2f& operator/=(const fsPoint2f& rhs);
	fsPoint2f& operator/=(const float val);
	fsPoint2f& operator*=(const float val);
	bool operator == (const fsPoint2f& rhs);
	bool operator != (const fsPoint2f& rhs);
	

	
	
	
	float x,y;

	
};
	
#endif
