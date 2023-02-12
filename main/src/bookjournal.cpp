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
    ui.widgetEdit->setVisible(0);
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

    //Main Background
    QPixmap back;
    back.load(":/rsc/img/bcg/tempBack.png");
    back = back.scaled(this->size()*1.3, Qt::KeepAspectRatio, Qt::SmoothTransformation);
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
    std::string bookDir;
    QIcon bookImg;

    std::string listText = "";
    for (i; i < listStructs.size(); i++) {
        tempStruct = listStructs[i];
        listText = std::to_string(tempStruct.ID);
        listText += ". " + tempStruct.NAME;
        listText += " | " + tempStruct.AUTHOR;
        listText += " | " + std::to_string(tempStruct.PAGES);
        listText += "Pg";
        if (int(tempStruct.READ)) { bookDir = ":/rsc/img/icons/book.png"; }
        else { bookDir = ":/rsc/img/icons/open-book.png"; }
        bookImg = QIcon(bookDir.c_str());
        QListWidgetItem* widgetItem = new QListWidgetItem(QIcon(bookImg), QString::fromStdString(listText));
        widgetItem->setFont(QFont("Ink Free", 16));
        ui.listWidget->addItem(widgetItem);
    }
}


/******************************
* Main Menu Operations
******************************/
void bookjournal::on_listWidget_doubleClicked() {
    dbStruct bookDataEntry;
    std::string bookText = ui.listWidget->currentItem()->text().toStdString();
    std::string findQuery;
    int i;
    
    for (i = 0; i < bookText.size(); i++) {
        if (bookText[i] == '.') {
            findQuery = bookText.substr(0, i);
            i = bookText.size();
        }
    }
    bookDataEntry = dbObj.getBook(DB, NULL, findQuery);

    ui.lineEditName_2->setText(QString(bookDataEntry.NAME.c_str()));
    ui.lineEditAuthor_2->setText(QString(bookDataEntry.AUTHOR.c_str()));
    ui.textEditDesc_2->setText(QString(bookDataEntry.DESCRIPTION.c_str()));
    ui.textEditNotes_2->setText(QString(bookDataEntry.NOTES.c_str()));
    ui.checkBox_3->setChecked(bookDataEntry.READ);
    ui.spinBoxRead_3->setValue(bookDataEntry.PAGES);
    ui.widgetMain->hide();
    ui.widgetEdit->show();
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
void bookjournal::on_pushButtonCancel_2_clicked() {
    //Hide new menu, show main menu, reset data to default
    ui.widgetMain->setVisible(1);
    ui.widgetEdit->setVisible(0);
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
    
    if (saveValues.NAME == "" || saveValues.AUTHOR == "") {
        QMessageBox::warning(this, "Insert Error", "Please make sure all the fields are entered correctly");
    }
    else {
        dbObj.insertBook(DB, saveValues);
        updateList();
        ui.widgetMain->setVisible(1);
        ui.widgetPage->setVisible(0);
        setDefaults();
    }
}
void bookjournal::on_pushButtonUpdate_clicked() {
    //push db call, hide new menu, show main menu + update list
    dbStruct saveValues;
    saveValues.NAME = ui.lineEditName_2->text().toStdString();
    saveValues.AUTHOR = ui.lineEditAuthor_2->text().toStdString();
    saveValues.DESCRIPTION = ui.textEditDesc_2->toPlainText().toStdString();
    saveValues.NOTES = ui.textEditNotes_2->toPlainText().toStdString();
    saveValues.READ = ui.checkBox_3->isChecked();
    saveValues.PAGES = ui.spinBoxRead_3->value();
    std::string bookText = ui.listWidget->currentItem()->text().toStdString();
    std::string findQuery;
    int i;

    for (i = 0; i < bookText.size(); i++) {
        if (bookText[i] == '.') {
            findQuery = bookText.substr(0, i);
            i = bookText.size();
        }
    }

    dbObj.updateBook(DB, saveValues, findQuery);
    updateList();
    ui.widgetMain->setVisible(1);
    ui.widgetEdit->setVisible(0);
    setDefaults();
}
void bookjournal::on_pushButtonDelete_clicked() {
    //push db call, hide new menu, show main menu + update list
    std::string bookText = ui.listWidget->currentItem()->text().toStdString();
    std::string findQuery;
    int i;

    for (i = 0; i < bookText.size(); i++) {
        if (bookText[i] == '.') {
            findQuery = bookText.substr(0, i);
            i = bookText.size();
        }
    }
    dbObj.deleteBook(DB, NULL, findQuery);
    updateList();

    ui.widgetMain->setVisible(1);
    ui.widgetEdit->setVisible(0);
    setDefaults();
}