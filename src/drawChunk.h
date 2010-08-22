/*
 *  drawChunk.h
 *  sank-into
 *
 *  Created by futurestack on 8/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef DRAW_CHUNK_H_
#define DRAW_CHUNK_H_

#include "scriptInterpreter.h"
#include <string>
#include <vector>
#include "fsPoint2i.h"

class gameObject;
class fsRendererGL;

class drawChunk
    {
    public:
        drawChunk();
        drawChunk(std::string path);
        ~drawChunk();

        void setParent(gameObject* par) { parent = par; };
        void draw( const fsRendererGL& renderer);
        void update();
        
        scriptInterpreter script;
        
        std::vector<fsPoint2i> m_vPoints;
        gameObject* parent;
        
        int m_iJitter;
    };

#endif
