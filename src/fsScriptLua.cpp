/*
 *  fsScriptLua.cpp
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 6/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "fsScriptLua.h"

#ifdef SCRIPT_USE_LUA

//debug
#include <iostream>
static const bool debug_fsScriptLua = false;
fsScriptLua::fsScriptLua()
{
	L = lua_open();
    luaL_openlibs(L);
}

fsScriptLua::~fsScriptLua()
{
	lua_close(L);
}


void fsScriptLua::doString( std::string s )
{
    int error = luaL_dostring(L, s.c_str());
    if (error) {
        std::cout << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    ++error;
}

void fsScriptLua::doFile( std::string s )
{
    
    int error = luaL_dofile(L, s.c_str());
    if (error) {
        std::cout << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
    }
    ++error;
}

void fsScriptLua::runTest( )
{
    std::cout << "fsScriptLua::runTest";

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

int fsScriptLua::getInt( std::string s )
{
	lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    lua_Number result = lua_tonumber(L, -1 );
    lua_pop(L, 1 );
    return result;
}

float fsScriptLua::getFloat( std::string s )
{
    lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    lua_Number result = lua_tonumber(L, -1 );
    lua_pop(L, 1 );
    
	return result;
}

std::string fsScriptLua::getString( std::string s )
{
    std::string result = "";
    if (debug_fsScriptLua) std::cout << "fsScriptLua::getString:" << s << std::endl;


    lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    result = lua_tostring(L, -1 );
    lua_pop(L, 1 );

	return result;
}

void fsScriptLua::getInts(  std::string s  ,std::vector<int>& vec)
{
    if(debug_fsScriptLua) std::cout << "getting some ints." << s << "\n";
    lua_getglobal(L, s.c_str() );    
    lua_pushnil(L);

    //int index = 0;
    while (lua_next(L, -2)) // -2 is the table
    {
        vec.push_back( (int)lua_tonumber(L, -1 ));
      //  index++;
        lua_pop(L, 1 );
    }
    lua_pop(L, 1 );
}

void fsScriptLua::getStrings(  std::string s ,std::vector<std::string>& vec )
{
    
}
void fsScriptLua::getFloats(  std::string s , std::vector<float>& vec )
{
    
}


#endif
