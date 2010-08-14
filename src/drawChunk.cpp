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

typedef std::vector<fsPoint2i> polyLine;

drawChunk::drawChunk():
parent(NULL),
script()
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
        printf("Point:%d,%d\n", p.x, p.y ); 
        
    }
    
}

drawChunk::~drawChunk()
{
    
    
}
void drawChunk::update()
{
    
    
    
}


void drawChunk::draw()
{
    //std::cout << ".";
    static fsRendererGL renderer;

    renderer.pushMatrix();
    if (parent)
        renderer.translate( parent->loc );
    
    
    //std::cout << m_vPoints.size();
    //check for odd #
    int numPoints = m_vPoints.size();
    //lop one off the top
    if( numPoints % 2 != 0 ) numPoints--;
    
    for( int i = 0; i < numPoints - 1 ; ++i )
    {
        renderer.renderLine( m_vPoints[i], m_vPoints[i+1] );   
        
    }
    
    
    renderer.popMatrix();
    
}