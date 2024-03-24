#pragma once

#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H



#include <cstdlib>
#include <iostream>
#include <string>

void clear_arr_3d(int*** arr, int width, int height, int row);
void set_arr_3d_5(int*** arr, int i, int j, int a, int b, int c, int d, int e);
void set_arr_3d_6(int*** arr, int i, int j, int a, int b, int c, int d, int e, int f);
void copy_arr_3d(int*** og, int*** arr, int width, int height, int row);
void get_arr3d_and_set_arr1d_5(int*** get_arr, int i, int j, int arr[]);
void get_arr3d_and_set_arr1d(int*** get_arr, int i, int j, int r, int arr[]);

void clear_arr_3d(double*** arr, int width, int height, int row);
void set_arr_3d_5(double*** arr, int i, int j, double a, double b, double c, double d, double e);
void set_arr_3d_6(double*** arr, int i, int j, double a, double b, double c, double d, double e, double f);
void copy_arr_3d(double*** og, double*** arr, int width, int height, int row);
void get_arr3d_and_set_arr1d_5(double*** get_arr, int i, int j, double arr[]);
void get_arr3d_and_set_arr1d(double*** get_arr, int i, int j, int r, double arr[]);

int get_random(int lower, int upper);
bool prob(double probability);
void split_string_x(std::string& string, int* res);


#endif //MY_UTILITIES_H
