#include <iostream>
#include "KNN.h"
#include <iostream>

int main()
{
	// We have Cartesian axis system with :
	// 250 Random Points on first quadrant which contains Squares.
	// 250 Random Points on second quadrant which contains Triangles.
	// 250 Random Points on third quadrant which contains Rectangles.
	// 250 Random Points on fourth quadrant which contains circles.
	// We look for the seven closest neighboors to our object, to predict what object is is.


	KNN M(1'000, 7); 
	//M.Write();
	std::cout << "(" << M.Predict( Point(80, 75) ) << ")" << std::endl;   // we except : Square
	std::cout << "(" << M.Predict(Point(-3, 5)) << ")" << std::endl;      // we except : Triangle
	std::cout << "(" << M.Predict(Point(-19, -30)) << ")" << std::endl;   // we except : Rectangle
	std::cout << "(" << M.Predict(Point(3, -7)) << ")" << std::endl;      // we except : Circle

	std::cout << "(" << M.Predict(Point(0, 0)) << ")" << std::endl;       // ??? it depends
}   // main

