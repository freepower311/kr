#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "bintree.h"
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
void MainWindow::on_pushButton_2_clicked()
{
    int i = ui->spinBox->text().toInt();
    QString solutionResult = QString::fromStdString(solution("input4.txt",i));
    ui->lineEdit->clear();
    ui->lineEdit->insert(solutionResult);
}
void MainWindow::about()
{
   QMessageBox::about(this, tr("О программе ЛР №4"),
                      tr("Данная программа выводит узлы дерева в порядке удаления от корня справа на лево"
                         "<b> Автор: Надежин Н.Д. </b>"));
}
void MainWindow::on_pushButton_clicked()
{
    //Перестроить
    ui->treeWidget->clear();
    tree.clear();
    //MyBinTree<char> tree;
    tree.random(ui->spinBox->text.toInt());
    //read tree
    tree.printTree(ui->treeWidget);
}

void MainWindow::on_pushButton_2_clicked()
{
    //Удалить
}

void MainWindow::on_pushButton_3_clicked()
{
    //Вставить
}
