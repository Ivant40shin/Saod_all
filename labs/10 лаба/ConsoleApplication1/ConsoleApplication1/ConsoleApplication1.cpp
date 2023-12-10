/*
13. Узлами дерева являются записи информации о некотором
товаре в сети магазинов. Корень дерева соответствуют всей сети,
далее идут торговые точки, отделы, прилавки, полки и сами товары.
Существуют два дерева соответствующие разным периодам
торговли. Необходимо составить отчет об изменениях, то есть
определить:
• измененные (в том числе перемещенные в другой отдел)
товары;
• новые товары;
• удаленные товары;
• изменения в структуре торговой сети.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Node
{
public:
	std::string name; // Имя товара
	std::vector<Node*> children; // Список дочерних узлов
	Node* parent; // Родительский узел

	// Конструктор
	Node(std::string name) : name(name), parent(nullptr) {}

	// Функция для добавления дочернего узла
	void addChild(Node* child)
	{
		children.push_back(child);
		child->parent = this;
	}
};

// Функция для создания дерева
Node* createTree(std::string rootName)
{
	return new Node(rootName);
}

// Функция для проверки пустоты дерева
bool isTreeEmpty(Node* root)
{
	return root == nullptr;
}

// Функция для печати дерева
void printTree(Node* root, int level = 0)
{
	if (isTreeEmpty(root))
		return;

	for (int i = 0; i < level; i++)
		std::cout << "--";

	std::cout << root->name << std::endl;

	for (Node* child : root->children)
		printTree(child, level + 1);
}

// Функция для удаления элемента из дерева
void deleteNode(Node* parent, Node* child)
{
	parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), child), parent->children.end());
	delete child;
}

// Функция для удаления дерева
void deleteTree(Node*& root)
{
	if (isTreeEmpty(root))
		return;

	for (Node* child : root->children)
		deleteTree(child);

	delete root;
	root = nullptr;
}

// Функция для сравнения двух деревьев
void compareTrees(Node* oldTree, Node* newTree, std::unordered_map<std::string, Node*>& oldNodes, std::unordered_map<std::string, Node*>& newNodes)
{
	if (isTreeEmpty(oldTree) && isTreeEmpty(newTree))
		return;

	if (!isTreeEmpty(oldTree))
		oldNodes[oldTree->name] = oldTree;

	if (!isTreeEmpty(newTree))
		newNodes[newTree->name] = newTree;

	for (int i = 0; i < std::max(isTreeEmpty(oldTree) ? 0 : oldTree->children.size(), isTreeEmpty(newTree) ? 0 : newTree->children.size()); i++)
		compareTrees(i < oldTree->children.size() ? oldTree->children[i] : nullptr, i < newTree->children.size() ? newTree->children[i] : nullptr, oldNodes, newNodes);
}

// Функция для создания узла и его добавления к родительскому узлу
Node* createAndAddNode(Node* parent, const std::string& name)
{
	Node* node = new Node(name);
	parent->addChild(node);
	return node;
}

// Функция для печати изменений дерева
void printChanges(std::unordered_map<std::string, Node*>& oldNodes, std::unordered_map<std::string, Node*>& newNodes)
{
    // Проверяем измененные и удаленные товары
    for (auto& pair : oldNodes)
    {
        if (newNodes.count(pair.first) == 0)
        {
            std::cout << "Удаленный товар: " << pair.first << std::endl;
        }
    }

    // Проверяем новые товары
    for (auto& pair : newNodes)
    {
        if (oldNodes.count(pair.first) == 0)
        {
            std::cout << "Новый товар: " << pair.first << std::endl;
        }
    }

	// Проверяем перемещенные товары
	for (auto& pair : oldNodes)
	{
		if (newNodes.count(pair.first) != 0 && oldNodes[pair.first]->parent != newNodes[pair.first]->parent)
		{
			// Проверяем, что перемещенный узел является товаром, а не промежуточным узлом
			if (oldNodes[pair.first]->children.empty() && newNodes[pair.first]->children.empty())
			{
				std::cout << "Перемещенный товар: " << pair.first << std::endl;
			}
		}
	}
}

// Функция для сравнения и печати двух деревьев
void compareAndPrintChanges(Node* oldTree, Node* newTree)
{
	std::unordered_map<std::string, Node*> oldNodes, newNodes;
	compareTrees(oldTree, newTree, oldNodes, newNodes);
	printChanges(oldNodes, newNodes);
}

int main()
{
	system("chcp 1251 & cls");

	// Создаем два дерева
	Node* oldTree = createTree("Сеть магазинов");
	Node* newTree = createTree("Сеть магазинов");

	// Создаем структуру дерева для старого дерева
	Node* oldShop = createAndAddNode(oldTree, "Магазин 1");
	Node* oldDepartment1 = createAndAddNode(oldShop, "Отдел 1");
	Node* oldCounter1 = createAndAddNode(oldDepartment1, "Прилавок 1");
	Node* oldShelf1 = createAndAddNode(oldCounter1, "Полка 1");
	Node* oldProduct1 = createAndAddNode(oldShelf1, "Товар 1");
	Node* oldProduct2 = createAndAddNode(oldShelf1, "Товар 3");


	Node* oldDepartment2 = createAndAddNode(oldShop, "Отдел 2");
	Node* oldCounter2 = createAndAddNode(oldDepartment2, "Прилавок 2");
	Node* oldShelf2 = createAndAddNode(oldCounter2, "Полка 2");
	Node* oldProduct3 = createAndAddNode(oldShelf2, "Товар 2");


	// Создаем структуру дерева для нового дерева
	Node* newShop = createAndAddNode(newTree, "Магазин 1");
	Node* newDepartment1 = createAndAddNode(newShop, "Отдел 1");
	Node* newCounter1 = createAndAddNode(newDepartment1, "Прилавок 1");
	Node* newShelf1 = createAndAddNode(newCounter1, "Полка 1");

	Node* newDepartment2 = createAndAddNode(newShop, "Отдел 2");
	Node* newCounter2 = createAndAddNode(newDepartment2, "Прилавок 2");
	Node* newShelf2 = createAndAddNode(newCounter2, "Полка 2");
	Node* newProduct1 = createAndAddNode(newShelf2, "Товар 3");
	Node* newProduct2 = createAndAddNode(newShelf2, "Товар 4");
	Node* newProduct3 = createAndAddNode(newShelf2, "Товар 5");

	// Печатаем старое дерево
	std::cout << "Старое дерево:" << std::endl;
	printTree(oldTree);
	std::cout << std::endl;

	// Печатаем новое дерево
	std::cout << "Новое дерево:" << std::endl;
	printTree(newTree);
	std::cout << std::endl;

	// Сравниваем два дерева и выводим отчет об изменениях
	compareAndPrintChanges(oldTree, newTree);

	// Удаляем два дерева
	deleteTree(oldTree);
	deleteTree(newTree);

	return 0;
}
