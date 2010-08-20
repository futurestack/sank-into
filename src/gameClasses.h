/*
 *  gameClasses.h
 *  sank-into
 *
 *  Created by ndrw on 8/20/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef GAME_CLASSES_H_
#define GAME_CLASSES_H_

#include "gameObject.h"
#include "gameEntity.h"

#include <vector>

class gameWeapon : public gameObject
    {
    public:   
        gameWeapon();
        ~gameWeapon();
        
    };

class gameInventory: public gameObject
    {
    public:
        gameInventory();
        ~gameInventory();
        void addObject(gameObject* obj );
        gameObject* getObject(gameObject* obj );
        gameObject* getObject( int index );
        
        void removeObject(gameObject* obj );
        
        std::vector<gameObject*> m_vObjects;
    };

class gamePlayer: public gameEntity
    {
    public:  
        gamePlayer();
        ~gamePlayer();
        
        void update();
        void draw();
        
        float m_fFiringRadius;
        float m_fCurrentAngle;
        
        gameInventory m_pInventory;
    };

#endif
