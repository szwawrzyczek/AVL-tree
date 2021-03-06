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
    void Inorder(Node<T>*);
    void Preorder(Node<T>*); 
    void Postorder(Node<T>*);  

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
    else if(value > parent->GiveValue())
    {
        tmp=Insert(parent->Getright(),value);
        parent->setRight(tmp);
        parent = tree_balance(parent);       
    }
    else    //security of AVL tree properties 
    {
        cout<<"This value already exist"<<endl;
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
            else                //No child
            {             
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

template <class T>
void AVL_tree<T>::Preorder(Node<T> *parent)
{
    if (parent==NULL)
        return;
    cout<<"  "<<parent->GiveValue()<<endl;
    Preorder(parent->Getleft());
    Preorder(parent->Getright());
}

template <class T>
void AVL_tree<T>::Inorder(Node<T> *parent)
{
    if (parent==NULL)
        return;
    Inorder(parent->Getleft());
    cout<<"  "<<parent->GiveValue()<<endl;
    Inorder(parent->Getright());
}

template <class T>
void AVL_tree<T>::Postorder(Node<T> *parent)
{
    if (parent==NULL)
        return;
    Postorder(parent->Getleft());
    Postorder(parent->Getright());
    cout<<"  "<<parent->GiveValue()<<endl;
}

/******************************************************************************/
int main()
{   
    srand( time( NULL ) );
    float value;
    int choice;
    Node<float> *tmp_root=NULL;
    AVL_tree <float> tree;
    cout<<endl<<endl<<"AVL tree program options"<<endl<<endl;  
    do
    {
        cout<<"1.   Insert           6.   Display tree height"<<endl;
        cout<<"2.   Remove           7.   Preorder display   "<<endl;
        cout<<"3.   Display          8.   Inorder display    "<<endl;
        cout<<"4.   Random tree      9.   Postorder display  "<<endl;
        cout<<"5.   Exit                                     "<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            cout<<endl<<"Enter a value to insert:   ";
            cin>>value;
            cout<<endl;
            tmp_root=tree.Insert(tree.Getroot(),value);
            tree.setRoot(tmp_root);
            break;
           
        case 2:
            cout<<endl<<"Enter a value to remove:   ";
            cin>>value;
            cout<<endl;
            tree.setRoot(tree.Remove(tree.Getroot(),value));

            break;
           
        case 3:
            if (tree.Getroot()!=NULL)
                tree.display(tree.Getroot(),1);
            else
                cout<<"AVL TREE is empty!!! "<<endl;
            cout<<endl;
            break;

        case 4:
            for(int i=0; i<9; i++) 
            {
                value=rand()%101;          
                tmp_root=tree.Insert(tree.Getroot(),value);
                tree.setRoot(tmp_root);
            }
            break;

        case 5:     //Exit
            break;             

        case 6:
            cout<<endl<<"Height of tree....... ";
            cout<<tree.tree_height(tree.Getroot())<<endl<<endl;
            break;

        case 7:
            if (tree.Getroot()!=NULL)
                tree.Preorder(tree.Getroot());
            else
                cout<<"AVL TREE is empty!!! "<<endl;
            cout<<endl;
            break;

        case 8:
            if (tree.Getroot()!=NULL)
                tree.Inorder(tree.Getroot());
            else
                cout<<"AVL TREE is empty!!! "<<endl;
            cout<<endl;
            break;

        case 9:
            if (tree.Getroot()!=NULL)
                tree.Postorder(tree.Getroot());
            else
                cout<<"AVL TREE is empty!!! "<<endl;
            cout<<endl;
            break;
          
        default:
            cout<<endl<<"Invalid input value."; 
            cout<<"Enter value from one to six"<<endl;

            break;
        }
    }  
    while(choice!=5);

return 0;
}
