#pragma once

#include <string>
#include <vector>
#include <QFile>
#include <QTextStream>
#include "companyentity.h"

static class DataPersistor {
public:
	static bool save(const QString& path, const std::vector<CompanyEntity>& records);
	static bool read(const QString& path, std::vector<CompanyEntity>& records);

private:
	const static char s_separator{ ';' };
};
