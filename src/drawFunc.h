/*
 *  drawFunc.h
 *  sank-into
 *
 *  Created by futurestack on 8/20/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef DRAW_FUNC_H_
#define DRAW_FUNC_H_

//debug
#include <iostream>
static bool debug_drawFunc = false;

#include "fsRendererGL.h"
#include "assistants.h"
#include "general.h"
static fsRan myRan(0);

static fsRendererGL pRenderer;
inline void drawBlits(int jitter )
{
    
    static int rad = 5;
    for( int i = 0; i < jitter; i++ )
    {
        float x = myRan.doub() * SCREEN_WIDTH;
        float y = myRan.doub() * SCREEN_HEIGHT;
        
        float x2 = (x + myRan.doub() * rad ) - rad/2;
        float y2 = (y + myRan.doub() * rad ) - rad/2;
        
        if( myRan.doub() * 10000  < 5 )
        {
            x2 = x;
            y2 = y + myRan.doub() * SCREEN_HEIGHT;
        }
        pRenderer.renderLine(  x,y,x2,y2 ); 
        
    }
    
}

inline void drawDiags(int jitter )
{
    if( jitter <1 ) 
        return;
    int blockSize = 2;
    int numB = floor(myRan.doub()* 5) + 2;
    if (debug_drawFunc) std::cout << "numB:" << numB << std::endl;
    for( int i = 0; i < numB; ++i )
    {
        blockSize *= 2;
    }
     if (debug_drawFunc) std::cout << "blockSize:" << blockSize << std::endl;
    
    int x = (SCREEN_WIDTH / blockSize) * myRan.doub() * blockSize;
    int y = (SCREEN_HEIGHT / blockSize) * myRan.doub() * blockSize;
     if (debug_drawFunc) std::cout << "x:" << x << std::endl;
     if (debug_drawFunc) std::cout << "y:" << y << std::endl;

    if( myRan.doub() * 10 < 5 )
    {
        int skip = blockSize;
        skip -= myRan.doub()* blockSize;
        if (skip < 2 ) skip = 2;
         if (debug_drawFunc) std::cout << "Skip:" << skip << std::endl;
        
        for( int i = 0; i < blockSize; i+= skip )
        {
            
            pRenderer.renderLine( x+i, y, x+i, y+i );
        }
    }
    
    
    
}

#endif
