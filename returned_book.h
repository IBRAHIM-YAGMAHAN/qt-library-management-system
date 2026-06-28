//ibrahim omer yagmahan 22100011011
#ifndef RETURNED_BOOK_H
#define RETURNED_BOOK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class returned_book;
}

class returned_book : public QDialog
{
    Q_OBJECT

public:
    explicit returned_book(QSqlDatabase db,QWidget *parent = nullptr);
    ~returned_book();

private slots:
    void print_all();

    void on_btn_return_clicked();

    void on_tw_borrowed_clicked(const QModelIndex &index);

private:
    Ui::returned_book *ui;
    QSqlQuery *query;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
};

#endif // RETURNED_BOOK_H
