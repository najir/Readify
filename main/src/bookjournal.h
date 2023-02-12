#pragma once

#include <QtWidgets/QMainWindow>
#include <qmessagebox.h>
#include <QFontDatabase>
#include "ui_bookjournal.h"
#include "bookjournaldb.h"

class bookjournal : public QMainWindow
{
    Q_OBJECT

public:
    bookjournal(QWidget* parent = nullptr);
    ~bookjournal();
    void setDefaults();
    void updateList();
    void setVisual();

private:
    std::string tempName;               // Saves old book name for updating changes on db
    Ui::bookjournalClass ui;

private slots:
    void on_listWidget_doubleClicked();
    void on_pushButtonNew_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_2_clicked();
};
