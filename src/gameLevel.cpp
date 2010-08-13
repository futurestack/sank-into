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

gameLevel::gameLevel()
{
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

}