/*
 *  gameController.cpp
 *  sank-into
 *
 *  Created by hornet on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "gameController.h"

gameController* gameController::pInstance = 0;

gameController::gameController()
{
    
}

gameController::~gameController()
{
    
    
}

gameController* gameController::getRef()
{
    if ( pInstance == 0 )
        pInstance = new gameController();
        
    return pInstance;

}

