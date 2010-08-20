// File:   general.h
/****************************************************************************
 * Copyright (c) 2008 Gareth Morgan.                                        *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, distribute with modifications, sublicense, and/or sell       *
 * copies of the Software, and to permit persons to whom the Software is    *
 * furnished to do so, subject to the following conditions:                 *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE ABOVE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,   *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR    *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR    *
 * THE USE OR OTHER DEALINGS IN THE SOFTWARE.                               *
 ****************************************************************************/


#ifndef _GENERAL_H
#define    _GENERAL_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <SDL/SDL.h>
#include "glContext.h"

#define SCREEN_WIDTH  800  
#define SCREEN_HEIGHT 335
#define SCREEN_BPP     32
#define CAM_OFFSET_X 400
#define CAM_OFFSET_Y 200

#define TRUE  1
#define FALSE 0

#define JITTER_MAX 0

void Quit(int returnCode);

extern glContext *renderer;
extern bool done;
extern bool isActive;


#ifndef SANKINTO_CONFIG_H_
#define SANKINTO_CONFIG_H_

#ifndef SCRIPT_USE_LUA
#ifndef SCRIPT_USE_PYTHON
#ifndef SCRIPT_USE_IO

// we are not using the selection from scons, so pick script engine here for now
#define SCRIPT_USE_LUA

#endif
#endif
#endif

#endif



#endif    /* _GENERAL_H */

