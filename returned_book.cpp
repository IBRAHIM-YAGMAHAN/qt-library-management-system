//ibrahim omer yagmahan 22100011011
#include "returned_book.h"
#include "ui_returned_book.h"

returned_book::returned_book(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::returned_book)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    print_all();
}

returned_book::~returned_book()
{
    delete ui;
}

void returned_book::print_all()
{
    query->prepare("select * from borrowed_book");
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error","An error occurred while retrieving the borrowed_book table!");
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery(*query);
    ui->tw_borrowed->setModel(model);

    query->prepare("select * from returned_book");
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error","An error occurred while retrieving the returned_book table!");
        return;
    }
    model2 = new QSqlQueryModel();
    model2->setQuery(*query);
    ui->tw_returned->setModel(model2);
}

void returned_book::on_tw_borrowed_clicked(const QModelIndex &index)
{
    ui->ln_mem_no->setText(model->index(index.row(), 0).data().toString());
    ui->ln_book_no->setText(model->index(index.row(), 1).data().toString());
}

void returned_book::on_btn_return_clicked()
{
    if (ui->ln_book_no->text().isEmpty() || ui->ln_mem_no->text().isEmpty())
    {
        QMessageBox::critical(this, "Warning!", "Please fill in the gaps!");
        return;
    }

    query->prepare("select * from borrowed_book where book_no=? and member_no=?");
    query->addBindValue(ui->ln_book_no->text().toInt());
    query->addBindValue(ui->ln_mem_no->text().toInt());

    if (!query->exec())
    {
        QMessageBox::critical(this, "Error", "An error occurred while retrieving the borrowed book record!");
        return;
    }

    QString alma_tarihi;
    if (query->next())
    {
        // `borrowed_date` alanının indeksini bulmak için sütun adını kullanmak daha güvenlidir
        alma_tarihi = query->value("borrowed_date").toString();
    }
    else
    {
        QMessageBox::critical(this, "Error", "No borrowed book record found for the given book and member!");
        return;
    }

    QDate alma = QDate::fromString(alma_tarihi, "dd/MM/yyyy");
    QDate verme = ui->dateEdit_2->date();
    int dept = 0;
    int gun_farki = alma.daysTo(verme);

    if (gun_farki > 15)
    {
        dept = (gun_farki - 15) * 4;
    }

    query->prepare("insert into returned_book(member_no, book_no, borrowed_date, due_date, dept) values (?, ?, ?, ?, ?)");
    query->addBindValue(ui->ln_mem_no->text().toInt());
    query->addBindValue(ui->ln_book_no->text().toInt());
    query->addBindValue(alma_tarihi);
    query->addBindValue(ui->dateEdit_2->text());
    query->addBindValue(dept);

    if (!query->exec())
    {
        QMessageBox::critical(this, "Error", "An error occurred when the book was returned!");
        return;
    }

    query->prepare("delete from borrowed_book where member_no = ? and book_no = ?");
    query->addBindValue(ui->ln_mem_no->text().toInt());
    query->addBindValue(ui->ln_book_no->text().toInt());

    if (!query->exec())
    {
        QMessageBox::critical(this, "Error", "An error occurred while deleting the borrowed book record!");
        return;
    }

    print_all();
}

