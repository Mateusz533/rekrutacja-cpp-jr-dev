#include "datapersistor.h"

bool DataPersistor::save(const QString& path, const std::vector<CompanyEntity>& records) {
	QFile file(path);

	if (!file.open(QIODevice::Truncate | QIODevice::WriteOnly | QIODevice::Text))
		return false;

	for (const auto& record : records) {
		const auto& args{ record.toArray() };

		constexpr auto parser = [&](auto& init, auto& arg) { return init + s_separator + arg; };
		const std::string line{ std::accumulate(args.begin() + 1, args.end(), args[0], parser) + '\n' };
		file.write(QByteArray::fromStdString(line));
	}

	file.close();
	return true;
}

bool DataPersistor::read(const QString& path, std::vector<CompanyEntity>& records_buffer) {
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QTextStream stream(&file);
	records_buffer.clear();

	while (!stream.atEnd()) {
		const QStringList list{ stream.readLine().split(s_separator) };
		if (list.size() != FIELD_NUMER) {
			file.close();
			return false;
		}

		std::array<std::string, FIELD_NUMER> args;
		std::transform(list.begin(), list.end(), args.begin(), [](auto& arg) { return arg.toStdString(); });
		records_buffer.push_back(CompanyEntity::fromArray(args));
	}

	file.close();
	return true;
}
