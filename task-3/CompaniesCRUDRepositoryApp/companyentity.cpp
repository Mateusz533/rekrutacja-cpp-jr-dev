#include "companyentity.h"

CompanyEntity::CompanyEntity(const std::string& name, const std::string& id, const std::string& phone_number,
	const std::string& address, const std::string& email)
	: m_name(name), m_id(id), m_phone_number(phone_number), m_address(address), m_email(email)
{}

void CompanyEntity::setName(const std::string& name) {
	m_name = name;
}

void CompanyEntity::setId(const std::string& id) {
	m_id = id;
}

void CompanyEntity::setPhoneNumber(const std::string& phone_number) {
	m_phone_number = phone_number;
}

void CompanyEntity::setAddress(const std::string& address) {
	m_address = address;
}

void CompanyEntity::setEmail(const std::string& email) {
	m_email = email;
}

std::string CompanyEntity::getName() const {
	return m_name;
}

std::string CompanyEntity::getId() const {
	return m_id;
}

std::string CompanyEntity::getPhoneNumber() const {
	return m_phone_number;
}

std::string CompanyEntity::getAddress() const {
	return m_address;
}

std::string CompanyEntity::getEmail() const {
	return m_email;
}

std::array<std::string, FIELD_NUMER> CompanyEntity::toArray() const {
	return std::array<std::string, FIELD_NUMER>({ m_name, m_id, m_phone_number, m_address, m_email });
}

CompanyEntity CompanyEntity::fromArray(const std::array<std::string, FIELD_NUMER>& args){
	return CompanyEntity(args[0], args[1], args[2], args[3], args[4]);
}
