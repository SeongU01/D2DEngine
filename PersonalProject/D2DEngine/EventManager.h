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
		// 이 메서드는 사용할 수 없으므로 예외를 던집니다.
		throw std::runtime_error("Invalid Invoke call without arguments");
	}
};

// 템플릿 특수화: 매개변수가 없는 경우
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
	//복사 생성자를 사용하지않음->하나만 존재하게
	EventManager(const EventManager&) = delete;
	//복사 할당 연산자 사용하지 않음->하나만 존재하게
	EventManager& operator=(const EventManager&) = delete;

	//이벤트리스트들을 저장하고있는 해쉬 맵
	std::unordered_map<std::wstring, std::vector<std::shared_ptr<EventBase>>> _events;
public:
	static EventManager& GetInstance()
	{
		static EventManager instance;
		return instance;
	}

	void RegisterEvent(const std::wstring& eventName)
	{
		//등록 되지 않은 이벤트라면 새로운 이벤트 리스트 생성
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
	 * @brief // 이벤트 구독하는 법
	   ex) EventManager::GetInstance().Subscribe<>(L"BossDamaged", std::function<void()>(std::bind(&Boss::Damaged, this)));
	 * @tparam ...Args 
	 * @param eventName 
	 * @param callback 
	 */
	template<typename... Args>
	void Subscribe(const std::wstring& eventName, std::function<void(Args...)> callback)
	{
		//이벤트가 등록되어있는지 확인
		if (_events.find(eventName) != _events.end())
		{
			//이벤트 콜백 리스트에 새로운 콜백 추가
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
		// 이벤트가 등록되어있는지 확인
		if (_events.find(eventName) != _events.end())
		{
			auto& callbacks = _events[eventName];
			// 콜백 리스트에서 특정 콜백을 제거해준다.
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