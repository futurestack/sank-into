/*
 *  resourceManager.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/13/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "resourceManager.h"
#include "scriptInterpreter.h"
#include "drawChunk.h"

#include "gameObject.h"
#include "gameLevel.h"
#include "scriptInterpreter.h"

#include "general.h"

//debug temp
#include "assistants.h"

resourceManager::resourceManager():
m_pScript(NULL)
{
    m_pScript = new scriptInterpreter;
}

resourceManager::~resourceManager()
{
    delete m_pScript;
    
}
gameObject* resourceManager::loadObject(std::string path )
{
    static fsRan myRan(0);
    gameObject* obj = new gameObject;
    obj->setName("someObj");

    m_pScript->doFile( path );
    
    obj->setName( m_pScript->getString("name") );
    
    std::string drawFile = m_pScript->getString("drawFile");
    obj->m_dChunk = drawChunk( drawFile );
    
    //hacky but I'm tired of Everything having to draw itself.
    obj->m_dChunk.setParent(obj);
    obj->loc.x = myRan.doub() * DEFAULT_LEVEL_SIZE;
    obj->loc.y = myRan.doub() * DEFAULT_LEVEL_SIZE / 2;
    
    return obj;
    
    
}



gameLevel* resourceManager::loadLevel( std::string path )
{
    fsPoint2i origin = fsPoint2i(0,0);
    fsPoint2i bound = fsPoint2i(DEFAULT_LEVEL_SIZE , DEFAULT_LEVEL_SIZE );
    printf( "resourceManager::loadLevel():Input params are %d, %d / %d, %d\n", origin.x,origin.y,bound.x,bound.y);

    gameLevel* level = new gameLevel(origin,bound);

    
    
    

    return level;
}
