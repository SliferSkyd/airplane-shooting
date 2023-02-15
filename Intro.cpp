#include "Intro.h"

const int WIDTH_OFF = 200;
const int HEIGHT_OFF = 133;
const int WIDTH_ON = 250;
const int HEIGHT_ON = 167;

int intro::run() {
    SDL_Texture *background = loadTexture("data/image/bg.png");
    buttonObject *start = new buttonObject();
    start->loadImage("data/image/start_button.png");
    start->setPosition(100, 100);
    start->setSize(WIDTH_OFF, HEIGHT_OFF, WIDTH_ON, HEIGHT_ON);

    buttonObject *help = new buttonObject();
    help->loadImage("data/image/help_button.png");
    help->setPosition(100, 250);
    help->setSize(WIDTH_OFF, HEIGHT_OFF, WIDTH_ON, HEIGHT_ON);
    
    buttonObject *quit = new buttonObject();
    quit->loadImage("data/image/quit_button.png");
    quit->setPosition(100, 400);
    quit->setSize(WIDTH_OFF, HEIGHT_OFF, WIDTH_ON, HEIGHT_ON);
    
    target *aim = new target();
    aim->loadImage("data/image/target.png");
    SDL_Event e;
    while (1) {
        std::chrono::system_clock::time_point entryTime = std::chrono::system_clock::now();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (start->isClicked(e)) return 1;
            if (help->isClicked(e)) return 0;
            if (quit->isClicked(e)) exit(1);
            aim->handleInputAction(e);
        }
        start->handleMove(aim->getRect());
        help->handleMove(aim->getRect());
        quit->handleMove(aim->getRect());
        
        clearScreen();
        applyBackground(background);
        aim->show();
        start->show();
        help->show();
        quit->show();
        
        show();
    }
}