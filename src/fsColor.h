/*
 *  fsColor.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef FS_COLOR_H_
#define FS_COLOR_H_

struct fsColor
	{
		fsColor(): r(1.0f), g(0.0f), b(0.0f),a(1.0f){};
		fsColor( float _r, float _g, float _b, float _a )
		{
			r = _r;
			g = _g;
			b = _b;
			a = _a;
		};
		
		fsColor( const fsColor& c );
		
		~fsColor() {};
		
		float r,g,b,a;
		
		
		
	};

#endif
