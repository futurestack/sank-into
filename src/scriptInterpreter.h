/*
 *  scriptInterpreter.h
 *  sank-into
 *
 *  Created by futurestack on 8/3/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SCRIPT_INTERPRETER_H_
#define SCRIPT_INTERPRETER_H_

#include <string>
#include <vector>

class fsScript;

class scriptInterpreter
{
public:

    void runTest();
    void doString(	std::string s );
    void doFile(	std::string s );
    
    int         getInt( std::string s );
    std::string getString( std::string s );
    float       getFloat( std::string s );
    void getInts( std::string s , std::vector<int>& vec );
    void getFloats( std::string s , std::vector<float>& vec );
    void getStrings( std::string s , std::vector<std::string>& vec );
    
    scriptInterpreter();
    ~scriptInterpreter();
private:
    
    fsScript* m_pScript;

    
};

#endif
