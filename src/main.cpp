// File:   main.cpp
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

#include <cstdio>
#include <cstdlib>
#include "general.h"
#include "handleScreen.h"
#include "handleEvents.h"

glContext *renderer;

bool done = false;
bool isActive = false;

Uint32 gameStart;
Uint32 period;

void Quit(int returnCode) {
  SDL_Quit();
  
  exit(returnCode);
}

void getStats(Uint32 updatePeriod) {
  static Uint32 time = 0;
  static int frames = 0;

  frames++;
  time += updatePeriod;

  if(time >= 5000) {
    float seconds = time / 1000.0;
    float fps = frames / seconds;
    printf("%d frames in %g seconds = %g FPS\n", frames, seconds, fps);
    time = 0;
    frames = 0;
  }
}

int update(Uint32 updatePeriod) {
  float frameTime = updatePeriod / 1000.0;

  renderer->update(frameTime);

  return(TRUE);
}


int render() { // Here goes our drawing code
  renderer->render();
  SDL_GL_SwapBuffers();

  return(TRUE);
}

void init() {
  // main loop variable
  done = false;
  // whether or not the window is active
  isActive = true;
  period = 1000 / 80;
  renderer = new glContext;

  // initialise SDL
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(stderr, "Video startup failed: %s\n",
            SDL_GetError());
    Quit(1);
  }

  initWindowed(); //initialises SDL in windowed mode

  SDL_EnableKeyRepeat(1000, 1);
  
}

int main(int argc, char **argv) {
  Uint32 before, after, diff, wait, overWait = 0, updatePeriod = 0;

  init();

  gameStart = SDL_GetTicks();
  before = gameStart;

  while(!done) { 
    if(isActive) {
      getStats(updatePeriod);
      update(updatePeriod);
      render();
    }
    handleEvents();

    after = SDL_GetTicks();
    diff = after - before + overWait;
    if(period > diff) {
      wait = period - diff;
      SDL_Delay(wait);
      overWait = SDL_GetTicks() - after - wait;
    } else {
      overWait = 0;
    }
    after = SDL_GetTicks();
    updatePeriod = after - before;
    before = after;
  }

  Quit(0);

  return(0);
}
