#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace std;
//2 dimensions
struct Point
{
	int x,y, index;
};

//distance formula
float findDistance(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
               );
}


int main(int argc, char* argv[]){
	string file = argv[1];
	int line;
	string writeStrFile = argv[2];
	vector<Point> pts;
	ifstream myfile(file);
	ofstream writeFile(writeStrFile);
	int n = pts.size();
	//open file
	//read in variables
	if(myfile.is_open()){
		while(myfile >> line){
			int index = line;
			myfile >> line;
			int x = line;
			myfile >> line;
			int y = line;
			Point pt = {x, y, index};
			pts.push_back(pt);
		}
	}
	// for (int i = 0; i < pts.size(); i++)
	// {
	// 	cout << i << " " << pts[i].x << " " << pts[i].y << endl;
	// }
	int a;
	int b;
	clock_t t1,t2;
    t1=clock();
	//brute force formula
	float min = FLT_MAX;
    for (int i = 0; i < pts.size(); ++i)
        for (int j = i+1; j < pts.size(); ++j)
        {
        //	cout << findDistance(pts[i],pts[j]) << endl;
            if (findDistance(pts[i], pts[j]) < min)
            {
            	a = i;
            	b = j;
                min = findDistance(pts[i], pts[j]);
            }
        }
    //cout << a << " " << b << " " << min << endl;
    //write to file the results
    writeFile << "The first index is: " << pts[a].index << " (" << pts[a].x << "," << pts[a].y << ")" << " (Line: " << a+1 << " in the input file)"<< endl;
    writeFile << "The second index is: " << pts[b].index << " (" << pts[b].x << "," << pts[b].y << ")" <<" (Line: " << b+1 << " in the input file)"<< endl;
    writeFile << "The minimum distance is : " << min << endl;
    t2=clock();
    float diff ((float)t2-(float)t1);
    writeFile << "Time to run: " << diff<<endl;
    return 0;
}