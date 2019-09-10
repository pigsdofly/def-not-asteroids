#include "game_state.h"

GameState::GameState(Player *p) {
    player = p;
    spawnEnemies();
}

void GameState::spawnEnemies() {
    int x = 0;
    int y = 0;
    int angle = 0;
    srand(time(0));
    for( auto &enemy : enemies ) {
        do {
            x = rand() % SCREEN_WIDTH;
            y = rand() % SCREEN_HEIGHT;
        } while (x != player->pX && y != player->pY);
        angle = rand() % 360;
        enemy = new Enemy(x,y);
    }
}

void GameState::getState() {
    
}

void GameState::render(SDL_Renderer *renderer) {
    
    getEnemyPos();
    for( auto &enemy : enemies) {
        if (enemy != NULL)
            enemy->render(renderer);
    }

}

bool GameState::checkEnemies() {
    return true;
}

bool GameState::getEnemyPos() {
    double pX, pY;
    for (auto &projectile : player->projectiles) {
        if (projectile != NULL) {
            pX = projectile->pX;
            pY = projectile->pY;
            for (auto &enemy : enemies) {
                if(enemy != NULL)
                    if(enemy->checkBounds(pX, pY)) {
                        std::cout<<"Its a hit!"<<std::endl;
                        projectile->finished = true;
                        enemy->killed = true;
                        enemy = NULL;
                    }
            }
        }
    }
    return true;
}   
