/*
 *  gameClasses.cpp
 *  sank-into
 *
 *  Created by ndrw on 8/20/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "gameClasses.h"

#include <iostream>

//temp
#include "fsRendererGL.h"
#include <math.h>
#include <cassert>

static const fsRendererGL localRenderer;

gameWeapon::gameWeapon()
{
    
}

gameWeapon::~gameWeapon()
{
    
    
}


gameInventory::gameInventory()
{
}

gameInventory::~gameInventory()
{
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        delete (*it);    
    m_vObjects.clear();
}

void gameInventory::addObject( gameObject* obj )
{
    assert(obj);
    m_vObjects.push_back(obj);
}

void gameInventory::removeObject( gameObject* obj )
{
    
    assert(0);
}

gamePlayer::gamePlayer():
m_fFiringRadius(100),
m_fCurrentAngle(0),
m_pInventory(NULL)
{
    m_pInventory = new gameInventory;
    gameWeapon* firstGun = new gameWeapon;
    
    m_pInventory->addObject(firstGun);
    

}


gamePlayer::~gamePlayer()
{

    
}

void gamePlayer::update()
{
    gameObject::update();   
    
    
}

void gamePlayer::draw()
{
    gameObject::draw();
    localRenderer.pushMatrix();
    localRenderer.translate( loc );
    localRenderer.renderCircle( m_fFiringRadius );
    localRenderer.translate( sin( m_fCurrentAngle ) * m_fFiringRadius /2, cos( m_fCurrentAngle) * m_fFiringRadius /2 , 0 );
    localRenderer.renderCircle( 20 );

    localRenderer.popMatrix();
    //std::cout << ".";
}

