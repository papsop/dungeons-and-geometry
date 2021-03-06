#include "CvarUtils.h"
#include <type_traits>
#include <string>
namespace Engine
{
	template<typename T>
	Engine::CvarWrapper<T>::CvarWrapper(std::string key, T* ptr, T defaultValue, std::function<void(void)> func)
		: I_Cvar(key, func)
		, m_ptr(ptr)
	{
		*m_ptr = defaultValue;
	}

	template<typename T>
	void Engine::CvarWrapper<T>::SetValue(T newValue)
	{
		T oldValue = *m_ptr;

		if (oldValue == newValue)
			return;

		*m_ptr = newValue;
		m_modified = true;
		if (m_onChanged != nullptr)
			m_onChanged();
	}


	template<typename T>
	void Engine::CvarWrapper<T>::SetValueString(std::string value)
	{
		if constexpr (std::is_same_v<T, int>)
			SetValue(std::stoi(value.c_str()));
		else if constexpr (std::is_same_v<T, float>)
			SetValue(std::stof(value.c_str()));
		else if constexpr (std::is_same_v<T, std::string>)
			SetValue(value);
	}

	template<typename T>
	void Engine::CvarWrapper<T>::SetValueInt(int value)
	{
		if constexpr (std::is_same_v<T, int>)
			SetValue(value);
		else if constexpr (std::is_same_v<T, float>)
			SetValue(static_cast<float>(value));
		else if constexpr (std::is_same_v<T, std::string>)
			SetValue(std::to_string(value));
	}

	template<typename T>
	void Engine::CvarWrapper<T>::SetValueFloat(float value)
	{
		if constexpr (std::is_same_v<T, int>)
			SetValue(static_cast<int>(value));
		else if constexpr (std::is_same_v<T, float>)
			SetValue(value);
		else if constexpr (std::is_same_v<T, std::string>)
			SetValue(std::to_string(value));
	}

	template<typename T>
	std::string Engine::CvarWrapper<T>::GetValueAsString()
	{
		if constexpr (std::is_same_v<T, std::string>)
			return *m_ptr;
		else
			return std::to_string(*m_ptr);
	}

};