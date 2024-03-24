#pragma once

#ifndef LGA_SYM_H
#define LGA_SYM_H

#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include <vector>
#include <unordered_set>
#include "my_utilities.h"

//#define TIME_MEASURE

class LGA_sym {
	SDL_Renderer* gRenderer;
	const int width;
	const int height;
	const int threads_num = 8;

	
	double*** state_matrix;
	double*** new_state_matrix;
	int** border_matrix;

	std::unordered_set<std::string> border_set;
	std::unordered_set<std::string> to_process;

	int border_size = 2;
	
	int hole_size = 100;
	int hole_y_pos = 80;
	int hole_x_pos = 80;

	SDL_Color border_color = { 0xFF, 0xFF, 0xFF, 0xFF };
	SDL_Color particle_color = { 0x00, 0xFF, 0x00, 0xFF };
	SDL_Color clear_color = { 0x00, 0x00, 0x00, 0xFF };

public:
	LGA_sym(SDL_Renderer* gRenderer, int width, int height);

	void init_state_matrix();

	void add_to_process_set(int i, int j, int state[5]);

	void process();

	void process_step(int id);

	void draw();

	~LGA_sym();
	

};

#endif