#define null 0
#include <iostream>

unsigned int _abs(int n)
{
	if (n < 0)
		return -n;
	return n;
}

template< class T >
struct treenode
{
	T value;
	treenode* left;
	treenode* right;
	int height;

	treenode(T const& value) :
		value(value),
		left(null),
		right(null),
		height(1)
	{
	}
}; // class treenode

// balance < 0 -> left rotation
// balance > 0 -> right rotation
// adapted from https://github.com/geekific-official/geekific-youtube/blob/main/tree-avl/src/main/java/com/youtube/geekific/AVLTree.java
template< class T >
class avltree
{
	public:
	typedef treenode< T > node_type;

	private:
	node_type* root;

	public:
	avltree() :
		root(null)
	{
	}

	~avltree()
	{
		avltree::release(this->root);
	}

	public:
	void insert(T const& value)
	{
		this->root = avltree::insert(value, this->root);
	}

	void remove(T const& value)
	{
		this->root = avltree::remove(value, this->root);
	}

	bool search(T const& value)
	{
		node_type* node = root;

		while (node != null)
		{
			if (value > node->value)
				node = node->right;
			else if (value < node->value)
				node = node->left;
			else
				return true;
		}
		return false;
	}

	void print(std::ostream &stream = std::cout)
	{
		avltree::print("", this->root, false);
		std::cout.flush();
	}

	void print_inorder()
	{
		avltree::print_inorder(this->root);
	}

	private:
	static node_type* insert(T const& value, node_type* node)
	{
		if (node == null)
			return new node_type(value);
		if (value < node->value)
			node->left = avltree::insert(value, node->left);
		else if (value > node->value)
			node->right = avltree::insert(value, node->right);
		else
			return node;
		avltree::update_height(node);
		return avltree::rebalance(node);
	}

	static node_type* remove(T const& value, node_type* node)
	{
		if (node == null)
			return null;
		if (value < node->value)
			node->left = avltree::remove(value, node->left);
		else if (value > node->value)
			node->right = avltree::remove(value, node->right);
		else
		{
			//* value was found in the tree

			// has 0-1 child
			if (node->left == null)
				return node->right;
			else if (node->right == null)
				return node->left;

			// has 2 children
			node->value = avltree::get_max(node->left); //? maybe swap pointers instead
			node->left = avltree::remove(node->value, node->left);
		}
		avltree::update_height(node);
		return avltree::rebalance(node);
	}

	static node_type* search(T const& value, node_type* node)
	{
		return false;
	}

	static void update_height(node_type* node)
	{
		int max_height = std::max(
			avltree::get_height(node->left),
			avltree::get_height(node->right)
		);
		node->height = max_height + 1;
	}

	static node_type* rebalance(node_type* node)
	{
		int balance = avltree::get_balance(node);
		int balance_next;

		if (balance > 1)
		{
			balance_next = avltree::get_balance(node->left);
			if (balance_next < 0)
				node->left = avltree::rotate_left(node->left);
			return avltree::rotate_right(node);
		}
		else if (balance < -1)
		{
			balance_next = avltree::get_balance(node->right);
			if (balance_next > 0)
				node->right = avltree::rotate_right(node->right);
			return avltree::rotate_left(node);
		}
		return node;
	}

	static node_type* rotate_right(node_type* node)
	{
		node_type* left = node->left;
		node_type* center = left->right;

		left->right = node;
		node->left = center;
		avltree::update_height(node);
		avltree::update_height(left);
		return left;
	}

	static node_type* rotate_left(node_type* node)
	{
		node_type* right = node->right;
		node_type* center = right->left;

		right->left = node;
		node->right = center;
		avltree::update_height(node);
		avltree::update_height(right);
		return right;
	}

	static int get_balance(node_type* node)
	{
		if (node == null)
			return 0;
		return avltree::get_height(node->left) - avltree::get_height(node->right);
	}

	static int get_height(node_type* node)
	{
		if (node == null)
			return 0;
		return node->height;
	}

	static void print(std::string const& prefix, node_type const* node, bool is_left)
	{
		std::cout
			<< prefix
			<< (is_left ? "├──" : "└──")
			<< " ";
		if (node == null)
			std::cout << '\n';
		else
		{
			std::cout << node->value << '\n';
			print(prefix + (is_left ? "│" : " ") + "   ", node->left, true);
			print(prefix + (is_left ? "│" : " ") + "   ", node->right, false);
		}
	}

	static void print_inorder(node_type const* node)
	{
		if (node == null)
			return ;
		print_inorder(node->left);
		std::cout << node->value << '\n';
		print_inorder(node->right);
	}

	static void release(node_type* node)
	{
		if (node == null)
			return ;
		release(node->left);
		release(node->right);
		delete node;
	}

	static bool is_balanced(node_type* node)
	{
		int h_left = avltree::get_height(node->left);
		int h_right = avltree::get_height(node->right);

		return _abs(h_left - h_right) <= 1;
	}

	static bool check_balance(node_type* node)
	{
		return (avltree::is_balanced(node))
			&& (avltree::check_balance(node->left))
			&& (avltree::check_balance(node->right));
	}

	static T& get_max(node_type* node)
	{
		if (node->right != null)
			return avltree::get_max(node->right);
		return node->value;
	}
}; // class avltree
