#include "AccessToken.h"
#include "utils/Storage.h"

using namespace sol::auth;
using namespace sol::utils;

AccessToken::AccessToken(std::string_view raw)
{
	m_rawToken = raw;
}

bool AccessToken::isExpired() const noexcept
{
	/// TODO: Add implementation 
	return false;
}

void AccessToken::store(StorageWriterSPtr writer)
{
	if (!writer)
		writer->write(m_rawToken);
}
