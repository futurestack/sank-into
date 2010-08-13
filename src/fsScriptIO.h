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
#include "IoState.h"
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


/* derrida version
 
#include "fsScriptIo.h"

#ifdef SCRIPT_USE_IO

//debug
#include <iostream>


fsScriptIo::fsScriptIo() {
    m_pState = IoState_new();
    IoState_init(m_pState);
}

fsScriptIo::~fsScriptIo() {
    IoState_free(m_pState);
}


IoTag *fsScriptIo::tag(IoState* state, const char* name)
{
    IoTag* tag = IoTag_newWithName_(name);
    tag->state = state;
    tag->cloneFunc = (TagCloneFunc*) rawClone;
    tag->markFunc = (TagMarkFunc*) mark;
    tag->freeFunc = (TagFreeFunc*) free;
    
    return tag;
}

IoObject *fsScriptIo::proto(IoState* state)
{
    IoMethodTable methods[] = {
        {"GetNum", GetNum},
        {"SetNum", SetNum},
        {"CompareWith", CompareWith},
        {NULL, NULL}
    };
    IoObject* self = IoObject_new(state);
    self->tag = tag(state, "fsScriptIo");
    self->data = 0;
    IoObject_addMethodTable_(self, methods);
    return self;
}

void fsScriptIo::addBinding(IoState* state)
{
    IoObject* self = proto(state);
    IoState_registerProtoWithFunc_(state, self, (IoStateProtoFunc*)proto);
    IoObject_setSlot_to_(state->lobby, IOSYMBOL("fsScriptIo"), self);
}

IoObject *fsScriptIo::rawClone(IoObject *self)
{
    IoObject *clone = IoObject_rawClonePrimitive(self);
    if (self->data)
        clone->data = new fsScriptIo(reinterpret_cast<fsScriptIo*>(self->data));
    else
        clone->data = new fsScriptIo;
    return clone;
}

IoObject *fsScriptIo::mark(IoObject *self)
{
    return self;
}

IoObject *fsScriptIo::free(IoObject *self)
{
    if (self->data)
    {
        fsScriptIo* obj = reinterpret_cast<fsScriptIo*>(self->data);
        delete obj;
        self->data = NULL;
    }
    return self;
}

IoObject* fsScriptIo::GetNum(IoObject *self, IoObject *locals, IoMessage *m)
{
    IOASSERT(self->data, "No C++ object");
    fsScriptIo* obj = reinterpret_cast<fsScriptIo*>(self->data);
    
    return IoNumber_newWithDouble_(self->state, obj->GetNum());
    
};


IoObject* fsScriptIo::SetNum(IoObject *self, IoObject *locals, IoMessage *m)
{
    IOASSERT(self->data, "No C++ object");
    fsScriptIo* obj = reinterpret_cast<fsScriptIo*>(self->data);
    
    IOASSERT(IoMessage_argCount(m) == 1, "Wrong number of arguments");
    
    IoObject *arg1 = IoMessage_locals_numberArgAt_(m, locals, 0);
    
    obj->SetNum(IoNumber_asInt(arg1));
    
    return self;
    
};

IoObject* fsScriptIo::CompareWith(IoObject *self, IoObject *locals, IoMessage *m)
{
    IOASSERT(self->data, "No C++ object");
    fsScriptIo* obj = reinterpret_cast<fsScriptIo*>(self->data);
    
    IOASSERT(IoMessage_argCount(m) == 1, "Wrong number of arguments");
    
    IoObject *arg1 = IoMessage_locals_valueArgAt_(m, locals, 0);
    
    // make sure the object is tagged  
    IOASSERT(arg1->tag, "No tag in arg");
    
    // check the tag to make sure it is the right object class
    IOASSERT(strcmp(arg1->tag->name, "fsScriptIo") == 0, "arg not fsScriptIo object");
    
    // check for the actual existence of the C++ object
    IOASSERT(arg1->data, "No C++ object in arg");
    
    fsScriptIo* arg1obj = reinterpret_cast<fsScriptIo*>(arg1->data);
    
    // bool is simulated by returning self or nil
    if (obj->CompareWith(arg1obj))
        return self;
    else
        return IONIL(self);
};

#endif
 
 */
