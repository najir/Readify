/************************************************************
* Book Journal
* Isaac Perks
* 2/3/23
************************************************************/
#include "bookjournal.h"
#include "bookjournaldb.h"

sqlite3* DB;

/******************************
* GUI initialization
******************************/
bookjournal::bookjournal(QWidget *parent)
    : QMainWindow(parent){
    ui.setupUi(this);
    createDB(DB);
}

bookjournal::~bookjournal(){

}


/******************************
* Helper Functions
******************************/
void bookjournal::setDefaults() {
    ui.checkBox->setChecked(0);
    ui.lineEditName->setText("Name");
    ui.lineEditAuthor->setText("Author");
    ui.textEditDesc->setText("");
    ui.textEditNotes->setText("");
    ui.spinBoxRead->setValue(0);
}
void bookjournal::updateList() {
    // This function is used to create/update the list of widgets holding book data
    std::vector<dbStruct> listStructs = getAllBooks(DB);
    dbStruct tempStruct;
    int i = 0;
    QString listText = "";
    for (i; i < listStructs.size(); i++) {
        tempStruct = listStructs[i];
        listText = tempStruct.NAME.c_str();
        listText += "    |    " + tempStruct.AUTHOR;
        listText += "    |    " + tempStruct.PAGES;
        listText += " Pages";
        QListWidgetItem()   
    }
}


/******************************
* Main Menu Operations
******************************/
void bookjournal::on_listWidget_doubleClicked() {
    std::vector<dbStruct> bookData;
    dbStruct bookDataEntry = bookData[0];
    tempName = bookDataEntry.NAME;

    ui.lineEditName->setText(QString(bookDataEntry.NAME.c_str()));
    ui.lineEditAuthor->setText(QString(bookDataEntry.AUTHOR.c_str()));
    ui.textEditDesc->setText(QString(bookDataEntry.DESCRIPTION.c_str()));
    ui.textEditNotes->setText(QString(bookDataEntry.NOTES.c_str()));
    ui.checkBox->setChecked(bookDataEntry.READ);
    ui.spinBoxRead->setValue(bookDataEntry.PAGES);
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
    dbStruct saveValues;
    saveValues.NAME = ui.lineEditName->text().toDouble();
    saveValues.AUTHOR = ui.lineEditAuthor->text().toDouble();
    saveValues.DESCRIPTION = ui.textEditDesc->toPlainText().toDouble();
    saveValues.NOTES = ui.textEditNotes->toPlainText().toDouble();
    saveValues.READ = ui.checkBox->isChecked();
    saveValues.PAGES = ui.spinBoxRead->value();
    
    insertBook(DB, saveValues);
    updateList();
    ui.widgetMain->show();
    ui.widgetPage->hide();
    setDefaults();
}
void bookjournal::on_pushButtonUpdate_clicked() {
    //push db call, hide new menu, show main menu + update list
    dbStruct saveValues;
    saveValues.NAME = ui.lineEditName->text().toDouble();
    saveValues.AUTHOR = ui.lineEditAuthor->text().toDouble();
    saveValues.DESCRIPTION = ui.textEditDesc->toPlainText().toDouble();
    saveValues.NOTES = ui.textEditNotes->toPlainText().toDouble();
    saveValues.READ = ui.checkBox->isChecked();
    saveValues.PAGES = ui.spinBoxRead->value();

    updateBook(DB, saveValues, tempName);
    updateList();
    ui.widgetMain->show();
    ui.widgetPage->hide();
    setDefaults();
}
void bookjournal::on_pushButtonDelete_clicked() {
    //push db call, hide new menu, show main menu + update list
    deleteBook(DB, NULL, ui.lineEditName->text().toStdString());
    updateList();

    ui.widgetMain->show();
    ui.widgetPage->hide();
    setDefaults();
}