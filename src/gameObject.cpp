/*
 *  gameObject.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "gameObject.h"
#include "gameLevel.h"

gameObject::gameObject()
:
loc(0,0),
vel(0,0),
m_dChunk(),
m_sName("gameObject"),
m_pLevel(NULL)
{


}

gameObject::~gameObject()
{


}

void gameObject::draw()
{
    m_dChunk.draw();
}

void gameObject::update()
{
    loc += vel;
    static float dampen = .9;
    vel *= dampen;
    
    //bounds check against level edges
    
    if( m_pLevel )
    {
        fsPoint2i p1 = m_pLevel->m_pOrigin;
        fsPoint2i p2 = m_pLevel->m_pBound;
        if( loc.x < p1.x ) loc.x = p1.x;
        if( loc.y < p1.y ) loc.y = p1.y;
        if( loc.x < p2.x ) loc.x = p2.x;
        if( loc.y < p2.y ) loc.y = p2.y;
    }
}

void gameObject::setLevel( gameLevel* level )
{
    assert(level);
    m_pLevel = level;  
}

gameLevel* gameObject::getLevel()
{
    return m_pLevel;
}