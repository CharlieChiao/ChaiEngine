#include <iostream>
#include "glm/glm.hpp"
#include "SDL3/SDL.h"

int main(int argc, char* argv[])
{
    
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "EEEEEEEEEEEEEEEE";
    }
    SDL_Window* window = SDL_CreateWindow("123",400,400, SDL_WINDOW_OPENGL);
    SDL_SetWindowFocusable(window, true);
    SDL_SetWindowInputFocus(window);
    bool Quit = false;
    SDL_Event event;
    while(!Quit)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                Quit = true;
            }
            else if(event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP || event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                glm::vec2 pos;
                SDL_GetMouseState(&pos.x,&pos.y);
                //SDL_SetWindowGrab(window, SDL_TRUE);
                SDL_SetRelativeMouseMode(SDL_TRUE);
                std::cout << pos.x << std::endl;
            }
            const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
            SDL_Scancode scancode = SDL_GetScancodeFromKey(event.key.keysym.sym);
            if(keyboardState[scancode])
            {
                std::cout << "Keys" << std::endl;
            }
        }
    }
    return 0;
}
