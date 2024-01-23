#include "companiescrudrepositoryapp.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	const QString& locale{ QLocale::system().name() };
	const QString& file_name{ LANG_FILE_PREFIX + (locale == "pl_PL" || locale == "en_EN") ? locale : "pl_PL" };
	QTranslator translator;

	if (!translator.load(file_name, LANG_FILES_DIRECTORY))
		return 1;
	else if (!QCoreApplication::installTranslator(&translator))
		return 2;

	CompaniesCRUDRepositoryApp w;
	w.show();
	return a.exec();
}
