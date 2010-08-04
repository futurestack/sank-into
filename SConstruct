import os
import sys
from SCons.Script.SConscript import SConsEnvironment

env = Environment(ENV = {'PATH' : os.environ['PATH']})
env = Environment(CPPPATH='src')

flags = '-Wall -pedantic -g'

if sys.platform == 'win32':          #win
    Tool('mingw')(env)
    env.Append(LIBS = ['mingw32','SDLmain', 'SDL', 'OpenGL32', 'GLU32', 'Python'])
elif (sys.platform == 'darwin'):     #mac
    env['FRAMEWORKS'] = ['OpenGL', 'Cocoa', 'SDL']
    env.Append(LIBS = ['Lua']);
    env.Append(CPPPATH = ['/opt/local/include/'])
else:                                #linux
    env.Append(LIBS = ['SDL','GL', 'GLU', 'Python'])

if (sys.platform == 'darwin' ):
	Object('src/SDLMain.o', 'src/SDLMain.m', FRAMEWORKS=env['FRAMEWORKS'])
	Program('sankinto',  ['src/SDLMain.o'] + Glob('src/*.cpp'), FRAMEWORKS=env['FRAMEWORKS'] , LIBS=env['LIBS'], LIBPATH=['.','/opt/local/lib/'], LDFLAGS=env['FRAMEWORKS'], CPPPATH=env['CPPPATH'], CPPFLAGS=flags)
else:
	Program('sankinto',  Glob('src/*.cpp'), LIBPATH=['.'], LIBS=env['LIBS'], LDFLAGS=env['FRAMEWORKS'], CPPFLAGS=flags)

