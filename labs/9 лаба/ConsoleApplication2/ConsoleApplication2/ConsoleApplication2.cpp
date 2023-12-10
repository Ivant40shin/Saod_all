/*
Записи файла о неуспевающих студентах имеют следующую
структуру:
Факультет
Группа
Фамилия студента
Число хвостов
Файл частично отсортирован. Записи по каждому факультету, а также по каждой группе расположены
в файле друг за другом. После пересдачи экзаменов число хвостов у студентов уменьшается.
Требуется обеспечить коррекцию информации с помощью индексирования. Если студент выбывает из
должников, пометить соответствующую запись специальным флагом. Написать программу копирования
файла с физическим удалением помеченных записей.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Уменьшает количество долгов каждого студента на 1
void decreaseDebts(const string& inputFilename, const string& outputFilename)
{
	ifstream inputFile(inputFilename);
	ofstream outputFile(outputFilename);

	if (!inputFile.is_open() || !outputFile.is_open())
	{
		cerr << "Failed to open the files." << endl;
		return;
	}

	string line;

	// Читаем строки из input.txt
	while (getline(inputFile, line))
	{
		size_t posTails = line.find_last_of(' ');
		string tailsStr = line.substr(posTails + 1);
		int tails = stoi(tailsStr);

		if (tails > 0)
			tails--;
		
		outputFile << line.substr(0, posTails + 1) << tails << '\n';
	}

	inputFile.close();
	outputFile.close();

	cout << "Debts decreased successfully." << endl;
}

// Создает файл индексов, содержащий номера строк, в которых студенты не имеют долгов
void writeIndexFile(const string& inputFilename, const string& indexFilename)
{
	ifstream inputFile(inputFilename);
	ofstream indexFile(indexFilename);

	if (!inputFile.is_open() || !indexFile.is_open())
	{
		cerr << "Failed to open the files." << endl;
		return;
	}

	string line;
	int index = 1;

	while (getline(inputFile, line))
	{
		size_t posTails = line.find_last_of(' ');
		string tailsStr = line.substr(posTails + 1);
		int tails = stoi(tailsStr);

		if (tails == 0)
			indexFile << index << '\n';
		
		index++;
	}

	inputFile.close();
	indexFile.close();

	cout << "Index file created successfully." << endl;
}

// Копирует данные с файла без учета помеченных записей
void copyUnmarkedLines(const string& inputFilename, const string& outputFilename, const string& indexFilename)
{
	ifstream indexFile(indexFilename);
	ifstream inputFile(inputFilename);
	ofstream outputFile(outputFilename);

	if (!indexFile.is_open() || !inputFile.is_open() || !outputFile.is_open())
	{
		cerr << "Failed to open the files." << endl;
		return;
	}

	vector<int> positions;
	int position;

	// Читаем индексы строк из index.txt и сохраняем их в векторе
	while (indexFile >> position)
	{
		positions.push_back(position);
	}

	indexFile.close();

	string line;
	int currentIndex = 1;
	int deleteIndex = 0;

	// Читаем строки из input.txt и пропускаем строки, которые должны быть удалены
	while (getline(inputFile, line))
	{
		if (deleteIndex >= positions.size() || currentIndex != positions[deleteIndex])
		{
			outputFile << line << '\n';
		}
		else
		{
			deleteIndex++;
		}

		currentIndex++;
	}

	inputFile.close();
	outputFile.close();

	cout << "Lines removed successfully." << endl;
}

int main()
{
	string testFilename = "test.txt";
	string inputFilename = "input.txt";
	string outputFilename = "output.txt";
	string indexFilename = "index.txt";

	decreaseDebts(testFilename, inputFilename);
	writeIndexFile(inputFilename, indexFilename);
	copyUnmarkedLines(inputFilename, outputFilename, indexFilename);

	return 0;
}