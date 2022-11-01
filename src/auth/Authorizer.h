#pragma once

#include "ForwardDeclare.h"
#include "utils/ForwardDeclare.h"
#include "AccessToken.h"
#include <string_view>

namespace sol::auth
{
	class Authorizer
	{
	public:
		Authorizer() = default;
		
		AccessTokenSPtr autorize(std::string_view name, std::string_view pass);

	private:
		ValidatorSPtr m_validator;
		std::shared_ptr<TokenCache> m_cache;
		sol::utils::StorageSPtr m_storage;
	};

} // namespace sol::auth
