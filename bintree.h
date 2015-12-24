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
    T val[5];
    NodeBTree* left;
    NodeBTree* right;
    NodeBTree()
    {
        left = NULL;
        right = NULL;
    }
};
/*
 * Класс MyBinTree представляет из себя бинарное дерево поиска
 * Служит для записи произвольного значения в дерево с последующим эффективным чтением
 * \warning Класс преднозначен только для исследования времени вставки/удаления узлов
*/
template<typename T>
class MyBinTree
{
    //Голова списка
    NodeBTree<T>* head;
    T curval[5];
public:
    MyBinTree()
    {
        head = NULL;
        for(int i = 0; i< 5;i++) curval[i] = 0;
    }
	~MyBinTree()
    {
        clear();
    }
    ///Функция очистки дерева
    void clear()
    {
        deleteAllElem(head);
        head = NULL;
    }
    ///Выводит дерево в QTreeWidget для графического представления
	void printTree(QTreeWidget* widget) 
	{
       if(isEmpty()) return;
 	   QTreeWidgetItem* root = new QTreeWidgetItem(widget);
       std::string str;
       writeVal(head->val[0],str);
       writeVal(head->val[1],str);
       writeVal(head->val[2],str);
       writeVal(head->val[3],str);
       writeVal(head->val[4],str);
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
        writeBracketsView(str, head);
        return str;
    }
    ///Добавляет в бинарное дерево случайные элементы в количестве count
    void pushRandomElem(int count)
    {
        //Защита от "плохих" вызовов (иначе - бесконечный цикл)
        if (count > 11000000 - 460000 * height(head) || count < 0) return;
        srand(time(NULL));
        for (int i = 0; i < count; i++)
            if(!push((char)(rand() % 26 + 'a'),(char)(rand() % 26 + 'a'),
                     (char)(rand() % 26 + 'a'), (char)(rand() % 26 + 'a'),
                     (char)(rand() % 26 + 'a'))) i--;
    }
    ///Вставляет новый элемент в дерево, возвращает true при успешной вставке
    bool push(char ch1,char ch2,char ch3, char ch4, char ch5)
    {
       curval[0] = ch1;
       curval[1] = ch2;
       curval[2] = ch3;
       curval[3] = ch4;
       curval[4] = ch5;
       return pushRec(head);
    }
    bool deleteNode(char ch1,char ch2,char ch3,char ch4, char ch5)
    {
        curval[0] = ch1;
        curval[1] = ch2;
        curval[2] = ch3;
        curval[3] = ch4;
        curval[4] = ch5;
        if (isEmpty()) return 0;
        if (head->val[0] == curval[0]
                && head->val[1] == curval[1]
                && head->val[2] == curval[2]
                && head->val[3] == curval[3]
                && head->val[4] == curval[4])
        {
            //удаляем
            NodeBTree<T>* nodeDel = head;
            if (head->left == NULL)
            {
                head = head->right;
                delete nodeDel;
                return 1;
            }
            if (head->right == NULL)
            {
                head = head->left;
                delete nodeDel;
                return 1;
            }
            NodeBTree<T>* node  = head->left;
            if (node->right !=NULL)
            {
                while(node->right->right != NULL) node = node->right;
                head = node->right;
                node->right = head->left;
                head->left = nodeDel->left;
                head->right = nodeDel->right;
            }
            else
            {
                head = head->left;
                head->right = nodeDel->right;
            }
            delete nodeDel;
            return 1;
        }
        else return deleteNodeRec(head);
    }
    int height()
    {
        return height(head);
    }
    void test2(int count)
    {
        if (isEmpty()) return;
        char ch1 = head->val[0],
                ch2 = head->val[1],
                ch3 = head->val[2],
                ch4 = head->val[3],
                ch5 = head->val[4];
        for(int i = 0; i< count;i++)
        {
            deleteNode(ch1,ch2,ch3,ch4,ch5);
            push(ch1,ch2,ch3,ch4,ch5);
        }
    }
private:
    bool pushRec(NodeBTree<T>* &cur)
    {
        if(cur == NULL)
        {
            cur = cons(NULL,NULL);
            return 1;
        }
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] == curval[2]
                && cur->val[3] == curval[3]
                && cur->val[4] == curval[4]) return 0;
        if (cur->val[0] < curval[0]) return pushRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] < curval[1]) return pushRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] < curval[2]) return pushRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] == curval[2]
                && cur->val[3] < curval[3]) return pushRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] == curval[2]
                && cur->val[3] == curval[3]
                && cur->val[4] < curval[4]) return pushRec(cur->left);
        return pushRec(cur->right);
    }
    bool deleteNodeRec(NodeBTree<T>* &cur)
    {
        if(cur == NULL) return 0;
        //if (cur->left == NULL && cur->right == NULL) return 0;
        if (cur->left != NULL
                && cur->left->val[0] == curval[0]
                && cur->left->val[1] == curval[1]
                && cur->left->val[2] == curval[2]
                && cur->left->val[3] == curval[3]
                && cur->left->val[4] == curval[4])
        {
            //удаляем
            NodeBTree<T>* nodeDel = cur->left;
            if (cur->left->left == NULL)
            {
                cur->left = cur->left->right;
                delete nodeDel;
                return 1;
            }
            if (cur->left->right == NULL)
            {
                cur->left = cur->left->left;
                delete nodeDel;
                return 1;
            }
            if (height(cur->left->left) > height(cur->left->right))
            {
                NodeBTree<T>* node  = cur->left->left;
                if (node->right !=NULL)
                {
                    while(node->right->right != NULL) node = node->right;
                    cur->left = node->right;
                    node->right = cur->left->left;
                    cur->left->left = nodeDel->left;
                    cur->left->right = nodeDel->right;
                }
                else
                {
                    cur->left = cur->left->left;
                    cur->right = nodeDel->right;
                }
            }
            else
            {
                NodeBTree<T>* node  = cur->left->right;
                if (node->left !=NULL)
                {
                    while(node->left->left != NULL) node = node->left;
                    cur->left = node->left;
                    node->left = cur->left->right;
                    cur->left->left = nodeDel->left;
                    cur->left->right = nodeDel->right;
                }
                else
                {
                    cur->left = cur->left->left;
                    cur->right = nodeDel->right;
                }
            }
            delete nodeDel;
            return 1;

        }
        if(cur->right != NULL
                && cur->right->val[0] == curval[0]
                && cur->right->val[1] == curval[1]
                && cur->right->val[2] == curval[2]
                && cur->right->val[3] == curval[3]
                && cur->right->val[4] == curval[4])
        {
            //удаляем
            NodeBTree<T>* nodeDel = cur->right;
            if (cur->right->left == NULL)
            {
                cur->right = cur->right->right;
                delete nodeDel;
                return 1;
            }
            if (cur->right->right == NULL)
            {
                cur->right = cur->right->left;
                delete nodeDel;
                return 1;
            }
            NodeBTree<T>* node  = cur->right->left;
            if (node->right !=NULL)
            {
                while(node->right->right != NULL) node = node->right;
                cur->right = node->right;
                node->right = cur->right->left;
                cur->right->left = nodeDel->left;
                cur->right->right = nodeDel->right;
            }
            else
            {
                cur->right = cur->right->left;
                cur->right = nodeDel->right;
            }
            delete nodeDel;
            return 1;
        }
        if (    cur->val[0] < curval[0]   ) return deleteNodeRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] < curval[1]) return deleteNodeRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] < curval[2]) return deleteNodeRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] == curval[2]
                && cur->val[3] < curval[3]) return deleteNodeRec(cur->left);
        if (cur->val[0] == curval[0]
                && cur->val[1] == curval[1]
                && cur->val[2] == curval[2]
                && cur->val[3] == curval[3]
                && cur->val[4] < curval[4]) return deleteNodeRec(cur->left);
        return deleteNodeRec(cur->right);
    }
	///Специальная функция для вывода дерева
    void printTree(QTreeWidgetItem*& item, NodeBTree<T>*& node)
	{
		std::string str;
        writeVal(node->val[0],str);
        writeVal(node->val[1],str);
        writeVal(node->val[2],str);
        writeVal(node->val[3],str);
        writeVal(node->val[4],str);
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
    int height(NodeBTree<T> *cur)
    {
        if(cur == NULL) return 0;
        int l = height(cur->left);
        int r = height(cur->right);
        if(l > r) return ++l;
        else return ++r;
    }
	///Функция формирования узла дерева
    NodeBTree<T>* cons(NodeBTree<T>* lt,NodeBTree<T>* rt)
    {
        NodeBTree<T>* ntree = new NodeBTree<T>;
        ntree->val[0] = curval[0];
        ntree->val[1] = curval[1];
        ntree->val[2] = curval[2];
        ntree->val[3] = curval[3];
        ntree->val[4] = curval[4];
        ntree->left = lt;
        ntree->right = rt;
        return ntree;
    }
	///Специальная функция записи скобочного представления дерева
    void writeBracketsView(std::string &str, NodeBTree<T>* cur)
    {
        if(cur == NULL) return;
        if (cur->left != NULL || cur->right != NULL)str += "( ";
        writeVal(cur->val[0],str);
        writeVal(cur->val[1],str);
        writeVal(cur->val[2],str);
        writeVal(cur->val[3],str);
        writeVal(cur->val[4],str);
        str += ' ';
        if(cur->left != NULL) writeBracketsView(str, cur->left);
        if(cur->right != NULL) writeBracketsView(str, cur->right);
        if (cur->left != NULL || cur->right != NULL) str +=')';
    }
    ///Функция для записи буквенного элемента дерева в строку
    void writeVal(char val, std::string &str)
    {
        str += val;
    }
	///Проверка на пустоту дерева. Возвращает true, если дерево пустое
    bool isEmpty() const
    {
        if (NULL == head) return 1;
        else return 0;
    }
    ///Специальная рекурсивная фунция удаления дерева
    void deleteAllElem(NodeBTree<T>* cur)
    {
        if(cur == NULL) return;
        deleteAllElem(cur->left);
        deleteAllElem(cur->right);
        delete cur;
    }
};
#endif // BINTREE

