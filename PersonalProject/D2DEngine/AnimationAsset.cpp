#include "pch.h"
#include "AnimationAsset.h"
#include "ReferenceCounter.h"

bool AnimationAsset::LoadAnimation(std::wstring filePath)
{
	std::wifstream file(filePath);
	if (!file.is_open())
	{
		throw std::runtime_error("Can not open file");
		return false;
	}
	std::wstring line;
	int animationCount = 0;
	{
		std::getline(file, line);
		std::getline(file, line);
		std::wstringstream wss(line);
		wss >> animationCount;
	}
	m_animations.resize(animationCount);
	for (int i = 0; i < animationCount; i++)
	{
		//�ִϸ��̼��� �̸�,csvPath,loop true false ���� �Է��ϱ�.
		//csv,txt ���Ϸκ��� rect���� �о����. rect-> left,top,right,bottom,centerx,centery,duration
		std::getline(file, line);
		std::wstring token;
		std::wstringstream wss(line);
		{
			std::getline(wss, token, L',');
			m_animations[i].name = WStringToString(token);
			std::getline(wss, token, L',');
			LoadAnimationFromCSV(i, token.c_str());
			std::getline(wss, token, L',');


			//1=ture, 0=false
			if (token == L"1" || token == L"true")
				m_animations[i].Loop = true;
			else if (token == L"0" || token == L"false")
				m_animations[i].Loop = false;
		}
	}
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)
{
	AnimationInfo temp;
	std::wifstream file(fileName);
	if (!file.is_open()) {
		throw std::runtime_error("Can not open file");
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	int FrameCount = 0;			// �������� ����
	{
		std::getline(file, line);	
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);
		wss >> FrameCount;
	}
	m_animations[index].frames.resize(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		getline(file, line);		// ���� �б�
		std::wstringstream wss(line);    // ������ �о wstringstream�� ����
		std::wstring token;
		{
			getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
			m_animations[index].frames[j].source.left = (float)_wtof(token.c_str());
			getline(wss, token, L',');
			m_animations[index].frames[j].source.top = (float)_wtof(token.c_str());
			getline(wss, token, L',');
			m_animations[index].frames[j].source.right = (float)_wtof(token.c_str());
			getline(wss, token, L',');
			m_animations[index].frames[j].source.bottom = (float)_wtof(token.c_str());
			getline(wss, token, L',');
			m_animations[index].frames[j].center.x = (float)_wtof(token.c_str());
			getline(wss, token, L',');
			m_animations[index].frames[j].center.y = (float)_wtof(token.c_str());
			getline(wss, token, L',');
			m_animations[index].frames[j].duration = (float)_wtof(token.c_str());
		}
	}

	return true;
}



