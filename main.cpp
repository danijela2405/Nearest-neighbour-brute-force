#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATED
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array2d.h"
int main(void)
{
	Array2D array;
	int rowcount = array.Populate();
	std::cout << "Number of points: " << rowcount << std::endl;

	int row=array.FindRow(4,3,4,rowcount);

	int nearestRow = array.Nearest(row, rowcount);

	std::cout << "Nearest point to (4,3,4): " << std::endl;

	array.FindPoint(nearestRow);
	getchar();
	return 0;
}
