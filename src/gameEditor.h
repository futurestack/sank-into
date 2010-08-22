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
#include "fsPoint2f.h"

#include "interfaces.h"

class gameLevel;
class gameMap;
class gameObject;
class fsRendererGL;

class gameEditor : public eventHandler
    {
    public:
        gameEditor();
        ~gameEditor();
        
        void mouseUp( int x, int y, int mod );
        void mouseDown( int x, int y, int mod );
        void mouseMove( int x, int y, int mod );
        void keyRelease( SDL_keysym * keysm );
        void keyPress( SDL_keysym *keysym );
        
        
        void update();
        void draw( const fsRendererGL& renderer );
    private:
        std::vector< std::vector<fsPoint2f> > m_vLines;
        std::vector< fsPoint2f> currentLine ;
    };

#endif
