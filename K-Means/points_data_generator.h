#pragma once
#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <random>
#include <ctime>  

using namespace std;

struct square
{
	double x_min;
	double x_max;
	double y_min;
	double y_max;
}square_1, square_2, square_3, square_4, square_5, square_6, square_7, square_8, square_9, square_10;

void init_square_areas()
{
	square_1.x_min = 0.75;	square_1.x_max = 1.25;	square_1.y_min = 0.75;	square_1.y_max = 1.25;
	square_2.x_min = 0.0;	square_2.x_max = 0.5;	square_2.y_min = 0.0;	square_2.y_max = 0.5;
	square_3.x_min = 0.0;	square_3.x_max = 0.5;	square_3.y_min = 1.5;	square_3.y_max = 2.0;
	square_4.x_min = 1.5;	square_4.x_max = 2.0;	square_4.y_min = 0.0;	square_4.y_max = 0.5;
	square_5.x_min = 1.5;	square_5.x_max = 2.0;	square_5.y_min = 1.5;	square_5.y_max = 2.0;
	square_6.x_min = 0.6;	square_6.x_max = 0.8;	square_6.y_min = 0.0;	square_6.y_max = 0.4;
	square_7.x_min = 0.6;	square_7.x_max = 0.8;	square_7.y_min = 1.6;	square_7.y_max = 2.0;
	square_8.x_min = 1.2;	square_8.x_max = 1.4;	square_8.y_min = 0.0;	square_8.y_max = 0.4;
	square_9.x_min = 1.2;	square_9.x_max = 1.4;	square_9.y_min = 1.6;	square_9.y_max = 2.0;
	square_10.x_min = 0.0;	square_10.x_max = 2.0;	square_10.y_min = 0.0;	square_10.y_max = 2.0;
}

double generate_random_number(double min, double max)
{
	static default_random_engine generator(unsigned(time(nullptr)));
	uniform_real_distribution<double> distribution(min, max);
	return distribution(generator);
}

void generate_random_points()
{

	init_square_areas();
	square pinakas[] = { square_1, square_2, square_3, square_4, square_5, square_6, square_7, square_8, square_9, square_10 };

	// Create and open a text file
	ofstream MyFile("points_data.txt");



	int i, j, number_of_points, point_counter = 0;
	for (j = 0; j < 10; j++)
	{
		if (j < 5 || j == 9) { number_of_points = 150; }
		else { number_of_points = 75; }
		point_counter = point_counter + number_of_points;

		for (i = 0; i < number_of_points; i++)
		{
			double x1 = generate_random_number(pinakas[j].x_min, pinakas[j].x_max);
			double x2 = generate_random_number(pinakas[j].y_min, pinakas[j].y_max);

			//Write to the file
			MyFile << x1 << " " << x2 << endl;
		}
	}

	// Close the file
	MyFile.close();
}


