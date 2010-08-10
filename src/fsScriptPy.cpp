/*
 *  fsScriptPy.cpp
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */


#include "fsScriptPy.h"

#ifdef SCRIPT_USE_PYTHON


//debug
#include <iostream>
static const bool fsDebug_fsScriptPy = false;


fsScriptPy::fsScriptPy()
{
	Py_Initialize();
	
	if ( fsDebug_fsScriptPy ) runTest();
}

fsScriptPy::~fsScriptPy()
{
	Py_Finalize();

}

void fsScriptPy::doString( std::string s )
{
	
	if ( fsDebug_fsScriptPy ) std::cout << ">>>" << s << "\n";
	PyRun_SimpleString( s.c_str() );
}

void fsScriptPy::doFile( std::string s )
{
	
	FILE* f;
	f = fopen( s.c_str(), "r" );
    
	PyRun_SimpleFile( f , s.c_str() );
	
	fclose(f);

}

void fsScriptPy::runTest()
{
    std::cout << "fsScriptPy::runTest";
    
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

int fsScriptPy::getInt( std::string s )
{
	
	PyObject* evalModule;
	PyObject* evalDict;
	PyObject* evalVal;
	int retInt;
	
	evalModule = PyImport_AddModule( (char*)"__main__" );
	evalDict = PyModule_GetDict( evalModule );
	evalVal = PyDict_GetItemString( evalDict, s.c_str() );
	
	if( evalVal == NULL )
	{
		PyErr_Print();

	}else{
		retInt = PyInt_AsLong( evalVal );	
	}
	//std:: cout << "getInt:" << retInt;
	
	//return 777;
	return retInt;

}

float fsScriptPy::getFloat( std::string s )
{
	
	PyObject* evalModule;
	PyObject* evalDict;
	PyObject* evalVal;
	float retFloat;
	
	evalModule = PyImport_AddModule( (char*)"__main__" );
	evalDict = PyModule_GetDict( evalModule );
	evalVal = PyDict_GetItemString( evalDict, s.c_str() );
	
	if( evalVal == NULL )
	{
		PyErr_Print();

	}else{
		retFloat = PyFloat_AsDouble( evalVal );	
	}

	return retFloat;
	
}

std::string fsScriptPy::getString( std::string s )
{
	
	 PyObject* evalModule;
	 PyObject* evalDict;
	 PyObject* evalVal;
	 char* retString;
	 
	 //PyRun_SimpleString("result = 'foo' + 'bar'");
	 
	 evalModule = PyImport_AddModule( (char*)"__main__" );
	 evalDict = PyModule_GetDict( evalModule );
	 evalVal = PyDict_GetItemString( evalDict, s.c_str() );
	 
	 if( evalVal == NULL )
	 {
		 PyErr_Print();

	 }else{
		 retString = PyString_AsString( evalVal );	
	 }
	 

	std::string result = retString;
	return result;
	
}

#endif
