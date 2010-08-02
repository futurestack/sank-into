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
	g++ $(objects) $(applelib) -o sankinto

LINUX : $(objects)
	g++ $(objects) $(linlib) -o sankinto

WINDOWS : $(objects)
	g++ $(objects) $(winlib) -o sankinto.exe

main.o : src/main.cpp src/general.h src/CGfxOpenGL.h
	g++ -c src/main.cpp -o main.o

CGfxOpenGL.o : src/CGfxOpenGL.cpp src/general.h src/CGfxOpenGL.h
	g++ -c src/CGfxOpenGL.cpp -o CGfxOpenGL.o

handleScreen.o : src/handleScreen.cpp src/handleScreen.h src/general.h
	g++ -c src/handleScreen.cpp -o handleScreen.o

handleEvents.o: src/handleEvents.cpp src/handleEvents.h src/general.h
	g++ -c src/handleEvents.cpp -o handleEvents.o

clean : $(cleantarget)

cleanwin :
	rm -rf main.exe $(objects) stdout.txt

cleanunix :
	rm -rf main $(objects) stdout.txt *~
