#pragma once

#include <functional>
#include <unordered_map>
#include <string>

template<typename... T>
class Delegator
{
public:
  using CallbackFunction = std::function<void(T...)>;

  using CallbackMap = std::unordered_map<std::wstring, CallbackFunction>;

  void AddCallback(const std::wstring& key, CallbackFunction callback) {
    _callbackFunction[key] = callback;
  }

  void RemoveCallback(const std::wstring& key) {
    _callbackFunction.erase(key);
  }

  void ExecuteCallback(const std::wstring& key, T... args) {
    auto iter = _callbackFunction.find(key);
    if (iter != _callbackFunction.end()) {
      iter->second(args...);
    }
  }

private:
  CallbackMap _callbackFunction;
};