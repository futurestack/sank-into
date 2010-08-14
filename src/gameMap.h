/*
 *  gameMap.h
 *  sank-into
 *
 *  Created by ndrw on 8/13/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "quadtree.h"

//debug
#include <iostream>

#include "fsRendererGL.h"

#include <cassert>
#include <SDL/SDL.h>

const int WIDTH = 1024;
const int HEIGHT = WIDTH;

class gameMap : public QuadTree<bool>
{
public:
    gameMap() :
    QuadTree<bool>(QuadTree<bool>::SIZE_256x256)
    {
    };
    virtual ~gameMap() { };
    
    virtual void Draw( const fsRendererGL& renderer )
    {
        Draw(*this, 0, 0, WIDTH, HEIGHT, renderer );
    }
    
    virtual void Update()
    {
        
    }
    
    virtual void Click(int x, int y)
    {
        
        int blockx = x / (WIDTH / (*this)[-1].width());
        int blocky = y / (HEIGHT / (*this)[-1].height());
        
        /*
         
        well this isn't quite what I wanted, I'm misusing the positional data somewhere.  commenting for now.
        for( int i = 0; i < (*this)[0](blockx,blocky).layers() ; ++i )
        {
            std::cout << "Autosplitting.\n";
            gameMap * splitLayer = dynamic_cast<gameMap*>(&(*this)[i] );
            if( splitLayer ) splitLayer->BreakUp(blockx,blocky);
        }
       */
        
        //set block
        (*this)[-1](blockx, blocky).object() = true;
    }
    
    virtual void Key(unsigned int num, int x, int y)
    {
        if (num > layers())
            return;
        int blockx = x / (WIDTH / (*this)[num].width());
        int blocky = y / (HEIGHT / (*this)[num].width());
        (*this)[num](blockx, blocky).object() = true;
    }
    
    virtual void BreakUp(int x, int y)
    {
        int blockx = x / (WIDTH / (*this)[-1].width());
        int blocky = y / (HEIGHT / (*this)[-1].width());
        
        QuadTree<bool> *qt = &(*this)[-1](blockx, blocky);
        
        while (true)
        {
            if (qt->object() == true && qt->layers() > 0)
            {
                qt->setAllObjects(false);
                (*qt)[1](0, 0).object() = true;
                (*qt)[1](0, 1).object() = true;
                (*qt)[1](1, 0).object() = true;
                (*qt)[1](1, 1).object() = true;
                return;
            }
            if (qt->hasParent())
                qt = &qt->parent();
            else
                break;
        }
    }
protected:
    
    virtual void Draw(QuadTree<bool> &bw, int x, int y, int w, int h, const fsRendererGL& renderer)
    {
        if (bw.object() == false)
        {
            if (bw.layers() == 0)
                return;
            Draw(bw[1](0, 0),  x,         y,         w / 2, h / 2, renderer);
            Draw(bw[1](1, 0), x + w / 2, y,         w / 2, h / 2, renderer);
            Draw(bw[1](0, 1),  x,         y + h / 2, w / 2, h / 2, renderer);
            Draw(bw[1](1, 1), x + w / 2, y + h / 2, w / 2, h / 2 , renderer);
        }
        else
        {
            SDL_Rect r;
            r.x = x + 1;
            r.y = y + 1;
            r.w = w - 1;
            r.h = h - 1;
            SDL_FillRect(SDL_GetVideoSurface(), &r, 0x00CCAA77);
            renderer.setColor(0.,0.,0.,.5);
            renderer.renderRect(x,y,x+w,y+h);
            renderer.setColor(0.,0.,0.,.2);
            renderer.renderRectFill(x,y,x+w,y+h);
        }
    }
};
                                

#endif
                                
/*
int main()
{
    bool running = true;
    SDL_Event ev;
    gameMap bw;
    bw.setAllObjects(false);
    
    SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_DOUBLEBUF);
    
    while (running)
    {
        SDL_FillRect(SDL_GetVideoSurface(), NULL, 0);
        bw.Draw();
        bw.Update();
        SDL_Flip(SDL_GetVideoSurface());
        
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    bw.Click(ev.motion.x, ev.motion.y);
                    break;
                case SDL_KEYDOWN:
                {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (ev.key.keysym.sym == SDLK_c)
                        bw.setAllObjects(false);
                    if (ev.key.keysym.sym == SDLK_s)
                        bw.BreakUp(x, y);
                    else
                        bw.Key(ev.key.keysym.sym - '0', x, y);
                    break;
                }
                default:
                    break;
            }
        }
    }
    
    SDL_Quit();
    return 0;
}
#endif

*/
