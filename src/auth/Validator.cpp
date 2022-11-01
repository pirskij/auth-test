#include "Validator.h"

using namespace sol::auth;

bool BackendValidator::validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb)
{
	/// TODO: implement backend 
	return false;
}

bool LocalValidator::validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb)
{
	if (clb)
	{
		std::string raw = "{\"name\"=\"";
		raw += name;
		raw += "\",\"token\"=\"test token\"}";

		clb(true, raw);
	}

	return true;
}
