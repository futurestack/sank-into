/*
 *  gameMap.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/13/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "gameMap.h"
#include "fsPoint2f.h"

/*
gameMap::gameMap():
QuadTree<bool>(QuadTree<bool>::SIZE_64x64 )
{
}
*/

gameMap::gameMap(fsPoint2f origin, fsPoint2f bound):
QuadTree<bool>(QuadTree<bool>::SIZE_64x64 )
{
    m_quadTree = new QuadTree<bool>(QuadTree<bool>::SIZE_64x64 );
    m_iWidth = bound.x - origin.y;
    m_iHeight = bound.y - origin.y;
    printf("Creating dynamic quad tree with %f,%f x %f,%f\n", origin.x, origin.y, bound.x,bound.y);
    
    std::cout << "m_iWidth:" << m_iWidth;
    std::cout << "m_iHeight:" << m_iHeight;
}

gameMap::~gameMap()
{
    
}

void gameMap::Draw( const fsRendererGL& renderer )
{
    Draw(*this, 0, 0, WIDTH, HEIGHT, renderer );
}

void gameMap::Update()
{
    
}

void gameMap::Click(int x, int y)
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


void gameMap::Key( unsigned int num, int x, int y )
{
    if (num > layers())
        return;
    int blockx = x / (WIDTH / (*this)[num].width());
    int blocky = y / (HEIGHT / (*this)[num].width());
    (*this)[num](blockx, blocky).object() = true;
}

void gameMap::BreakUp(int x, int y)
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

void gameMap::Draw(QuadTree<bool> &bw, int x, int y, int w, int h, const fsRendererGL& renderer)
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
        
        renderer.setColor( c_black );
        renderer.setAlpha( .6 );
        renderer.renderRect(x,y,x+w,y+h);
        renderer.setAlpha( .2 );
        renderer.renderRectFill(x,y,x+w,y+h);
    }
}


