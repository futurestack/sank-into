/*
 *  scriptInterpreter.cpp
 *  sank-into
 *
 *  Created by hornet on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "scriptInterpreter.h"

scriptInterpreter::scriptInterpreter()
{
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print 'Testing python embedding.  Today is',ctime(time())\n");

}

scriptInterpreter::~scriptInterpreter()
{

    Py_Finalize();


}

