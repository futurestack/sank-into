/*
 *  resourceManager.h
 *  sank-into
 *
 *  Created by futurestack on 8/13/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <string>

class gameObject;
class gameLevel;
class scriptInterpreter;

class resourceManager
    {
    public:
        resourceManager();
        ~resourceManager();
        gameObject* loadObject( std::string path );
        gameLevel* loadLevel( std::string path );
    protected:
        scriptInterpreter* m_pScript;
    };

#endif
