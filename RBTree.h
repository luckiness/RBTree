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
		 //查找合适的位置
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
	   //插入节点
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
		  //保证了parent不为空，并且grandfather存在
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
				 //(2)cur=red p=red g=black uncle不存在/存在为black
				 //p为g的左孩子，cur为p的右孩子，则对p进行左旋
				 //(3)cur=red p=red g=black uncle不存在/存在为black
				 //p为g的左孩子，cur为p的左孩子，则对p进行右旋
				  else
				  {
					   if(cur==parent->_right )
					   {
							RotateL(parent);
							swap(cur,parent)；
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
	 //左旋
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

	 //右旋
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

	 //面试题如何检查一颗红黑树的正确性
	 bool CheckTree()
	 {
		  if(_root&& _root->_col ==RED)
			  return false;

		  //计算一条路径上的黑色节点数量作为基准值 ，
		  //只要剩下路径中任何一条的黑色节点的值和这个值不相等则认为红黑树不正确
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
			 cout<<"违反规则3"<<root->_key <<endl;
	        return false;
		 }

	   //更新路径上黑色节点的数量
		  if(root->_col ==BLACK)
		  {
		  ++count;
		  }

		  if(root->_left ==NULL&& root->_right ==NULL&& nodenumber!=count)
		  {
		   cout<<"违反规则4"<<root->_key <<endl;
		   return false;
		  }

		  return (_CheckTree(root->_left ,nodenumber,count)&&_CheckTree(root->_right ,nodenumber,count));
	 }
 };

 