/*
 *  gameLevel.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/8/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "gameLevel.h"

//debug
#include <iostream>

#include "quadtree.h"

#include "fsRendererGL.h"
#include "fsPoint2f.h"

static const bool updateQuads = true;

/*
gameLevel::gameLevel():
m_pOrigin(),
m_pBound()
{
    m_map.setAllObjects(false);
    
}
*/

gameLevel::gameLevel(const fsPoint2f &origin , const fsPoint2f& bound):
m_pOrigin(origin),
m_pBound(bound),
m_map(origin, bound)
{
    printf( "gameLevel::gameLevel():Input params are %f, %f / %f, %f\n", origin.x,origin.y,bound.x,bound.y);

    
    std::cout << "Creating level:";
    printf( "%d, %d / %d, %d\n", m_pOrigin.x,m_pOrigin.y,m_pBound.x,m_pBound.y);
    m_map.m_pQuadTree->setAllObjects(false);
    
}


gameLevel::~gameLevel()
{
    
    
}

void gameLevel::update()
{
    if ( updateQuads ) m_map.Update();
}

void gameLevel::draw(const fsRendererGL& renderer)
{
    if ( updateQuads ) m_map.Draw(renderer);
    renderer.renderCircle(m_pOrigin,20);
    renderer.renderCircle(m_pBound,20);
    renderer.renderRect(m_pOrigin,m_pBound);
}

