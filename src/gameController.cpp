/*
 *  gameController.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "general.h"
#include "gameController.h"
#include "resourceManager.h"
#include <math.h>

#include "assistants.h"

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

gameController* gameController::pInstance = 0;

gameController::gameController():
m_level(),
m_iGlobalJitter(0)
{
    resourceManager rm;
    
    m_vObjects.push_back( rm.loadObject("resource/objects/tree.lua"));
    m_vObjects.push_back( rm.loadObject("resource/objects/guy.lua"));
    m_vObjects.push_back( rm.loadObject("resource/objects/rock.lua"));

    //for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
    //    std::cout << "Obj loaded:" << (*it)->getName() << "\n";
    
    m_vLevels.push_back( rm.loadLevel("resource/levels/level_00.lua") );
    m_vLevels.push_back( rm.loadLevel("resource/levels/level_01.lua") );
    m_vLevels.push_back( rm.loadLevel("resource/levels/level_02.lua") );
    
    //hack!
    m_ePlayer.loc.y = 300;
}

gameController::~gameController()
{
    
    
}

gameController* gameController::Instance()
{
    if ( pInstance == 0 )
        pInstance = new gameController();
        
    return pInstance;

}

void gameController::update()
{
    //update mouse and camera positions
    m_oGameCamera.update();
    m_oMouseLocScreen.update();
   // m_oMouseLocWorld.loc = m_oMouseLocScreen.loc;
    m_oMouseLocWorld.loc.x = m_oMouseLocScreen.loc.x + m_oGameCamera.loc.x;
    m_oMouseLocWorld.loc.y = m_oMouseLocScreen.loc.y + m_oGameCamera.loc.y;
    
    
    //figure out the current angle of aim, update the player
    float x =  m_ePlayer.loc.x - m_oMouseLocWorld.loc.x;
    float y =  m_ePlayer.loc.y - m_oMouseLocWorld.loc.y;
    m_ePlayer.m_fCurrentAngle = -1* atan2( y,x ) - HALF_PI;
    m_ePlayer.update();
    
    //update object
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        (*it)->update();
    
    //not sure why we're updating this yet, but ...
    m_level.update();
    
    //make camera follow player
    x = m_oGameCamera.loc.x + CAM_OFFSET_X - m_ePlayer.loc.x ; 
    y = m_oGameCamera.loc.y + CAM_OFFSET_Y - m_ePlayer.loc.y; 
    static float camSpeed = .02;

    m_oGameCamera.loc.x += x*-camSpeed;
    m_oGameCamera.loc.y += y*-camSpeed;

    
}

void gameController::draw()
{
    
    m_ePlayer.draw();

    m_oGameCamera.draw();
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        (*it)->draw();
    
    
}