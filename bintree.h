#ifndef BINTREE
#define BINTREE
#include <string>
//#include "myqueue.h"
//#include "mystack.h"
#include <cstdlib>
#include <ctime>
#include <QTreeWidget>
///Элемент дерева.
/*
 *Структура данных. Представляет собой элемент дерева.
*/
template<typename T>
struct NodeBTree
{
    T val1;
    T val2;
    T val3;
    NodeBTree* left;
    NodeBTree* right;
    NodeBTree()
    {
        left = NULL;
        right = NULL;
    }
};
/*
 * Класс MuBinTree представляет из себя бинарное дерево
 * Служит для записи произвольного значения в дерево.
 * Методы:
 *
*/
template<typename T>
class MyBinTree
{
    NodeBTree<T>* head;
    //NodeBTree<T>* head;
    //std::string str;
    //int ind;
    //int len;
	//Double trouble
	//Triple trouble
public:
    MyBinTree()
    {
        head = NULL;
        //ind = 0;
        //len =0;
    }
	~MyBinTree()
    {
        if (!isEmpty())
        {
            deleteAllElem(head);
        }
        head = NULL;
    }
    void clear()
    {
        if (!isEmpty())
        {
            deleteAllElem(head);
        }
        head = NULL;
    }
    ///Выводит дерево в QTreeWidget для графического представления
	void printTree(QTreeWidget* widget) 
	{
 	   QTreeWidgetItem* root = new QTreeWidgetItem(widget);
       //root->setText(0, QString("root"));
       std::string str;
       writeVal(head->val1,str);
       writeVal(head->val2,str);
       writeVal(head->val3,str);
       root->setText(0, QString::fromStdString(str));
 	   printTree(root, head);
 	   widget->addTopLevelItem(root);
 	   widget->expandAll();
 	   widget->resizeColumnToContents(0);
	}
	///Функция перевода бинарного дерева в скобочное представление
    std::string toStdString()
    {
        std::string str;
        write(str, head);
        return str;
    }
	///Считывает бинарное дерево из строки со скобочным представлением дерева и формирует его
    void random(int h)
    {
        //char ch;
        srand(time(NULL));
        for (int i = 0; i < h; i++)
        {
            //ch =  rand() % 25 + 'a';
            push((char)(rand() % 25 + 'a'),(char)(rand() % 25 + 'a'),(char)(rand() % 25 + 'a'));
        }
    }
    bool push(char ch1,char ch2,char ch3)
    {
       return pushRec(head, ch1,ch2,ch3);
    }
    /*bool deleteNode()
    {

    }*/
private:
    bool pushRec(NodeBTree<T>* &cur, char ch1,char ch2,char ch3)
    {
        if(cur == NULL)
        {
            cur = cons(ch1,ch2,ch3,NULL,NULL);
            return 1;
        }
        bool e1 = 0,
                e2 = 0,
                e3 = 0;
        if (cur->val1 == ch1) e1 = 1;
        if (cur->val2 == ch2) e2 = 1;
        if (cur->val3 == ch3) e3 = 1;
        if (e1 && e2 && e3) return 0;
        if (cur->val1 < ch1) return pushRec(cur->left,ch1,ch2,ch3);
        if (e1 && cur->val2 < ch2) return pushRec(cur->left,ch1,ch2,ch3);
        else return pushRec(cur->right,ch1,ch2,ch3);
        if (e2 && cur->val3 < ch3)return pushRec(cur->left,ch1,ch2,ch3);
        else return pushRec(cur->right,ch1,ch2,ch3);
    }
	///Специальная функция для вывода дерева
    void printTree(QTreeWidgetItem*& item, NodeBTree<T>*& node)
	{
		std::string str;
        writeVal(node->val1,str);
        writeVal(node->val2,str);
        writeVal(node->val3,str);
        item->setText(0, QString::fromStdString(str));
        str.clear();
        if (node->left != NULL) {
	        QTreeWidgetItem* left = new QTreeWidgetItem(item);
            //left->setText(0, QString("left"));
            //left->setText(0, node->left->val);
            printTree(left, node->left);
	    }

        if (node->right != NULL) {
	        QTreeWidgetItem* right = new QTreeWidgetItem(item);
            //right->setText(0, QString("right"));
            //right->setText(0, node->right->val);
	        printTree(right, node->right);
	    }
	}
	///Функция измерения "высоты" дерева
    int hight(NodeBTree<T> *cur)
    {
        if(cur == NULL) return 0;
        int l = hight(cur->left);
        int r = hight(cur->right);
        if(l > r) return ++l;
        else return ++r;
    }
	///Функция формирования узла дерева
    NodeBTree<T>* cons(T nval1,T nval2,T nval3,NodeBTree<T>* lt,NodeBTree<T>* rt)
    {
        NodeBTree<T>* ntree = new NodeBTree<T>;
        ntree->val1 = nval1;
        ntree->val2 = nval2;
        ntree->val3 = nval3;
        ntree->left = lt;
        ntree->right = rt;
        return ntree;
    }
    ///Специальная рекурсивная функция построения дерева
    /*NodeBTree<T>* enter()
    {
        NodeBTree<T>* lt;
        NodeBTree<T>* rt;
        T nval;
        while ((str[ind] == ' ')&& (ind < len) )ind++;
        if(str[ind] == '(')
        {
            ind++;
            while ((str[ind] == ' ')&& (ind < len) )ind++;
            if (!readVal(nval)) return NULL;
            lt = enter();
            rt = enter();
            while ((str[ind] == ' ')&& (ind < len) )ind++;
            if (str[ind] == ')')
            {
                ind++;
                return cons(nval,lt,rt);
            }
            else return NULL;
        }
        else
        {
            if(readVal(nval)) return cons(nval,NULL,NULL);
            else return NULL;
        }
    }*/
	///Функция чтения целого значения элемента дерева
    /*bool readVal(int & nval)
    {
        if(str[ind] == ' ') do ind++ ; while(str[ind] == ' ' && ind < len);
        if(ind >= len) return 0;
        //if(nil)?
        bool otr;
        if(str[ind] == '-')
        {
            otr = true;
            ind++;
        }
                if (str[ind] >= '0' && str[ind] <='9')
                {
                    nval = (int)str[ind] - '0';
                    ind++;
                    while(str[ind] >= '0' && str[ind] <='9')
                    {
                        nval *= 10;
                        nval += (int)str[ind] - '0';
                        ind++;
                    }
                    if (otr) nval *= -1;
                    return 1;
                }
                else return 0;
    }*/
	///Функция чтения буквенного элемента дерева
    /*bool readVal(char & nval)
    {
        //int ajksdf =aksujd;
        //ind++;
        while(str[ind] == ' ' && ind < len) ind++;
        if(ind >= len) return 0;
        //if(nil)?
        nval = str[ind++];
        return 1;
    }*/
    ///Функция чтения логического(true/false) элемента дерева
    /*bool readVal(bool & nval)
    {
        if(str[ind] == ' ') do ind++ ; while(str[ind] == ' ' && ind < len);
        if(ind >= len) return 0;
        //if(nil)?
        if(str[ind] != '1' && str[ind] != '0') return 0;
        if(str[ind] == '1') nval=true;
        if(str[ind] == '0') nval = false;
        ind++;
        return 1;
    }*/
	///Функция чтения значения с плавающей запятой элемента дерева
    /*bool readVal(double & nval)
    {
        if(str[ind] == ' ') do ind++ ; while(str[ind] == ' ' && ind < len);
        if(ind >= len) return 0;
        //if(nil)?
        // todo
        nval = 0;
        ind++;
        return 1;
    }*/
	///Специальная функция записи скобочного представления дерева
    void write(std::string &str, NodeBTree<T>* cur)
    {
        if(cur == NULL) return;
        if (cur->left != NULL || cur->right != NULL)str += "( ";
        writeVal(cur->val1,str);
        writeVal(cur->val2,str);
        writeVal(cur->val3,str);
        str += ' ';
        if(cur->left != NULL) write(str, cur->left);
        if(cur->right != NULL) write(str, cur->right);
        if (cur->left != NULL || cur->right != NULL) str +=')';
    }
    ///Функция для записи буквенного элемента дерева в строку
    void writeVal(char val, std::string &str)
    {
        str += val;
    }
    /*
	///Функция для записи целочисленного элемента дерева в строку
    void writeVal(int val, std::string str)
    {
        
    }
	///Функция для записи логического (true/false) элемента дерева в строку
    void writeVal(bool val, std::string str)
    {
        if (val) str += '1';
        else str += '0';
    }
	///Функция для записи значения с плавающей запятой элемента дерева в строку
    void writeVal(double val, std::string str)
    {
        
    }*/
	///Проверка на пустоту дерева. Возвращает true, если дерево пустое
    bool isEmpty() const
    {
        if (NULL == head) return 1;
        else return 0;
    }
	///Специальная рекурсивная фунция деструктора
    void deleteAllElem(NodeBTree<T>* cur)
    {
        if(cur == NULL) return;
        deleteAllElem(cur->left);
        deleteAllElem(cur->right);
        delete cur;
    }
};
/*std::string print()
{
    MyQueue<NodeBTree<T>* > queue;
    std::string str;
    if(isEmpty()) return "Введено пустое дерево";
    queue.push(head);
    NodeBTree<T>* cur;
    int count = 0,
        line = 2,
        h = hight(head);
    int tab = 1;
    for (int i = 0;i<h;i++) tab *= 2;
    tab -= h;
    for(int i = 0; i<tab;i++) str += ' ';
    while(!queue.isEmpty())
    {
        queue.pop(cur);
        if(cur != NULL)
        {
            queue.push(cur->left);
            queue.push(cur->right);
            writeVal(cur->val, str);
        }
        count++;
        if (count %2 == 0) str += "   ";
        else str += " ";
        if(count == line - 1)
        {
            line *= 2;
            str += '\n';
            h--;
            tab--;
            for(int i = 0; i<tab;i++) str += ' ';
            str += "/ ";
            str += '[' +1;
            str += '\n';
        }
    }
    for(int i = -128;i<128;i++)
    {
        str += i;
        str += '\n';
    }
    return str;
}*/
///Функция вывода элементов дерева в порядке удаления от корня
/*std::string lab4()
{
    MyQueue<NodeBTree<T>* > queue;
    std::string str;
    if(isEmpty()) return "Введено пустое дерево";
    queue.push(head);
    NodeBTree<T>* cur;
    while(!queue.isEmpty())
    {
        queue.pop(cur);
        if(cur->left != NULL) queue.push(cur->left);
        if(cur->right != NULL) queue.push(cur->right);
        writeVal(cur->val, str);
        str += ' ';
    }
    return str;
}*/
/*bool fromStdString(std::string nstr)
{
    ind = 0;
    len = nstr.length();
    str = nstr;
    head = enter();
    if (head != NULL) return 1;
    this->~MyBinTree();
    return 0;
}*/
#endif // BINTREE

