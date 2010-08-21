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
m_pPlayer(NULL),
m_pCurrentLevel(NULL),
m_bJitter(false),
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
    m_pCurrentLevel = m_vLevels[0];
    assert(m_pCurrentLevel);
    
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
    {
        (*it)->setLevel(m_pCurrentLevel);
        (*it)->m_bGravity = true;
    }
    //hack!
    m_pPlayer = new gamePlayer;
    m_pPlayer->setLevel(m_pCurrentLevel);
    m_pPlayer->loc.y = 2048;
    m_pPlayer->loc.x = 1024;
    m_pPlayer->m_bGravity = true;
    
    m_pCamera.loc = m_pPlayer->loc;
}

gameController::~gameController()
{
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        delete (*it);
    m_vObjects.clear();
    
    for( std::vector<gameLevel*>::iterator it = m_vLevels.begin(); it != m_vLevels.end(); ++it)
        delete (*it);
    m_vLevels.clear();
    
    delete m_pPlayer;
    
}

gameController* gameController::Instance()
{
    if ( pInstance == 0 )
        pInstance = new gameController();
        
    return pInstance;

}

void gameController::update()
{
    //set a testing jitter var
    m_bJitter ? m_iGlobalJitter = 5 : m_iGlobalJitter = 0;
    
    //update mouse and camera positions
    m_pCamera.update();
    m_oMouseLocScreen.update();
   // m_oMouseLocWorld.loc = m_oMouseLocScreen.loc;
    m_oMouseLocWorld.loc.x = m_oMouseLocScreen.loc.x + m_pCamera.loc.x;
    m_oMouseLocWorld.loc.y = m_oMouseLocScreen.loc.y + m_pCamera.loc.y;
    
    
    //figure out the current angle of aim, update the player
    float x =  m_pPlayer->loc.x - m_oMouseLocWorld.loc.x;
    float y =  m_pPlayer->loc.y - m_oMouseLocWorld.loc.y;
    m_pPlayer->m_fCurrentAngle = -1* atan2( y,x ) - HALF_PI;
    m_pPlayer->update();
    
    //update object
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        (*it)->update();
    
    //not sure why we're updating this yet, but ...
    m_pCurrentLevel->update();
    
    //make camera follow player
    x = m_pCamera.loc.x + CAM_OFFSET_X - m_pPlayer->loc.x ; 
    y = m_pCamera.loc.y + CAM_OFFSET_Y - m_pPlayer->loc.y; 
    static float camSpeed = .02;

    m_pCamera.loc.x += x*-camSpeed;
    m_pCamera.loc.y += y*-camSpeed;

    
}

void gameController::draw(fsRendererGL& renderer)
{
    renderer.setColor( c_black );
    m_pCurrentLevel->draw(renderer);
    renderer.setColor( c_black );

    m_pPlayer->draw(renderer);

    m_pCamera.draw(renderer);

    
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        (*it)->draw(renderer);
    
    
}