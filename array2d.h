#ifndef ARRAY2D_H
#define ARRAY2D_H
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "filereader.h"

class Array2D
{
public:
	
	Array2D();
	~Array2D();

	int Populate(); //cita datoteku, pravi matricu velicine 3*n
	int FindRow(int, int, int, int); //prima koordinate i trazi red, -1 ako nije u redu
	int FindPoint(int); //prima red i ispisuje tocku, vraca 1 ako je nasao, -1 ako nije
	int Nearest(int,int); //prima vrijednost reda u kojoj je referentna i broj redova
					 //tocka i vraca vrijednost reda u kojoj je najbliza tocka, -1 ako nije u redu
private:

	int **data;
	
};

int Array2D::Populate()
{
	int number = null;
	int status = null;
	int datasize = 0;
	int i = 3;
	int j, rows;
	char filepath[1024] = "C:\\Users\\Danijela\\Desktop\\diplomski\\octree_code\\tree.txt";
	FileReader freader(filepath);
	if (freader.ReadAllContent() < null)
	{
		std::cout << "File does not exist." << std::endl;
		
	}
	else
	{
		datasize = freader.FindCount();
		rows=j=(int)(datasize / 3);
		data = new int*[j];
		for (int x = 0; x < j; ++x)
			data[x] = new int[i];
		freader.ReadAllContent();
		i = j = 0;
		do
		{
			status = freader.GetNumber(number);

			if (status != ENDOFFILE)
			{

				data[j][i] = number;
				i++;
				if (i == 3)
				{
					j++;
					i = 0;
				}
			}
			else
			{
				break;
			}
		} while (1);
		}
	for (int y = 0; y < rows; y++)
	{ 
		std::cout << "Point: " << data[y][0] << "," << data[y][1] << "," << data[y][2] << std::endl;
	}
	return rows;
	
	}


int Array2D::FindRow(int x, int y, int z , int rows)
{
	
	for (int i = 0; i < rows; ++i )
	{
		if (data[i][0] == x && data[i][1] == y && data[i][2] == z)
			return i;
	}
	return -1;
}
int Array2D::FindPoint(int row)
{
	if (data[row])
	{
		std::cout << "Point coordinates: (x,y,z) (" << data[row][0] << "," << data[row][1] << "," << data[row][2] << ")"<< std::endl;
		return 1;
	}
	else return -1;
}
int Array2D::Nearest(int row, int numOfRows)
{
	int nearestRow=0;
	int xref = data[row][0];
	int yref = data[row][1];
	int zref = data[row][2];
	int xd, yd, zd;
	double distance, nearest;
	xd = xref - data[0][0];
	yd = yref - data[0][1];
	zd = zref - data[0][2];
	distance = sqrt(xd*xd + yd*yd + zd*zd);
	nearest = distance;
	for (int i = 1; i < numOfRows; i++)
	{
		xd = xref - data[i][0];
		yd = yref - data[i][1];
		zd = zref - data[i][2];
		distance = sqrt(xd*xd + yd*yd + zd*zd);
		if (distance < nearest && distance != 0)
		{
			nearest = distance;
			nearestRow = i;
		}
	}
	
	return nearestRow;
}


Array2D::Array2D()
{
	memset(this, 0, sizeof(Array2D));
}
Array2D::~Array2D()
{
	memset(this, 0, sizeof(Array2D));
}
#endif
