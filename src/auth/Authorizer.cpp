#include "AccessToken.h"
#include "Authorizer.h"
#include "Validator.h"
#include "utils/Memory.h"

using namespace sol::auth;
using namespace sol::utils;

Authorizer::Authorizer()
{
	m_cache = sol_make_shared<TokenCache>();
	m_validator = sol_make_shared<LocalValidator>();
}

AccessTokenSPtr Authorizer::autorize(std::string_view name, std::string_view pass)
{
	std::string key = std::string(name.data()) + "+" + pass.data();

	auto token = m_cache->getItem(key);
	if (token)
		return token;

	if (m_validator)
	{
		m_validator->validate(name, pass, [this, key](bool res, std::string raw) {
			if (res)
			{
				auto newToken = sol_make_shared<AccessToken>(raw);
				m_cache->putItem(key, newToken);
			}
		});

		return m_cache->getItem(key);
	}

	return nullptr;
}
