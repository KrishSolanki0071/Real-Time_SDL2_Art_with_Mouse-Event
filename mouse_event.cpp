#include<vector>
#include<SDL.h>
#include<iostream>
#undef main

int main()
{
    //SDL Init Stuff
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(2000, 2000, 0, &window, &renderer);
    SDL_Event event; 


    //Making a single point to update every frame
    //
    SDL_Point current;


    //vector of all points clicked so far
    //
    std::vector<SDL_Point> vector_of_points;

    //the type of connection you want i.e 1 point to 1 point or doing connections to many to many
    int type = 0;


    //Main Loop

    while(true)
    {
        while(SDL_PollEvent(&event))
        {   
            //handle closing the window

            if(event.type == SDL_QUIT)
            {
                SDL_QUIT;
                exit(0);
            }
            //store the x and y coordinates of the mouse where left button is clicked of the mouse
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                int x,y;
                auto button = SDL_GetMouseState(&x, &y);  //getting the x and y coordinates of mouse cursor
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    vector_of_points.push_back({x,y});  //storing the coordinates
                }
            }

            //Get the current mouse pointer location per frame
            if(event.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&current.x, &current.y);
            }

            //if the 'C' button of the keyboard is pressed to CLEAR THE CONTAINER
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_c)
            {
                vector_of_points.clear();
            }

            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_1)
            {
                type = 1;
            }
            
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_2)
            {
                type = 0;
            }

        }


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        //SDL_RenderDrawLines(renderer, vector_of_points.data(), vector_of_points.size());

        if(type == 0 )
        {
            for(auto point : vector_of_points)
            {
                for(auto point2 : vector_of_points)
                {
                    SDL_RenderDrawLine(renderer, point.x, point.y, point2.x, point2.y);
                }        
            }
        }

        if(type == 1)
        {
            SDL_RenderDrawLines(renderer,vector_of_points.data(), vector_of_points.size());
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }

    return 0;
}