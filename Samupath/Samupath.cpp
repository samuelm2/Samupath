// Samupath.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>	
#include <chrono>
#include <thread>
#include <SDL.h>
#include "World.h"

//void window_loop() {
//	bool quit = false;
//	while (!quit) {
//		SDL_Event event;
//		while (SDL_PollEvent(&event)) {
//			/* handle your event here */
//
//		   //User requests quit
//			if (event.type == SDL_QUIT)
//				quit = true;
//		}
//	}
//}

int main(int argc, char* argv[])
{
	glm::vec3 res = glm::vec3(400, 400, .05);

	SDL_Window *window;  

	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
	window = SDL_CreateWindow("Samupath", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, res.x, res.y, 0);
	//SDL_RenderClear(renderer);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window or renderer: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	SDL_UpdateWindowSurface(window);


	
	auto start = std::chrono::high_resolution_clock::now();
	World w = World();
	w.build();
	w.set_samples(16, 64, 16);
	w.set_resolution((int)res.x, (int)res.y, res.z);
	RawImage r2 = RawImage(w.view_plane, window, "roughmetal_medium_high.bmp");
	//w.render_scene_perspective(r2, 2);
	w.render_scene_perspective(r2, 11);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << std::endl;
	r2.export_image();

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
