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

glContext::glContext()
{
    pController = gameController::getRef();
    
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
	glDisable(GL_DEPTH_TEST);
	glDisable (GL_LINE_SMOOTH);				// Initially Disable Line Smoothing
    
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

void glContext::renderObject(const gameObject& obj )
{
    
    
    fsPoint2i p = obj.loc;
    
    renderer.pushMatrix();
    renderer.translate(p.x,p.y,0);
    renderer.renderSquare (20 );
    renderer.popMatrix();
}

void glContext::render()
{
    renderer.clear(1.0,1.0,1.0,1.0);
    
    renderer.setColor(0.0,0.0,0.0,1.0);
    renderObject( pController->mouseLoc );
    renderObject( pController->player) ;
    
    
    /*
  float lineWidth = 0.5;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(0.0, 10.0, 0.1, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  float line;
  for(line = 0.0; line < 7.0; line += 0.5) {
    glLineWidth(lineWidth);

    glBegin(GL_LINES);
      glVertex3f(-5.0, 0.0,line - 3.0f);
      glVertex3f(-1.0, 0.0, line - 3.0f);
    glEnd();

    lineWidth += 1.0;
  }

  lineWidth = 0.5;

  glEnable(GL_LINE_STIPPLE);

  // 0xAAAA = 1010 1010 1010 1010
  short stipplePattern = 0xAAAA;

  glLineStipple(2, stipplePattern);

  for(line = 0.0; line < 7.0; line += 0.5) {
    glLineWidth(lineWidth);

    glBegin(GL_LINES);
      glVertex3f(1.0f, 0.0f, line - 3.0f);
      glVertex3f(5.0f, 0.0f, line - 3.0f);
    glEnd();
    
    lineWidth += 1.0;
  }
  glDisable(GL_LINE_STIPPLE);
     */
    
    
    
}

