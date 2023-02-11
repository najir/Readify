/************************************************************
* Book Journal
* Isaac Perks
* 2/3/23
************************************************************/
#include "bookjournal.h"

databaseObject dbObj;
sqlite3* DB;
std::string welcomeMessage = 
"Welcome to my personal book journal project. This application is used to store and maintain"
" a journal of all books you are or have read. All data is stored locally and the application"
" has zero reliance on any cloud or online service. To begin: Click \" Add New\" Enter the info"
" and finally click save to store it in your journal.";
/******************************
* GUI initialization
******************************/
bookjournal::bookjournal(QWidget *parent)
    : QMainWindow(parent){
    ui.setupUi(this);
    dbObj.createDB(DB);
    setVisual();
    ui.widgetMain->setVisible(1);
    ui.widgetPage->setVisible(0);
    updateList();
    setDefaults();
    QMessageBox::about(this, "Welcome", welcomeMessage.c_str());
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
    ui.textEditDesc->setText("Desc");
    ui.textEditNotes->setText("Note");
    ui.spinBoxRead->setValue(1);
}
void bookjournal::setVisual() {
    //Main Window
    this->setWindowFlags(this->windowFlags() | Qt::MSWindowsFixedSizeDialogHint);

    //Fonts
    QFontDatabase::addApplicationFont(":/rsc/font/CantWrite-K7nqA.ttf");
    //QFont mainFont("CantWrite-K7nqA");
    //QApplication::setFont(mainFont);

    //Main Background
    QPixmap back;
    back.load(":/rsc/img/bcg/tempBack.png");
    back = back.scaled(this->size()*1.1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette bgPal;
    bgPal.setBrush(QPalette::Window, back);
    this->setPalette(bgPal);

}
void bookjournal::updateList() {
    // This function is used to create/update the list of widgets holding book data
    ui.listWidget->clear();
    std::vector<dbStruct> listStructs = dbObj.getAllBooks(DB);
    dbStruct tempStruct;
    int i = 0;
    std::string bookImg;

    std::string listText = "";
    for (i; i < listStructs.size(); i++) {
        tempStruct = listStructs[i];
        listText = tempStruct.NAME;
        listText += "    |||    " + tempStruct.AUTHOR;
        listText += "    |||    " + std::to_string(tempStruct.PAGES);
        listText += " Pages";
        if (int(tempStruct.READ)) { bookImg = ":/rsc/img/icon/open-book.png"; }
        else { bookImg = ":/rsc/img/icon/book.png"; }
        QListWidgetItem* widgetItem = new QListWidgetItem(QIcon(bookImg.c_str()), QString::fromStdString(listText));
        widgetItem->setFont(QFont("Ink Free", 18));
        ui.listWidget->addItem(widgetItem);
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
    ui.widgetMain->setVisible(0);
    ui.widgetPage->setVisible(1);
}

/******************************
* Second Menu Operations
******************************/
void bookjournal::on_pushButtonCancel_clicked() {
    //Hide new menu, show main menu, reset data to default
    ui.widgetMain->setVisible(1);
    ui.widgetPage->setVisible(0);
    setDefaults();
    
}
void bookjournal::on_pushButtonSave_clicked() {
    //push db call, hide new menu, show main menu + update list
    dbStruct saveValues;
    saveValues.NAME = ui.lineEditName->text().toStdString();
    saveValues.AUTHOR = ui.lineEditAuthor->text().toStdString();
    saveValues.DESCRIPTION = ui.textEditDesc->toPlainText().toStdString();
    saveValues.NOTES = ui.textEditNotes->toPlainText().toStdString();
    saveValues.READ = ui.checkBox->isChecked();
    saveValues.PAGES = ui.spinBoxRead->value();
    
    dbObj.insertBook(DB, saveValues);
    updateList();
    ui.widgetMain->setVisible(1);
    ui.widgetPage->setVisible(0);
    setDefaults();
}
void bookjournal::on_pushButtonUpdate_clicked() {
    //push db call, hide new menu, show main menu + update list
    dbStruct saveValues;
    saveValues.NAME = ui.lineEditName->text().toStdString();
    saveValues.AUTHOR = ui.lineEditAuthor->text().toStdString();
    saveValues.DESCRIPTION = ui.textEditDesc->toPlainText().toStdString();
    saveValues.NOTES = ui.textEditNotes->toPlainText().toStdString();
    saveValues.READ = ui.checkBox->isChecked();
    saveValues.PAGES = ui.spinBoxRead->value();

    dbObj.updateBook(DB, saveValues, tempName);
    updateList();
    ui.widgetMain->setVisible(1);
    ui.widgetPage->setVisible(0);
    setDefaults();
}
void bookjournal::on_pushButtonDelete_clicked() {
    //push db call, hide new menu, show main menu + update list
    dbObj.deleteBook(DB, NULL, ui.lineEditName->text().toStdString());
    updateList();

    ui.widgetMain->setVisible(1);
    ui.widgetPage->setVisible(0);
    setDefaults();
}