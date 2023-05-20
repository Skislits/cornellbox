#include "main.h"

int main(int argc, char* argv[]) {
    SDL_Window* window;
    init(window);

    Model model;
    Control control(model);
    View view(model);

    SDL_Event event;
    while (true) {
        control.handleInput();

        view.render(window);
    }

    return 0;
}
