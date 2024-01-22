#pragma once

#include <string>
#include <vector>
#include <array>

constexpr int FIELD_NUMER{ 5 };

class CompanyEntity {
public:
	CompanyEntity() = delete;
	CompanyEntity(const std::string& name, const std::string& id, const std::string& phone_number,
		const std::string& adress, const std::string& email);

	void setName(const std::string& name);
	void setId(const std::string& id);
	void setPhoneNumber(const std::string& phone_number);
	void setAddress(const std::string& adress);
	void setEmail(const std::string& email);
	std::string getName() const;
	std::string getId() const;
	std::string getPhoneNumber() const;
	std::string getAddress() const;
	std::string getEmail() const;
	std::array<std::string, FIELD_NUMER> toArray() const;
	static CompanyEntity fromArray(const std::array<std::string, FIELD_NUMER>& list);

private:
	std::string m_name;
	std::string m_id;
	std::string m_phone_number;
	std::string m_address;
	std::string m_email;
};
