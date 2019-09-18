#ifndef game_state
#define game_state
#include "main.h"
#include "game_objects.h"

#include <cstdlib>
#include <ctime>
#include <vector>

#define MAX_ENEMIES 3

class Player;
class Enemy;

class GameState
{
    public:
        GameState(Player *p);
        void gameActions();
        void spawnEnemies();
        bool getEnemyPos();
        bool checkEnemies();
        void render(SDL_Renderer *renderer);
    private:
        Enemy *enemies[MAX_ENEMIES];
        Player *player;
};

#endif
