#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include <SDL2/SDL.h>


// Get a random number between 0 and 255
int randCol()
{
    return rand() % 255 + 0;
}

int main(int argc, char** argv)
{
    // Initialize the random number generator
    srand (time(NULL));

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Open a 800x600 window and define an accelerated renderer
    SDL_Window* window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Initial renderer color
    SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);

    bool running = true;
    Uint32 old_time = 0, change_color_time = 1000, new_time;
    SDL_Event event;
    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close)
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                const char* key = SDL_GetKeyName(event.key.keysym.sym);
                if (strcmp(key, "Q") == 0 || strcmp(key, "Escape") == 0)
                {
                    running = false;
                }
            }
            else if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }

	    // Clear buffer
	    SDL_RenderClear(renderer);

        // Draw here ...

	    // Switch buffers
	    SDL_RenderPresent(renderer);

	    new_time = SDL_GetTicks();
	    if(new_time - old_time > change_color_time)
        {
            SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);
            old_time = new_time;
        }
    }

    // Release any of the allocated resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

