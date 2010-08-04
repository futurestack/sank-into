/*
 *  gameController.h
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_CONTROLLER_H_
#define GAME_CONTROLLER_H_

#include "gameObject.h"
#include "gameEntity.h"

class gameController
    {
    public:
        

        
        gameEntity player;
        gameObject mouseLoc;
        
        
        static gameController* getRef();
    private:
        gameController();
        ~gameController();
        
        static gameController* pInstance;
        
        
    };

#endif
