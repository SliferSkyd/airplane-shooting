#ifndef SDL_UTILS__H
#define SDL_UTILS__H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int MAX_LEN = 4000;
const string WINDOW_TITLE = "Airplane Shooting";
const double PI = acos(-1);

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static std::vector<Mix_Chunk*> sound;
static std::vector<std::string> pathSound = {"laser", "sphere", "explosion", "bomb", "victory", "defeat", "pop", "theme", "menu"};

void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL();
void quitSDL();
void waitUntilKeyPressed();
SDL_Texture* loadTexture(const std::string& path);
void applyBackground(SDL_Texture* texture);
void applyTexture(SDL_Texture* texture, int src, int des, int len);
void applyTexture(SDL_Texture* texture, int srcX, int srcY, int desX, int desY, int w, int h);
void applyTexture(SDL_Texture* texture, int x, int y);
void applyTexture(SDL_Texture* texture, int x, int y, double angle);
void applyTexture(SDL_Texture* texture, SDL_Rect rect);
void clearScreen();
void show();
int Rand(int L, int R);
bool checkCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
bool checkInside(const SDL_Rect& rect, const int& x, const int& y);
void messageBox(string message);
void playSound(int type);
void playSound(int type, int loops);
void haltSound(int type);
std::vector<bool> randomTrueFalse(int numTrue, int numFalse);
void applyText(TTF_Font *font, SDL_Color color, const std::string& s, int x, int y);

#endif