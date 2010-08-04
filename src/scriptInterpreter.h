/*
 *  scriptInterpreter.h
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCRIPT_INTERPRETER_H_
#define SCRIPT_INTERPRETER_H_

#ifdef __APPLE__
extern "C" {
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
}
#else
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
#endif

class scriptInterpreter
{
public:
    
    scriptInterpreter();
    ~scriptInterpreter();
	lua_State* L;

};

#endif
