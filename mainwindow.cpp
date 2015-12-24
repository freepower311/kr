#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <sstream>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action, SIGNAL(triggered()), this, SLOT(about()));
    outfile.open("outKR_BDP.txt");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::about()
{
   QMessageBox::about(this, tr("О программе КР-БДП"),
                      tr("Данная программа служит для изучения времени выполнения операций удаления и вставки в БДП"
                         "<b> Автор: Надежин Н.Д. </b>"));
}
std::string fromIntToStr(int proctime)
{
    std::string str,rlt;
    if (proctime == 0) rlt = "0";
    if (proctime < 0)
    {
        rlt += '-';
        proctime *= -1;
    }
    while (proctime != 0)
    {
        str += proctime % 10 + '0';
        proctime /= 10;
    }
    for (int i = str.length();i > 0;i--) rlt += str[i-1];
    return rlt;
}
std::string fromDoubleToStr(double x)
{
    std::ostringstream ost;
    ost << x;
    return ost.str();

}
void MainWindow::on_pushButton_clicked()
{
    //Перестроить
    ui->treeWidget->clear();
    tree.clear();
    int volume = (ui->lineEdit_2->text().toInt());
    ui->textBrowser->clear();
    ui->lineEdit_3->clear();
    int proctime = clock();
    if (volume > 0)
    {
        tree.pushRandomElem(volume);
        proctime = clock() - proctime;
        if(ui->checkBox_2->isChecked()) tree.printTree(ui->treeWidget);
        if(ui->checkBox->isChecked()) ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
        ui->lineEdit_3->insert(QString::fromStdString(fromIntToStr(tree.height())));
    }
    else proctime = clock() - proctime;
    ui->time->clear();
    ui->time->insert(QString::fromStdString(fromIntToStr(proctime)));
}

void MainWindow::on_pushButton_2_clicked()
{
    //Удалить
    std::string str = ui->lineEdit->text().toStdString();
    int proctime = clock();
    if (!tree.deleteNode(str[0],str[1],str[2],str[3],str[4]))
    {
        proctime = clock() - proctime;
        QMessageBox::about(this, tr("Ошибка"),
                           tr("Не удалось удалить элемент из дерева, возможно, он не присутствует в нем"));
    }
    else proctime = clock() - proctime;
    ui->treeWidget->clear();
    if(ui->checkBox_2->isChecked()) tree.printTree(ui->treeWidget);
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked()) ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
    ui->time->clear();
    ui->time->insert(QString::fromStdString(fromIntToStr(proctime)));
    ui->lineEdit_3->clear();
    ui->lineEdit_3->insert(QString::fromStdString(fromIntToStr(tree.height())));
}

void MainWindow::on_pushButton_3_clicked()
{
    //Вставить
    std::string str = ui->lineEdit->text().toStdString();
    int proctime = clock();
    if(!tree.push(str[0],str[1],str[2],str[3],str[4]))
    {
        proctime = clock() - proctime;
        QMessageBox::about(this, tr("Ошибка"),
                           tr("Не удалось добавить элемент в дерево, возможно, он уже существует"));
    }
    else proctime = clock() - proctime;
    ui->treeWidget->clear();
    if(ui->checkBox_2->isChecked()) tree.printTree(ui->treeWidget);
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked()) ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
    ui->time->clear();
    ui->time->insert(QString::fromStdString(fromIntToStr(proctime)));
    ui->lineEdit_3->clear();
    ui->lineEdit_3->insert(QString::fromStdString(fromIntToStr(tree.height())));
}
void MainWindow::on_pushButton_4_clicked()
{
    //Вставка случайного элемента в дерево
    //int count = (ui->lineEdit_4->text().toInt());
    if (tree.height() > 15000)
    {
        QMessageBox::about(this, tr("Ошибка"),
                           tr("Превышена максимальная высота дерева! Его необходимо перестроить!"));
        return;
    }
    int count = 10000;
    srand(time(NULL));
    char **matr = new char* [count];
    for (int i = 0; i< count;i++) matr[i] = new char [5];
    for (int i = 0;i< count;i++)
    {
        for (int j = 0; j<5; j++) matr[i][j] = rand() % 26 + 'a';
    }
    int proctime = clock();
    for(int i = 0;i< count;i++)
    {
        tree.push(matr[i][0],matr[i][1],matr[i][2],matr[i][3],matr[i][4]);
    }
    proctime = clock() - proctime;
    for (int i = 0; i< count;i++) delete [] matr[i];
    delete matr;
    ui->treeWidget->clear();
    if(ui->checkBox_2->isChecked()) tree.printTree(ui->treeWidget);
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked()) ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
    ui->time->clear();
    ui->time->insert(QString::fromStdString(fromIntToStr(proctime)));
    double avertime = 1.0*proctime/count;
    ui->lineEdit_3->clear();
    ui->lineEdit_3->insert(QString::fromStdString(fromIntToStr(tree.height())));
    ui->lineEdit_5->clear();
    ui->lineEdit_5->insert(QString::fromStdString(fromDoubleToStr(avertime)));
}

void MainWindow::on_pushButton_5_clicked()
{
    //Тест 2 в+и
    //Вставка случайного элемента в дерево
    //int count = (ui->lineEdit_4->text().toInt());
    if (tree.height() > 15000)
    {
        QMessageBox::about(this, tr("Ошибка"),
                           tr("Превышена максимальная высота дерева! Его необходимо перестроить!"));
        return;
    }
    int count = 10000;
    int proctime = clock();
    tree.test2(count);
    proctime = clock() - proctime;
    ui->treeWidget->clear();
    if(ui->checkBox_2->isChecked()) tree.printTree(ui->treeWidget);
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked()) ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
    ui->time->clear();
    ui->time->insert(QString::fromStdString(fromIntToStr(proctime)));
    double avertime = 1.0*proctime/count;
    ui->lineEdit_3->clear();
    ui->lineEdit_3->insert(QString::fromStdString(fromIntToStr(tree.height())));
    ui->lineEdit_7->clear();
    ui->lineEdit_7->insert(QString::fromStdString(fromDoubleToStr(avertime)));
}

void MainWindow::on_pushButton_6_clicked()
{
    //Тест 3 удаление
    if (tree.height() > 15000)
    {
        QMessageBox::about(this, tr("Ошибка"),
                           tr("Превышена максимальная высота дерева! Его необходимо перестроить!"));
        return;
    }
    int count = 10000;
    int proctime = clock();
    tree.test2(count);
    proctime = clock() - proctime;
    ui->treeWidget->clear();
    if(ui->checkBox_2->isChecked()) tree.printTree(ui->treeWidget);
    ui->textBrowser->clear();
    if(ui->checkBox->isChecked()) ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
    ui->time->clear();
    ui->time->insert(QString::fromStdString(fromIntToStr(proctime)));
    double avertime = 1.0*proctime/count;
    ui->lineEdit_3->clear();
    ui->lineEdit_3->insert(QString::fromStdString(fromIntToStr(tree.height())));
    ui->lineEdit_8->clear();
    ui->lineEdit_8->insert(QString::fromStdString(fromDoubleToStr(avertime)));
}
