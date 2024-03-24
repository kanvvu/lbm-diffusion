#include "lga_sym.h"

LGA_sym::LGA_sym(SDL_Renderer* gRenderer, int width, int height) : gRenderer(gRenderer), width(width), height(height) {

	state_matrix = new double** [width];
	new_state_matrix = new double** [width];
	border_matrix = new int* [width];
	for (int i = 0; i < width; i++) {
		state_matrix[i] = new double* [height];
		new_state_matrix[i] = new double* [height];
		border_matrix[i] = new int[height];
		for (int j = 0; j < height; j++) {
			state_matrix[i][j] = new double[6];
			new_state_matrix[i][j] = new double[6];
			border_matrix[i][j] = 0;

			for (int k = 0; k < 6; k++) {
				state_matrix[i][j][k] = 0;
				new_state_matrix[i][j][k] = 0;
			}
		}
	}
}

void LGA_sym::init_state_matrix() {
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < border_size; j++)
		{
			set_arr_3d_6(state_matrix, i, j, 1, 0, 0, 0, 0, 0);
			set_arr_3d_6(state_matrix, i, height - j - 1, 1, 0, 0, 0, 0, 0);

			border_set.emplace(std::to_string(i) + 'x' + std::to_string(j));
			border_set.emplace(std::to_string(i) + 'x' + std::to_string(height - j - 1));
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < border_size; j++)
		{
			set_arr_3d_6(state_matrix, j, i, 1, 0, 0, 0, 0, 0);
			set_arr_3d_6(state_matrix, width - j - 1, i, 1, 0, 0, 0, 0, 0);

			border_set.emplace(std::to_string(j) + 'x' + std::to_string(i));
			border_set.emplace(std::to_string(width - j - 1) + 'x' + std::to_string(i));


			if ((i >= 0 && i <= hole_y_pos) || (i >= hole_y_pos + hole_size)) {
				set_arr_3d_6(state_matrix, hole_x_pos+j, i, 1, 0, 0, 0, 0, 0);
				border_set.emplace(std::to_string(hole_x_pos + j) + 'x' + std::to_string(i));
			}
		}
	}

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (i > border_size && i < hole_x_pos && j > border_size && j < height - border_size) {
				
				//state_matrix[i][j][get_random(1, 4)] = 1;
				for (int k = 0; k < 4; k++) {
					state_matrix[i][j][k+1] = 1;
				}
				state_matrix[i][j][5] = 1;
				double state[6]{ 0.0 };
				get_arr3d_and_set_arr1d(state_matrix, i, j, 6, state);

				//add_to_process_set(i, j, state);
			}
		}
	}


}

void LGA_sym::add_to_process_set(int i, int j, int state[5])
{	
	if (state[0] == 1) return;

	to_process.emplace(std::to_string(i) + 'x' + std::to_string(j));
	
	if (state[1] == 1)
		to_process.emplace(std::to_string(i) + 'x' + std::to_string(j-1));
	if (state[2] == 1)
		to_process.emplace(std::to_string(i+1) + 'x' + std::to_string(j));
	if (state[3] == 1)
		to_process.emplace(std::to_string(i) + 'x' + std::to_string(j+1));
	if (state[4] == 1)
		to_process.emplace(std::to_string(i-1) + 'x' + std::to_string(j));


}

void LGA_sym::process()
{
#ifdef TIME_MEASURE
	auto start = std::chrono::high_resolution_clock::now();
#endif
	clear_arr_3d(new_state_matrix, width, height, 6);

#ifdef TIME_MEASURE
	auto stop = std::chrono::high_resolution_clock::now();
	std::cout << "clearing time: " << (std::chrono::duration<double>(stop - start)).count() << std::endl;
#endif

#ifdef TIME_MEASURE
	start = std::chrono::high_resolution_clock::now();
#endif

	std::vector<std::thread> threads;

	for (int i = 0; i < threads_num; i++) {
		//process_step(i);
		threads.emplace_back(&LGA_sym::process_step, this, i);
	}

	for (auto& thread : threads) {
		thread.join();
	}


#ifdef TIME_MEASURE
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "processing time: " << (std::chrono::duration<double>(stop - start)).count() << std::endl;

#endif
#ifdef TIME_MEASURE
	start = std::chrono::high_resolution_clock::now();
#endif

	copy_arr_3d(new_state_matrix, state_matrix, width, height, 6);

#ifdef TIME_MEASURE
	stop = std::chrono::high_resolution_clock::now();
	std::cout << "coping time: " << (std::chrono::duration<double>(stop - start)).count() << std::endl;
#endif


}

void LGA_sym::process_step(int id)
{
	int start = id;
	int stop = width;
	int step = threads_num;

	for (int i = start; i < stop; i += step)
	{
		for (int j = 0; j < height; j++)
		{
			double state[6];
			get_arr3d_and_set_arr1d(state_matrix, i, j, 6, state);

			if (state[0] == 1) {
				set_arr_3d_6(new_state_matrix, i, j, 1, 0, 0, 0, 0, 0);
			}
			else if (state_matrix[i][j][0] == 0) {
				double new_state[6] = { 0 };
				double state_up[6];
				double state_right[6];
				double state_down[6];
				double state_left[6];
				double c = 0.0;
				get_arr3d_and_set_arr1d(state_matrix, i - 1, j, 6, state_up);
				get_arr3d_and_set_arr1d(state_matrix, i, j + 1, 6, state_right);
				get_arr3d_and_set_arr1d(state_matrix, i + 1, j, 6, state_down);
				get_arr3d_and_set_arr1d(state_matrix, i, j - 1, 6, state_left);

				// collision with boundry
				//if (state[1] == 1 && state_up[0] == 1) { //co??? lewo
				//	new_state[3] = 1;
				//	new_state[5] = state[5];// +0.5;
				//}
				//else if (state[4] == 1 && state_left[0] == 1) { // gora
				//	new_state[2] = 1;
				//	new_state[5] = state[5];// +0.5;
				//}
				//else if (state[3] == 1 && state_down[0] == 1) { // prawo
				//	new_state[1] = 1;
				//	new_state[5] = state[5];// +0.5;
				//}
				//else if (state[2] == 1 && state_right[0] == 1) { // dol
				//	new_state[4] = 1;
				//	new_state[5] = state[5];// +0.5;
				//}
			
				//streaming
				/*new_state[3] = state_up[3];
				new_state[2] = state_left[2];
				new_state[4] = state_right[4];
				new_state[1] = state_down[1];*/

				if (state_up[0] && state[1])
					new_state[3] = state[1];
				else
					new_state[3] = state_up[3];

				if (state_left[0] && state[4])
					new_state[2] = state[4];
				else
					new_state[2] = state_left[2];

				if (state_right[0] && state[2])
					new_state[4] = state[2];
				else
					new_state[4] = state_right[4];

				if (state_down[0] && state[3])
					new_state[1] = state[3];
				else
					new_state[1] = state_down[1];


				for (int k = 0; k < 4; k++) {
					c += new_state[k + 1];
				}

				for (int k = 0; k < 4; k++) {
					new_state[k+1] = new_state[k+1] + 0.1*(( c / 4) - new_state[k+1]);
				}
				
				new_state_matrix[i][j][0] = new_state[0];
				new_state_matrix[i][j][1] = new_state[1];
				new_state_matrix[i][j][2] = new_state[2];
				new_state_matrix[i][j][3] = new_state[3];
				new_state_matrix[i][j][4] = new_state[4];
				new_state_matrix[i][j][5] = new_state[5];
			}

		}
	}
}

void LGA_sym::draw() {
	SDL_SetRenderDrawColor(gRenderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	int success = SDL_RenderClear(gRenderer);
	if (success != 0) {
		std::cout << "ERROR : " << SDL_GetError() << std::endl;
	}

	int border_count = 0;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (state_matrix[i][j][0] == 1) {
				border_count++;
				SDL_SetRenderDrawColor(gRenderer, border_color.r, border_color.g, border_color.b, border_color.a);
				SDL_RenderDrawPoint(gRenderer, i, j);
			}
			else if (state_matrix[i][j][1] || state_matrix[i][j][2] || state_matrix[i][j][3] || state_matrix[i][j][4]){
				//std::cout << state_matrix[i][j][5] << " ";
				double c = 0.0;
				for (int k = 0; k < 4; k++) {
					c += state_matrix[i][j][k + 1];
				}
				//std::cout << c/4 << " ";
				SDL_SetRenderDrawColor(gRenderer, particle_color.r,(c/4)* particle_color.g, particle_color.b, particle_color.a);
				SDL_RenderDrawPoint(gRenderer, i, j);
			}

		}

	}
	//std::cout << "border: " << border_count << std::endl;
}

LGA_sym::~LGA_sym() {
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			delete[] state_matrix[i][j];
			delete[] new_state_matrix[i][j];
		}
		delete[] state_matrix[i];
		delete[] new_state_matrix[i];
		delete[] border_matrix[i];
	}
	delete[] state_matrix;
	delete[] new_state_matrix;
	delete[] border_matrix;
}