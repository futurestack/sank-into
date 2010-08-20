// File:   handleEvents.cpp
/****************************************************************************
 * Copyright (c) 2008 Gareth Morgan.                                        *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 ****************************************************************************/

#include "handleEvents.h"


#include <iostream>

#include "gameController.h"

eventHandler::eventHandler()
{
    pController = gameController::Instance();
    
}

eventHandler::~eventHandler()
{
    
    
}


void eventHandler::handleKeyPress(SDL_keysym *keysym) 
{ 
    // function to handle key press events
    static const float keyVel = 5.0f;
    fsPoint2i p =  pController->m_oMouseLocWorld.loc;
    
    switch (keysym->sym) 
    {
        case SDLK_c:
        {
            pController->m_level.m_map.setAllObjects(false);
            std::cout << "Resetting.\n";
            break;  
        }
        case SDLK_v:
        {
            pController->m_level.m_map.BreakUp(p.x , p.y);
            std::cout << "Splitting.\n";
            break;              
        }
        case SDLK_a:
            pController->m_oGameCamera.vel.x -= keyVel;  break;
        case SDLK_d:
            pController->m_oGameCamera.vel.x += keyVel;  break;
        case SDLK_w:
            pController->m_oGameCamera.vel.y -= keyVel;  break;
        case SDLK_s:
            pController->m_oGameCamera.vel.y += keyVel;  break;
        case SDLK_q:
            pController->m_oGameCamera.vel = fsPoint2f(0,0);  
            pController->m_oGameCamera.loc = fsPoint2f(0,0);  
            break;
            
        case SDLK_ESCAPE:
        // ESC key was pressed
            Quit(0);
            break;
            
        case SDLK_F1:
            /* F1 key was pressed
             * this toggles fullscreen mode
             */
            toggleFullscreen();
            break;
        case SDLK_LEFT:
            pController->m_ePlayer.vel.x -= keyVel;
            break;
        case SDLK_RIGHT:
            pController->m_ePlayer.vel.x += keyVel;
            break;
        case SDLK_UP:
            pController->m_ePlayer.vel.y -= keyVel;
            break;
        case SDLK_DOWN:
            pController->m_ePlayer.vel.y += keyVel;
            break;
        case SDLK_TAB:
            toggleFullscreen();
            break;
        default:
            pController->m_level.m_map.Key(keysym->sym - '0', p.x,p.y);
            break;
      }
      
    return;
}

void eventHandler::handleMouseUp( int x, int y)
{
    pController->m_ePlayer.loc = pController->m_oMouseLocWorld.loc;

}

void eventHandler::handleMouseDown( int x, int y)
{
    pController->m_level.m_map.Click(x,y);

                               
                               
                               
}

void eventHandler::handleMouseMotion( int x, int y)
{
    pController->m_oMouseLocScreen.loc = fsPoint2f(x,y);
}


void eventHandler::handleEvents() 
{
    static SDL_Event event;

    while(SDL_PollEvent(&event)) 
    {
        fsPoint2f p = pController->m_oMouseLocWorld.loc;

        switch(event.type) 
        {

            case SDL_MOUSEMOTION:
                handleMouseMotion(event.button.x,event.button.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                handleMouseDown(p.x,p.y );
                
                break;           
            case SDL_MOUSEBUTTONUP:
                handleMouseUp(p.x,p.y );
                break;
                /*
                 //case SDL_ACTIVEEVENT:
                //Something's happend with our focus
                 //If we lost focus or we are iconified, we
                 //shouldn't draw the screen
            
            if (event.active.gain == 0)
                isActive = false;
            else
                isActive = true;
                */
            break;
        case SDL_VIDEORESIZE:
            resizeWindow(event.resize.w, event.resize.h);
            break;
        case SDL_KEYDOWN:
            // handle key presses
            handleKeyPress(&event.key.keysym);
            break;
        case SDL_QUIT:
            // handle quit requests
            done = true;
            break;
        default:
            break;
        }
    }
}
