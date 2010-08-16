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
    TTF_OpenFont("resource/fonts/akz_light.ttf", 12);
    
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
}

void fsRendererGL::setColor( float r, float g, float b, float a ) const
{

    glColor4f(r,g,b,a);
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
*/
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

void fsRendererGL::renderText( const std::string& str ) const
{
/*
    //FIX THIS.  Need to get off uglyfont
    pushMatrix();
    
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
