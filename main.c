#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "render.h"
#include "particle.h"

#include <GL/glu.h>  // Needed for gluPerspective and gluLookAt


int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("3D Plate Packing",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
        SDL_WINDOW_OPENGL);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    glewInit();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 5.0, 10.0,   // eye position
          0.0, 0.0, 0.0,    // center of scene
          0.0, 1.0, 0.0);   // up vector

    
    glEnable(GL_DEPTH_TEST);

    init_renderer();
    init_particles();
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // Dark navy blue@!!!!!!!!


    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
        }

        update_particles();
        draw_particles();

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
