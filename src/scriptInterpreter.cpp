/*
 *  scriptInterpreter.cpp
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "scriptInterpreter.h"

//debug
#include <cassert>

#include <iostream>
#include <stdio.h>

#include "general.h"

#include "fsScript.h"

#ifdef SCRIPT_USE_LUA
#include "fsScriptLua.h"
#endif

#ifdef SCRIPT_USE_PYTHON
    #include "fsScriptPy.h"
#endif

#ifdef SCRIPT_USE_IO
    #include "fsScriptIO.h"
#endif

scriptInterpreter::scriptInterpreter()
:
m_pScript(NULL)
{
#ifdef SCRIPT_USE_LUA
    m_pScript = new fsScriptLua;
#endif
    
#ifdef SCRIPT_USE_PYTHON    
    m_pScript = new fsScriptPy();
#endif
    
#ifdef SCRIPT_USE_IO
    m_pScript = new fsScriptIO;
#endif
    
}

scriptInterpreter::~scriptInterpreter()
{
    delete m_pScript;
    
}
void scriptInterpreter::doString( std::string s )
{
	
    m_pScript->doString(s);
}

void scriptInterpreter::doFile( std::string s )
{
    m_pScript->doFile(s);
}

void scriptInterpreter::runTest()
{
    assert(m_pScript);
    m_pScript->runTest();
}

int scriptInterpreter::getInt( std::string s )
{
    return m_pScript->getInt( s );

}

float scriptInterpreter::getFloat( std::string s )
{
    return m_pScript->getFloat( s );

}

std::string scriptInterpreter::getString( std::string s )
{
	
	return m_pScript->getString( s );
}


void scriptInterpreter::getInts( std::string s , std::vector<int>& vec )
{
    m_pScript->getInts( s, vec);
    
}


void scriptInterpreter::getFloats( std::string s , std::vector<float>& vec )
{
    m_pScript->getFloats( s, vec);

}

void scriptInterpreter::getStrings( std::string s , std::vector<std::string>& vec )
{
    m_pScript->getStrings( s, vec);

}



