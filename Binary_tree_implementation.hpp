#ifndef BINARY_TREE_IMPLEMENTATION_HPP
#define BINARY_TREE_IMPLEMENTATION_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>


namespace BinaryTreeScope
{

	template <typename T>
	struct Node
	{
		T key;
		Node<T>* left;
		Node<T>* right;
		Node<T>* parent;
		int bf;
	};


	template <typename T>
	class BinaryTree
	{
	private:

		int height;
		Node<T>* root;

		int max(int x, int y);

		void insert_private(Node<T>* &current_node, Node<T>* parent, T key);

		Node<T>* remove_node(Node<T>*& n, T key);

		void destroy(Node<T>* current_node);

		void displayNode(Node<T> *Node, int count);

		Node<T>* find_node(Node<T>* current_node, T key);

		Node<T>* max(Node<T>* current_node);

		Node<T>* min(Node<T>* current_node);

		Node<T>* successor_private(Node<T>* current_node, T key);

		Node<T>* predecessor_private(Node<T>* current_node, T key);

		bool check_if_bst ( Node<T> * root ) const; // private


		void toStringHelper(Node<T>* current_node, int count, int secondCount);




	public:
		BinaryTree();

		~BinaryTree();

		bool empty();

		void insert(T key);

		void remove(T key);

		void display();

		Node<T>* find(T key);

		Node<T>* successor(T key);

		Node<T>* predecessor(T key);

	 	bool check_if_bst() const; // public

	 	void toString();



	 	//****************

		int balFactOfNode(Node<T>* &current_node);

		void rotateLeft(Node<T> *& current_node);

		void rotateRight(Node<T>*& current_node);

		void dRotateRight(Node<T>* &current_node);

		void dRotateLeft(Node<T>* &current_node);

		void fixImbalance(Node<T>* &current_node);



		//****************


	};


	template <typename T>
	BinaryTree<T>::BinaryTree()
	{
		root = nullptr;

	}

	template <typename T>
	BinaryTree<T>::~BinaryTree()
	{
		destroy(root);
	}

	template <typename T>
	bool BinaryTree<T>::empty()
	{
		return root == nullptr;
	}

	template <typename T>
	int max(int x, int y)
	{
		if (x > y)
		{
			return x;
		}
		else
		{
			return y;
		}
	}

	template <typename T>
	void BinaryTree<T>::insert_private(Node<T>* &current_node, Node<T>* parent, T key)
	{
		if (current_node == nullptr)
		{
			current_node = new Node<T>;
			current_node->left = nullptr;
			current_node->right = nullptr;
			current_node->key = key;
			current_node->parent = parent;
			balFactOfNode(current_node);
			fixImbalance(parent);
		}
		else if (key >= current_node->key)
		{

			insert_private(current_node->right, current_node, key);
		}
		else if (key < current_node->key)
		{
			insert_private(current_node->left, current_node, key);
		}

	}


	template <typename T>
	void BinaryTree<T>::insert(T key)
	{
		insert_private(root, nullptr, key);
	}



	template <typename T>
	Node<T>* BinaryTree<T>::remove_node(Node<T>* &node, T key) {
	  	std::cout << "key remove: " << key << std::endl;
	  	Node<T>* n = find_node(node, key);
		if(n != nullptr){
		    Node<T>* p = n->parent;

		    //Case 1: No children
		    if(n->left == nullptr && n->right == nullptr){
		      //
		      	std::cout<<"Case1\n";
		      //
		    	if(p == nullptr){ //if node is root
					root = nullptr;
		      	}
		      	else{
					if(n == p->left) //if n is left child
			 		 p->left = nullptr;
				else
			  		p->right = nullptr;
		      	}
		      	balFactOfNode(p);
		      	delete n;

		    }

		    //Case 2: One child
		    else if(n->left == nullptr || n->right == nullptr){
		      //
		      std::cout<<"Case2\n";
		      //
		      Node<T>* c;
		      if(n == p->left){ //if n is left child
				if(n->left != nullptr) //if child was left
			  		c = n->left;
				else //if child was right
			 	 c = n->right;
				if(p != nullptr) p->left = c;
		      }
		      else{ //if n is right child
				if(n->left != nullptr) //if child was left
			  		c = n->left;
				else //if child was right
			  		c = n->right;
				if(p != nullptr) p->right = c;
		      }

		      balFactOfNode(p);
		      c->parent = p;
		      delete n;

		    }

		    //Case 3: Two children
		    else{
		      //
		      std::cout<<"Case3\n";
		      //

		      Node<T>* s = successor(n->key);
		      T new_key = s->key;
		      std::cout<<"paso del sucesor :D\n";
		      p = remove_node(s->parent, new_key);
		      std::cout<<"lo oneshoteo :D\n";
		      n->key = new_key;

		    }
		    fixImbalance(p);

		    return p;
		  }

		  return nullptr;
		}



	template <typename T>
	void BinaryTree<T>::remove(T key)
	{

		Node<T>* node_to_destroy = find(key);
		remove_node(node_to_destroy, key);
		// if (parent != nullptr)
		// {
		//
		// 	//fixImbalance(parent);
		//
		// }

	}


	template <typename T>
	void BinaryTree<T>::destroy(Node<T>* current_node)
	{
		if (current_node != nullptr)
		{
			destroy(current_node->left);
			destroy(current_node->right);
			delete current_node;
		}
	}


	template <typename T>
	void BinaryTree<T>::displayNode(Node<T> *Node, int count)
	{
		if (Node != nullptr )
		{
			count++;
			displayNode(Node->left, count);
			std::cout << "(" << count - 1 << ")" << Node->key << " ";
			displayNode(Node->right, count);
		}
	}




	template <typename T>
	void BinaryTree<T>::display()
	{
		displayNode(root,0);
		std::cout << std::endl;
	}


	template <typename T>
	Node<T>* BinaryTree<T>::find_node(Node<T>* current_node, T key)
	{
		if (current_node == nullptr)
		{
			return nullptr;
		}
		else if(current_node->key == key)
		{
			return current_node;
		}
		else if(key < current_node->key)
		{
			return find_node(current_node->left, key);
		}
		else //current_node->key > key
		{
			return find_node(current_node->right, key);

		}
	}


	template <typename T>
	Node<T>* BinaryTree<T>::find(T key)
	{
		//std::cout << "key: " << root->key << std::endl;
		return find_node(root, key);
	}


	template <typename T>
	Node<T>* BinaryTree<T>::max(Node<T>* current_node)
	{
		if (current_node->right == nullptr)
		{
			return current_node;
		}
		else
		{
			return max(current_node->right);
		}

	}


	template <typename T>
	Node<T>* BinaryTree<T>::min(Node<T>* current_node)
	{
		if (current_node->left == nullptr)
		{
			return current_node;
		}
		else
		{
			return min(current_node->left);
		}

	}


	template <typename T>
	Node<T>* BinaryTree<T>::successor_private(Node<T>* current_node, T key)
	{
		Node<T>* current_successor = current_node;

		if (current_node->left == nullptr && current_node->right == nullptr)
		{
			return current_node;
		}

		else if (key >= current_node->key && current_node->right != nullptr)
		{
			//std::cout << "hey key mayor" << std::endl;
			current_successor = successor_private(current_node->right, key);

		}
		else if (key < current_node->key)
		{
			//std::cout << "hey key menor" << std::endl;
			Node<T>* lower_node = successor_private(current_node->left, key);
			if (key < lower_node->key && lower_node->key < current_successor->key)
			{
				//std::cout << "hey key condicional" << std::endl;
				current_successor = lower_node;
			}
		}

		return current_successor;
	}


	template <typename T>
	Node<T>* BinaryTree<T>::successor(T key)
	{
		Node<T>* node = successor_private(root, key);
		if (node->key < key)
		{
			throw std::runtime_error("successor_error: is not in the Tree");
		}
		return node;
	}

	template <typename T>
	Node<T>* BinaryTree<T>::predecessor_private(Node<T>* current_node, T key)
	{
		Node<T>* current_predecessor = current_node;
		if (current_node->left == nullptr && current_node->right == nullptr)
		{
			return current_node;
		}
		else if (current_node->key >= key && current_node->left != nullptr)
		{
			//std::cout << "hey key menor" << std::endl;
			current_predecessor = predecessor_private(current_node->left, key);
		}else if (current_node->key < key)
		{
			//std::cout << "hey key mayor" << std::endl;
			Node<T>* lower_node = predecessor_private(current_node->right, key);
			//std::cout << "lower node: " << lower_node->key << std::endl;
			if (current_predecessor->key < lower_node->key && lower_node->key < key)
			{

				//std::cout << "hey key condicional" << current_node->key << std::endl;
				current_predecessor = lower_node;
			}
		}
		return current_predecessor;
	}


	template <typename T>
	Node<T>* BinaryTree<T>::predecessor(T key)
	{
		Node<T>* node = predecessor_private(root, key);
		if (node->key > key)
		{
			throw std::runtime_error("predecessor_error: is not in the Tree");
		}
		return node;
	}


	template <typename T>
	bool BinaryTree<T>::check_if_bst ( Node<T> * root ) const
	{
		if (root == nullptr)
		{
			return true;
		}
		else
		{
			bool left = true;
			bool right = true;

			//Si el hijo izquierdo es distinto a nullptr
			if (root->left != nullptr)
			{
				left = root->left->key <= root->key;
			}

			//Si el hijo izquierdo es distinto a nullptr
			if (root->right != nullptr)
			{
				right = root->right->key >= root->key;
			}

			bool valor = left && right;

			return check_if_bst(root->left) && valor && check_if_bst(root->right);
		}
	}


	template <typename T>
	bool BinaryTree<T>::check_if_bst () const
	{
		return check_if_bst(root);
	}




	template <typename T>
	void BinaryTree<T>::toStringHelper(Node<T>* current_node, int count, int secondCount)
	{
		if (current_node != nullptr)
		{
			count += secondCount;

			toStringHelper(current_node->right, count, secondCount);

			std::cout << std::endl;

			for (int i = secondCount ; i < count; i++)
			{
				std::cout << " ";
			}

			std::cout << current_node->key << std::endl;

			toStringHelper(current_node->left, count, secondCount);


		}
	}


	template <typename T>
	void BinaryTree<T>::toString()
	{
		std::cout << "***STRING***" << std::endl;
		toStringHelper(root, 0, 5);
		std::cout << "***********" << std::endl;
	}


	//****AVL Tree*****
	/*Varios metodos fueron obtenidos de la clase de Carlos*/

	template <typename T>
	int BinaryTree<T>::balFactOfNode(Node<T>* &current_node) {
		if(current_node->left == nullptr && current_node->right == nullptr) //t is a leaf
		{
			current_node->bf = 0; //balancing factor
			return 0; //h - depth of the node
		}
		else{

			int lf=-1;
			int rf=-1;

			if(current_node->left != nullptr)
			{
				lf = balFactOfNode(current_node->left);
			}
			if(current_node->right != nullptr)
			{
				rf = balFactOfNode(current_node->right);
			}
			current_node->bf = rf - lf; //balancing factor
			return std::max(lf,rf) + 1; //h - depth of the node
		}
	}


	template <typename T>
	void BinaryTree<T>::rotateRight(Node<T>* &current_node)
	{
		Node<T>* child = current_node->left;
		std::cout<< "Child" << child->key << std::endl;
		current_node->left = child->right;
		if(current_node->left != nullptr)
		{
			current_node->left->parent = current_node;
			std::cout<< "Child right:" << child->key << std::endl;
		}
		child->right = current_node;
		child->parent = current_node->parent;
		current_node->parent = child;
		Node<T>* p = child->parent;


		if(p != nullptr)
		{
			std::cout<< "Child parent:" << p->key << std::endl;
			if(p->key > child->key)
			p->left = child;
			else
			{

				p->right = child;
			}

		}
		else
		{
			root = child;
		}
	}


	template <typename T>
	void BinaryTree<T>::rotateLeft(Node<T>* &current_node)
	{

		Node<T>* child = current_node->right;
		current_node->right = child->left;
		if(current_node->right != nullptr)
		{
			current_node->right->parent = current_node;
		}
		child->left = current_node;
		child->parent = current_node->parent;
		current_node->parent = child;
		Node<T>* p = child->parent;
		if(p != nullptr)
		{
			if(p->key > child->key)
			{
				p->left = child;
			}
			else
			{
				p->right = child;
			}
		}
		else
		{
			root = child;
		}
	}

	template <typename T>
	void BinaryTree<T>::dRotateRight(Node<T>* &current_node)
	{
		rotateLeft(current_node->left);
		std::cout << "rotate left: " << current_node->left->key << std::endl;

		rotateRight(current_node);
		std::cout << "rotate right: " << current_node->key << std::endl;
	}

	template <typename T>
	void BinaryTree<T>::dRotateLeft(Node<T>* &current_node)
	{
		rotateRight(current_node->right);
		rotateLeft(current_node);
	}



	template <typename T>
	void BinaryTree<T>::fixImbalance(Node<T>* &current_node) {
		bool btest = false;
		while(current_node != nullptr){ //search backwards for the first inbalanced node
			if(fabs(current_node->bf) > 1){
				std::cout << current_node->key << " is imbalanced ["
				<< current_node->bf << "], and my ";
				if(current_node->bf < 0){
					std::cout << "left child's bf is ["<<
					current_node->left->bf;
					if(current_node->left->bf < 0){
						std::cout << "<0]\n Performing a "
						<< "single rotation to the right.\n";
						rotateRight(current_node);
					}else{
						std::cout << ">=0]\n Performing a "
						<< "double rotation to the right.\n";
						dRotateRight(current_node);
					}
				}else{
					std::cout << "right child's bf is ["
					<< current_node->right->bf;
					if(current_node->right->bf < 0){
						std::cout << "<0]\n Performing a "
						<< "double rotation to the left.\n";
						dRotateLeft(current_node);
					}else{
						std::cout << ">=0]\n Performing a "
						<< " single rotation to the left.\n";
						rotateLeft(current_node);
					}
				}
				btest = true;
			}
			current_node = current_node->parent;
			if(current_node != nullptr){
				//set balancing factors for the sub-tree
				balFactOfNode(current_node);
			}
			if(btest)
			{
				break;
			}
		}
	}




};


#endif
