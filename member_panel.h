//ibrahim omer yagmahan 22100011011
#ifndef MEMBER_PANEL_H
#define MEMBER_PANEL_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QPainter>



namespace Ui {
class member_panel;
}

class member_panel : public QDialog
{
    Q_OBJECT

public:
    explicit member_panel(QSqlDatabase db,QWidget *parent = nullptr);
    ~member_panel();

private slots:
    void print_all();
    void on_tableView_clicked(const QModelIndex &index);
    void on_btn_new_clicked();
    void on_btn_updata_clicked();
    void on_btn_delete_clicked();

private:
    Ui::member_panel *ui;
    QSqlQuery *query;
    QSqlQueryModel *model;
};

#endif // MEMBER_PANEL_H
