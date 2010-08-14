/*
 *  resourceManager.cpp
 *  sank-into
 *
 *  Created by ndrw on 8/13/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "resourceManager.h"
#include "scriptInterpreter.h"

gameObject* resourceManager::loadObject(std::string str )
{
    gameObject* obj = new gameObject;
    obj->setName("someObj");

    static scriptInterpreter script;
    
    script.doFile( str );
    
    obj->setName( script.getString("name") );
    
    
    return obj;
}
