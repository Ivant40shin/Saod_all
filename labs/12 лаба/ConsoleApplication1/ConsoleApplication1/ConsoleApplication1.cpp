#include <iostream>
#include <vector>

/*
10.Имеется несколько AVL деревьев.Разработайте алгоритм
и программу поиска в этих деревьях.Затем разработайте алгоритм и
программу конкатенации этих деревьев и поиска в нем.Сравните
эффективность обоих подходов к поиску.
*/


struct Node
{
	int key;
	int height;
	Node* left;
	Node* right;
};

// Функция для создания нового узла
Node* createNode(int key)
{
	Node* newNode = new Node();
	newNode->key = key;
	newNode->height = 1;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}

// Функция для получения высоты узла
int getHeight(Node* node)
{
	if (node == nullptr)
		return 0;

	return node->height;
}

// Функция для обновления высоты узла
void updateHeight(Node* node)
{
	int leftHeight = getHeight(node->left);
	int rightHeight = getHeight(node->right);

	node->height = 1 + std::max(leftHeight, rightHeight);
}

// Функция для получения баланса узла
int getBalance(Node* node)
{
	if (node == nullptr)
		return 0;

	return getHeight(node->left) - getHeight(node->right);
}

// Функция для выполнения правого поворота
Node* rotateRight(Node* root)
{
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;

	updateHeight(root);
	updateHeight(newRoot);

	return newRoot;
}

// Функция для выполнения левого поворота
Node* rotateLeft(Node* root)
{
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;

	updateHeight(root);
	updateHeight(newRoot);

	return newRoot;
}

Node* balanceNode(Node* node)
{
    updateHeight(node);

    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0)
    {
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) <= 0)
    {
        return rotateLeft(node);
    }
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


bool isBalanced(Node* root)
{
	if (root == nullptr)
		return true;

	int balance = getBalance(root);

	if (balance > 1 || balance < -1)
	{
		//std::cout << "Дерево разбалансировано в узле с ключом " << root->key << ", баланс фактор: " << balance << std::endl;
		return false;
	}

	return isBalanced(root->left) && isBalanced(root->right);
}


// Функция для балансировки всего AVL-дерева
Node* balanceTree(Node* root)
{
	if (root == nullptr)
		return nullptr;

	root->left = balanceTree(root->left);
	root->right = balanceTree(root->right);

	root = balanceNode(root);
	if (isBalanced(root)) return root;
	return balanceTree(root);
}

// Функция для вставки узла в AVL-дерево
Node* insertNode(Node* root, const int key)
{
	if (root == nullptr)
		return createNode(key);
	if (key < root->key)
		root->left = insertNode(root->left, key);
	else if (key > root->key)
		root->right = insertNode(root->right, key);
	else
		return root;

	return balanceNode(root);
}

// Функция для создания AVL-дерева на основе упорядоченного массива
Node* createAVLTree(std::vector<int>& sortedArray, int start, int end)
{
	if (start > end)
		return nullptr;

	int mid = (start + end) / 2;
	Node* root = createNode(sortedArray[mid]);
	root->left = createAVLTree(sortedArray, start, mid - 1);
	root->right = createAVLTree(sortedArray, mid + 1, end);

	updateHeight(root);

	return root;
}

// Функция для создания упорядоченного AVL-дерева из неупорядоченного массива
Node* createOrderedAVLTree(std::vector<int>& array)
{
	Node* root = nullptr;
	for (int key : array)
		root = insertNode(root, key);

	return root;
}

// Функция для обхода AVL-дерева в порядке возрастания ключей (in-order traversal)
void inOrderTraversal(Node* root)
{
	if (root == nullptr)
		return;

	inOrderTraversal(root->left);
	std::cout << root->key << " ";
	inOrderTraversal(root->right);
}

// Функция для поиска ключа в AVL-дереве
Node* searchNode(Node* root, int key)
{
	if (root == nullptr || root->key == key)
		return root;

	if (key < root->key)
		return searchNode(root->left, key);
	else
		return searchNode(root->right, key);
}

// Функция для конкатенации двух AVL-деревьев (подход с последовательной вставкой элементов из второго дерева)
Node* concatenateAVLTrees(Node* tree1, Node* tree2)
{
	if (tree2 == nullptr)
		return tree1;

	tree1 = insertNode(tree1, tree2->key);
	tree1 = concatenateAVLTrees(tree1, tree2->left);
	tree1 = concatenateAVLTrees(tree1, tree2->right);
	
	return tree1;
}

// Функция для поиска узла с максимальным ключом
Node* findMax(Node* node)
{
	Node* current = node;

	// Переходим к самому правому узлу
	while (current->right != nullptr)
		current = current->right;

	return current;
}

// Функция для поиска узла с минимальным ключом
Node* findMin(Node* node)
{
	Node* current = node;

	// Переходим к самому правому узлу
	while (current->left != nullptr)
		current = current->left;

	return current;
}

// Функция для удаления узла с заданным ключом
Node* deleteNode(Node* root, const int key)
{
	// Базовый случай: корень - NULL или ключ - корень
	if (root == nullptr)
		return root;
	if (key < root->key)
		root->left = deleteNode(root->left, key);
	else if (key > root->key)
		root->right = deleteNode(root->right, key);
	else
	{
		// Удаление узла с одним или без дочерних узлов
		if ((root->left == nullptr) || (root->right == nullptr))
		{
			Node* temp = root->left ? root->left : root->right;

			// Без дочерних узлов
			if (temp == nullptr)
			{
				temp = root;
				root = nullptr;
			}
			else // Узел с одним дочерним узлом
				*root = *temp; // Копирование содержимого дочернего узла

			delete temp;
		}
		else
		{
			// Узел с двумя дочерними узлами: получаем инордерный преемник
			Node* temp = findMin(root->right);

			// Копирование содержимого инордерного преемника в этот узел
			root->key = temp->key;

			// Удаление инордерного преемника
			root->right = deleteNode(root->right, temp->key);
		}
	}

	if (root == nullptr)
		return root;

	return balanceNode(root);
}

// Функция для конкатенации двух AVL-деревьев (подход с удалением максимального узла из первого дерева)
Node* concatenateAVLTrees2(Node* tree1, Node* tree2)
{
	if (tree1 == nullptr)
		return tree2;

	if (tree2 == nullptr)
		return tree1;

	Node* maxNode = findMax(tree1);
	int maxKey = maxNode->key;

	tree1 = deleteNode(tree1, maxKey);


	Node* node = tree2->left;

	tree2->left = createNode(maxKey);

	tree2->left->left = tree1;
	tree2->left->right = node;


	return balanceTree(tree2);
}


int main() 
{
	system("chcp 1251");
	std::vector<int> arr1 = { 9, 5, 2, 7, 1, 1, 8, 6, 4, 10, 3 };
	Node* root1 = createOrderedAVLTree(arr1);

	std::cout << "AVL-дерево 1: ";
	inOrderTraversal(root1);
	std::cout << std::endl;

	int keyToFind = 6;
	Node* foundNode = searchNode(root1, keyToFind);
	if (foundNode != nullptr)
		std::cout << "Ключ " << keyToFind << " найден в AVL дереве 1." << std::endl;
	else
		std::cout << "Ключ " << keyToFind << " не найден в AVL дереве 1." << std::endl;

	std::vector<int> arr2 = { 15, 11, 11, 20, 14, 12, 18, 13, 19, 16, 17 };
	Node* root2 = createOrderedAVLTree(arr2);

	std::cout << "AVL-дерево 2: ";
	inOrderTraversal(root2);
	std::cout << std::endl;

	root1 = concatenateAVLTrees(root1, root2);
	std::cout << "конкатенация 2 AVL-деревьев: ";
	inOrderTraversal(root1);
	std::cout << std::endl;

	if (isBalanced(root1))
		std::cout << "Дерево сбалансировано после вставки." << std::endl;
	else
		std::cout << "Дерево разбалансировано после вставки." << std::endl;

	return 0;
}