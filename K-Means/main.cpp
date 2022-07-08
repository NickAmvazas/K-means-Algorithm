#include <iostream>
#include <fstream>
#include <stdlib.h>     
#include <math.h>
#include "points_data_generator.h"
#include <string> 
using namespace std;

#define	D 2  	// Dimensions
#define N 1200  //Number of Points in 2d
#define	M 3	// Clusters - Centers

struct point
{
	double x_1, x_2;
	int cluster = -1;
};

point points[N];
point Center[M];
point old_Center[M];
double point_clustering_error[N];

void read_file();
void init_centers();
void calculate_distances();
void calculate_new_centers();
void calculate_clustering_error();
void export_file();

int main()
{
	generate_random_points(); // Create a file with 1200 Points.
	read_file();			  // Read the file and update points matrix.
	
	/********************K - MEANS********************/

	// Initialize random Centers.
	init_centers();
	// Loop for number of iterations (t)
	int flag = 0;
	int loop_counter = 0;
	while(flag<M)
	{
		loop_counter++;
		//Step 1
		calculate_distances();	
		//Step 2
		calculate_new_centers();
		//Step 3 Termination Check
		flag = 0;
		for (unsigned int j = 0; j < M; j++)
		{
			if (old_Center[j].x_1 == Center[j].x_1 && old_Center[j].x_2 == Center[j].x_2)
			{
				flag = flag+1;
			}
		}	
	}

	/*************************************************/

	/*******************Console*******************/

	// Print Iterations(t)
	cout << "\nIterations(t): " << loop_counter << "\n\n";
	// Print number of points in each Cluster.
	for (unsigned int j = 0; j < M; j++)
	{
		int point_counter =0;
		for (unsigned int i = 0; i < N; i++)
		{
			if(points[i].cluster==j+1)
			{
				point_counter++;
			}
		}
		cout << "Cluster_" << j+1 << " has " << point_counter << " points.\n"; 
	}
	// Calculate and Print Clustering Error
	calculate_clustering_error();
   
    /*********************************************/
	export_file();	
	return 0;
}

void read_file()
{
	// Open File
	ifstream myFile;
	myFile.open("points_data.txt");
	point mypoint;
	for (unsigned int i=0;i<N;i++)
	{
		myFile >> mypoint.x_1;
		myFile >> mypoint.x_2;
		points[i] = mypoint;
	}
	// Close File
	myFile.close();
}

void init_centers()
{
	int point_id[M]= { 0 };
	int random_number;
	srand(time(NULL));
	cout<<"\nInitialized Centers Id: ";
	//Init Random Centers
	for (unsigned int i = 0; i < M; i++)
	{
		random_number = rand() % N;
		point_id[i] = random_number;
		cout<< point_id[i] << "  ";
		Center[i] = points[point_id[i]];	
	}
}

void calculate_distances()
{
	// For each point 
	for (unsigned int i = 0; i < N; i++)
	{
		double *distances_array = new double[M];
		// For each Center
		for (unsigned int j = 0; j < M; j++)
		{
			double x_distance = abs(points[i].x_1 - Center[j].x_1);	
			double y_distance = abs(points[i].x_2 - Center[j].x_2);
			distances_array[j] = sqrt(pow(x_distance,2) + pow(y_distance,2));
		}
		
		int this_point_cluster = 0;
		double min_distance = 999.999;
		for (unsigned int j = 0; j < M; j++)
		{
			if (distances_array[j] < min_distance)
			{
				min_distance = distances_array[j];
				this_point_cluster = j + 1;
			}
		}
		points[i].cluster = this_point_cluster;
		delete[] distances_array;
	}
}

void calculate_new_centers()
{
	// Keep old (t-1) Centers.
	for (unsigned int j = 0; j < M; j++)
	{
		old_Center[j] = Center[j];
	}
	// Calculate New Centers.
	int counter = 0;
	for (unsigned int j = 0; j < M; j++)
	{
		double center_x = 0.0;
		double center_y = 0.0;
		// For each point 
		for (unsigned int i = 0; i < N; i++)
		{
			if (points[i].cluster == j+1)
			{
				center_x = center_x + points[i].x_1;
				center_y = center_y + points[i].x_2;
				counter++;
			}
		}
		if(counter==0){counter=1;}
		Center[j].x_1 = center_x / counter;
		Center[j].x_2 = center_y / counter;
		Center[j].cluster = j+1;
		//Init counter to 0 for next cluster(loop)
		counter = 0;
	}
}

void calculate_clustering_error()
{
	double x, y;
	// For each point 
	for (unsigned int i = 0; i < N; i++)
	{
		x = points[i].x_1 - Center[points[i].cluster - 1].x_1;
		y = points[i].x_2 - Center[points[i].cluster - 1].x_2;
		point_clustering_error[i] = pow(x, 2) + pow(y, 2);
		//Print Clustering Error for each Point
		//cout << "Point "<< i+1 << " Clustering Error: " << point_clustering_error[i] << "\n";
	}
	double clustering_error=0;
	for (unsigned int i = 0; i < N; i++)
	{
		clustering_error = clustering_error + point_clustering_error[i];
	}
	cout << "\nClustering Error: " << clustering_error;
	cout << "\n Average Clustering Error for each Point: " << clustering_error/N;
}

void export_file()
{
	// Create text files
	ofstream MyPointsFile("points_result.txt");
	ofstream MyCentersFile("centers_result.txt");
	//File for Points
	for (unsigned int i = 0; i < N; i++)
	{
		MyPointsFile << points[i].x_1 << " " << points[i].x_2 << " " << points[i].cluster << endl;
	}
	//File for Centers
	for (unsigned int j = 0; j < M; j++)
	{
		MyCentersFile << Center[j].x_1 << " " << Center[j].x_2 << " " << Center[j].cluster << endl;
	}
	// Close the file
	MyPointsFile.close();
	MyCentersFile.close();
}


