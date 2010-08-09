/*
 *  gameObject.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "gameObject.h"

gameObject::gameObject()
{


}

gameObject::~gameObject()
{


}

void gameObject::update()
{

    loc += vel;
    static float dampen = .9;
    vel *= dampen;
    
}
