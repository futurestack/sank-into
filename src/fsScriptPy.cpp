/*
 *  fsScriptPy.cpp
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */


#include "fsScriptPy.h"
#ifdef __FS_SCRIPT_PY__


//debug
#include <iostream>
static const bool fsDebug_fsScriptPy = false;

fsScriptPy* fsScriptPy::pInstance = NULL;

fsScriptPy* fsScriptPy::Instance()
{
	if ( pInstance == NULL )
	{
		pInstance = new fsScriptPy();
	}
	return pInstance;
	
	
}

fsScriptPy::fsScriptPy()
{
	Py_Initialize();
	
	if ( fsDebug_fsScriptPy ) runTest( "pants = 102" );
}

fsScriptPy::~fsScriptPy()
{
	Py_Finalize();

}

void fsScriptPy::doScript( std::string s )
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

void fsScriptPy::runTest( std::string s )
{
	std::cout << "//pythontests:---------------------------\n";
	
    std::cout << "//-testing a file--------------------------\n";
	doFile("/forge/fsCore_v02/src/fsScript/py/hello.py");
	
    std::cout << "//-testing a string--------------------------\n";
    doScript("print 'hello again'");
	
    std::cout << "//-putting some vars--------------------------\n";
    doScript("someInt = 5");
    doScript("someFloat = 8.1234123");
    doScript("someString = 'ffffffffffffffffff'");
    std::cout << "//-getting some vars--------------------------\n";
	
    std::cout << "someInt:" << getInt("someInt") << std::endl;
    std::cout << "someFloat:" << getFloat("someFloat") << std::endl;
    std::cout << "someString:" << getString("someString") << std::endl;
	
	std::cout << "someInt:" << getInt("fileFooInt") << std::endl;
    std::cout << "someFloat:" << getFloat("fileFooFloat") << std::endl;
    std::cout << "someString:" << getString("fileFooString") << std::endl;
	
	std::cout << "//---------------------------\n";

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
