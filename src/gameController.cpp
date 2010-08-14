/*
 *  gameController.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "gameController.h"
#include "resourceManager.h"

gameController* gameController::pInstance = 0;

gameController::gameController():
m_level()
{
    resourceManager rm;
    
    m_vObjects.push_back( rm.loadObject("resource/objects/tree.lua"));
    m_vObjects.push_back( rm.loadObject("resource/objects/guy.lua"));
    m_vObjects.push_back( rm.loadObject("resource/objects/rock.lua"));


    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        std::cout << "Obj loaded:" << (*it)->getName() << "\n";
    
    
    
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
    m_oGameCamera.update();
    m_oMouseLocScreen.update();
    m_oMouseLocWorld.loc = m_oMouseLocScreen.loc;
    m_oMouseLocWorld.loc += m_oGameCamera.loc;
    
    m_ePlayer.update();

    m_level.update();

}

void gameController::draw()
{



}