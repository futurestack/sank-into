/*
 *  resourceManager.h
 *  sank-into
 *
 *  Created by ndrw on 8/13/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef RESOURCE_MANAGER_H_
#define RESOURCE_MANAGER_H_

#include <string>
#include "gameObject.h"

class resourceManager
    {
    public:
        
        gameObject* loadObject( std::string str );
        
        
    };

#endif
