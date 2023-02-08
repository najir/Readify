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


/******************************
* Main Menu Operations
******************************/
void bookjournal::on_listWidget_doubleClicked() {

}
void bookjournal::on_pushButtonNew_clicked() {
    //Hide main menu, show new menu
    ui.verticalLayoutWidget->hide();
    ui.verticalLayoutWidget_2->show();
}

/******************************
* Second Menu Operations
******************************/
void bookjournal::on_pushButtonCancel_clicked() {
    //Hide new menu, show main menu
    ui.verticalLayoutWidget->show();
    ui.verticalLayoutWidget_2->hide();
}
void bookjournal::on_pushButtonSave_clicked() {
    //push db call, hide new menu, show main menu + update list
    ui.verticalLayoutWidget->show();
    ui.verticalLayoutWidget_2->hide();
}