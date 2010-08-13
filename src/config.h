/*
 *  general.h
 *  sank-into
 *
 *  Created by futurestack on 8/9/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

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
