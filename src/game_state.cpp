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
        enemy = new Enemy(x,y, angle);
    }
}

void GameState::gameActions() {
    
}

void GameState::render(SDL_Renderer *renderer) {
    
    player->render(renderer);
    getEnemyPos();
    for( auto &enemy : enemies) {
        if (enemy != NULL) {
            enemy->move();
            enemy->render(renderer);

        }
    }

}

bool GameState::checkEnemies() {
    for (auto &enemy : enemies) {
        if(enemy != NULL)
            return true;
    }
    return false;
}

bool GameState::getEnemyPos() {
    double pX, pY;
    for (auto &projectile : player->projectiles) {
        if (projectile != NULL) {
            pX = projectile->pX;
            pY = projectile->pY;
            for (auto &enemy : enemies) {
                if(enemy != NULL)
                    if(enemy->inBounds(pX, pY)) {
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
