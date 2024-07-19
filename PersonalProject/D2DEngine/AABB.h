	#pragma once
	#include "Vector2F.h"
	enum class CollisionDirection
	{
		None,
		Left,
		Right,
		Top,
		Bottom
	};

	class AABB
	{
	private:
		Vector2F m_Center;
		Vector2F m_Extent;
		D2D_RECT_F m_AABBRect;
	public:
		AABB() :m_Center(0), m_Extent(0) {}

		AABB(const AABB&) = default;
		AABB& operator=(const AABB&) = default;
		AABB(AABB&&) = default;
		AABB& operator=(AABB&&) = default;
		~AABB() = default;
		void SetCenter(float x, float y) { m_Center = { x, y }; }
		void SetExtent(float x, float y) { m_Extent = { x, y }; }
		void SetAABBRect()
		{
			m_AABBRect = {
				m_Center.x - m_Extent.x,
				m_Center.y - m_Extent.y,
				m_Center.x + m_Extent.x,
				m_Center.y + m_Extent.y,
			};
		}
		float GetMinX() const{ return m_Center.x - m_Extent.x; }
		float GetMaxX() const { return m_Center.x + m_Extent.x; }
		float GetMinY() const { return m_Center.y - m_Extent.y; }
		float GetMaxY() const { return m_Center.y + m_Extent.y; }
		Vector2F GetCenter() const { return m_Center; }
		D2D_RECT_F GetRect() const { return m_AABBRect; }

		bool CheckIntersect(const AABB& other) const
		{
			//// self min,max
			//float BoxA_xmin = m_Center.x - m_Extent.x;
			//float BoxA_xmax = m_Center.x + m_Extent.x;
			//float BoxA_ymin = m_Center.y - m_Extent.y;
			//float BoxA_ymax = m_Center.y + m_Extent.y;

			//// other min,max
			//float BoxB_xmin = other.m_Center.x - other.m_Extent.x;
			//float BoxB_xmax = other.m_Center.x + other.m_Extent.x;
			//float BoxB_ymin = other.m_Center.y - other.m_Extent.y;
			//float BoxB_ymax = other.m_Center.y + other.m_Extent.y;
			float BoxA_xmin = m_AABBRect.left;
			float BoxA_xmax = m_AABBRect.right;
			float BoxA_ymin = m_AABBRect.top;
			float BoxA_ymax = m_AABBRect.bottom;

				// other min,max
			float BoxB_xmin = other.m_AABBRect.left;
			float BoxB_xmax = other.m_AABBRect.right;
			float BoxB_ymin = other.m_AABBRect.top;
			float BoxB_ymax = other.m_AABBRect.bottom;
			// Check for no overlap conditions
			if (BoxA_xmax < BoxB_xmin ||  // 오른쪽에 있으면 겹칠수가 없음
				BoxA_xmin > BoxB_xmax ||  // 왼쪽에 있으면 겹칠수가 없음
				BoxA_ymax < BoxB_ymin ||  // 아래에 있으면 겹칠수가 없음
				BoxA_ymin > BoxB_ymax)	  // 위에 있으면 겹칠수가 없음
			{
				return false;
			}

			return true;

		}

		CollisionDirection GetCollisionDirection(const AABB& other) const
		{
			// self min,max
			float BoxA_xmin = m_Center.x - m_Extent.x;
			float BoxA_xmax = m_Center.x + m_Extent.x;
			float BoxA_ymin = m_Center.y - m_Extent.y;
			float BoxA_ymax = m_Center.y + m_Extent.y;

			// other min,max
			float BoxB_xmin = other.m_Center.x - other.m_Extent.x;
			float BoxB_xmax = other.m_Center.x + other.m_Extent.x;
			float BoxB_ymin = other.m_Center.y - other.m_Extent.y;
			float BoxB_ymax = other.m_Center.y + other.m_Extent.y;

			// Calculate the distances between the centers
			float dx = (BoxA_xmin + BoxA_xmax) / 2 - (BoxB_xmin + BoxB_xmax) / 2;
			float dy = (BoxA_ymin + BoxA_ymax) / 2 - (BoxB_ymin + BoxB_ymax) / 2;

			// Calculate the half extents
			float combinedHalfWidth = (BoxA_xmax - BoxA_xmin) / 2 + (BoxB_xmax - BoxB_xmin) / 2;
			float combinedHalfHeight = (BoxA_ymax - BoxA_ymin) / 2 + (BoxB_ymax - BoxB_ymin) / 2;

			// Check for no overlap conditions first
			if (std::abs(dx) > combinedHalfWidth || std::abs(dy) > combinedHalfHeight) 
			{
				return CollisionDirection::None;
			}

			// Determine the collision direction based on the smallest overlap
			float overlapX = combinedHalfWidth - std::abs(dx);
			float overlapY = combinedHalfHeight - std::abs(dy);

			if (overlapX < overlapY) 
			{
				if (dx > 0) 
				{
					return CollisionDirection::Left;
				}
				else
				{
					return CollisionDirection::Right;
				}
			}
			else 
			{
				if (dy > 0)
				{
					return CollisionDirection::Top;
				}
				else 
				{
					return CollisionDirection::Bottom;
				}
			}
		}

		std::pair<CollisionDirection, CollisionDirection> CheckIntersectionDetails(const AABB& other) const
		{
			CollisionDirection thisDirection = GetCollisionDirection(other);
			CollisionDirection otherDirection = other.GetCollisionDirection(*this);

			return std::make_pair(thisDirection, otherDirection);
		}


	
	};


