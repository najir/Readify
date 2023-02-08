/************************************************************
* Book Journal
* Isaac Perks
* 2/3/23
************************************************************/
#include "bookjournal.h"
#include "bookjournaldb.h"

/******************************
* GUI initialization
******************************/
bookjournal::bookjournal(QWidget *parent)
    : QMainWindow(parent){
    ui.setupUi(this);
}

bookjournal::~bookjournal(){

}

void bookjournal::setDefaults() {
    ui.checkBox->setChecked(0);
    ui.lineEditName->setText("Name");
    ui.lineEditAuthor->setText("Author");
    ui.textEditDesc->setText("");
    ui.textEditNotes->setText("");
    ui.spinBoxRead->setValue(0);
}
/******************************
* Main Menu Operations
******************************/
void bookjournal::on_listWidget_doubleClicked() {
    ui.widgetMain->hide();
    ui.widgetPage->show();
}
void bookjournal::on_pushButtonNew_clicked() {
    //Hide main menu, show new menu
    ui.widgetMain->hide();
    ui.widgetPage->show();
}

/******************************
* Second Menu Operations
******************************/
void bookjournal::on_pushButtonCancel_clicked() {
    //Hide new menu, show main menu, reset data to default
    ui.widgetMain->show();
    ui.widgetPage->hide();
    setDefaults();
    
}
void bookjournal::on_pushButtonSave_clicked() {
    //push db call, hide new menu, show main menu + update list
    ui.widgetMain->show();
    ui.widgetPage->hide();
    dbStruct saveValues;
    saveValues.NAME = ui.lineEditName->text().toDouble();
    saveValues.AUTHOR = ui.lineEditAuthor->text().toDouble();
    saveValues.DESCRIPTION = ui.textEditDesc->toPlainText().toDouble();
    saveValues.NOTES = ui.textEditNotes->toPlainText().toDouble();
    saveValues.READ = ui.checkBox->isChecked();
    saveValues.PAGES = ui.spinBoxRead->value();
    
    setDefaults();


}