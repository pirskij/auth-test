#pragma once

#include "ForwardDeclare.h"
#include <functional>
#include <string_view>

namespace sol::auth
{
	using OnValidatedClb = std::function<void(bool)>;

	class Validator
	{
	public:
		virtual ~Validator() = default;
		virtual bool validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb) = 0;

	protected:
		OnValidatedClb m_clb;
	};

	class BackendValidator : public Validator
	{
	public:
		virtual bool validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb) override;
	};

	class LocalValidator : public Validator
	{
	public:
		virtual bool validate(std::string_view name, std::string_view pass, OnValidatedClb const& clb) override;
	};
} // namespace sol::auth
