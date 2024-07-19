#pragma once
#include "pch.h"
#include "cmath"

#define M_PI 3.141592

class Vector2F: public D2D1_VECTOR_2F
{
public:
	Vector2F(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}
	~Vector2F(){}

	float Magnitude()const
	{
		return sqrt(x * x + y * y);
	}

	Vector2F Normalized()const
	{
		float length = Magnitude();
		
		if (length != 0)
		{
			float normX = x / length;
			float normY = y / length;
			return Vector2F(normX, normY);
		}
		return Vector2F();
	}
	float GetAngleRadian() 
	{
		return std::atan2(y, x);
	}

	float GetAngleDegree()
	{
		return std::atan2(y, x)*(180.f/M_PI);
	}
public:
	//operator
	Vector2F& operator=	(const Vector2F& rhs)
	{
		if (this != &rhs)
		{
			x = rhs.x;
			y = rhs.y;
		}
		return *this;
	}
	Vector2F operator +=	(const Vector2F& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	
	Vector2F operator -=	(const Vector2F& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	
	Vector2F operator *=	(const Vector2F& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	
	Vector2F operator /=	(const Vector2F& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}

	Vector2F operator *=	(const int rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	Vector2F operator /=	(const int rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	Vector2F operator *=	(const float rhs)
	{
		x *= rhs;
		y *= rhs;
		return *this;
	}
	Vector2F operator /=	(const float rhs)
	{
		x /= rhs;
		y /= rhs;
		return *this;
	}
	Vector2F operator +	(const Vector2F& rhs)
	{
		return Vector2F(x + rhs.x, y + rhs.y);
	}
	Vector2F operator -	(const Vector2F& rhs)
	{
		return Vector2F(x - rhs.x, y - rhs.y);
	}
	Vector2F operator *	(const Vector2F& rhs)
	{
		return Vector2F(x * rhs.x, y * rhs.y);
	}
	Vector2F operator /	(const Vector2F& rhs)
	{
		return Vector2F(x / rhs.x, y / rhs.y);
	}

	//½ºÄ®¶ó °ö
	Vector2F operator*(const int rhs) 
	{
		return Vector2F(x * rhs, y * rhs);
	}
	Vector2F operator /	(const int rhs) 
	{
		return Vector2F(x / rhs, y / rhs);
	}
	Vector2F operator*(const float rhs) 
	{
		return  Vector2F(x * rhs, y * rhs);
	}
	Vector2F operator /	(const float rhs) 
	{
		return  Vector2F(x / rhs, y / rhs);
	}

	friend Vector2F operator*(const int lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs * rhs.x, lhs * rhs.y);
	}
	friend Vector2F operator*(const float lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs * rhs.x, lhs * rhs.y);
	}
	friend Vector2F operator/(const int lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs * rhs.x, lhs * rhs.y);
	}
	friend Vector2F operator/(const float lhs, const Vector2F& rhs)
	{
		return Vector2F(lhs * rhs.x, lhs * rhs.y);
	}
	

	bool operator ==	(const Vector2F& rhs) const
	{
		if (x == rhs.x && y == rhs.y)
			return true;
		return false;
	}
	bool operator !=	(const Vector2F& rhs) const
	{
		if (x == rhs.x && y == rhs.y)
			return false;
		return true;
	}

};

