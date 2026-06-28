//ibrahim omer yagmahan 22100011011
#ifndef BORROWED_BOOK_H
#define BORROWED_BOOK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class borrowed_book;
}

class borrowed_book : public QDialog
{
    Q_OBJECT

public:
    explicit borrowed_book(QSqlDatabase db,QWidget *parent = nullptr);
    ~borrowed_book();

private slots:
    void print_all();

    void on_tw_all_mem_clicked(const QModelIndex &index);

    void on_tw_all_book_clicked(const QModelIndex &index);

    void on_btn_borrow_clicked();

private:
    Ui::borrowed_book *ui;
    QSqlQuery *query;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;
};

#endif // BORROWED_BOOK_H
