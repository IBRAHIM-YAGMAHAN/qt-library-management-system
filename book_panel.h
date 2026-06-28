//ibrahim omer yagmahan 22100011011
#ifndef BOOK_PANEL_H
#define BOOK_PANEL_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPainter>

namespace Ui {
class book_panel;
}

class book_panel : public QDialog
{
    Q_OBJECT

public:
    explicit book_panel(QSqlDatabase db,QWidget *parent = nullptr);
    ~book_panel();

private slots:
    void print_all();

    void on_tw_all_clicked(const QModelIndex &index);

    void on_btn_new_clicked();

    void on_btn_updata_clicked();

    void on_btn_delete_clicked();

    void paintEvent(QPaintEvent *);

private:
    Ui::book_panel *ui;
    QSqlQuery *query;
    QSqlQueryModel *model;
    QSqlQueryModel *model2;
    QSqlQueryModel *model3;
};

#endif // BOOK_PANEL_H
