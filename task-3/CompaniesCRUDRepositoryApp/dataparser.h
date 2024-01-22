#pragma once

#include <algorithm>
#include <iterator>
#include <numeric>
#include <functional>
#include "companyentity.h"

static class DataParser {
public:
	DataParser() = delete;

	static CompanyEntity trim(const CompanyEntity& data);
	static bool validateAll(const CompanyEntity& data);
	static bool validateName(const CompanyEntity& data);
	static bool validateId(const CompanyEntity& data);
	static bool validatePhoneNumber(const CompanyEntity& data);
	static bool validateAddress(const CompanyEntity& data);
	static bool validateEmail(const CompanyEntity& data);
};
