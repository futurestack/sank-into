/*
 *  fsScriptIO.cpp
 *  sank-into
 *
 *  Created by ndrw on 8/8/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */



#include "fsScriptIO.h"

#ifdef SCRIPT_USE_IO

//debug
#include <iostream>

fsScriptIO::fsScriptIO()
{
    m_pState = IoState_new();
    IoState_init(m_pState);
}

fsScriptIO::~fsScriptIO()
{
    IoState_free(m_pState);
}


void fsScriptIO::doString( std::string s )
{

}

void fsScriptIO::doFile( std::string s )
{
    

}

void fsScriptIO::runTest( )
{
    
    std::cout << "fsScriptIO::runTest";
    
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

int fsScriptIO::getInt( std::string s )
{
    return 0;
}

float fsScriptIO::getFloat( std::string s )
{
    return 0.;
}

std::string fsScriptIO::getString( std::string s )
{
    return "";
}

#endif