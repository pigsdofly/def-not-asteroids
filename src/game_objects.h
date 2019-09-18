#ifndef g_obj
#define g_obj
#include "main.h"
#include "game_state.h"

const int ENEMY_DIMENSION = 50;


class GameObject 
{
    public:
        GameObject();

        bool checkBounds(int, int, int, int);
};

class Projectile : public GameObject
{
    public:
        Projectile(double, double, double, double);
        double pX;
        double pY;
        double x_inc;
        double y_inc;
      //  GameState * state;
        void render(SDL_Renderer *renderer);
        int pW;
        int pH;
        int degrees;
        bool finished = false;

};


class Player : public GameObject
{
    public:
        Player(std::string, int, int, SDL_Renderer *renderer);
        void render(SDL_Renderer *renderer);
        void move(bool[]);
        void shoot();
        Projectile *projectiles[MAX_BULLETS];
        double pX;
        double pY;
        int pW;
        int pH;
        int degrees;
    private:
        int index = 0;
        SDL_Texture* pTexture;
        SDL_Rect pBox;

};

class Enemy : public GameObject
{
    public:
        Enemy(int, int, int);
        void render(SDL_Renderer *);
        void move();
        bool inBounds(double, double);
        double eX;
        double eY;
        double x_inc;
        double y_inc;
        int angle;
        int eW = ENEMY_DIMENSION;
        int eH = ENEMY_DIMENSION;
        bool killed = false;
    
};
#endif
