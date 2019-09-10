#include "main.h"
#include "game_objects.h"
#include "game_state.h"


SDL_Surface* loadSurface(std::string path);
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;


bool init()
{
    bool success = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL error\n");
        success = false;
    } else {
        window = SDL_CreateWindow("Definitely Not Asteroids", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("Window could not be created!");
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                printf("Renderer could not be created\n");
                success = false;
            } else {
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);


            }
            screenSurface = SDL_GetWindowSurface(window);
        }
    }

    return success;
}

void close()
{
    SDL_FreeSurface( screenSurface );
    screenSurface = NULL;

    SDL_DestroyWindow( window );
    window = NULL;

    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char* argv[])
{
    if ( !init() )
    {
        printf("Failed to initialise\n");
    }
    else {
        bool quit = false;

        SDL_Event e;

        int x_axis = SCREEN_WIDTH/2;
        int y_axis = SCREEN_HEIGHT/2;
        bool forward = true;
        int square_width = SCREEN_WIDTH/10;
        int square_height = SCREEN_HEIGHT/10;
        int x_iter, y_iter;
        bool pressed[] = {false, false, false, false};
        Player p = Player("assets/Triangle.png",x_axis, y_axis, renderer);
        GameState *state = new GameState(&p);
        p.makePlayer(renderer);
        bool shooting = false;
        while(!quit) {

            while(SDL_PollEvent( &e ) != 0) {
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if(e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_UP)
                        pressed[UP] = true;
                    else if (e.key.keysym.sym == SDLK_DOWN)
                        pressed[DOWN] = true;
                    if (e.key.keysym.sym == SDLK_LEFT)
                        pressed[LEFT] = true;
                    else if (e.key.keysym.sym == SDLK_RIGHT)
                        pressed[RIGHT] = true;
                    if (e.key.keysym.sym == SDLK_SPACE)
                        shooting = true;
                }
                else if(e.type == SDL_KEYUP) {
                    if (e.key.keysym.sym == SDLK_UP)
                        pressed[UP] = false;
                    else if (e.key.keysym.sym == SDLK_DOWN)
                        pressed[DOWN] = false;
                    if (e.key.keysym.sym == SDLK_LEFT)
                        pressed[LEFT] = false;
                    else if (e.key.keysym.sym == SDLK_RIGHT)
                        pressed[RIGHT] = false;
                }

            }
            
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);
            
            if(shooting) {
                p.shoot();
                shooting = false;
            }

            p.move(pressed);

            p.makePlayer(renderer);
            state->render(renderer);

            SDL_RenderPresent(renderer);
        }

    }

    close();
    return 0;
}
