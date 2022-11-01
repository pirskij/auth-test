#pragma once

#include "ForwardDeclare.h"
#include <string>
#include <unordered_map>

namespace sol::utils
{
	template<class T>
	class Cache
	{
	public:
		Cache() = default;

		bool hasItem(std::string const& key)
		{
			return (m_cache.find(key) != std::end(m_cache));
		}

		std::shared_ptr<T> getItem(std::string const& key)
		{
			auto itr = m_cache.find(key);
			if (itr != std::end(m_cache))
				return itr->second;

			return nullptr;
		}

		bool putItem(std::string const& key, std::shared_ptr<T> item)
		{
			auto itr = m_cache.find(key);
			if (itr != std::end(m_cache))
				return false;

			m_cache[key] = item;

			return true;
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<T>> m_cache;
	};
} // namespace sol::utils
