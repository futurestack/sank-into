/*
 *  gameObject.h
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "fsPoint2f.h"

class gameObject
    {
    public:  
        gameObject();
        virtual ~gameObject();
        
        void update();
        void draw();
        
        fsPoint2f loc;        
        fsPoint2f vel;

        
    };

#endif
