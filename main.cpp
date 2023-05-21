#include "main.h"

int main(int argc, char* argv[]) {
    SDL_Window* window;
    init(window);

    Model model;
    View view(model);
    Control control(model, view);
    
    while (true) {
        control.handleInput();

        view.render(window);
    }

    return 0;
}
