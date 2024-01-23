#include "dataparser.h"

constexpr auto INVALID_CHARS = [](const char& c) { return c < ' '; };
constexpr auto NOT_DIGITS = [](const char& c) { return c < '0' || c > '9'; };

CompanyEntity DataParser::trim(const CompanyEntity& data) {
	auto arr{ data.toArray() };
	for (auto& field : arr) {
		const auto& first{ field.find_first_not_of(' ') };
		const auto& offset{ first == std::string::npos ? 0 : first };
		const auto& length{ first == std::string::npos ? 0 : field.find_last_not_of(' ') + 1 - offset };
		field = field.substr(offset, length);
	}
	return CompanyEntity::fromArray(arr);
}

bool DataParser::validateAll(const CompanyEntity& data) {
	return validateName(data) && validateId(data) && validatePhoneNumber(data)
		&& validateAddress(data) && validateEmail(data);
}

bool DataParser::validateName(const CompanyEntity& data) {
	const std::string& name{ data.getName() };
	if (name.empty())
		return false;

	return std::find_if(name.begin(), name.end(), INVALID_CHARS) == name.end();
}

bool DataParser::validateId(const CompanyEntity& data) {
	constexpr auto NUMBER_SIZE = 13;
	constexpr auto NUMBER_OF_DIGITS = 10;
	const auto WEIGHTS = { 6,5,7,2,3,4,5,6,7,0 };
	constexpr auto TRANSFORM = [](const char& c, const int& w) { return (c - '0') * w; };

	const std::string& id{ data.getId() };
	std::string number;
	std::copy_if(id.begin(), id.end(), std::back_inserter(number), [](auto& c) { return c != '-'; });

	if (std::any_of(number.begin(), number.end(), NOT_DIGITS))
		return false;

	if (id.size() != NUMBER_SIZE || number.size() != NUMBER_OF_DIGITS)
		return false;

	auto ctrl = std::inner_product(number.begin(), number.end(), WEIGHTS.begin(), 0, std::plus<int>(), TRANSFORM) % 11;
	if (*number.rbegin() - '0' != ctrl)
		return false;

	return true;
}

bool DataParser::validatePhoneNumber(const CompanyEntity& data) {
	constexpr auto NUMBER_SIZE = 9;
	const std::string& number{ data.getPhoneNumber() };

	if (number.size() != NUMBER_SIZE)
		return false;

	return std::none_of(number.begin(), number.end(), NOT_DIGITS);
}

bool DataParser::validateAddress(const CompanyEntity& data) {
	const std::string& address{ data.getAddress() };
	if (address.empty())
		return false;

	return std::find_if(address.begin(), address.end(), INVALID_CHARS) == address.end();
}

bool DataParser::validateEmail(const CompanyEntity& data) {
	std::string email{ data.getEmail() };

	if (std::find_if(email.begin(), email.end(), INVALID_CHARS) != email.end())
		return false;

	const auto& at_pose{ email.find('@') };
	if (at_pose == std::string::npos || at_pose == 0)
		return false;

	const auto& dot_pose{ email.find('.', at_pose) };
	if (dot_pose == std::string::npos || dot_pose == at_pose + 1 || dot_pose == email.size() - 1)
		return false;

	constexpr auto VALID_CHARS = [](char c) { return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '.'; };
	email.erase(at_pose, 1);

	return std::all_of(email.begin(), email.end(), VALID_CHARS);
}
