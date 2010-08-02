objects = main.o CGfxOpenGL.o handleScreen.o handleEvents.o
applelib = -framework Cocoa -framework OpenGL -F/Library/Frameworks -framework SDL -L/opt/local/lib/ -lSDLmain
winlib = `sdl-config --cflags --libs` -lopengl32 -lglu32
linlib = `sdl-config --cflags --libs` -lGL -lGLU

OS = $(shell uname -s)

ifeq ($(OS), Darwin)
target = APPLE
cleantarget = cleanunix
else
ifeq ($(OS), Linux)
target = LINUX
cleantarget = cleanunix
else
target = WINDOWS
cleantarget = cleanwin
endif
endif

all : $(target)

APPLE : $(objects)
	g++ $(objects) $(applelib) -o main

LINUX : $(objects)
	g++ $(objects) $(linlib) -o main

WINDOWS : $(objects)
	g++ $(objects) $(winlib) -o main.exe

main.o : main.cpp general.h CGfxOpenGL.h
	g++ -c main.cpp -o main.o

CGfxOpenGL.o : CGfxOpenGL.cpp general.h CGfxOpenGL.h
	g++ -c CGfxOpenGL.cpp -o CGfxOpenGL.o

handleScreen.o : handleScreen.cpp handleScreen.h general.h
	g++ -c handleScreen.cpp -o handleScreen.o

handleEvents.o: handleEvents.cpp handleEvents.h general.h
	g++ -c handleEvents.cpp -o handleEvents.o

clean : $(cleantarget)

cleanwin :
	rm -rf main.exe $(objects) stdout.txt

cleanunix :
	rm -rf main $(objects) stdout.txt *~
