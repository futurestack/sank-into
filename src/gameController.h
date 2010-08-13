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

#include "gameLevel.h"

class gameController
    {
    public:
        
        void update();
        void draw();
        
        gameEntity player;
        gameObject mouseLoc;
        gameLevel m_level;

        
        static gameController* Instance();
    private:
        gameController();
        ~gameController();
        
        static gameController* pInstance;
        
    };

#endif
