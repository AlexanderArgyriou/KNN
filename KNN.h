#pragma once
#include "Point.h"
#include <map>
#include <vector>
#include <string>
#include <algorithm>

typedef std::multimap<Point, std::string> Map;

class KNN
{
	private :
		std::size_t              K; // The number on neighboors.
		Map                      M; // The Map whic holds a Point and the object which exists in this point
		std::size_t   NumOfObjects; // Number of objects in our map
		std::string ObjectTypes[4]; // Objects

		inline void PopulateQuadrant(const std::size_t Obj, std::size_t Num) noexcept; // PopulateQuadrant

	public :
		inline KNN(std::size_t newNumOfObjects, std::size_t newK) noexcept;    // Constructor
		inline ~KNN()  noexcept;                                               // Destructor
		inline std::string Predict(const Point &P) noexcept;                   // Predict
		inline void Write() const noexcept;                                    // Write
};	// KNN

inline void KNN::PopulateQuadrant(const std::size_t Obj, std::size_t Num) noexcept
{
	if (Num == 1) // First Quadrant +x , +y
		for (std::size_t i = 0; i < NumOfObjects / 4; i++)
			M.insert({ Point(rand() % 100 + 1, rand() % 100 + 1), ObjectTypes[Obj] });
	else if (Num == 2) // Second Quadrant -x , +y
		for (std::size_t i = 0; i < NumOfObjects / 4; i++)
			M.insert({ Point(-(rand() % 100 + 1), rand() % 100 + 1), ObjectTypes[Obj] });
	else if (Num == 3) // Third Quadrant -x, -y
		for (std::size_t i = 0; i < NumOfObjects / 4; i++)
			M.insert({ Point(-(rand() % 100 + 1), -(rand() % 100 + 1)), ObjectTypes[Obj] });
	else // Fourth Quadrant +x, -y
		for (std::size_t i = 0; i < NumOfObjects / 4; i++)
			M.insert({Point(rand() % 100 + 1, -(rand() % 100 + 1)), ObjectTypes[Obj]});
}	// Populate()

inline KNN::KNN(std::size_t newNumOfObjects, std::size_t newK) noexcept
	: NumOfObjects(newNumOfObjects), K(newK)
{
	// Some constaits to populate normal and avoid same number of same neighboors.
	if (K < 7 || K % 2 == 0 
		|| NumOfObjects % 2 != 0 || NumOfObjects < 4)
		exit(1);

	ObjectTypes[0] = "Square";
	ObjectTypes[1] = "Triangle";
	ObjectTypes[2] = "Rectangle";
	ObjectTypes[3] = "Circle";

	PopulateQuadrant(0, 1); // populate the 1st quadrant with Squares.
	PopulateQuadrant(1, 2); // populate the 2nd quadrant with Triangles.
	PopulateQuadrant(2, 3); // populate the 3rd quadrant with Rectangles.
	PopulateQuadrant(3, 4); // populate the 4th quadrant with Circles.
}	// Constructor

inline KNN::~KNN() noexcept
{
	M.clear();
	NumOfObjects = 0;

	ObjectTypes[0] = "";
	ObjectTypes[1] = "";
	ObjectTypes[2] = "";
	ObjectTypes[3] = "";
}	// Destructor

inline std::string KNN::Predict(const Point &P) noexcept
{
	// Distance's of the given point from all the other points
	std::vector<std::pair<double, std::string>> Distances;

	for (auto &p : M)
	{
		// find the distance between the 2 points to hit the K closest.
		Distances.push_back({ std::sqrt(std::pow(p.first.x - P.x, 2) +
			std::pow(p.first.y - P.y, 2)), p.second });
	}	// for

    // sort the vector of pairs to find the k closest points.
	std::sort(Distances.begin(), Distances.end(), [](const auto& op1, const auto& op2) -> bool
	{
		return op1.first < op2.first;
	});

	// Classify and predict what the object is.
	std::vector<std::size_t> Objs(4, 0);
	for (std::size_t i = 0; i < K; i++)
	{
		std::cout << Distances[i].second << " ";
		if (Distances[i].second == "Square")
			Objs[0]++;
		else if (Distances[i].second == "Triangle")
			Objs[1]++;
		else if (Distances[i].second == "Rectangle")
			Objs[2]++;
		else
			Objs[3]++;
	}	// for

	// The Prediction
	std::string Pr = ObjectTypes[std::max_element(Objs.begin(), Objs.end()) - Objs.begin()];
	return Pr;
}	// Predict

inline void KNN::Write() const noexcept
{
	for (auto &p : M)
		std::cout << p.first.x << "," << p.first.y
		<< " | "<< p.second << std::endl;
}	// Write