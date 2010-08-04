/*
 *  scriptInterpreter.h
 *  sank-into
 *
 *  Created by hornet on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCRIPT_INTERPRETER_H_
#define SCRIPT_INTERPRETER_H_

#ifdef __APPLE__
#include <Python/Python.h>
#else
#include <Python.h>
#endif

class scriptInterpreter
{
public:
    
    scriptInterpreter();
    ~scriptInterpreter();

};

#endif
