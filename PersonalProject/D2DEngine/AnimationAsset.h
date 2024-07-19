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

class AnimationInfo//�ϳ��ϳ��� ������ ����
{
public:
	std::string name;//�ִϸ��̼� �̸�
	std::vector<FrameInfo>frames;//�������� ����
	bool Loop;//�ݺ�?
	std::string nextAnim;//loop-> false�ϰ�� ����ϴ� ���� �ִϸ��̼� �̸�
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
	std::vector<AnimationInfo>m_animations;//�ִϸ��̼��� ����
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
