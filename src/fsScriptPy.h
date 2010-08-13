/*
 *  fsScriptPy.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/9/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "general.h"

#ifdef SCRIPT_USE_PYTHON

#ifndef FS_SCRIPT_PY_H_
#define FS_SCRIPT_PY_H_

#include "fsScript.h"

#include <Python/Python.h>

class fsScriptPy: public fsScript
{
public:
    
    fsScriptPy();
    ~fsScriptPy();
    
    void runTest();
    void doString(	std::string s );
    void doFile(	std::string s );
    
    int         getInt( std::string s );
    std::string getString( std::string s );
    float       getFloat( std::string s );
    
private:
    
	PyObject* m_pObject;

	
};

#endif // end header def
#endif // end SCRIPT_USE_PYTHON
