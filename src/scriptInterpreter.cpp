/*
 *  scriptInterpreter.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "scriptInterpreter.h"
#include <string>

scriptInterpreter::scriptInterpreter()
{
	L = lua_open();
	
	std::string str = "print('Hello World')";
	luaL_dostring (L,str.c_str());

}

scriptInterpreter::~scriptInterpreter()
{


	
	lua_close(L);

}

