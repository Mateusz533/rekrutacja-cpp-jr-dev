#include "companiescrudrepositoryapp.h"

CompaniesCRUDRepositoryApp::CompaniesCRUDRepositoryApp(QWidget* parent)
	: QMainWindow(parent), m_persistance_controller(new CSVPersistanceController())
{
	ui.setupUi(this);
	connect(ui.pbAdd, &QPushButton::click, this, &CompaniesCRUDRepositoryApp::on_pbAdd_clicked);
	connect(ui.pbUpdate, &QPushButton::click, this, &CompaniesCRUDRepositoryApp::on_pbUpdate_clicked);
	connect(ui.pbDelete, &QPushButton::click, this, &CompaniesCRUDRepositoryApp::on_pbDelete_clicked);
	connect(ui.tabData, &QTableWidget::clicked, this, &CompaniesCRUDRepositoryApp::on_tabData_clicked);
	connect(ui.actionSave, &QAction::trigger, this, &CompaniesCRUDRepositoryApp::on_actionSave_triggered);
	connect(ui.actionSaveAs, &QAction::trigger, this, &CompaniesCRUDRepositoryApp::on_actionSaveAs_triggered);
	connect(ui.actionRead, &QAction::trigger, this, &CompaniesCRUDRepositoryApp::on_actionRead_triggered);
}

CompaniesCRUDRepositoryApp::~CompaniesCRUDRepositoryApp()
{}

std::vector<CompanyEntity> CompaniesCRUDRepositoryApp::getTableData() const {
	std::vector<CompanyEntity> records;
	records.reserve(ui.tabData->rowCount());

	for (int i{ 0 }; i < ui.tabData->rowCount(); ++i)
		records.push_back(getRecord(i));

	return records;
}

void CompaniesCRUDRepositoryApp::setTableData(const std::vector<CompanyEntity>& records) {
	ui.tabData->clearContents();
	ui.tabData->setRowCount(records.size());

	for (int i{ 0 }; i < records.size(); ++i)
		setRecord(i, records[i]);
}

CompanyEntity CompaniesCRUDRepositoryApp::getRecord(const int& row) const {
	std::array<std::string, FIELD_NUMER> record;
	for (int j{ 0 }; j < FIELD_NUMER; ++j)
		record[j] = ui.tabData->item(row, j)->text().toStdString();

	return CompanyEntity::fromArray(record);
}

void CompaniesCRUDRepositoryApp::setRecord(const int& row, const CompanyEntity& record) {
	const auto& data{ record.toArray() };
	for (int j{ 0 }; j < data.size(); ++j)
		ui.tabData->setItem(row, j, new QTableWidgetItem(QString::fromStdString(data[j])));
}

CompanyEntity CompaniesCRUDRepositoryApp::getFormData() const {
	constexpr auto toString = [](QLineEdit* p_field) { return p_field->text().toStdString(); };

	std::array<std::string, FIELD_NUMER> form_data;
	const auto& form_fields{ formFields() };
	std::transform(form_fields.begin(), form_fields.end(), form_data.begin(), toString);

	return DataParser::trim(CompanyEntity::fromArray(form_data));
}

void CompaniesCRUDRepositoryApp::setFormData(const CompanyEntity& record) {
	const auto& form_fields{ formFields() };
	const auto& fields{ record.toArray() };

	for (int i{ 0 }; i < fields.size(); ++i)
		form_fields[i]->setText(QString::fromStdString(fields[i]));
}

void CompaniesCRUDRepositoryApp::clearForm() {
	for (auto* field : formFields())
		field->clear();
}

std::array<QLineEdit*, FIELD_NUMER> CompaniesCRUDRepositoryApp::formFields() const {
	return std::array<QLineEdit*, FIELD_NUMER>({ ui.lneName, ui.lneID, ui.lnePhone, ui.lneAddress, ui.lneEmail });
}

/*******************/
/* All SLOTS BELOW */
/*******************/

void CompaniesCRUDRepositoryApp::on_pbAdd_clicked() {
	const auto& form_data{ getFormData() };

	if (!DataParser::validateAll(form_data))
		return ui.statusBar->showMessage("Invalid form data!");

	for (const auto& record : getTableData()) {
		if (record.getId() == form_data.getId())
			return ui.statusBar->showMessage("Duplicated ID!");
	}

	const int& row_number{ ui.tabData->rowCount() };
	ui.tabData->insertRow(row_number);
	setRecord(row_number, form_data);

	ui.tabData->clearSelection();
	clearForm();
	ui.statusBar->clearMessage();
}

void CompaniesCRUDRepositoryApp::on_pbUpdate_clicked() {
	const auto& selected_items{ ui.tabData->selectedItems() };
	if (selected_items.isEmpty())
		return;

	const auto& form_data{ getFormData() };
	if (!DataParser::validateAll(form_data))
		return ui.statusBar->showMessage("Invalid form data!");

	const auto& selected_row{ selected_items.at(0)->row() };
	const auto& selected_record{ getRecord(selected_row) };
	const auto& records{ getTableData() };

	for (int i{ 0 }; i < records.size(); ++i) {
		if (i != selected_row && records[i].getId() == form_data.getId())
			return ui.statusBar->showMessage("Duplicated ID!");
	}

	setRecord(selected_row, form_data);

	ui.tabData->clearSelection();
	clearForm();
	ui.statusBar->clearMessage();
}

void CompaniesCRUDRepositoryApp::on_pbDelete_clicked() {
	const auto& selected_items{ ui.tabData->selectedItems() };
	if (selected_items.isEmpty())
		return;

	ui.tabData->removeRow(selected_items.at(0)->row());
	ui.tabData->clearSelection();
	clearForm();
	ui.statusBar->clearMessage();
}

void CompaniesCRUDRepositoryApp::on_tabData_clicked() {
	const auto& selected_items{ ui.tabData->selectedItems() };
	if (selected_items.isEmpty())
		return;

	const int& row_number{ selected_items.at(0)->row() };
	setFormData(getRecord(row_number));
	ui.statusBar->clearMessage();
}

void CompaniesCRUDRepositoryApp::on_actionSave_triggered() {
	if (!m_persistance_controller->saveData(getTableData()))
		ui.statusBar->showMessage("Incorrect file!");
	else
		ui.statusBar->clearMessage();
}

void CompaniesCRUDRepositoryApp::on_actionSaveAs_triggered() {
	if (!m_persistance_controller->saveDataAs(getTableData()))
		ui.statusBar->showMessage("Incorrect file!");
	else
		ui.statusBar->clearMessage();
}

void CompaniesCRUDRepositoryApp::on_actionRead_triggered() {
	std::vector<CompanyEntity> buffer;

	if (!m_persistance_controller->fetchData(buffer))
		return ui.statusBar->showMessage(QString("File data is incorrect!"));

	if (!std::all_of(buffer.begin(), buffer.end(), [](const auto& record) { return DataParser::validateAll(record); }))
		return ui.statusBar->showMessage(QString("File data is incorrect!"));

	setTableData(buffer);
	ui.statusBar->clearMessage();
}
