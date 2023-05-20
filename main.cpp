#include "main.h"

int main(int argc, char* argv[]) {
    SDL_Window* window;
    init(window);

    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {}

        SDL_GL_SwapWindow(window);
    }

    return 0;
}
