#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <list>
#include <string>
#include <stdio.h>
#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


using namespace std;
//  The problem can be solved in O(n log n) time using the recursive divide and conquer approach, e.g., as follows:[1]

//     Sort points according to their y-coordinates.
//     Split the set of points into two equal-sized subsets by a vertical line x=xmid.
//     Solve the problem recursively in the left and right subsets. This yields the left-side and right-side minimum distances dLmin and dRmin, respectively.
//     Find the minimal distance dLRmin among the set of pairs of points in which one point lies on the left of the dividing vertical and the second point lies to the right.
//     The final answer is the minimum among dLmin, dRmin, and dLRmin.

// A divide and conquer program in C++ to find the smallest distance from a
// given set of points.
 
// struct for 2dimensions and the index
struct Point
{
    int x, y, index;
    //int z;
};

//compare x values
bool xComparing(const Point &x, const Point &y)
{
    if(x.x < y.x){
    	return true;
    }
    return false;
}
//compare y values
bool yComparing(const Point &x, const Point &y)
{
    if(x.y < y.y){
        return true;
    }
    return false;
}
//compare z values
// bool zComparing(const Point &x, const Point &y)
// {
//     if(x.z < y.z){
//         return true;
//     }
//     return false;
// }

//distance formula
float findDistance(Point p1, Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
                 //(p1.z - p2.z)*(p1.z - p2.z)
               );
}

//find the minimum value
float min(float x, float y)
{
    if(x < y){
    	return x;
    }
    else{
    	return y;
    };
}

//finding the closest segment
float closestSegment(Point line[], int size, float oldDMin)
{
    float lineMin = oldDMin;
    for (int i = 0; i < size; ++i){
        for (int j = i+1; j < size && (line[j].y - line[i].y) < lineMin; ++j){
            if (findDistance(line[i],line[j]) < lineMin){
                //cout << i << " " << j << endl;
                lineMin = findDistance(line[i], line[j]);
            }
        }
    }
    return lineMin;
}
//brute force algorithm for small sizes
float bruteForce(Point coors[], int count)
{
    int a;
    int b;
    float min = numeric_limits<float>::max();
    for (int i = 0; i < count; ++i){
        for (int j = i+1; j < count; ++j){
            if (findDistance(coors[i], coors[j]) < min){
                a = i;
                b = j;
                min = findDistance(coors[i], coors[j]);
            }
        }
    }
    return min;
}

//finding the closest pairs
float closestPair(Point Px[], Point Py[], int n)
{
    //use brute force for small size
    if (n <= 3)
        return bruteForce(Px, n);
 
    //find mid point
    int mid = n/2;
    Point MP = Px[mid];
    Point Pyl[mid+1];   // y sorted points on left of vertical line
    Point Pyr[n-mid-1];  // y sorted points on right of vertical line
    int li = 0, ri = 0;  
    for (int i = 0; i < n; i++)
    {
      if (Py[i].x <= MP.x)
         Pyl[li++] = Py[i];
      else
         Pyr[ri++] = Py[i];
    }
    //calculate the smallest distance dl on left of middle point and dr on right
    float dl = closestPair(Px, Pyl, mid);
    float dr = closestPair(Px + mid, Pyr, n-mid);
    //find smaller of 2 distances
    float d = min(dl, dr);
    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++){
        if (abs(Py[i].x - MP.x) < d){
            strip[j] = Py[i], j++;
        }
    }
    return min(d, closestSegment(strip, j, d) );
}

//finds the smallest distance
float closest(vector<Point> p, int count)
{
    vector<Point> sortedX;
    vector<Point> sortedY;
    //vector<Point> sortedZ;
    sortedX = p;
    sortedY = p;
    //sortedZ = p;
    sort(sortedX.begin(), sortedX.end(), xComparing);
    sort(sortedY.begin(), sortedY.end(), yComparing);
    //sort(sortedZ.begin(), sortedZ.end(), zComparing);
    return closestPair(sortedX.data(), sortedY.data(), count);
}

int main(int argc, char* argv[]){
    string writeStrFile = argv[2];
    ofstream writeFile(writeStrFile);
	float minD = numeric_limits<float>::max();
	int min1 = numeric_limits<int>::max();
	int min2 = numeric_limits<int>::max();
	vector<Point> pts;
	int line;
	int findSize = 0;
	ifstream myfile (argv[1]);
	if(myfile.is_open()){
		while(myfile >> line){
		    findSize++;
			int index = line;
			myfile >> line;
			int x = line;
			myfile >> line;
			int y = line;
			Point pt = {x, y,index};
			pts.push_back(pt);
		}
	}
	// for (int i = 0; i < pts.size(); i++)
	// {
	// 	cout << i << " " << pts[i].x << " " << pts[i].y << endl;
	// }
    clock_t t1,t2;
    t1=clock();
	float end = closest(pts, findSize); 
	t2=clock();
    float diff ((float)t2-(float)t1);
    //we are done
    //to make finding the output easier we will use the brute force algorithm
    int a;
    int b;
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
    //write to file the results
    writeFile << "The first index is: " << pts[a].index << " (" << pts[a].x << "," << pts[a].y << ")" << " (Line: " << a+1 << " in the input file)"<< endl;
    writeFile << "The second index is: " << pts[b].index << " (" << pts[b].x << "," << pts[b].y << ")" <<" (Line: " << b+1 << " in the input file)"<< endl;
    writeFile << "The minimum distance is : " << end << endl;
    writeFile << "Time to run: " << diff<<endl;
    return 0;
}
