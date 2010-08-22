/*
 *  drawChunk.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "drawChunk.h"

//debug
#include <iostream>
#include "fsRendererGL.h"

#include "gameObject.h"

#include "assistants.h"
#include "general.h"

#include "gameController.h"

typedef std::vector<fsPoint2i> polyLine;

drawChunk::drawChunk():
script(),
parent(NULL)
{

}

drawChunk::drawChunk(std::string path):
script()
{
    script.doFile( path );
    std::vector<int> xdata;
    std::vector<int> ydata;
    script.getInts( "ydata", ydata);
    script.getInts( "xdata", xdata);

    for(unsigned int i = 0; i < xdata.size(); ++i)
    {
        m_vPoints.push_back( fsPoint2i( xdata[i], ydata[i] )) ;
        
    }
    
    for(polyLine::iterator it = m_vPoints.begin(); it != m_vPoints.end() ;++it )
    {
        fsPoint2i p = (*it);
        //printf("Point:%d,%d\n", p.x, p.y ); 
        
    }
    
    
    m_vPoints = normalizePoints(m_vPoints);
    
    
}

drawChunk::~drawChunk()
{
    
    
}
void drawChunk::update()
{
    static gameController* control = gameController::Instance();
    m_iJitter = control->m_iGlobalJitter;
    
}


void drawChunk::draw( const fsRendererGL& renderer)
{

//    static fsRendererGL renderer;
    static fsRan myRan(0);
    
    renderer.pushMatrix();
    if (parent)
        renderer.translate( parent->loc );
    
    
    //std::cout << m_vPoints.size();
    //check for odd #
    int numPoints = m_vPoints.size();
    //lop one off the top
    if( numPoints % 2 != 0 ) numPoints--;
    
    float jitterMax = myRan.doub()* m_iJitter;
    
    for( int i = 0; i < numPoints - 1 ; ++i )
    {
        fsPoint2f pointA = m_vPoints[i];
        fsPoint2f pointB = m_vPoints[i+1];
        pointA.x += myRan.doub() * jitterMax;
        pointA.y += myRan.doub() * jitterMax;
        pointB.x += myRan.doub() * jitterMax;
        pointB.y += myRan.doub() * jitterMax;
        pointA -= jitterMax/2;
        pointB -= jitterMax/2;
        renderer.renderLine( pointA , pointB );   
        
    }
    
    
    renderer.popMatrix();
    
}