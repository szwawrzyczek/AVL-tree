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
	const T GiveValue(){return data;};
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
    Node<T>* Insert(Node<T>*,T);
    Node<T>* Getroot(){return root;};
    void setRoot(Node<T>*tmp){root=tmp;};
    void display(Node<T>*,int);
    int tree_height(Node<T>*);
    int height_difference(Node<T>*);
    Node<T>* L_rotation(Node<T>*);
    Node<T>* R_rotation(Node<T>*);
    Node<T>* LR_rotation(Node<T>*);
    Node<T>* RL_rotation(Node<T>*);
    Node<T>* tree_balance(Node<T>*);
    Node<T>* Remove(Node<T>*,T);    

};

template <class T>
Node<T>* AVL_tree<T>::Insert(Node<T> *parent,T value)
{ 
    Node <T> *tmp=NULL;         /*wskaźnik pomocniczy*/
	if(parent==NULL) 
	{
		parent=new Node<T> (value);
		return parent;
	}
    else if(value < parent->GiveValue())
    {
        tmp=Insert(parent->Getleft(),value);
        parent->setLeft(tmp);
        parent = tree_balance(parent);
    }
    else if(value >= parent->GiveValue())
    {
        tmp=Insert(parent->Getright(),value);
        parent->setRight(tmp);
        parent = tree_balance(parent);       
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

template <class T>
int AVL_tree<T>::tree_height(Node<T> *tmp)
{
    int height=0;
    if (tmp!=NULL)
    {
        int left_height=tree_height(tmp->Getleft());
        int right_height=tree_height(tmp->Getright());
        int max_height=max(left_height,right_height);
        height=max_height+1;
    }
    return height;
}

template <class T>
int AVL_tree<T>::height_difference(Node<T> *tmp)
{
    int left_height=tree_height(tmp->Getleft());
    int right_height=tree_height(tmp->Getright());
    int height_difference=left_height-right_height;
    return height_difference;
}
//Case 1: Parent node -->right node --> right node 
//[single left rotation]
template <class T>
Node<T>* AVL_tree<T>::L_rotation(Node<T> *parent)
{
    Node<T>*tmp;
    tmp = parent->Getright();
    parent->setRight(tmp->Getleft());
    tmp->setLeft(parent);

    return tmp;   // return "new parent"
}
//Case 2: Parent node -->left node --> left node []
//[single right rotation]
template <class T>
Node<T>* AVL_tree<T>::R_rotation(Node<T> *parent)
{
    Node<T>*tmp;
    tmp = parent->Getleft();
    parent->setLeft(tmp->Getright());
    tmp->setRight(parent);
    return tmp;   // return "new parent"
}
//Case 3: Parent node --> left node -->right node []
//[Left rotation and next right rotation]
template <class T>
Node<T>* AVL_tree<T>::LR_rotation(Node<T> *parent)
{
    cout<<"LR ROtation"<<endl;
    Node<T>*tmp;
    tmp = parent->Getleft();
    parent->setLeft(L_rotation(tmp));
    return R_rotation(parent);   // return "new parent"
}
//Case 4: Parent node -->right node --> left node []
//[Right rotation and next left rotation]
template <class T>
Node<T>* AVL_tree<T>::RL_rotation(Node<T> *parent)
{
    cout<<"RL ROtation"<<endl;
    Node<T>*tmp;
    tmp = parent->Getright();
    parent->setRight(R_rotation(tmp));
    return L_rotation(parent);   // return "new parent"
}

template <class T>
Node<T>* AVL_tree<T>::tree_balance(Node<T> *tmp)
{
    int balance_factor = height_difference(tmp);
    if(balance_factor > 1)
    {
        if(height_difference(tmp->Getleft()) > 0)
            tmp = R_rotation(tmp);
        else
            tmp = LR_rotation(tmp);
    }
    else if (balance_factor < -1)
    {
        if(height_difference(tmp->Getright()) > 0)
            tmp = RL_rotation(tmp);
        else
            tmp = L_rotation(tmp);
    }
    return tmp;  
}

// Method Remove inspired by a code from: 
// https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
template <class T>
Node<T>* AVL_tree<T>::Remove(Node<T> *parent,T key)
{
    if(parent==NULL)
    {
        cout<<endl<<"Key not found in this tree"<<endl;
        return parent;
    }
    Node<T> *tmp;    
    if (key < parent->GiveValue())   //serched value is in left subtree 
    {
        tmp=Remove(parent->Getleft(),key);
        parent->setLeft(tmp);  
    }
    else if (key > parent->GiveValue())  //serched value is in right subtree 
    {
        tmp=Remove(parent->Getright(),key);
        parent->setRight(tmp); 
    }
    else        //serched value is in this node
    {
        if((parent->Getleft()!=NULL) && (parent->Getright()!=NULL))  //two child
        {
            tmp=parent->Getright();
            while(tmp->Getleft()!=NULL)
                tmp=tmp->Getleft();
            parent->GetValue()=tmp->GiveValue();
            Node<T> *tmp2=Remove(parent->Getright(),tmp->GiveValue());
            parent->setRight(tmp2);
        }
        else                    
        {
            tmp=parent->Getleft() ? parent->Getleft():parent->Getright();
            if (tmp != NULL)    //One child
                *parent=*tmp;
            else 
            {             //No child
                tmp=parent;
                parent=NULL;
            }
            free(tmp);
        }
    }
    if(parent==NULL)
        return parent;
    return tree_balance(parent); 
}
/******************************************************************************/
int main()
{   
    srand( time( NULL ) );
    float wartosc;
    Node<float> *tmp_root=NULL;
    AVL_tree <float> tree;
/*
   cin>>wartosc;
        while(wartosc>-1)
        {
            tmp_root=tree.Insert(tree.Getroot(),wartosc);
            tree.setRoot(tmp_root);
            tree.display(tree.Getroot(),1);
            cin>>wartosc;
        }*/
    
    for(int i=0; i<5; i++)      //testowanie
    {
        wartosc=rand()%95;          
        tmp_root=tree.Insert(tree.Getroot(),wartosc);
        tree.setRoot(tmp_root);
    }
        tree.display(tree.Getroot(),1);
        cout<<"wysokosc avl tree= "<<tree.tree_height(tree.Getroot())<<endl;
        cin>>wartosc;
        while(wartosc>-1)
        {
            tree.setRoot(tree.Remove(tree.Getroot(),wartosc));
            if (tree.Getroot()!=NULL)
            tree.display(tree.Getroot(),1);
            else
            cout<<"AVL TREE is empty!!! "<<endl;
            cin>>wartosc;
        }




return 0;
}
