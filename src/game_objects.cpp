#include "game_objects.h"
#include "main.h"

GameObject::GameObject() {
    return;
}

Enemy::Enemy(int x, int y) {
    eX = x;
    eY = y;
}


Projectile::Projectile(double xi, double yi, double startX, double startY) {
    x_inc = xi;
    y_inc = yi;
    pX = startX;
    pY = startY;
    //state = s;

    pW = 10;
    pH = 10;
}

Player::Player(std::string path, int x, int y, SDL_Renderer *renderer) {
    
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    pW = loadedSurface->w;
    pH = loadedSurface->h;

    pX = x - (pW/2);
    pY = y - (pH/2);
    degrees = 270;
    
    SDL_FreeSurface(loadedSurface);
    projectile = NULL;
    for (auto &p : projectiles) {
        p = NULL;
    }
    
    pTexture = newTexture;
}

void Projectile::render(SDL_Renderer *renderer) {

    int rounded_x = round(pX);

    int rounded_y = round(pY);
    
    SDL_Rect pBox = { rounded_x, rounded_y, pW, pH };

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);

    SDL_RenderFillRect(renderer, &pBox);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    
    if(checkBounds((int) (pX+x_inc), (int) (pY+y_inc), pW, pH)) {
        pX += x_inc;
        pY += y_inc;
    } else {
        finished = true;
    }
     
}

bool GameObject::checkBounds(int x, int y, int pW, int pH) {

    if((x< (SCREEN_WIDTH - pW) && x > 0) && (y < SCREEN_HEIGHT - pH && y > 0 ))
        return true;
    else
        return false;
}



void Player::render(SDL_Renderer *renderer) {
    int rounded_x = round(pX);
    int rounded_y = round(pY);
    pBox = { rounded_x, rounded_y, pW, pH};
    SDL_Point* point = NULL;
    SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, pTexture, NULL, &pBox, (double) degrees, point, flip);

    for (auto &projectile : projectiles) {
        if ( projectile != NULL) {
            projectile->render(renderer);
            if(projectile->finished == true)
                projectile = NULL;
        }
    }

}

void Player::move( bool pressed[] ) {
    double x_inc = 0;
    double y_inc = 0;
    double rads = degrees * M_PI / 180.0;

    if(pressed[UP]) {
        x_inc = cos(rads) ;
        y_inc = sin(rads) ;
    }

    if(pressed[LEFT])
        degrees -=1;
    if(pressed[RIGHT])
        degrees +=1;

    degrees %= 360;

    if(pX + x_inc < (SCREEN_WIDTH - pW) && pX + x_inc > 0)
        pX += x_inc;
    if(pY + y_inc < SCREEN_HEIGHT - pH && (pY + y_inc) > 0)
        pY += y_inc;
}

void Player::shoot() {
    double rads = degrees * M_PI / 180.0;
    double x_inc = cos(rads) *1.1;
    double y_inc = sin(rads) *1.1; 
    double startX = pX + (pW/2);
    double startY = pY + (pH/2);
    projectiles[index] = new Projectile(x_inc, y_inc, startX, startY);
    index = (index + 1) % 10;
}

void Enemy::render(SDL_Renderer *renderer) {
    int rounded_x = round(eX);

    int rounded_y = round(eY);
    
    SDL_Rect pBox = { rounded_x, rounded_y, eW, eH };

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);

    SDL_RenderFillRect(renderer, &pBox);

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

}

bool Enemy::checkBounds(double x, double y) {
    int pX = round(x);
    int pY = round(y);
    int rX = round(eX);
    int rY = round(eY);
    return pX > rX && pX < (rX + eW) && pY > rY && pY < (rY + eH);
}
