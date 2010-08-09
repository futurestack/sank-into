/*
 *  fsScriptLua.cpp
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 6/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "fsScriptLua.h"

//debug
#include <iostream>
static const bool fsDebug_fsScriptLua = false;

/*  obsolete, apparently
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}*/

#include "lua.hpp"

fsScriptLua* fsScriptLua::pInstance = NULL;

fsScriptLua* fsScriptLua::Instance()
{
	if ( pInstance == NULL )
	{
		pInstance = new fsScriptLua();
	}
	return pInstance;
	
	
}

fsScriptLua::fsScriptLua()
{
	if ( fsDebug_fsScriptLua ) runTest( "pants = 102" );
	
    L = lua_open();
	luaL_openlibs(L);

}

fsScriptLua::~fsScriptLua()
{
	lua_close(L);

}

void fsScriptLua::doScript( std::string s )
{
    //luaL_dostring(L,"io.write ('hello World\n')");

    luaL_dostring( L, s.c_str() );
    
}

void fsScriptLua::doFile( std::string s )
{
	
	//FILE* f;
	//f = fopen( s.c_str(), "r" );
    
    luaL_dofile( L , s.c_str() );
    
	//fclose(f);	
}

void fsScriptLua::runTest( std::string s )
{
	std::cout << "//Luatests:---------------------------\n";

    std::cout << "//-testing a file--------------------------\n";
	doFile("/forge/fsCore_v02/src/fsScript/lua/hello.lua");

    std::cout << "//-testing a string--------------------------\n";
    doScript("io.write ('hello again\\n')");

    std::cout << "//-putting some vars--------------------------\n";
    doScript("someInt = 5");
    doScript("someFloat = 8.1234123");
    doScript("someString = 'ffffffffffffffffff'");
    std::cout << "//-getting some vars--------------------------\n";
    std::cout << "someInt:" << getInt("someInt") << std::endl;
    std::cout << "someFloat:" << getFloat("someFloat") << std::endl;
    std::cout << "someString:" << getString("someString") << std::endl;

	std::cout << "//---------------------------\n";

}

int fsScriptLua::getInt( std::string s )
{
	//lua_Number result;
	lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    lua_Number result = lua_tonumber(L, -1 );
    lua_pop(L, 1 );
    
    return result;
}

float fsScriptLua::getFloat( std::string s )
{
    //lua_Number result;
	lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    lua_Number result = lua_tonumber(L, -1 );
    lua_pop(L, 1 );

	return result;
}

std::string fsScriptLua::getString( std::string s )
{
    //lua_Number result;
	lua_pushstring(L, s.c_str() );
    lua_gettable(L,LUA_GLOBALSINDEX);
    std::string result = lua_tostring(L, -1 );
    lua_pop(L, 1 );
    
	return result;
	
}


