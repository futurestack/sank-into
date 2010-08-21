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

gameLevel::gameLevel():
m_pOrigin(),
m_pBound()
{
    m_map.setAllObjects(false);
    
}

gameLevel::gameLevel(fsPoint2i origin , fsPoint2i bound):
m_pOrigin(origin.x,origin.y),
m_pBound(bound.x,bound.y)
{
    std::cout << "Creating level:";
    printf( "%d, %d / %d, %d\n", m_pOrigin.x,m_pOrigin.y,m_pBound.x,m_pBound.y);
    m_map.setAllObjects(false);
    
}


gameLevel::~gameLevel()
{
    
    
}

void gameLevel::update()
{
    m_map.Update();
}

void gameLevel::draw(const fsRendererGL& renderer)
{
    m_map.Draw(renderer);
    renderer.renderCircle(m_pOrigin,20);
    renderer.renderCircle(m_pBound,20);
    renderer.renderRect(m_pOrigin,m_pBound);
}

