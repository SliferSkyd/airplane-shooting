#include "SDL_utils.h"

void logSDLError(std::ostream& os, const std::string &msg, bool fatal) {
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) logSDLError(std::cout, "Init Audio", true);
    sound.resize(pathSound.size());
    for (int i = 0; i < pathSound.size(); ++i) {
        sound[i] = Mix_LoadWAV(("data/sound/" + pathSound[i] + ".wav").c_str());
        if (sound[i] == NULL) logSDLError(std::cout, "Can not open Audio", true);
    }
}

void quitSDL() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void waitUntilKeyPressed() {
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e) != 0 && (e.type == SDL_KEYDOWN || e.type == SDL_QUIT)) return;
        SDL_Delay(100);
    }
}

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());;
    SDL_Texture* newTexture = NULL;
    
    if (loadedSurface == NULL) logSDLError(std::cout, "Unable To Load Image!", true);
    Uint32 colorKey = SDL_MapRGB(loadedSurface->format, 0, 255, 255);
    SDL_SetColorKey(loadedSurface, SDL_TRUE, colorKey);
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    
    if (newTexture == NULL) logSDLError(std::cout, "Unable To Creater Texture From Image!", true);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void applyBackground(SDL_Texture* texture) {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void applyTexture(SDL_Texture* texture, int src, int des, int len) {
    SDL_Rect rectSrc, rectDes;
    rectSrc.x = src; rectDes.x = des;
    rectSrc.y = 0; rectDes.y = 0;
    rectSrc.w = len; rectDes.w = len;
    rectSrc.h = SCREEN_HEIGHT; rectDes.h = SCREEN_HEIGHT;
    SDL_RenderCopy(renderer, texture, &rectSrc, &rectDes);
}

void applyTexture(SDL_Texture* texture, int srcX, int srcY, int desX, int desY, int w, int h) {
    SDL_Rect rectSrc, rectDes;
    rectSrc.x = srcX; rectDes.x = desX;
    rectSrc.y = srcY; rectDes.y = desY;
    rectSrc.w = w; rectDes.w = w;
    rectSrc.h = h; rectDes.h = h;
    SDL_RenderCopy(renderer, texture, &rectSrc, &rectDes);
}

void applyTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = x, rect.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void applyTexture(SDL_Texture* texture, int x, int y, double angle) {
    angle = 180 * angle / PI;
    SDL_Rect rect;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.x = x, rect.y = y;
    SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void clrscr() {
    SDL_RenderClear(renderer);
}

void show() {
    SDL_RenderPresent(renderer);
}

int Rand(int L, int R) {
    return rand() % (R - L + 1) + L;   
}

bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2) {
    if (max(rect1.x, rect2.x) + 2 >= min(rect1.x + rect1.w, rect2.x + rect2.w) - 2) return false;
    if (max(rect1.y, rect2.y) + 2 >= min(rect1.y + rect1.h, rect2.y + rect2.h) - 2) return false;
    return true;
}

void messageBox(string message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game Over!", message.c_str(), window);
}

void playSound(int type) {
    Mix_PlayChannel(-1, sound[type], 0);
}

std::vector<bool> randomTrueFalse(int numTrue, int numFalse) {
    int num = numTrue + numFalse;
    std::vector<int> p(num);
    for (int i = 0; i < num; ++i) p[i] = i;
    std::random_shuffle(p.begin(), p.end());
    std::vector<bool> ret(num);
    for (int i = 0; i < num; ++i)
        ret[i] = (p[i] < numTrue);
    return ret;
}