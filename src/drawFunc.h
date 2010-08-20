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

#include "fsRendererGL.h"
#include "assistants.h"
#include "general.h"
static fsRan myRan(0);

static fsRendererGL pRenderer;
static void drawBlits()
{
    
    static int rad = 5;
    for( int i = 0; i < 50; i++ )
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

static void drawDiags()
{
    static int blockSize = 64;
    
    for ( int y = 0; y < SCREEN_HEIGHT; y += blockSize )
        for ( int x = 0; x < SCREEN_WIDTH; x += blockSize )
        {
            if( myRan.doub() * 10000 < 5 )
            for( int i = 0; i < blockSize; i+=2 )
                pRenderer.renderLine( x+i, y, x+i, y+i );
            
            
        }
    
}

#endif
