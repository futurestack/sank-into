// File:   glContext.cpp
/****************************************************************************
 * Copyright (c) 2008 Gareth Morgan.                                        *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 ****************************************************************************/

#include <math.h>
#include "glContext.h"
#include "general.h"

#include "gameController.h"
#include "gameObject.h"
#include "gameEntity.h"

#include "drawFunc.h"

#ifdef __APPLE__
#include <SDL/SDL_opengl.h>
#include <OpenGL/OpenGL.h>
#else
#include <GL/gl.h>
#include <SDL/SDL_opengl.h>
#endif

//debug
#include <sstream>

glContext::glContext()
{
    pController = gameController::Instance();
    
}

glContext::~glContext()
{
}

bool glContext::init() 
{   
  //class initialisation
  
  initGL();
  return true;
}

bool glContext::initGL() 
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
/*
#ifdef __APPLE__
	GLint swap = 1;
	CGLSetParameter ( CGLGetCurrentContext(), kCGLCPSwapInterval, &swap);
#endif
  */  
	//proper transparency setting
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	// no good : text setting glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
	glAlphaFunc(GL_GREATER,0.1f);
	glEnable(GL_ALPHA_TEST);
	
	glEnable( GL_BLEND );
	
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT,viewport);
	double zSpace = (double)viewport[3];
	glOrtho( 0.0,(double)viewport[2],(double)viewport[3],0.0,-1*zSpace,zSpace );
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LINE_SMOOTH );				// Initially Disable Line Smoothing
    
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
					GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
					GL_NEAREST);
	
	glEnableClientState( GL_VERTEX_ARRAY );

    
    
    
    return true;
}

bool glContext::shutdown()
{
    return true;
}

void glContext::setupProjection(int width, int height)
{	
    glOrtho( 0, width, height , 0, 1, -1 );
	glMatrixMode(GL_PROJECTION);
	glColorMask(true, true, true, true);        
	glLoadIdentity();
	init();
    /*
     
    if (height == 0) {
        height = 1;                 
    }

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    windowWidth = width;
    windowHeight = height;
    */
}

void glContext::update(float dt)
{
}

void glContext::renderObject(gameObject& obj )
{
    
    
    fsPoint2f p = obj.loc;
    
    renderer.pushMatrix();
    renderer.translate(p.x,p.y,0);
    renderer.renderSquare (30 );
    obj.draw(renderer);
    renderer.popMatrix();
}

void glContext::render()
{
    renderer.clear( c_white );
    
    renderer.setColor( c_black );
    
    fsPoint2i p = pController->m_pCamera.loc;
    
    renderer.pushMatrix();
    
    //invert camera for convenience.
    p.x *= -1;
    p.y *= -1;
    renderer.translate(p);
    pController->draw(renderer);
    pController->m_pCurrentLevel->draw(renderer);
    renderObject( *(pController->m_pPlayer) ) ;
    renderer.popMatrix();
    
    renderer.setColor( c_black );

    //some debugging data onscreen
    renderer.pushMatrix();
    renderer.translate( pController->m_oMouseLocScreen.loc );
    std::stringstream s;
    p = pController->m_oMouseLocWorld.loc;
    s << p.x << "/" << p.y ;
    renderer.renderText( pController->m_oMouseLocScreen.loc, s.str() );
    renderer.popMatrix();
    
    renderer.pushMatrix();
    s.clear();
    s.str("");
    p = pController->m_pPlayer->loc;
    s << "player:";
    s << p.x << "/" << p.y ;
    renderer.renderText( fsPoint2f( 20, 200) , s.str() );
    renderer.popMatrix();
    
    s.str("");
    p = pController->m_pCamera.loc;
    s << "camera:";
    s << p.x << "/" << p.y ;
    renderer.renderText( fsPoint2f( 20, 220) , s.str() );
    
    renderObject( pController->m_oMouseLocScreen );
    
    //render the inventory
    renderer.setColor( c_black );
    fsPoint2f renderPos;
    static int boxOffset = 20;
    renderPos = boxOffset*2;
    int numInventory = 6;
    for( int i = 0; i < numInventory; ++i )
    {
        gameObject* obj;
        obj = pController->m_pPlayer->m_pInventory.getObject( i );
        if( obj != NULL )
        {
            renderer.setColor( c_black );

            renderer.setTextureMode();
            //fsPoint2f renderTextPos = renderPos - boxOffset;
            renderer.renderText( fsPoint2f(renderPos.x - boxOffset, renderPos.y + 12 ) , obj->getName() );
            renderer.setLineMode();
        }
        renderer.setColor(c_black);
        renderer.setAlpha(.5);
        renderer.renderSquare(renderPos, boxOffset*2 );
        renderPos.x += boxOffset*2 + boxOffset;
    }
    renderer.setColor( c_black );
    drawBlits();
    drawDiags();
    
}

