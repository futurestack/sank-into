/*
 *  scriptInterpreter.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "scriptInterpreter.h"
#include <iostream>

#include "lua.hpp"
#include "lauxlib.h"

#include <stdio.h>


scriptInterpreter::scriptInterpreter()
{
	L = lua_open();
}

scriptInterpreter::~scriptInterpreter()
{
	lua_close(L);
}


void scriptInterpreter::doString( std::string s )
{
    int error = luaL_dostring(L, s.c_str());
    if (error) {
        std::cout << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    ++error;
}

void scriptInterpreter::doFile( std::string s )
{
    
    int error = luaL_dofile(L, s.c_str());
    if (error) {
        std::cout << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    ++error;
}

void scriptInterpreter::runTest( )
{
    
    std::cout << "//-testing a file\n";
	doFile("scripts/hello.lua");
    
    std::cout << "//-testing a string\n";
    doString("io.write ('hello again\\n')");
    
    std::cout << "//-putting some vars\n";
    doString("someInt = 5");
    doString("someFloat = 8.1234123");
    doString("someString = 'ffffffffffffffffff'");
    
    std::cout << "//-getting some vars\n";
    std::cout << "someInt:" << getInt("someInt") << std::endl;
    std::cout << "someFloat:" << getFloat("someFloat") << std::endl;
    std::cout << "someString:" << getString("someString") << std::endl;
    
    
}

int scriptInterpreter::getInt( std::string s )
{
	lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    lua_Number result = lua_tonumber(L, -1 );
    lua_pop(L, 1 );
    return result;
}

float scriptInterpreter::getFloat( std::string s )
{
    lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    lua_Number result = lua_tonumber(L, -1 );
    lua_pop(L, 1 );
    
	return result;
}

std::string scriptInterpreter::getString( std::string s )
{
	lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    std::string result = lua_tostring(L, -1 );
    lua_pop(L, 1 );
    
	return result;
}

