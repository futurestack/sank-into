/*
 *  gameEditor.h
 *  sank-into
 *
 *  Created by futurestack on 8/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_EDITOR_H_
#define GAME_EDITOR_H_

#include <vector>
class gameLevel;
class gameMap;
class gameObject;
class fsRendererGL;

class gameEditor
    {
    public:
        gameEditor();
        ~gameEditor();
        
        
        void update();
        void draw( const fsRendererGL& renderer );
        
    };

#endif
