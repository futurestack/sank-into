/*
 *  fsRendererGL.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef FS_RENDERER_GL_H_
#define FS_RENDERER_GL_H_

#include <vector>
#include <string>

class fsPoint2i;
class fsPoint2f;
#include "fsColor.h"

class fsRendererGL
	{
	public:
		
		//state operations
		void clear();
		void clear(float r, float g, float b, float a);
		void clear( fsColor c );
		void swapBuffers();
		
		//state operations *SOON TO BE DEPRECATED BY OPENGL STANDARD*
		void pushMatrix() const;
		void popMatrix() const;
		void translate(float x, float y, float z) const;
		void translate(const fsPoint2i& p) const;
		void translate(const fsPoint2f& p) const;
		void scale(float x, float y, float z) const;
		void rotate(float r, float x, float y, float z) const;
		//color stuff
		void setColor( fsColor c ) const;
		void setColor( float r, float g, float b, float a ) const;

		//some primitives to start
		void renderLine(const fsPoint2i& p1, const fsPoint2i& p2 ) const;
		void renderLine(const int x1, const int y1, const int x2, const int y2 ) const;
        
        void renderPolyLine(std::vector<fsPoint2i> line ) const;
        void renderPolyLine(std::vector<fsPoint2f> line ) const;
        
		void renderCircle(const int rad ) const;
		void renderCircle(const fsPoint2i& p, const int rad ) const;
		void renderCircle(const fsPoint2i& p, const int rad , const int res) const;
		void renderCircle(const fsPoint2f& p, const int rad ) const;
		void renderCircle(const int x, const int y, int rad ) const;
		
		void renderSquare(const int rad ) const;
		void renderSquare(const fsPoint2i& p, const int rad ) const;
		void renderText( const std::string& str ) const;
		void renderText( const fsPoint2i& p, const std::string& str ) const;


		fsRendererGL();
		~fsRendererGL();
		
        fsColor lastColor;

	};

#endif
