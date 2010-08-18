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

extern "C" 
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

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
    
        void        getInts(    std::string s , std::vector<int>& vec);
		void        getStrings( std::string s ,std::vector<std::string>& vec );
		void        getFloats(  std::string s , std::vector<float>& vec );  
        
        fsScriptLua();
		~fsScriptLua();
        
	private:
        
		lua_State* L;

		
	};

#endif
#endif