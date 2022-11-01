#pragma once

#include "ForwardDeclare.h"
#include "utils/ForwardDeclare.h"
#include "utils/Cache.h"
#include <string>
#include <string_view>

namespace sol::auth
{
	class AccessToken
	{
	public:
		AccessToken(std::string_view raw);

		std::string_view getRawToken() const noexcept { return m_rawToken; }

		bool isExpired() const noexcept;

		void store(sol::utils::StorageWriterSPtr writer);

	private:
		std::string m_rawToken;
	};

	using TokenCache = sol::utils::Cache<AccessToken>;

} // namespace sol::auth
