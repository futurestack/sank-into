import os
import sys
from SCons.Script.SConscript import SConsEnvironment
env = Environment(ENV = {'PATH' : os.environ['PATH']})
env = Environment(CPPPATH='src')
print sys.platform

flags = '-Wall -pedantic -g '
ldflags = '-lSDL -lLua '

#scriptlanguage.  options are python, io, lua
scriptlanguage = 'io'


use_lua_framework = False;

#os specific stuff

if scriptlanguage == 'python':
    print 'python.'
    flags += " -DSCRIPT_USE_PYTHON"

if scriptlanguage == 'lua':
    print 'lua.'
    flags += " -DSCRIPT_USE_LUA"

if scriptlanguage == 'io':
    print 'io'
    flags += " -DSCRIPT_USE_IO"

if sys.platform == 'win32':         #win
    Tool('mingw')(env)
    env.Append(LIBS = ['mingw32','SDLmain', 'SDL', 'OpenGL32', 'GLU32', 'Python'])
    
if sys.platform == 'darwin':        #mac
    env['FRAMEWORKS'] = ['OpenGL', 'Cocoa', 'SDL']
    env.Append(CPPPATH = ['/opt/local/include/'])
    
    if scriptlanguage == 'lua':
        if use_lua_framework == 'true': 
            flags += " -DUSE_FRAMEWORK"
            env.Append(FRAMEWORKS = ['Lua'])
        else:
            env.Append(LIBS = ['Lua']);
    if scriptlanguage == 'io':
        env.Append(LIBS = ['iovmall.a']);
        env.Append(CPPPATH=['/opt/local/include/io'])
    if scriptlanguage == 'python':
        env.Append(LIBS = ['Python']);
            
if sys.platform == 'linux2':        #linux
    env.Append(LIBS = ['SDL','GL', 'GLU', 'lua5.1'])
    env.Append(CPPPATH = ['/usr/include/'])
    env.Append(CPPPATH = ['/usr/include/lua5.1'])

if sys.platform == 'darwin':
    Object( 'src/SDLMain.o', 'src/SDLMain.m', FRAMEWORKS=env['FRAMEWORKS'] )
    Program( 'sankinto-osx', ['src/SDLMain.o'] + Glob('src/*.cpp'), FRAMEWORKS=env['FRAMEWORKS'] , LIBS=env['LIBS'], LIBPATH=['.','/opt/local/lib/'], LDFLAGS=env['FRAMEWORKS'], CPPPATH=env['CPPPATH'], CPPFLAGS=flags)

if sys.platform == 'win32':
    Program( 'sankinto-win', Glob('src/*.cpp'), FRAMEWORKS=env['FRAMEWORKS'] , LIBS=env['LIBS'], CPPPATH=env['CPPPATH'], CPPFLAGS = flags)

if sys.platform == 'linux2':
    Program( 'sankinto-linux', Glob('src/*.cpp'), FRAMEWORKS=env['FRAMEWORKS'] , LIBS=env['LIBS'], CPPPATH=env['CPPPATH'], CPPFLAGS = flags)