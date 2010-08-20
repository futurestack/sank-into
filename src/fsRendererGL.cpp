/*
 *  fsRendererGL.cpp
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "fsRendererGL.h"

#ifndef __FS_RUN_HEADLESS__

//debug
#include <iostream>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL.h>
#include <cassert>

//debug ffs - should be we defining pi here?   PROBABLY NOT.
static const double pi = 3.14159265;
static const int res=300;
#include <math.h>

#include "fsPoint2f.h"
#include "fsPoint2i.h"
#include "fsColor.h"

fsRendererGL::fsRendererGL():
lastColor(0,0,0,0)
{
    TTF_Init();
    m_pFont = TTF_OpenFont("resource/font/akz_light.ttf", 16);
    assert( m_pFont );
    SDL_EnableUNICODE(1);

}

void fsRendererGL::setFont( std::string path, int size )
{
    if( m_pFont )
        TTF_CloseFont(m_pFont);
    m_pFont = TTF_OpenFont(path.c_str(), size);
    assert( m_pFont );
}

fsRendererGL::~fsRendererGL()
{
    
    TTF_Quit();
    TTF_CloseFont(m_pFont);
}

//state operations
void fsRendererGL::clear()
{
    
    glClearColor(lastColor.r,lastColor.g,lastColor.b,lastColor.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void fsRendererGL::clear(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void fsRendererGL::clear( fsColor c )
{
    glClearColor(c.r,c.g,c.b,c.a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void fsRendererGL::swapBuffers()
{
    SDL_GL_SwapBuffers ();

}

void fsRendererGL::pushMatrix() const
{
    glPushMatrix();
}

void fsRendererGL::popMatrix() const
{
    glPopMatrix();
}

void fsRendererGL::setColor( fsColor c ) const
{
    glColor4f(c.r,c.g,c.b,c.a);
    lastColor = c;
}

void fsRendererGL::setColor( float r, float g, float b, float a ) const
{

    glColor4f(r,g,b,a);
    lastColor = fsColor(r,g,b,a);
}
void fsRendererGL::translate(float x, float y, float z) const
{
    glTranslated( x , y , z );
}

void fsRendererGL::translate(const fsPoint2i& p) const
{
    glTranslated( p.x , p.y , 0 );
}

void fsRendererGL::translate(const fsPoint2f& p) const
{
    glTranslated( p.x , p.y , 0 );
}

void fsRendererGL::scale(float x, float y, float z) const
{
    glScalef(x,y,z);
}

void fsRendererGL::rotate(float r, float x, float y, float z) const
{
    glRotatef(r , x, y , z);
}

//some primitives to start
void fsRendererGL::renderLine(const fsPoint2i& p1, const fsPoint2i& p2 ) const
{
    //std::cout << ".";

    const GLfloat renderLine[] = 
    {
        p1.x, p1.y,
        p2.x, p2.y
    };
    glVertexPointer(2, GL_FLOAT, 0, renderLine);
    glDrawArrays(GL_LINE_STRIP, 0, 2 );
}

void fsRendererGL::renderLine( const int x1, const int y1, const int x2, const int y2 ) const
{
    //std::cout << "G.";
    
    const GLfloat renderLine[] = 
    {
        x1,y1,
        x2,y2
    };
    glVertexPointer(2, GL_FLOAT, 0, renderLine);
    glDrawArrays(GL_LINE_STRIP, 0, 2 );
}
/*
void fsRendererGL::renderPolyLine(std::vector<fsPoint2f> line ) const
{
    unsigned const int linesize = line.size();
    unsigned const int renderLineSize = (linesize*2);
    GLfloat renderLine[ renderLineSize ];
    unsigned int j =0;
    for( unsigned int i = 0; i < linesize; i++ )
    {
        renderLine[j] = (line[i].x);
        renderLine[j+1] = (line[i].y);
        j+=2;
    }
    glVertexPointer(2, GL_FLOAT, 0, renderLine);
    glDrawArrays(GL_LINE_STRIP, 0, linesize );    
}

void fsRendererGL::renderPolyLine(std::vector<fsPoint2i> line ) const
{
    unsigned const int linesize = line.size();
    unsigned const int renderLineSize = (linesize*2);
    GLfloat renderLine[ renderLineSize ];
    unsigned int j =0;
    for( unsigned int i = 0; i < linesize; i++ )
    {
        renderLine[j] = (line[i].x);
        renderLine[j+1] = (line[i].y);
        j+=2;
    }
    glVertexPointer(2, GL_FLOAT, 0, renderLine);
    glDrawArrays(GL_LINE_STRIP, 0, linesize );    
}
*/
void fsRendererGL::renderCircle(const int rad  ) const
{

    static float deg2rad( pi/res );
    static unsigned const int renderLineSize = (res*2);
    static GLfloat circleArray[ renderLineSize ];
    
    for (int i=0; i < (res*2) ; i+=2 )
    {
        float degInRad = i*deg2rad;
        circleArray[i] =        cos(degInRad) * rad/2;
        circleArray[i+1] =        sin(degInRad) * rad/2;;
    }
    glVertexPointer(2, GL_FLOAT, 0, circleArray);
    glDrawArrays(GL_LINE_LOOP, 0, res );
}

void fsRendererGL::renderCircle(const fsPoint2i& p, const int rad  ) const
{
    static float deg2rad( pi/res );
    static unsigned const int renderLineSize = (res*2);
    static GLfloat circleArray[ renderLineSize ];
    
    for (int i=0; i < (res*2) ; i+=2 )
    {
        float degInRad = i*deg2rad;
        circleArray[i] =    p.x+    cos(degInRad) * rad;
        circleArray[i+1] =    p.y+    sin(degInRad) * rad;;
    }
    glVertexPointer(2, GL_FLOAT, 0, circleArray);
    glDrawArrays(GL_LINE_LOOP, 0, res );
}
/*
void fsRendererGL::renderCircle(const fsPoint2i& p, const int rad, const int res  ) const
{
    const float deg2rad( pi/res );
    unsigned const int renderLineSize = (res*2);
    GLfloat circleArray[ renderLineSize ];
    
    for (int i=0; i < (res*2) ; i+=2 )
    {
        float degInRad = i*deg2rad;
        circleArray[i] =    p.x+    cos(degInRad) * rad;
        circleArray[i+1] =    p.y+    sin(degInRad) * rad;;
    }
    glVertexPointer(2, GL_FLOAT, 0, circleArray);
    glDrawArrays(GL_LINE_LOOP, 0, res );
}
*/
void fsRendererGL::renderCircle(const fsPoint2f& p, const int rad  ) const
{
    static float deg2rad( pi/res );
    unsigned const int renderLineSize = (res*2);
    GLfloat circleArray[ renderLineSize ];
    
    for (int i=0; i < (res*2) ; i+=2 )
    {
        float degInRad = i*deg2rad;
        circleArray[i] =    p.x+    cos(degInRad) * rad/2;
        circleArray[i+1] =    p.y+    sin(degInRad) * rad/2;
    }
    glVertexPointer(2, GL_FLOAT, 0, circleArray);
    glDrawArrays(GL_LINE_LOOP, 0, res );
}

void fsRendererGL::renderCircle(const int x, const int y, const int rad  ) const
{
    static float deg2rad( pi/res );
    static unsigned const int renderLineSize = (res*2);
    static GLfloat circleArray[ renderLineSize ];
    static float finalRad = rad/2;
    for (int i=0; i < (res*2) ; i+=2 )
    {
        float degInRad = i*deg2rad;
        circleArray[i] =    x+    cos(degInRad) * finalRad;
        circleArray[i+1] =    y+    sin(degInRad) * finalRad;
    }
    glVertexPointer(2, GL_FLOAT, 0, circleArray);
    glDrawArrays(GL_LINE_LOOP, 0, res );
}

void fsRendererGL::renderSquare(const fsPoint2i& p, const int rad) const
{
    float d = rad/2;
    GLfloat line[] =
    {
        p.x - d , p.y + d,
        p.x - d , p.y - d,
        p.x + d , p.y - d,
        p.x + d , p.y + d
    };
    glVertexPointer(2,GL_FLOAT, 0, line);
    glDrawArrays(GL_LINE_LOOP, 0, 4 );
}

void fsRendererGL::renderSquare( const int rad) const
{
    float d = rad/2;
    GLfloat line[] =
    {
        - d ,  d,
        - d , -d,
          d , -d,
          d , d
    };
    glVertexPointer(2,GL_FLOAT, 0, line);
    glDrawArrays(GL_LINE_LOOP, 0, 4 );
}
void fsRendererGL::renderRect(const fsPoint2i& p1, const fsPoint2i& p2) const
{
    GLfloat line[] =
    {
        p1.x, p1.y,
        p2.x, p1.y,
        p2.x, p2.y,
        p1.x, p2.y
    
    };
    glVertexPointer(2,GL_FLOAT, 0, line);
    glDrawArrays(GL_LINE_LOOP, 0, 4 );
}

void fsRendererGL::renderRect( int x1, int y1, int x2, int y2 ) const
{
    GLfloat line[] =
    {
        x1,y1,
        x2,y1,
        x2,y2,
        x1,y2
    };
    glVertexPointer(2,GL_FLOAT, 0, line);
    glDrawArrays(GL_LINE_LOOP, 0, 4 );
}
void fsRendererGL::renderRectFill( int x1, int y1, int x2, int y2 ) const
{
    GLfloat line[] =
    {
        x1,y1,
        x2,y1,
        x2,y2,
        x1,y2
    };
    glVertexPointer(2,GL_FLOAT, 0, line);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4 );
}

void fsRendererGL::renderText( fsPoint2f p, const std::string& str ) const
{
    setTextureMode();
	/*
    renderCircle(500);
    this->setpTextureMode();
    renderCircle(400);
*/
    int X = p.x;
    int Y = p.y;
    int Z = 0;
    
	SDL_Color Color = {lastColor.r, lastColor.g, lastColor.b};
	SDL_Surface *pMessage = TTF_RenderText_Blended( m_pFont, str.c_str(), Color);
	GLuint pTexture = 0;
    
	glGenTextures(1, &pTexture);
	glBindTexture(GL_TEXTURE_2D, pTexture);
    
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pMessage->w, pMessage->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, pMessage->pixels);
    
	glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3d(X, Y, Z);
    glTexCoord2d(1, 0); glVertex3d(X+pMessage->w, Y, Z);
    glTexCoord2d(1, 1); glVertex3d(X+pMessage->w, Y+pMessage->h, Z);
    glTexCoord2d(0, 1); glVertex3d(X, Y+pMessage->h, Z);
	glEnd();
    
	glDeleteTextures(1, &pTexture);
	SDL_FreeSurface(pMessage);
    setLineMode();
}

void fsRendererGL::setTextureMode() const
{
    //glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glLoadIdentity();
}

void fsRendererGL::setLineMode() const
{

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	// no good : text setting glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
	glAlphaFunc(GL_GREATER,0.1f);
	glEnable(GL_ALPHA_TEST);
	
	glEnable( GL_BLEND );

	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LINE_SMOOTH );				// Initially Disable Line Smoothing
    
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
					GL_NEAREST);
	
	glEnableClientState( GL_VERTEX_ARRAY );
    
    

    
}

void fsRendererGL::renderText( const fsPoint2i& p, const std::string& str ) const
{
    
    //FIX THIS.  Need to get off uglyfont
    /*
    pushMatrix();
    translate(  p );
    translate(0,-5,0);
    scale(10,-10,0);
#ifndef __FS_MINIMAL__
    
    YsDrawUglyFont( str.c_str() ,0 );
#else
    throw fsException("Minimal configuration doesn't allow uglyfont.");
#endif
    popMatrix();
    */
    
}



#endif
