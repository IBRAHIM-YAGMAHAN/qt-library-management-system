//ibrahim omer yagmahan 22100011011
#include "book_panel.h"
#include "ui_book_panel.h"

book_panel::book_panel(QSqlDatabase db,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::book_panel)
{
    ui->setupUi(this);
    query = new QSqlQuery(db);
    print_all();
}

book_panel::~book_panel()
{
    delete ui;
}

void book_panel::print_all()
{
    query->prepare("select * from book");
    if(!query->exec())
    {
         QMessageBox::critical(this,"Error","An error occurred while retrieving the book table!");
        return;
    }
    model = new QSqlQueryModel();
    model->setQuery(*query);
    ui->tw_all->setModel(model);
}

void book_panel::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap("qrc:/../im_2/sora_1.png");


    QPixmap scaled = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaled);
}

void book_panel::on_tw_all_clicked(const QModelIndex &index)
{
    ui->ln_no->setText(model->index(index.row(), 0).data().toString());
    ui->ln_name->setText(model->index(index.row(), 1).data().toString());
    ui->ln_stock->setText(model->index(index.row(), 2).data().toString());

    int bookNo = ui->ln_no->text().toInt();
    query->prepare("SELECT * FROM borrowed_book WHERE book_no =?");
    query->addBindValue(bookNo);

    if (!query->exec())
    {
        QMessageBox::critical(this, "Error", "An error occurred while retrieving the book table!");
        return;
    }
    model2 = new QSqlQueryModel();
    model2->setQuery(*query);
    ui->tw_now->setModel(model2);

    query->prepare("SELECT * FROM returned_book WHERE book_no =?");
    query->addBindValue(bookNo);

    if (!query->exec())
    {
        QMessageBox::critical(this, "Error", "An error occurred while retrieving the book table!");
        return;
    }
    model3 = new QSqlQueryModel();
    model3->setQuery(*query);
    ui->tw_previously->setModel(model3);
}


void book_panel::on_btn_new_clicked()
{
    if(ui->ln_name->text().isEmpty() || ui->ln_stock->text().isEmpty())
    {
        QMessageBox::critical(this,"warning!","Please fill in the gaps!");
        return;
    }
    query->prepare("insert into book (book_name,book_counter) values(?,?)");
    query->addBindValue(ui->ln_name->text());
    query->addBindValue(ui->ln_stock->text().toInt());
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error!","An error occurred while adding a new book to the book table!");
        return;
    }

    int  count =0;
    query->prepare("select * from book");
    query->exec();
    //yeni ekledimiz uyenin ID'sini cekmek icin kulandik, primary key autoincrease cunku.
    while(query->next())
    {
        count++;
    }
    QString line = "Id:%1\nBook name:%2\nStock:%3\nHas been added!";
    QMessageBox::information(this,"New book",line.arg(count).arg(ui->ln_name->text()).arg(ui->ln_stock->text()));
    print_all();
}

void book_panel::on_btn_updata_clicked()
{
    if(ui->ln_name->text().isEmpty() || ui->ln_stock->text().isEmpty())
    {
        QMessageBox::critical(this,"warning!","Please fill in the gaps!");
        return;
    }
    query->prepare("UPDATE book SET book_name=?, book_counter=? WHERE book_no=?");
    query->addBindValue(ui->ln_name->text());
    query->addBindValue(ui->ln_stock->text().toInt());
    query->addBindValue(ui->ln_no->text().toInt());
    if(!query->exec())
    {
        QMessageBox::critical(this,"Error!","An error occurred while retrieving the book table!");
        return;
    }
    QString line = "Id:%1\nName:%2\nSurname:%3\nHas been update!";
    QMessageBox::information(this,"New book ",line.arg(ui->ln_no->text()).arg(ui->ln_name->text()).arg(ui->ln_stock->text()));
    print_all();
}


void book_panel::on_btn_delete_clicked()
{
    query->prepare("select * from borrowed_book where book_no =?");
    query->addBindValue(ui->ln_no->text().toInt());
    query->exec();
    int counter=0;
    while (query->next())
    {
        counter++;
    }
    if(counter>0)
    {
        QMessageBox::critical(this,"warning","This book cannot be deleted because they have a borrowed!");
        return;
    }
    else
    {
        query->prepare("delete from book where book_no= ?");
        query->addBindValue(ui->ln_no->text().toInt());
        if(!query->exec())
        {
            QMessageBox::critical(this,"hata","An error occurred while deleting that book from the book table!");
            return;
        }
        print_all();
        QString line = "Id:%1\nName:%2\nStock:%3\nHas been delete!";
        QMessageBox::information(this,"Book info",line.arg(ui->ln_no->text()).arg(ui->ln_name->text()).arg(ui->ln_stock->text()));
    }
}

