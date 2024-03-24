#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "lga_sym.h"
#include <chrono>

//#define TIME_MEASURE
//Screen dimension constants
const int SCREEN_WIDTH = 200;
const int SCREEN_HEIGHT = 300;


int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	SDL_Renderer* gRenderer = NULL;

	int x = 0, y = 480-90, w = 30, h = 60;
	int mov = 1;
	bool key_pressed = false;
	SDL_Keycode kcode = NULL;
	//bool key_released = false;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "LBM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			//screenSurface = SDL_GetWindowSurface( window );
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}

			/*SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer);*/

			LGA_sym lga(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
			lga.init_state_matrix();

			lga.draw();

			/*double test = 1.0/3 * 3.3;
			double test2 = 1.1;
			double test3 = test - test2;
			std::cout << test << " " << test2 << " " << test3;
			if (test3 == 0.0) {
				std::cout<<" BOZE!!";
			}*/

			/*lga.process();

			lga.draw();

			lga.process();

			lga.draw();*/


            SDL_Event e;
			bool quit = false;
			while( quit == false ){ 
				while( SDL_PollEvent( &e ) ){ 
					if( e.type == SDL_QUIT ) quit = true; 
					else if (e.type == SDL_KEYDOWN) {
						key_pressed = true;
						kcode = e.key.keysym.sym;
						//Select surfaces based on key press
						switch (e.key.keysym.sym)
						{
						case SDLK_LEFT:
							break;

						case SDLK_RIGHT:
							break;

						case SDLK_UP:
							break;
						case SDLK_DOWN:
							break;
						case SDLK_ESCAPE:
							quit = true;
							break;

						default:
							break;
						}
					}
					else if (e.type == SDL_KEYUP) {
						key_pressed = false;
					}
				}
#ifdef TIME_MEASURE
				auto start1 = std::chrono::high_resolution_clock::now();
#endif 		
				lga.process();
#ifdef TIME_MEASURE
				auto stop = std::chrono::high_resolution_clock::now();
				std::cout << "total processing time: " << (std::chrono::duration<double>(stop - start1)).count() << std::endl;
#endif

#ifdef TIME_MEASURE
				auto start = std::chrono::high_resolution_clock::now();
#endif
				lga.draw();
#ifdef TIME_MEASURE
				stop = std::chrono::high_resolution_clock::now();
				std::cout << "drawing time: " << (std::chrono::duration<double>(stop - start)).count() << std::endl;

				std::chrono::duration<double> total_time = stop - start1;
				std::cout << "total time: " << total_time.count() << " FPS: " << 1 / total_time.count() << std::endl << std::endl;
#endif

				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	window = NULL;
	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
