#include<iostream>

using namespace std;

enum color
{
	RED,
	BLACK
};
template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K,V>* _left;
	RBTreeNode<K,V>* _right;
	RBTreeNode<K,V>* _parent;
	K _key;
	V _value;
	color _col;
   RBTreeNode(const K& key,const V& value):_left(NULL)
	                                      ,_right(NULL)
										  ,_parent(NULL)
										  ,_key(key)
										  ,_value(value)
										  ,_col(RED)
       {}
};

template<class K,class V>
 class RBTree
 {
	typedef RBTreeNode<K,V> Node;

 protected:
 Node* _root;

 public:

	  RBTree()
	  {}

	 RBTree(Node* root):_root(root)
	 {}

	 bool Insert(const K& key,const V& value)
	 {
		 //���Һ��ʵ�λ��
	   if(_root==NULL)
	   {
		   _root=new Node(key);
		   _root->_col =BLACK;
		   return true;
	   }

	   Node* parent=NULL;
	   Node* cur=_root;
	   while(cur)
	   {
		   if(cur->_key >key)
		   {
			   parent=cur;
			   cur=cur->_left ;
		   }
		   else if(cur->_key <key)
		   {
			   parent=cur;
			   cur=cur->_right ;
		   }
		   else
		   {
			 return false;
		   }
	   }
	   //����ڵ�
		   cur=new Node(key,value);
		   if(parent->_key >key)
		   {
			parent->_left =cur;
			cur->_parent =parent;
		   }
		   else
		   {
			parent->_right =cur;
			cur->_parent =parent;
		   }

      while(cur)
	  {
		  //��֤��parent��Ϊ�գ�����grandfather����
		  if(cur!=_root && parent->_col ==RED)
		  {
			  Node* grandfather=parent->_parent ;


			  if(parent=grandfather->_left )
				{
				  Node* uncle=grandfather->_right ;
				  //(1)cur=red p=red g=black uncle=red
				  if(uncle && uncle->_col ==RED)
				  {
					   parent->_col =BLACK;
					   uncle->_col =BLACK;
					   grandfather->_col =RED;

					   cur=grandfather;
					   parent=grandfather->_parent ;
				  }
				 //(2)cur=red p=red g=black uncle������/����Ϊblack
				 //pΪg�����ӣ�curΪp���Һ��ӣ����p��������
				 //(3)cur=red p=red g=black uncle������/����Ϊblack
				 //pΪg�����ӣ�curΪp�����ӣ����p��������
				  else
				  {
					   if(cur==parent->_right )
					   {
							RotateL(parent);
							swap(cur,parent)��
					   }
					   parent->_col=BLACK;
					   grandfather->_col =RED;
					   RotateR(grandfather);
				  }
			}

		 //parent=grandfather->right
		   else
			{
				 Node* uncle=grandfather->_left;
				 if(uncle && uncle->_col==RED)
				 {
				   uncle->_col =BLACK;
				   parent->_col =BLACK;
				   grangfather->_col=RED;
				   cur=grandfather;
				   parent=cur->_parent ;
				 }

				 else
				 {
				   if(cur==parent->_left )
				   {
				   RotateR(parent);
				   swap(cur,parent);
				   }
				    parent->_col =BLACK;
					grandfather->_col =RED;
					RotateR (grandfather);
				 }
			}
		  }

	   _root=BLACK;
	   return true;
	  }
	  
 }
	 //����
	 void RotateL(Node* parent)
	 {
		  Node* subR=parent->_right ;

		  Node* subRL=subR->_left ;
		  parent->_right =subRL;
		  if(subRL)
		   subRL->_parent =parent;

		   subR->_left =parent;
		   Node* ppNode=parent->_parent ;
		   parent->_parent =subR;

		  if(ppNode==NULL)
		  {
			_root=subR;
		  }

		  else 
		  {
			   if(ppNode->_left==parent)
				   ppNode->_left=subR;
			   else
				   ppNode->_right=subR;
			   subR->_parent =ppNode;
		  }
	 }

	 //����
	 void RotateR(Node* parent)
	 {
	 Node* subL=parent->_left ;
	 Node* subLR=subL->_right ;	
	 parent->_left =subLR;

	 if(subLR)
	     subLR->_parent =parent;

	     subL->_right =parent;
		 Node* ppNode=parent->_parent ;
		 parent->_parent =subL;

		 if(ppNode==NULL)
		 {
		 _root=subL;
		 }

		 else
		 {
		   if(ppNode->_left ==parent)
			   ppNode->_left subL;
		   else
			   ppNode->_right =subL;

		   subL->_parent =ppNode;
		 }
		 
	 }

	 //��������μ��һ�ź��������ȷ��
	 bool CheckTree()
	 {
		  if(_root&& _root->_col ==RED)
			  return false;

		  //����һ��·���ϵĺ�ɫ�ڵ�������Ϊ��׼ֵ ��
		  //ֻҪʣ��·�����κ�һ���ĺ�ɫ�ڵ��ֵ�����ֵ���������Ϊ���������ȷ
		  int nodenumber=0;
		  Node* cur=_root;
		  while(cur)
		  {
				  if(cur->_col ==BLACK)
				  {
				  nodenumber++;		  
				  }
				cur=cur->_left ;
		  }
         int count=0;
         return _CheckTree(_root,nodenumber,count);
	 }

	 bool _CheckTree(Node* root,int nodenumber,int count)
	 {
	  if(root==NULL)
	   return true;
	  Node* parent=root->_parent ;
	  if(root->_col ==RED&& parent->_col ==RED)
		 {
			 cout<<"Υ������3"<<root->_key <<endl;
	        return false;
		 }

	   //����·���Ϻ�ɫ�ڵ������
		  if(root->_col ==BLACK)
		  {
		  ++count;
		  }

		  if(root->_left ==NULL&& root->_right ==NULL&& nodenumber!=count)
		  {
		   cout<<"Υ������4"<<root->_key <<endl;
		   return false;
		  }

		  return (_CheckTree(root->_left ,nodenumber,count)&&_CheckTree(root->_right ,nodenumber,count));
	 }
 };

 