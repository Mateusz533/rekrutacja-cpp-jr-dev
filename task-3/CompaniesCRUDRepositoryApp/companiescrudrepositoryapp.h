#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_companiescrudrepositoryapp.h"

class CompaniesCRUDRepositoryApp : public QMainWindow
{
    Q_OBJECT

public:
    CompaniesCRUDRepositoryApp(QWidget *parent = nullptr);
    ~CompaniesCRUDRepositoryApp();

private:
    Ui::CompaniesCRUDRepositoryAppClass ui;
};
