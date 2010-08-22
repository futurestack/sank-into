/*
 *  interfaces.h
 *  sank-into
 *
 *  Created by hornet on 8/22/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INTERFACES_H_
#define INTERFACES_H_

#include "general.h"

class eventHandler
    {
    public:
        
        eventHandler() {};
        virtual ~eventHandler() {};
        virtual void mouseUp( int x, int y, int mod ) {};
        virtual void mouseDown( int x, int y, int mod ) {};
        virtual void mouseMove( int x, int y, int mod ) {};
        virtual void keyRelease( SDL_keysym * keysm ) {};
        virtual void keyPress( SDL_keysym *keysym ) {};

    
    };

#endif
