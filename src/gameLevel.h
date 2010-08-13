/*
 *  gameLevel.h
 *  sank-into
 *
 *  Created by futurestack on 8/8/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef GAME_LEVEL_H_
#define GAME_LEVEL_H_

class gameEntity;
class gameController;
class gameObject;

class fsRendererGL;
#include "gameMap.h"
#include "fsPoint2i.h"
#include <vector>

class gameLevel
    {
    public:
        gameLevel();
        ~gameLevel();
        
        void update();
        void draw( const fsRendererGL& renderer );
        void updateObjects();
        void updateMap();
        
        std::vector<gameObject*> m_pObjects;
        int width, height;
        
    //private:
        gameMap m_map;
    };

#endif
