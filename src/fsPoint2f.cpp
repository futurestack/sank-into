/*
 *  fsPoint2f.cpp
 *  fsGui
 *
 *  Created by futurestack on 2/23/09.
 *  Copyright 2009 st4tic_software. All rights reserved.
 *
 */

#include "fsPoint2f.h"
#include "fsPoint2i.h"
#include <algorithm>

fsPoint2f::fsPoint2f()
:
x(0),
y(0)
{
}

fsPoint2f::fsPoint2f( float _x, float _y )
:
x(_x),
y(_y)
{
}

fsPoint2f::~fsPoint2f()
{
	
}

fsPoint2f::fsPoint2f(const fsPoint2f& rhs)
:	
x(rhs.x),
y(rhs.y)
{
}

fsPoint2f::fsPoint2f(const fsPoint2i& rhs)
:	
x(rhs.x),
y(rhs.y)
{
}
void fsPoint2f::swap(fsPoint2f& rhs) throw()
{
	std::swap(x,rhs.x);
	std::swap(y,rhs.y);
}

fsPoint2f& fsPoint2f::operator -(const fsPoint2f& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

fsPoint2f& fsPoint2f::operator +(const fsPoint2f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

fsPoint2f& fsPoint2f::operator /(const fsPoint2f& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

fsPoint2f& fsPoint2f::operator =(const fsPoint2f& rhs)
{
	fsPoint2f temp(rhs);
	swap(temp);
	return *this;
}

fsPoint2f& fsPoint2f::operator +=(const fsPoint2f& rhs)
{
	x += rhs.x;
	y += rhs.y;
	
	return *this;
}

fsPoint2f& fsPoint2f::operator -=(const fsPoint2f& rhs)
{
	y -= rhs.x;
	x -= rhs.y;
	
	return *this;
}

fsPoint2f& fsPoint2f::operator *=(const fsPoint2f& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	
	return *this;
}

fsPoint2f& fsPoint2f::operator /=(const float val )
{
	x /= val;
	y /= val;
	return *this;
}

fsPoint2f& fsPoint2f::operator *=(const float val )
{
	x *= val;
	y *= val;
	return *this;
}

fsPoint2f& fsPoint2f::operator /=(const fsPoint2f& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

bool fsPoint2f::operator ==(const fsPoint2f& rhs)
{
	return ((x == rhs.x) && (y == rhs.y));
}
 

bool fsPoint2f::operator != (const fsPoint2f& rhs)
{
	return (!((x == rhs.x) && (y == rhs.y)));
}

