#pragma once
#include "Vector2F.h"
class Transform
{
private:
  Vector2F m_scale;
	float m_rotation;
  Vector2F m_location;
	Vector2F m_center;

public:
	Transform(void) :m_scale(1, 1), m_rotation(0), m_location(0, 0) {}
	~Transform(void){}

	D2D1_MATRIX_3X2_F m_relativeTransform;
	D2D1_MATRIX_3X2_F m_worldTransform;
	//setter
	void SetScale(const float x, const float y){m_scale = { x,y };}
	void SetScale(const  Vector2F & v2) { m_scale = v2; }
	void SetRotation(const float z) { m_rotation = z; }
	void SetLocation(const float x, const float y){m_location = { x,y };}
	void SetLocation(const Vector2F & v2){m_location = v2;}
	void SetCenter(const float x, const float y) { m_center = { x,y }; }

	//getter
	Vector2F& GetScale() { return m_scale; }
	float& GetRotation() { return m_rotation; }
  Vector2F& GetLocation() { return m_location; }
	Vector2F& GetCenter() { return m_center; }

	//operator
	Transform& operator=(const Transform& rhs)
	{
		if (this != &rhs)
		{
			this->m_rotation = rhs.m_rotation;
			this->m_scale = rhs.m_scale;
			this->m_location = rhs.m_location;
		}
		return *this;
	}
	
};

