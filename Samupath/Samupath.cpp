// Samupath.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>	
#include <chrono>
#include <thread>
#include "World.h"
int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	World w = World();
	w.build();
	w.set_samples(16, 2300, 25);
	w.set_resolution(400, 400, .5);
	RawImage r2 = RawImage(w.view_plane, "dragon_converged.bmp");
	//w.render_scene_perspective(r2, 1);
	w.render_scene_perspective(r2, std::thread::hardware_concurrency() - 1);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Elapsed time: " << elapsed.count() << std::endl;
	r2.export_image();
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
