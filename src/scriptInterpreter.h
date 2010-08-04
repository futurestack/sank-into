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

#include <string>

#ifdef __APPLE__
extern "C" 
{
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
}
#else
extern "C" 
{
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
}
#endif

class scriptInterpreter
{
public:
    void doString(	std::string s );
    void doFile(	std::string s );
    void runTest();
    int getInt( std::string s );
    std::string getString( std::string s );
    float getFloat( std::string s );
    
    
    scriptInterpreter();
    ~scriptInterpreter();
private:
	lua_State* L;

};

#endif
