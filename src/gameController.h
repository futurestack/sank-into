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
#include <vector>

class gameController
    {
    public:
        
        void update();
        void draw();
        
        gameEntity m_ePlayer;
        gameObject m_oMouseLocScreen;
        gameObject m_oMouseLocWorld;
        gameLevel m_level;
        gameObject m_oGameCamera;
        
        std::vector<gameObject*> m_vObjects;
        std::vector<gameLevel*> m_vLevels;
        
        
        static gameController* Instance();
    
    private:
        gameController();
        ~gameController();
        
        static gameController* pInstance;
        
    };

#endif
