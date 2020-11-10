#pragma once

class Point
{
	public:
		int x, y; // Coords

		inline Point(int newX, int newY) noexcept :
			x(newX), y(newY)
		{}	// Constructor

		inline ~Point() noexcept
		{
			x = y = 0;
		}	// Destructor

		inline Point(const Point& Other) noexcept :
			x(0), y(0)
		{
			if (this != &Other)
			{
				this->x = Other.x;
				this->y = Other.y;
			}	// if
		}	// Copy Constructor

		inline Point(Point&& Other) noexcept :
			x(0), y(0)
		{
			if (this != &Other)
			{
				this->x = Other.x;
				this->y = Other.y;

				Other.x = Other.y = 0;
			}	// if
		}	// Move Constructor

		inline const Point& operator=(const Point& Other) noexcept
		{
			if (this != &Other)
			{
				this->x = Other.x;
				this->y = Other.y;
			}	// if

			return *this;
		}	// operator = 

		inline Point& operator=(Point&& Other) noexcept
		{
			if (this != &Other)
			{
				this->x = Other.x;
				this->y = Other.y;

				Other.x = Other.y = 0;
			}	// if

			return *this;
		}	// move operator = 

		inline bool operator<(const Point &op2) const noexcept
		{
			return op2.y < y;
		}	// operator <
};	// Point Interface