/*
 *  fsScriptIO.h
 *  sank-into
 *
 *  Created by futurestack on 8/8/10.
 *  Copyright 2010 st4tic_software. All rights reserved.
 *
 */

#include "general.h"

#ifdef SCRIPT_USE_IO

#ifndef FS_SCRIPT_IO_H_
#define FS_SCRIPT_IO_H_

#include "fsScript.h"

#include <stdlib.h>

extern "C"
{
#include "IoVM.h"

}

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


 


/*
 derrida version


#include "config.h"

#ifdef SCRIPT_USE_IO
#ifndef FS_SCRIPT_IO_H_
#define FS_SCRIPT_IO_H_

#include "fsScript.h"

#include <stdlib.h>

extern "C"
{
#include "IoVM.h"
}

class fsScriptIo : public fsScript
    {
    public:	    	
        static IoObject* GetNum(IoObject *self, IoObject *locals, IoMessage *m);
        static IoObject* SetNum(IoObject *self, IoObject *locals, IoMessage *m);
        
        static IoObject* CompareWith(IoObject *self, IoObject *locals, IoMessage *m);
        
        static IoObject* proto(IoState* state);
        
        static IoTag* tag(IoState* state, const char* name);
        
        static IoObject* rawClone(IoObject* self);
        static IoObject* mark(IoObject* self);
        static IoObject* free(IoObject* self);
        
        static void addBinding(IoState* state);
    };

#endif //endif FS_SCRIPT_Io_H_
#endif //endif USE_SCRIPT_Io

//fsScriptIo();
//fsScriptIo(int n);
//fsScriptIo(fsScriptIo* ptr);
//~fsScriptIo();

//int GetNum(void) { return num; }
//int SetNum(int n) { num = n; }

//void runTest();
//void doString(std::string s);
//void doFile(std::string s);	  	    

//private:
//	int num;		
//	IoState * m_pState;		        


*/