#include "csvpersistancecontroller.h"

bool CSVPersistanceController::fetchData(std::vector<CompanyEntity>& buffer) {
	const QString name = QFileDialog::getOpenFileName(nullptr, QObject::tr("Select file"), QDir::homePath(), QObject::tr("CSV (*.csv)"));

	if (!DataPersistor::read(name, buffer))
		return false;

	m_current_repository_file_name = name;
	return true;
}

bool CSVPersistanceController::saveData(const std::vector<CompanyEntity>& data) {
	if (m_current_repository_file_name.isEmpty())
		return saveDataAs(data);
	else
		return DataPersistor::save(m_current_repository_file_name, data);
}

bool CSVPersistanceController::saveDataAs(const std::vector<CompanyEntity>& data) {
	const QString name = QFileDialog::getSaveFileName(nullptr, QObject::tr("Select file"), QDir::homePath(), QObject::tr("CSV (*.csv)"));
	if (name.isEmpty())
		return false;

	m_current_repository_file_name = name;
	return DataPersistor::save(name, data);
}
