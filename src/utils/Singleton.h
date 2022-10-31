#pragma once

namespace sol::utils
{
	template<typename T>
	class Singleton
	{
	protected:
		Singleton() = default;
		virtual ~Singleton() = default;
	
	public:
		static T* getInstance()
		{
			if (nullptr == s_pInstance)
			{
				s_pInstance = new T();
			}
			return s_pInstance;
		}

		static void purgeInstance()
		{
			if (nullptr != s_pInstance)
			{
				delete s_pInstance;
				s_pInstance = nullptr;
			}
		}
	
		static bool isCreated() { return (nullptr != s_pInstance); }

	private:
		static T* s_pInstance;
	};

	template<typename T>
	T* Singleton<T>::s_pInstance = nullptr;
} // namespace sol::utils
