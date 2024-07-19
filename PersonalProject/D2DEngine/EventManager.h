#pragma
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <iostream>




class EventBase
{
public:
	virtual ~EventBase() = default;
	virtual void Invoke() = 0;
};

template<typename...Args>
class Event :public EventBase
{
public:
	std::function<void(Args...)> callback;
public:
	Event(std::function<void(Args...)>_callback) :callback(_callback) {}

	void Invoke(Args... args)
	{
		callback(args...);
	}
	void Invoke() override
	{
		// �� �޼���� ����� �� �����Ƿ� ���ܸ� �����ϴ�.
		throw std::runtime_error("Invalid Invoke call without arguments");
	}
};

// ���ø� Ư��ȭ: �Ű������� ���� ���
template<>
class Event<> : public EventBase
{
public:
	std::function<void()> callback;
public:
	Event(std::function<void()> _callback) : callback(_callback) {}


	void Invoke() override
	{
		callback();
	}
};

class EventManager
{
private:
	
	EventManager() {}
	~EventManager() {}
	//���� �����ڸ� �����������->�ϳ��� �����ϰ�
	EventManager(const EventManager&) = delete;
	//���� �Ҵ� ������ ������� ����->�ϳ��� �����ϰ�
	EventManager& operator=(const EventManager&) = delete;

	//�̺�Ʈ����Ʈ���� �����ϰ��ִ� �ؽ� ��
	std::unordered_map<std::wstring, std::vector<std::shared_ptr<EventBase>>> _events;
public:
	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	void RegisterEvent(const std::wstring& eventName)
	{
		//��� ���� ���� �̺�Ʈ��� ���ο� �̺�Ʈ ����Ʈ ����
		if (_events.find(eventName) == _events.end())
		{
			_events[eventName] = std::vector<std::shared_ptr<EventBase>>();
		}
		else
		{
			throw std::runtime_error("event already regist!");
		}
	}

	void UnregisterEvent(const std::wstring& evnetName)
	{
		_events.erase(evnetName);
	}


	/**
	 * @brief // �̺�Ʈ �����ϴ� ��
	   ex) EventManager::GetInstance().Subscribe<>(L"BossDamaged", std::function<void()>(std::bind(&Boss::Damaged, this)));
	 * @tparam ...Args 
	 * @param eventName 
	 * @param callback 
	 */
	template<typename... Args>
	void Subscribe(const std::wstring& eventName, std::function<void(Args...)> callback)
	{
		//�̺�Ʈ�� ��ϵǾ��ִ��� Ȯ��
		if (_events.find(eventName) != _events.end())
		{
			//�̺�Ʈ �ݹ� ����Ʈ�� ���ο� �ݹ� �߰�
			_events[eventName].push_back(std::make_shared<Event<Args...>>(callback));
		}
		else
		{
			throw std::runtime_error("Event not registered!");
		}

	}



	template<typename...Args>
	void UnSubscribe(const std::wstring& eventName, std::function<void(Args...)> callback)
	{
		// �̺�Ʈ�� ��ϵǾ��ִ��� Ȯ��
		if (_events.find(eventName) != _events.end())
		{
			auto& callbacks = _events[eventName];
			// �ݹ� ����Ʈ���� Ư�� �ݹ��� �������ش�.
			callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(),
				[&callback](const std::shared_ptr<EventBase>& event)
				{
					auto derivedEvent = std::dynamic_pointer_cast<Event<Args...>>(event);
					return derivedEvent && derivedEvent->callback.target<void(Args...)>() == callback.target<void(Args...)>();
				}), callbacks.end());
		}
	}

	template<typename...Args>
	void Emit(const std::wstring& eventName, Args...args)
	{
		if (_events.find(eventName) != _events.end())
		{
			for (auto& event : _events[eventName])
			{
				auto derivedEvent = std::dynamic_pointer_cast<Event<Args...>>(event);
				if (derivedEvent)
				{
					derivedEvent->Invoke(args...);
				}
			}
		}
		else
		{
			throw std::runtime_error("event not registered!");
		}
	}

};