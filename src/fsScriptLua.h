/*
 *  fsScriptLua.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 6/7/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef FS_SCRIPT_LUA_H_
#define FS_SCRIPT_LUA_H_

#include "fsScript.h"

/*#include "lua.h"
extern "C"
{
#include <Lua/lua.h>
}
*/
#include "lua.hpp"

class fsObject;

class fsScriptLua: public fsScript
	{
	public:
		
		static fsScriptLua* Instance();
		void doScript(	std::string s );
		void doFile(	std::string s );
		void runTest( std::string s );
		
		int getInt( std::string s );
		std::string getString( std::string s );
		float getFloat( std::string s );
		
		//fsObject* getObj( std::string s );
		
		//PyObject* m_pObject;

		lua_State* L;
		
	private:
		
		static fsScriptLua* pInstance;
		
		fsScriptLua();
		~fsScriptLua();
		
	};

#endif
