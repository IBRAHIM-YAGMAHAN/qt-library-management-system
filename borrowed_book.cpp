//ibrahim omer yagmahan 22100011011
#include "borrowed_book.h"
#include "ui_borrowed_book.h"

borrowed_book::borrowed_book(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::borrowed_book)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    print_all();
}

borrowed_book::~borrowed_book()
{
    delete ui;
}

void borrowed_book::print_all()
{
    query->prepare("select * from member");
    if(!query->exec())
    {
        QMessageBox::critical(this,"warning","An error occurred while retrieving the member table!");
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery(*query);
    ui->tw_all_mem->setModel(model);

    query->prepare("select * from book");
    if(!query->exec())
    {
        QMessageBox::critical(this,"warning","An error occurred while retrieving the book table!");
        return;
    }
    model2 = new QSqlQueryModel();
    model2->setQuery(*query);
    ui->tw_all_book->setModel(model2);

    query->prepare("select * from borrowed_book");
    if(!query->exec())
    {
        QMessageBox::critical(this,"warning","An error occurred while retrieving the borrowed_book table!");
        return;
    }
    model3 = new QSqlQueryModel();
    model3->setQuery(*query);
    ui->tw_borrowed->setModel(model3);
}


void borrowed_book::on_tw_all_mem_clicked(const QModelIndex &indexx)
{
    ui->ln_mem_no->setText(model->index(indexx.row(),0).data().toString());
}

void borrowed_book::on_tw_all_book_clicked(const QModelIndex &indexx)
{
    ui->ln_book_no->setText(model2->index(indexx.row(),0).data().toString());
}


void borrowed_book::on_btn_borrow_clicked()
{
    if (ui->ln_mem_no->text().isEmpty() || ui->ln_book_no->text().isEmpty()) {
        QMessageBox::warning(this, "Warning", "Member number and book number cannot be empty.");
        return;
    }

    query->prepare("select count(*) from borrowed_book where member_no=? and book_no=?");
    query->addBindValue(ui->ln_mem_no->text().toInt());
    query->addBindValue(ui->ln_book_no->text().toInt());
    if (!query->exec())
    {
        QMessageBox::critical(this, "Error", "An error occurred while retrieving the borrowed_book table!");
        return;
    }

    while(query->next()) {
        int count = query->value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "warning", "This book has already been loaned to this borrower!");
            return;
        }
    }


    query->prepare("select book_counter from book where book_no=?");
    query->addBindValue(ui->ln_book_no->text().toInt());
    if (!query->exec()) {
        QMessageBox::critical(this, "Error", "An error occurred while retrieving the stock of the book in the book table.");
        return;
    }

    if (query->next())
    {
        int stok = query->value(0).toInt();
        if (stok <= 0)
        {
            QMessageBox::warning(this, "warning", "The book is out of stock.");
            return;
        }
    }

    query->prepare("insert into borrowed_book(member_no,book_no,borrowed_date) values(?,?,?)");
    query->addBindValue(ui->ln_mem_no->text().toInt());
    query->addBindValue(ui->ln_book_no->text().toInt());
    query->addBindValue(ui->dateEdit->text());
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error","An error occurred during the loan transaction processing!");
    }
    print_all();
}



