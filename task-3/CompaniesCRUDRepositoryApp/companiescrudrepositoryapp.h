#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_companiescrudrepositoryapp.h"
#include "dataparser.h"
#include "csvpersistancecontroller.h"

class CompaniesCRUDRepositoryApp : public QMainWindow
{
	Q_OBJECT

public:
	CompaniesCRUDRepositoryApp(QWidget* parent = nullptr);
	~CompaniesCRUDRepositoryApp();

private:
	std::vector<CompanyEntity> getTableData() const;
	void setTableData(const std::vector<CompanyEntity>& records);
	CompanyEntity getRecord(const int& row) const;
	void setRecord(const int& row, const CompanyEntity& record);
	CompanyEntity getFormData() const;
	void setFormData(const CompanyEntity& record);
	void clearForm();
	std::array<QLineEdit*, FIELD_NUMER> formFields() const;

	Ui::CompaniesCRUDRepositoryAppClass ui;
	IPersistanceController<std::vector<CompanyEntity>>* const m_persistance_controller;

private slots:
	void on_pbAdd_clicked();
	void on_pbUpdate_clicked();
	void on_pbDelete_clicked();
	void on_actionSave_triggered();
	void on_actionSaveAs_triggered();
	void on_actionRead_triggered();
	void on_tabData_clicked();
};
