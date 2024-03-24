#include "my_utilities.h"

void clear_arr_3d(int*** arr, int width, int height, int row)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < row; k++) {
				arr[i][j][k] = 0;
			}
		}
	}
}

void set_arr_3d_5(int*** arr, int i, int j, int a, int b, int c, int d, int e) {
	arr[i][j][0] = a;
	arr[i][j][1] = b;
	arr[i][j][2] = c;
	arr[i][j][3] = d;
	arr[i][j][4] = e;
}

void set_arr_3d_6(int*** arr, int i, int j, int a, int b, int c, int d, int e, int f) {
	arr[i][j][0] = a;
	arr[i][j][1] = b;
	arr[i][j][2] = c;
	arr[i][j][3] = d;
	arr[i][j][4] = e;
	arr[i][j][5] = f;
}


void copy_arr_3d(int*** og, int*** arr, int width, int height, int row)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < row; k++) {
				arr[i][j][k] = og[i][j][k];
			}
		}
	}
}

void get_arr3d_and_set_arr1d_5(int*** get_arr, int i, int j, int arr[])
{
	arr[0] = get_arr[i][j][0];
	arr[1] = get_arr[i][j][1];
	arr[2] = get_arr[i][j][2];
	arr[3] = get_arr[i][j][3];
	arr[4] = get_arr[i][j][4];
}

void get_arr3d_and_set_arr1d(int*** get_arr, int i, int j, int r, int arr[])
{
	for (int k = 0; k < r; k++) {
		arr[k] = get_arr[i][j][k];
	}
}


void clear_arr_3d(double*** arr, int width, int height, int row)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < row; k++) {
				arr[i][j][k] = 0;
			}
		}
	}
}

void set_arr_3d_5(double*** arr, int i, int j, double a, double b, double c, double d, double e) {
	arr[i][j][0] = a;
	arr[i][j][1] = b;
	arr[i][j][2] = c;
	arr[i][j][3] = d;
	arr[i][j][4] = e;
}

void set_arr_3d_6(double*** arr, int i, int j, double a, double b, double c, double d, double e, double f) {
	arr[i][j][0] = a;
	arr[i][j][1] = b;
	arr[i][j][2] = c;
	arr[i][j][3] = d;
	arr[i][j][4] = e;
	arr[i][j][5] = f;
}


void copy_arr_3d(double*** og, double*** arr, int width, int height, int row)
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < row; k++) {
				arr[i][j][k] = og[i][j][k];
			}
		}
	}
}

void get_arr3d_and_set_arr1d_5(double*** get_arr, int i, int j, double arr[])
{
	arr[0] = get_arr[i][j][0];
	arr[1] = get_arr[i][j][1];
	arr[2] = get_arr[i][j][2];
	arr[3] = get_arr[i][j][3];
	arr[4] = get_arr[i][j][4];
}

void get_arr3d_and_set_arr1d(double*** get_arr, int i, int j, int r, double arr[])
{
	for (int k = 0; k < r; k++) {
		arr[k] = get_arr[i][j][k];
	}
}




int get_random(int lower, int upper)
{
	int random = rand();
	return random % (upper - lower + 1) + lower;
}

bool prob(double probability)
{
	int upper = 10000;
	int random = get_random(0, upper);
	double prob = (double)random / upper;
	if (probability >= prob) return true;
	return false;
}

void split_string_x(std::string& string, int* res) {
	int x_pos = string.find("x");

	res[0] = std::stoi(string.substr(0, x_pos));
	res[1] = std::stoi(string.substr(x_pos + 1, string.size() - 1));
}