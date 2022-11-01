#include "Authorizer.h"

using namespace sol::auth;

AccessTokenSPtr Authorizer::autorize(std::string_view name, std::string_view pass)
{
	std::string key = std::string(name.data()) + "+" + pass.data();

	auto token = m_cache->getItem(key);
	if (token)
		return token;

	if (m_validator)
	{
		//m_validator
	}

	return nullptr;
}
