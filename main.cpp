#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

SDL_Window* window = NULL;

SDL_Surface* screenSurface = NULL;
SDL_Surface* media = NULL;

bool initSdl(){
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        printf("SDL init error !\n %s\n",SDL_GetError());
        return false;
    }else{
        window = SDL_CreateWindow("Solar Golf", 0, 0, SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            printf("Window could not created !\n %s\n",SDL_GetError());
            return false;
        }
        else{
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return true;
}

bool loadMedia(){
    media = SDL_LoadBMP("hello_world.bmp");
    if(media == NULL){
        printf("Media Load Error !\n %s\n",SDL_GetError());
        return false;
    }
}

void close(){
    SDL_FreeSurface(media);
    media = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}


int main(int argc, char* args[]){
    if(initSdl()){
        if(loadMedia()){
            SDL_BlitSurface(media,NULL,screenSurface,NULL);

            SDL_UpdateWindowSurface(window);
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }
    close();
    return 0;
}
