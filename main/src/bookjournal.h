#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_bookjournal.h"

class bookjournal : public QMainWindow
{
    Q_OBJECT

public:
    bookjournal(QWidget* parent = nullptr);
    ~bookjournal();

private:
    Ui::bookjournalClass ui;
    void on_listWidget_doubleClicked();
    void on_pushButtonNew_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
};
