#pragma once
#include "Vector2F.h"
#include "ReferenceCounter.h"

class FrameInfo
{
public:
	D2D1_RECT_F source;
	Vector2F center;
	FLOAT duration;
	FrameInfo()
	{
		source.left = 0;
		source.top = 0;
		source.bottom = 0;
		source.right = 0;
		duration = 0;
		center.x = 0;
		center.y = 0;
	}
	FrameInfo(float left, float top, float right, float bottom, float centerX, float centerY, float time)
	{
		source.left = left;
		source.top = top;
		source.right = right;
		source.bottom = bottom;
		center.x = centerX;
		center.y = centerY;
		duration = time;
	}
	FrameInfo(D2D1_RECT_F rect, float centerX, float centerY, float time)
	{
		source = rect;
		center.x = centerX;
		center.y = centerY;
		duration = time;
	}
};

class AnimationInfo//하나하나의 동작의 정보
{
public:
	std::string name;//애니매이션 이름
	std::vector<FrameInfo>frames;//프레임의 모임
	bool Loop;//반복?
	std::string nextAnim;//loop-> false일경우 사용하는 다음 애니메이션 이름
	void SetNextAnimInfo(std::string nextAnimation) { nextAnim = nextAnimation; }

	AnimationInfo()
		:name("Default")
	{

	}
	~AnimationInfo()
	{
	}
};


class AnimationAsset : public ReferenceCounter
{
public:
	std::vector<AnimationInfo>m_animations;//애니메이션의 모임
public:
	AnimationAsset() { }
	virtual ~AnimationAsset()
	{

	}

	AnimationInfo* GetAnimationInfo(int index)
	{
		if (index < 0 || index >= m_animations.size())
		{
			throw std::out_of_range("Invalid animation index");
		}
		return &m_animations[index];
	}
	AnimationInfo* GetAnimationInfo(std::string animationName)
	{

		for (auto& iter : m_animations)
		{
			if (iter.name == animationName)
			{
				return &iter;
			}
		}
		throw std::runtime_error("Animation not found: " + animationName);
	}

	bool LoadAnimation(std::wstring filePath);
	bool LoadAnimationFromCSV(int index, const wchar_t* fileName);
};
