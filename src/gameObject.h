/*
 *  gameObject.h
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "fsPoint2f.h"

#include <string>
#include "drawChunk.h"

class gameLevel;
class fsRendererGL;

class gameObject
    {
    public:  
        gameObject();
        virtual ~gameObject();
        
        void update();
        void draw( const fsRendererGL& renderer);
        
        fsPoint2f loc;        
        fsPoint2f vel;
        
        fsPoint2f m_pOrigin;
        fsPoint2f m_pBound;
        
        void setName(const std::string name)
        {
            m_sName = name;   
        };
        std::string getName() const
        {
            return m_sName;
        }
        
        void setLevel( gameLevel* level );
        gameLevel* getLevel();
        
        drawChunk m_dChunk;
        bool m_bGravity;
    protected:
        std::string m_sName;
        gameLevel* m_pLevel;
        
    };

#endif
