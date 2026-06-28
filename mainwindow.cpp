//ibrahim omer yagmahan 22100011011
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db.setDatabaseName("database.db");
    if(!db.open())
    {
        ui->statusbar->showMessage("Failed to connect to database");
    }
    else
    {
        ui->statusbar->showMessage("Connect to database");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_user_clicked()
{
    member_panel *member = new member_panel(db,this);
    member->show();
}


void MainWindow::on_pushButton_clicked()
{
    book_panel *books = new book_panel(db,this);
    books->show();
}


void MainWindow::on_pushButton_3_clicked()
{
    borrowed_book *borrow = new borrowed_book(db,this);
    borrow->show();
}


void MainWindow::on_pushButton_4_clicked()
{
    returned_book *returned = new returned_book(db,this);
    returned->show();
}

