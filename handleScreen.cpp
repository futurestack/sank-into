// File:   handleScreen.cpp
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

#include "handleScreen.h"

SDL_Surface *surface;
const SDL_VideoInfo *videoInfo;

int fullScreenVideoFlags;
int windowedVideoFlags;
bool isFullScreen = false;

// function to reset our viewport after a window resize
int updateProjection(int width, int height) {
  renderer->setupProjection(width, height);

  return(TRUE);
}

void toggleFullscreen() {
  if(isFullScreen) {
    surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
			       SCREEN_BPP, windowedVideoFlags);
    if (!surface) {
      fprintf(stderr, "Could not get a surface after resize: %s\n", SDL_GetError());
      Quit(1);
    }
    updateProjection(SCREEN_WIDTH, SCREEN_HEIGHT);
  } else {
    surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
			       SCREEN_BPP, fullScreenVideoFlags);
    updateProjection(SCREEN_WIDTH, SCREEN_HEIGHT);
  }

  isFullScreen = !isFullScreen;
}

void initVideoFlags() {
  // the flags to pass to SDL_SetVideoMode
  windowedVideoFlags  = SDL_OPENGL; // Enable OpenGL in SDL
  windowedVideoFlags |= SDL_GL_DOUBLEBUFFER; // Enable double buffering
  windowedVideoFlags |= SDL_HWPALETTE; // Store the palette in hardware
  windowedVideoFlags |= SDL_RESIZABLE; // Enable window resizing

  // This checks to see if surfaces can be stored in memory
  if(videoInfo->hw_available)
    windowedVideoFlags |= SDL_HWSURFACE;
  else
    windowedVideoFlags |= SDL_SWSURFACE;

  if(videoInfo->blit_hw)
    windowedVideoFlags |= SDL_HWACCEL;

  // the flags to pass to SDL_SetVideoMode if in fullScreen
  fullScreenVideoFlags  = SDL_OPENGL;
  fullScreenVideoFlags |= SDL_GL_DOUBLEBUFFER;
  fullScreenVideoFlags |= SDL_HWPALETTE;
  fullScreenVideoFlags |= SDL_FULLSCREEN;

  if(videoInfo->hw_available)
    fullScreenVideoFlags |= SDL_HWSURFACE;
  else
    fullScreenVideoFlags |= SDL_SWSURFACE;
  
  if(videoInfo->blit_hw)
    fullScreenVideoFlags |= SDL_HWACCEL;
}



int initGL() { // general OpenGL initialization function
  renderer->init();

  return(TRUE);
}

void initGeneral() {
   // Fetch the video info
  videoInfo = SDL_GetVideoInfo();

  if(!videoInfo) {
    fprintf(stderr, "Video query failed: %s\n",
            SDL_GetError());
    Quit(1);
  }

  initVideoFlags();

  // Sets up OpenGL double buffering
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void initWindowed() {
  initGeneral();

  // get a SDL surface
  surface = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
                             windowedVideoFlags);

  // Verify there is a surface
  if(!surface) {
    fprintf(stderr,  "Video mode set failed: %s\n", SDL_GetError());
    Quit(1);
  }
  
  // initialize OpenGL
  if(initGL() == FALSE) {
    fprintf(stderr, "Could not initialize OpenGL.\n");
    Quit(1);
  }

  updateProjection(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void resizeWindow(int width, int height) {
  // handle resize event
  surface = SDL_SetVideoMode(width, height, SCREEN_BPP, windowedVideoFlags);
  if (!surface) {
    fprintf(stderr, "Could not get a surface after resize: %s\n", SDL_GetError());
    Quit(1);
  }
  updateProjection(width, height);
}
