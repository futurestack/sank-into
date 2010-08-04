/*
 *  gameObject.h
 *  sank-into
 *
 *  Created by hornet on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "fsPoint2i.h"

class gameObject
    {
    public:  
        gameObject();
        virtual ~gameObject();
        
        
        fsPoint2i loc;        
        fsPoint2i vel;

        
    };

#endif
