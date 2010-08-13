/*
 *  fsScriptLua.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 6/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "general.h"

#define USE_FRAMEWORK
#ifdef SCRIPT_USE_LUA

#ifndef FS_SCRIPT_LUA_H_
#define FS_SCRIPT_LUA_H_

#include "fsScript.h"


//#define USE_FRAMEWORK
#ifdef __APPLE__
extern "C" 
{
    
#ifdef USE_FRAMEWORK
    //framework
#include <Lua/lua.hpp>
#include <Lua/lauxlib.h>
#include <Lua/lualib.h>
#else
    //lib
#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>
#endif
    
}
#else
extern "C" 
{
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
}
#endif

class fsObject;

class fsScriptLua: public fsScript
	{
	public:
		
		void runTest();
		void doString(	std::string s );
		void doFile(	std::string s );
        
		int         getInt( std::string s );
		std::string getString( std::string s );
		float       getFloat( std::string s );
    
        fsScriptLua();
		~fsScriptLua();
        
	private:
        
		lua_State* L;

		
	};

#endif
#endif