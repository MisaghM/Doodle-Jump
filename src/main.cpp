#define SDL_MAIN_HANDLED

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "RSDL/rsdl.hpp"
#include "consts.hpp"
#include "system.hpp"

void gameLoop(Window* win) {
    //gameprogrammingpatterns.com/game-loop.html
    
    const int MAX_LAG_UPDATE = 1000;
    System system(win);

    unsigned currTime = SDL_GetTicks();
    unsigned prevTime = currTime;
    unsigned turn = 0;
    unsigned lag = 0;
    
    while (true) {
        system.deltaTime = (turn + 1) > 2 ? 16 : 17;
        lag += currTime - prevTime;
        prevTime = currTime;

        if (lag > system.deltaTime * MAX_LAG_UPDATE) lag = system.deltaTime * MAX_LAG_UPDATE;

        while (lag >= system.deltaTime) {
            lag -= system.deltaTime;
            system.deltaTime = (++turn) > 2 ? (turn = 0, 16) : 17;
            if (!system.update()) goto endGameLoop;
        }

        win->clear();
        system.draw();
        win->update_screen();

        currTime = SDL_GetTicks();
        //delay time for 60fps: (17/17/16 ms delay) - (time passed for game update)
        int delayTime = system.deltaTime - (currTime - prevTime);
        if (delayTime < 0) delayTime = 0;
        currTime += delayTime;

        delay(delayTime);
    }
endGameLoop:;
}

int main() {
    try {
        Window win(consts::WIN_WIDTH, consts::WIN_HEIGHT, consts::WIN_NAME);
        win.set_icon(consts::ICON);
        gameLoop(&win);
    }
    catch (const std::invalid_argument& ex) {
        std::cerr << "Invalid argument exception thrown: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error& ex) {
        std::cerr << "Runtime error exception thrown: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}