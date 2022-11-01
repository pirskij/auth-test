#include "Validator.h"

using namespace sol::auth;

bool BackendValidator::validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb)
{
	/// TODO: implement backend 
	return false;
}

bool LocalValidator::validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb)
{
	/// TODO: implement local 

	return true;
}
