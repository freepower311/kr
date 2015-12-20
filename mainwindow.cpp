#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "bintree.h"
#include "solution.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(ui->action, SIGNAL(triggered()), this, SLOT(about()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::on_pushButton_2_clicked()
{
    int i = ui->spinBox->text().toInt();
    QString solutionResult = QString::fromStdString(solution("input4.txt",i));
    ui->lineEdit->clear();
    ui->lineEdit->insert(solutionResult);
}*/
void MainWindow::about()
{
   QMessageBox::about(this, tr("О программе ЛР №4"),
                      tr("Данная программа выводит узлы дерева в порядке удаления от корня справа на лево"
                         "<b> Автор: Надежин Н.Д. </b>"));
}
void MainWindow::on_pushButton_clicked()
{
    //Перестроить
    int proctime = clock();
    ui->treeWidget->clear();
    tree.clear();
    //MyBinTree<char> tree;
    int volume = (ui->lineEdit_2->text().toInt());
    //tree.random(ui->spinBox->text.toInt());
    ui->textBrowser->clear();
    if (volume > 0)
    {
        tree.random(volume);
        tree.printTree(ui->treeWidget);
        ui->textBrowser->append(QString::fromStdString(tree.toStdString()));
    }
    proctime = clock() - proctime;
    std::string str,rlt;
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
    ui->time->clear();
    ui->time->insert(QString::fromStdString(rlt));
}

void MainWindow::on_pushButton_2_clicked()
{
    //Удалить
}

void MainWindow::on_pushButton_3_clicked()
{
    //Вставить
}
