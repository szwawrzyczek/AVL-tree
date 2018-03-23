#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class Node {

	T data;
	Node *left;
	Node *right;
 
public:

	Node():data(0),left(NULL),right(NULL){};
	Node(T & value):data(value),left(NULL),right(NULL){};
	~Node(){};
	T & GetValue(){return data;};
	T GiveValue(){return data;};
	Node<T>* Getleft(){return left;};
    Node<T>* Getright(){return right;};
    void setLeft(Node<T>*tmp){left=tmp;};
    void setRight(Node<T>*tmp){right=tmp;};   
};

template <class T>
class AVL_tree {

    Node<T> *root;
 
public:

    AVL_tree():root(NULL){};
    ~AVL_tree(){};
    Node<T>* insert(Node<T>*,T);
    Node<T>* Getroot(){return root;};
    void setRoot(Node<T>*tmp){root=tmp;};
    void display(Node<T>*,int);
};

template <class T>
Node<T>* AVL_tree<T>::insert(Node<T> *parent,T value)
{
    Node <T> *tmp=NULL;         /*wskaźnik pomocniczy*/
	if(parent==NULL) 
	{
		parent=new Node<T> (value);
        cout<<"parent = NULL"<<endl;
		return parent;
	}
    else if(value < parent->GiveValue())
    {
        tmp=insert(parent->Getleft(),value);
        parent->setLeft(tmp);
        cout<<"new left child"<<endl;
    }
    else if(value >= parent->GiveValue())
    {
        tmp=insert(parent->Getright(),value);
        parent->setRight(tmp);
        cout<<"new right child"<<endl;
    }
return parent;
}
template <class T>
void AVL_tree<T>::display(Node<T> *parent,int level)
{
    int i;
    if(parent!=NULL)
    {
        display(parent->Getright(),level+1); 
        cout<<endl;
        if (parent==Getroot())
            cout<<"  ==ROOT==> ";
        for(i=0; i < level && parent!=Getroot();i++)
            cout<<"      ";
        if(parent!=Getroot())
            cout<<"      "<<parent->GiveValue()<<" <";
        else
            cout<<parent->GiveValue()<<" <";  
        display(parent->Getleft(),level+1);
        cout<<endl;
    }
}

/******************************************************************************/
int main()
{   
    srand( time( NULL ) );
    float wartosc;
    Node<float> *tmp_root=NULL;
    AVL_tree <float> tree;
    for(int i=0; i<15; i++)
    {
        wartosc=rand()%3;
        tmp_root=tree.insert(tree.Getroot(),wartosc);
        tree.setRoot(tmp_root);
    }

        tree.display(tree.Getroot(),1);





return 0;
}
