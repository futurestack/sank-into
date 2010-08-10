/*
 *  fsScriptIO.h
 *  sank-into
 *
 *  Created by ndrw on 8/8/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "config.h"

#ifdef SCRIPT_USE_IO
#ifndef FS_SCRIPT_IO_H_
#define FS_SCRIPT_IO_H_

#include "fsScript.h"
#include "IoState.h"

class fsScriptIO : public fsScript
    {
	public:
		
		void runTest();
		void doString(	std::string s );
		void doFile(	std::string s );
        
		int         getInt( std::string s );
		std::string getString( std::string s );
		float       getFloat( std::string s );
        
        fsScriptIO();
		~fsScriptIO();
        
	private:
        
        IoState * m_pState;
        
        
    };

#endif //endif FS_SCRIPT_IO_H_
#endif //endif USE_SCRIPT_IO