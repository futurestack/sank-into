/*
 *  fsScript.h
 *  fsCore_v02_tester
 *
 *  Created by futurestack on 5/22/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#ifndef FS_SCRIPT_H_
#define FS_SCRIPT_H_

#include <string>

class fsScript
	{
	public:
		fsScript() {};
		virtual ~fsScript() {};
		
		virtual void runTest() =0;
		virtual void doString(	std::string s ) =0;
		virtual void doFile(	std::string s ) =0;
        
		virtual int         getInt( std::string s ) =0;
		virtual std::string getString( std::string s ) =0;
		virtual float       getFloat( std::string s ) =0;
        
	};

#endif
