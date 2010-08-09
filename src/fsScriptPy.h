/*
 *  fsScriptPy.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */


#ifdef __FS_SCRIPT_PY__
#ifndef FS_SCRIPT_PY_H_
#define FS_SCRIPT_PY_H_

#include "fsScript.h"

#include <Python/Python.h>

class fsObject;

class fsScriptPy: public fsScript
{
public:
	
	static fsScriptPy* Instance();
	void doScript(	std::string s );
	void doFile(	std::string s );
	void runTest( std::string s );
	
	int getInt( std::string s );
	std::string getString( std::string s );
	float getFloat( std::string s );
	
	//fsObject* getObj( std::string s );
	
	PyObject* m_pObject;
	
private:
	
	static fsScriptPy* pInstance;
	
	fsScriptPy();
	~fsScriptPy();
	
};

#endif // end header def
#endif // end __FS_SCRIPT_PY__
