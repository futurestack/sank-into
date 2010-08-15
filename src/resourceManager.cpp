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

gameObject* resourceManager::loadObject(std::string path )
{
    gameObject* obj = new gameObject;
    obj->setName("someObj");

    static scriptInterpreter script;
    
    script.doFile( path );
    
    obj->setName( script.getString("name") );
    
    std::string drawFile = script.getString("drawFile");
    obj->m_dChunk = drawChunk( drawFile );
    
    //hacky but I'm tired of Everything having to draw itself.
    obj->m_dChunk.setParent(obj);
    obj->loc.x = 200;
    obj->loc.y = 150;
    
    return obj;
    
    
}



gameLevel* resourceManager::loadLevel( std::string path )
{
    gameLevel* level = new gameLevel;


    return level;
}
