//ibrahim omer yagmahan 22100011011
#include "member_panel.h"
#include "ui_member_panel.h"



member_panel::member_panel(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::member_panel)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    print_all();

}

member_panel::~member_panel()
{
    delete ui;
}

void member_panel::print_all()
{
    query->prepare("select * from member");
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error","An error occurred while retrieving the member table!");
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery(*query);
    ui->tableView->setModel(model);
}

void member_panel::on_tableView_clicked(const QModelIndex &index)
{
    ui->ln_no->setText(model->index(index.row(),0).data().toString());
    ui->ln_name->setText(model->index(index.row(),1).data().toString());
    ui->ln_surname->setText(model->index(index.row(),2).data().toString());
}


void member_panel::on_btn_new_clicked()
{
    if(ui->ln_name->text().isEmpty() || ui->ln_surname->text().isEmpty())
    {
        QMessageBox::critical(this,"warning","Please fill in the gaps!");
        return;
    }
    query->prepare("insert into member(member_name,member_surname) values(?,?)");
    query->addBindValue(ui->ln_name->text());
    query->addBindValue(ui->ln_surname->text());
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error","An error occurred while retrieving the member table!");
        return;
    }    
    query->prepare("select * from member");
    query->exec();
    int counter = 0;

    //yeni ekledimiz uyenin ID'sini cekmek icin kulandik, primary key autoincrease cunku.
    while(query->next())
    {
        counter++;
    }

    QString line = "Id:%1\nName:%2\nSurname:%3\nHas been added!";
    QMessageBox::information(this,"New member ",line.arg(counter).arg(ui->ln_name->text()).arg(ui->ln_surname->text()));
    print_all();
}


void member_panel::on_btn_updata_clicked()
{
    if(ui->ln_name->text().isEmpty() || ui->ln_surname->text().isEmpty())
    {
        QMessageBox::critical(this,"warning","Please fill in the gaps!");
        return;
    }
    query->prepare("UPDATE member SET member_name=?, member_surname=? WHERE member_no=?");
    query->addBindValue(ui->ln_name->text());
    query->addBindValue(ui->ln_surname->text());
    query->addBindValue(ui->ln_no->text());
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error!","An error occurred while update an member to the member table!");
        return;
    }
    QString line = "Id:%1\nName:%2\nSurname:%3\nHas been update!";
    QMessageBox::information(this,"New member info",line.arg(ui->ln_no->text()).arg(ui->ln_name->text()).arg(ui->ln_surname->text()));
    print_all();
}



void member_panel::on_btn_delete_clicked()
{
    query->prepare("select * from borrowed_book where member_no =?");
    query->addBindValue(ui->ln_no->text().toInt());
    query->exec();
    int counter=0;
    while (query->next())
    {
        counter++;
    }
    if(counter>0)
    {
        QMessageBox::critical(this,"warning","This user cannot be deleted because they have a borrowed book!");
        return;
    }
    else
    {
        query->prepare("delete from member where member_no= ?");
        query->addBindValue(ui->ln_no->text().toInt());
        if(!query->exec())
        {
            QMessageBox::critical(this,"Error","An error occurred while deleting that member from the member table!");
            return;
        }
        print_all();
        QString line = "Id:%1\nName:%2\nSurname:%3\nHas been delete!";
        QMessageBox::information(this,"Member info",line.arg(ui->ln_no->text()).arg(ui->ln_name->text()).arg(ui->ln_surname->text()));
    }
}

