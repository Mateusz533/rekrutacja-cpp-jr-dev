#pragma once

#include <QtWidgets/QFileDialog>
#include "ipersistancecontroller.h"
#include "companyentity.h"
#include "datapersistor.h"

class CSVPersistanceController : public IPersistanceController<std::vector<CompanyEntity>> {
public:
	bool fetchData(std::vector<CompanyEntity>& buffer) override;
	bool saveData(const std::vector<CompanyEntity>& data) override;
	bool saveDataAs(const std::vector<CompanyEntity>& data) override;

private:
	QString m_current_repository_file_name{ "" };
};
