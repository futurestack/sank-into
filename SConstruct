import os
env = Environment(ENV = {'PATH' : os.environ['PATH']})

flags = '-Wall -pedantic -g'

#libs = ['SDL']
#Library('moag', Glob('moag*.c'), CPPFLAGS=flags)

from SCons.Script.SConscript import SConsEnvironment

env = Environment(CPPPATH='src')
env['FRAMEWORKS'] = ['OpenGL', 'Foundation', 'Cocoa', 'SDL', 'SDL_net'] 

Object('src/SDLMain.o', 'src/SDLMain.m', FRAMEWORKS=env['FRAMEWORKS'])
Program('sankinto',  ['src/SDLMain.o'] + Glob('src/*.cpp'), FRAMEWORKS=env['FRAMEWORKS'],LIBPATH=['.','/opt/local/lib/','/System/Library/Frameworks/'], LDFLAGS=env['FRAMEWORKS'], CPPFLAGS=flags)


