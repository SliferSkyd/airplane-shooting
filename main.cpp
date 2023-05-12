#include "ButtonObject.h"
#include "Level.h"
#include "LastLevel.h"

using namespace std;

int score = 0;

int runIntroScreen() {
    SDL_Texture *background = loadTexture("data/image/bg.png");

    buttonObject *start = new buttonObject();
    start->loadImage("data/image/start_button.png");
    start->setPosition(500, 250);
    start->setSize();

    buttonObject *help = new buttonObject();
    help->loadImage("data/image/help_button.png");
    help->setPosition(500, 325);
    help->setSize();
    
    buttonObject *quit = new buttonObject();
    quit->loadImage("data/image/quit_button.png");
    quit->setPosition(500, 400);
    quit->setSize();
    
    targetObject *aim = new targetObject();
    aim->loadImage("data/image/target.png");
    
    SDL_Event e;
    while (1) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (start->isClicked(e)) return 1;
            if (help->isClicked(e)) {
                system("start https://github.com/SliferSkyd/airplane-shooting.git");
            }
            if (quit->isClicked(e)) exit(1);
            aim->handleInputAction(e);
        }
        start->handleMove(aim->getRect());
        help->handleMove(aim->getRect());
        quit->handleMove(aim->getRect());
        
        clearScreen();
        applyBackground(background);
        
        start->show();
        help->show();
        quit->show();
        aim->show();
        show();
    }
}

int runScreenVictory() {
    playSound(victory, -1);
    SDL_Texture *background = loadTexture("data/image/victory.png");

    buttonObject *replay = new buttonObject();
    replay->loadImage("data/image/replay_victory.png");
    replay->setPosition(800, 450);
    replay->setSize();

    buttonObject *credit = new buttonObject();  
    credit->loadImage("data/image/credit_victory.png");
    credit->setPosition(200, 450);
    credit->setSize();

    targetObject *aim = new targetObject();
    aim->loadImage("data/image/target.png");
    SDL_Event e;

    textObject *scoreText = new textObject();
    scoreText->loadFont("data/font/ComicShark.ttf", 50);
    scoreText->setText(("Your score: " + to_string(score)).c_str());
    scoreText->setColor(textObject::BLUE);
    int opacity = 0;
    int deltaOpacity = 2;
    auto renderTextScore = [&]() {
        opacity += deltaOpacity;
        if (opacity >= 256) opacity = 255, deltaOpacity *= -1;
        else if (opacity < 0) opacity = 0, deltaOpacity *= -1;
        scoreText->show(335, 325, opacity);
    };

    while (1) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (replay->isClicked(e)) {
                haltSound(victory);
                return 1;
            }
            if (credit->isClicked(e)) {
                system("start https://www.facebook.com/huy.hoang.5904");
            }
            aim->handleInputAction(e);
        }
        replay->handleMove(aim->getRect());
        credit->handleMove(aim->getRect());
        clearScreen();
        applyBackground(background);
        renderTextScore();
        replay->show();
        credit->show();
        aim->show();
        show();
    }
}

int runScreenDefeat() {
    playSound(defeat, -1);
    SDL_Texture *background = loadTexture("data/image/defeat.png");

    buttonObject *replay = new buttonObject();
    replay->loadImage("data/image/replay_defeat.png");
    replay->setPosition(800, 450);
    replay->setSize();

    buttonObject *credit = new buttonObject();  
    credit->loadImage("data/image/credit_defeat.png");
    credit->setPosition(200, 450);
    credit->setSize();

    targetObject *aim = new targetObject();
    aim->loadImage("data/image/target.png");
    SDL_Event e;

    textObject *scoreText = new textObject();
    scoreText->loadFont("data/font/ComicShark.ttf", 50);
    scoreText->setText(("Your score: " + to_string(score)).c_str());
    scoreText->setColor(textObject::BLUE);
    int opacity = 0;
    int deltaOpacity = 2;
    auto renderTextScore = [&]() {
        opacity += deltaOpacity;
        if (opacity >= 256) opacity = 255, deltaOpacity *= -1;
        else if (opacity < 0) opacity = 0, deltaOpacity *= -1;
        scoreText->show(335, 325, opacity);
    };

    while (1) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(1);
            if (replay->isClicked(e)) {
                haltSound(defeat);
                return 1;
            }
            if (credit->isClicked(e)) {
                system("start https://www.facebook.com/huy.hoang.5904");
            }
            aim->handleInputAction(e);
        }
        replay->handleMove(aim->getRect());
        credit->handleMove(aim->getRect());
        clearScreen();
        applyBackground(background);
        renderTextScore();
        replay->show();
        credit->show();
        aim->show();
        show();
    }
}

int main(int argc, char ** argv) {
    srand(time(NULL));
    initSDL();
    while (1) {
        score = 0;
        playSound(intro, -1);
        int option = runIntroScreen();
        std::vector<std::pair<int, int>> s = {{1, 1}, {2, 1}, {3, 1}};
        haltSound(intro);
        if (option == 1) {
            int noob = 0;
            for (int i = 0; i < s.size(); ++i) {
                level currentLevel;
                currentLevel.init(score, i + 1, s[i].first, s[i].second, 300, 250);
                if (!currentLevel.run(score)) {
                    noob = 1;
                    break;             
                } 
            }
            if (!noob) {
                lastLevel currentLevel;
                currentLevel.init(score, 300, 1000);
                if (!currentLevel.run(score)) noob = 1;
            }
            if (noob) {
                if (runScreenDefeat()) continue;
            } else {
                if (runScreenVictory()) continue;
            }
            break;
        } 
    } 
    quitSDL();
    return 0;
}