/*
 *  fsPoint2i.cpp
 *  fsGui
 *
 *  Created by futurestack on 2/23/09.
 *  Copyright 2009 st4tic_software. All rights reserved.
 *
 */

#include "fsPoint2i.h"
#include "fsPoint2f.h"

#include <algorithm>

fsPoint2i::fsPoint2i()
:
	x(0),
	y(0)
{
}

fsPoint2i::fsPoint2i( int _x, int _y )
:
x(_x),
y(_y)
{
}

fsPoint2i::~fsPoint2i()
{
	
}

fsPoint2i::fsPoint2i(const fsPoint2i& rhs)
:	
x(rhs.x),
y(rhs.y)
{
}

fsPoint2i::fsPoint2i(const fsPoint2f& rhs)
:	
x(rhs.x),
y(rhs.y)
{
}

void fsPoint2i::swap(fsPoint2i& rhs) throw()
{
	std::swap(x,rhs.x);
	std::swap(y,rhs.y);
}

fsPoint2i& fsPoint2i::operator -(const fsPoint2i& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

fsPoint2i& fsPoint2i::operator +(const fsPoint2i& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

fsPoint2i& fsPoint2i::operator /(const fsPoint2i& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

fsPoint2i& fsPoint2i::operator =(const fsPoint2i& rhs)
{
	fsPoint2i temp(rhs);
	swap(temp);
	return *this;
}

fsPoint2i& fsPoint2i::operator +=(const fsPoint2i& rhs)
{
	x += rhs.x;
	y += rhs.y;
	
	return *this;
}

fsPoint2i& fsPoint2i::operator -=(const fsPoint2i& rhs)
{
	y -= rhs.x;
	x -= rhs.y;
	
	return *this;
}

fsPoint2i& fsPoint2i::operator *=(const fsPoint2i& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	
	return *this;
}

fsPoint2i& fsPoint2i::operator /=(const int val )
{
	x /= val;
	y /= val;
	return *this;
}

fsPoint2i& fsPoint2i::operator /=(const fsPoint2i& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

bool fsPoint2i::operator ==(const fsPoint2i& rhs)
{
	return ((x == rhs.x) && (y == rhs.y));
}

bool fsPoint2i::operator !=(const fsPoint2i& rhs)
{
	return (!((x == rhs.x) && (y == rhs.y)));
}
