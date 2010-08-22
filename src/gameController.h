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
#include "gameClasses.h"

#include "gameLevel.h"
#include <vector>

class fsRendererGL;
class gameEditor;

class gameController
    {
    public:
        
        void update();
        void draw( const fsRendererGL& renderer );
        
        gamePlayer *m_pPlayer;
        
        gameObject m_oMouseLocScreen;
        gameObject m_oMouseLocWorld;

        gameLevel* m_pCurrentLevel;
        gameObject m_pCamera;
        
        std::vector<gameObject*> m_vObjects;
        std::vector<gameLevel*> m_vLevels;
        
        gameEditor* m_pEditor;
        static gameController* Instance();
        bool m_bJitter;
        int m_iGlobalJitter;
        
    private:
        gameController();
        ~gameController();
        
        static gameController* pInstance;
        
    };

#endif
