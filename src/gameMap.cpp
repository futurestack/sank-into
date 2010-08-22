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

gameMap::gameMap(fsPoint2f origin, fsPoint2f bound)
//QuadTree<bool>(QuadTree<bool>::SIZE_64x64 )
{
    m_pQuadTree = new QuadTree<bool>(QuadTree<bool>::SIZE_64x64 );
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
    Draw(*m_pQuadTree, 0, 0, m_iWidth, m_iHeight, renderer );
}

void gameMap::Update()
{
    
}

void gameMap::Click(int x, int y)
{
    
    int blockx = x / (m_iWidth / (*m_pQuadTree)[-1].width());
    int blocky = y / (m_iHeight / (*m_pQuadTree)[-1].height());
    
    //set block
    (*m_pQuadTree)[-1](blockx, blocky).object() = true;
}


void gameMap::Key( unsigned int num, int x, int y )
{
    if (num > (*m_pQuadTree).layers())
        return;
    int blockx = x / (m_iWidth / (*m_pQuadTree)[num].width());
    int blocky = y / (m_iHeight / (*m_pQuadTree)[num].width());
    (*m_pQuadTree)[num](blockx, blocky).object() = true;
}

void gameMap::BreakUp(int x, int y)
{
    int blockx = x / (m_iWidth / (*m_pQuadTree)[-1].width());
    int blocky = y / (m_iHeight / (*m_pQuadTree)[-1].width());
    
    QuadTree<bool> *qt = &(*m_pQuadTree)[-1](blockx, blocky);
    
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


