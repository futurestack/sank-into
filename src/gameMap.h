/*
 *  gameMap.h
 *  sank-into
 *
 *  Created by futurestack on 8/13/10.
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
    gameMap(fsPoint2f origin, fsPoint2f bound);
    ~gameMap();
    
    void Draw( const fsRendererGL& renderer );
    
    void Update();
    void Click(int x, int y);
       
    void Key(unsigned int num, int x, int y);
    
    void BreakUp(int x, int y);

    QuadTree<bool>* m_quadTree;
    int m_iWidth;
    int m_iHeight;
    
protected:
    
    void Draw(QuadTree<bool> &bw, int x, int y, int w, int h, const fsRendererGL& renderer);
private:
    
    //moving this here temporarily to lazily enforce that we are constructing these with coords.
    //gameMap();

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
