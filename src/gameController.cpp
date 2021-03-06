/*
 *  gameController.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "general.h"
#include "gameController.h"
#include "resourceManager.h"
#include <math.h>

#include "assistants.h"
#include "gameEditor.h"

#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

gameController* gameController::pInstance = 0;

gameController::gameController():
m_pPlayer(NULL),
m_pCurrentLevel(NULL),
m_pEditor(NULL),
m_bJitter(false),
m_iGlobalJitter(0),
m_bEditMode(false)
{
    resourceManager rm;
    
    
    m_vObjects.push_back( rm.loadObject("resource/objects/tree.lua"));
    m_vObjects.push_back( rm.loadObject("resource/objects/guy.lua"));
    m_vObjects.push_back( rm.loadObject("resource/objects/rock.lua"));

    //for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
    //    std::cout << "Obj loaded:" << (*it)->getName() << "\n";
    
    m_vLevels.push_back( rm.loadLevel("resource/levels/level_00.lua") );
    m_vLevels.push_back( rm.loadLevel("resource/levels/level_01.lua") );
    m_vLevels.push_back( rm.loadLevel("resource/levels/level_02.lua") );
    m_pCurrentLevel = m_vLevels[0];
    assert(m_pCurrentLevel);
    
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
    {
        (*it)->setLevel(m_pCurrentLevel);
        (*it)->m_bGravity = true;
    }
    //hack!
    m_pPlayer = new gamePlayer;
    m_pPlayer->setLevel(m_pCurrentLevel);
    m_pPlayer->loc.y = DEFAULT_LEVEL_SIZE;
    m_pPlayer->loc.x = DEFAULT_LEVEL_SIZE / 2;
    m_pPlayer->m_bGravity = true;
    
    m_pCamera.loc = m_pPlayer->loc;
    
    m_pEditor = new gameEditor;

    
}

gameController::~gameController()
{
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        delete (*it);
    m_vObjects.clear();
    
    for( std::vector<gameLevel*>::iterator it = m_vLevels.begin(); it != m_vLevels.end(); ++it)
        delete (*it);
    m_vLevels.clear();
    
    delete m_pPlayer;
    delete m_pEditor;
}

gameController* gameController::Instance()
{
    if ( pInstance == 0 )
        pInstance = new gameController();
        
    return pInstance;

}

void gameController::update()
{
    
    m_oMouseLocScreen.update();
    m_oMouseLocWorld.loc.x = m_oMouseLocScreen.loc.x + m_pCamera.loc.x - CAM_OFFSET_X;
    m_oMouseLocWorld.loc.y = m_oMouseLocScreen.loc.y + m_pCamera.loc.y - CAM_OFFSET_Y;
    

    
    if ( m_bEditMode )
    {
        updateEdit();
    }else{
        updateGame();
    }
}
void gameController::updateEdit()
{
    //do editing stuff here...
        
        
}    

    
void gameController::updateGame()
{
    
    //set a testing jitter var
    m_bJitter ? m_iGlobalJitter = 5 : m_iGlobalJitter = 0;
    
    //update mouse and camera positions
    m_pCamera.update();
    
    //figure out the current angle of aim, update the player
    float x =  m_pPlayer->loc.x - m_oMouseLocWorld.loc.x ;//+ m_pCamera.loc.x;
    float y =  m_pPlayer->loc.y - m_oMouseLocWorld.loc.y ;//+ m_pCamera.loc.y;
    m_pPlayer->m_fCurrentAngle = -1* atan2( y,x ) - HALF_PI;
    m_pPlayer->update();
    
    //update object
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        (*it)->update();
    
    //not sure why we're updating this yet, but ...
    m_pCurrentLevel->update();
    
    //make camera follow player
    x = m_pCamera.loc.x - m_pPlayer->loc.x ; 
    y = m_pCamera.loc.y - m_pPlayer->loc.y; 
    static float camSpeed = .02;

    m_pCamera.loc.x += x*-camSpeed;
    m_pCamera.loc.y += y*-camSpeed;

    //todo: still put in camera predicting player velocity to offer a wider look-ahead
    
}

void gameController::draw( const fsRendererGL& renderer)
{
    //transform camera space just a lil
    renderer.pushMatrix();
    renderer.translate( CAM_OFFSET_X,CAM_OFFSET_Y,0 );
    renderer.setColor( c_black );
    m_pCurrentLevel->draw(renderer);
    renderer.setColor( c_black );

    m_pPlayer->draw(renderer);

    m_pCamera.draw(renderer);

    
    for( std::vector<gameObject*>::iterator it = m_vObjects.begin(); it != m_vObjects.end(); ++it)
        (*it)->draw(renderer);
    
    //end cameraspace
    renderer.pushMatrix();
    
    if( m_pEditor ) 
        m_pEditor->draw(renderer);
}

bool gameController::toggleEditMode()
{
    m_bEditMode = !m_bEditMode;
    m_bEditMode ? std::cout << "Turning edit mode on.\n" : std::cout << "Turning edit mode off.\n";
    return m_bEditMode;
}


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

void gameController::keyRelease(SDL_keysym *keysym) 
{ 

}

void gameController::keyPress(SDL_keysym *keysym) 
{ 
    // function to handle key press events
    static const float keyVel = 10.0f;
    fsPoint2i p =  m_oMouseLocWorld.loc;
    
    switch (keysym->sym) 
    {
        case SDLK_c:
        {
            m_pCurrentLevel->m_map.m_pQuadTree->setAllObjects(false);
            std::cout << "Resetting.\n";
            break;  
        }
        case SDLK_v:
        {
            m_pCurrentLevel->m_map.BreakUp(p.x , p.y);
            std::cout << "Splitting.\n";
            break;              
        }
        case SDLK_a:
            m_pPlayer->vel.x -= keyVel;  break;
        case SDLK_d:
            m_pPlayer->vel.x += keyVel;  break;
        case SDLK_w:
            m_pPlayer->vel.y -= keyVel;  break;
        case SDLK_s:
            m_pPlayer->vel.y += keyVel;  break;
        case SDLK_e:
            toggleEditMode();  break;
        case SDLK_t:
        {
            std::cout << "Toggling jitter.\n";
            m_bJitter = !m_bJitter;  
            break;
        }
        case SDLK_q:
            
            m_pCamera.vel = fsPoint2f(0,0);  
            m_pCamera.loc = fsPoint2f(0,0);  
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
            m_pPlayer->vel.x -= keyVel;
            break;
        case SDLK_RIGHT:
            m_pPlayer->vel.x += keyVel;
            break;
        case SDLK_UP:
            m_pPlayer->vel.y -= keyVel;
            break;
        case SDLK_DOWN:
            m_pPlayer->vel.y += keyVel;
            break;
        case SDLK_TAB:
            toggleFullscreen();
            break;
        default:
            m_pCurrentLevel->m_map.Key(keysym->sym - '0', p.x,p.y);
            break;
    }
    
    return;
}

void gameController::mouseUp( int x, int y, int mod )
{
    //if( pController.m_bEditMode)
}

void gameController::mouseDown( int x, int y, int mod )
{
    m_pCurrentLevel->m_map.Click(x,y);      
}

void gameController::mouseMove( int x, int y, int mod )
{
    m_oMouseLocScreen.loc = fsPoint2f(x,y);
}


void gameController::handleEvents() 
{
    static SDL_Event event;
    
    while(SDL_PollEvent(&event)) 
    {
        fsPoint2f p = m_oMouseLocWorld.loc;
        
        switch(event.type) 
        {
                
            case SDL_MOUSEMOTION:
                mouseMove(event.button.x,event.button.y, 0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                mouseDown(p.x,p.y ,0);
                
                break;           
            case SDL_MOUSEBUTTONUP:
                mouseUp(p.x,p.y ,0);
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
                keyPress(&event.key.keysym);
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

