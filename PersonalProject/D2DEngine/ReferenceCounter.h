#pragma once

class ReferenceCounter
{
private:
	unsigned int m_refCount;

public:
	ReferenceCounter() :m_refCount(0) {}
	virtual ~ReferenceCounter() {}

	unsigned int AddRef()
	{
		m_refCount++;
		return m_refCount;
	}
	unsigned int Release()
	{
		m_refCount--;
		if (m_refCount == 0)
		{
			delete this;
			return 0;
		}
	}
	unsigned int GetRefCount()
	{
		return m_refCount;
	}
};