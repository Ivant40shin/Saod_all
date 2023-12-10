#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#define STUDENTS_COUNT 30
#define SIZE_FNAME 50
#define GRADES_COUNT 5

struct Student
{
	int number;

	char name[SIZE_FNAME];
	char surname[SIZE_FNAME];
	char patronymic[SIZE_FNAME];

	int gradebookID;
	int grades[GRADES_COUNT];
};

//считывает с файла и заполняет массив структур
void ReadFile(Student* students, const char* fileName, int& studentsCount)
{
	FILE* file;
	fopen_s(&file, fileName, "r");

	if (file == NULL)
	{
		printf_s("Файл не открылся");
		exit(-1);
	}
	while (!feof(file))
	{
		fscanf_s(file, "%d", &students[studentsCount].number);
		fscanf_s(file, "%s", students[studentsCount].surname, SIZE_FNAME);
		fscanf_s(file, "%s", students[studentsCount].name, SIZE_FNAME);
		fscanf_s(file, "%s", students[studentsCount].patronymic, SIZE_FNAME);
		fscanf_s(file, "%d", &students[studentsCount].gradebookID);

		for (int i = 0; i < GRADES_COUNT; i++)
			fscanf_s(file, "%d", &students[studentsCount].grades[i]);

		studentsCount++;
	}
	fclose(file);
}

//Выводит данные на экран
void PrintData(const Student* students, const int& studentsCount)
{
	for (int i = 0; i < 72; i++)
		printf_s("-");
	printf_s("\n");
		  
	printf_s("|  № |   Фамилие        Имя      Отчество |     ID | A | B | C | D | E |\n");

	for (int i = 0; i < 72; i++)
		printf_s("-");
	printf_s("\n");

	for (int i = 0; i < studentsCount; i++)
	{
		printf_s("| %2d | %9s %10s %13s | %d |", students[i].number, students[i].surname, students[i].name, students[i].patronymic, students[i].gradebookID);
		
		for (int j = 0; j < GRADES_COUNT; j++)
			printf_s(" %d |", students[i].grades[j]);

		printf_s("\n");
	}
	for (int i = 0; i < 72; i++)
		printf_s("-");

	printf_s("\n");
}

//Сравнивает 2 строки
int StrCmp(const char* str1, const char* str2) 
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}

	return *(unsigned char*)str1 - *(unsigned char*)str2;
}

//Сортирует по фамилии
void SortSurname(Student* students, const int& studentsCount)
{
	for (int i = 0; i < studentsCount - 1; i++)	
		for (int j = 0; j < studentsCount - i - 1; j++)		
			if (StrCmp(students[j].surname, students[j + 1].surname) > 0)
			{
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
}

//Сортирует по оценке
void SortGrade(Student* students, const int& studentsCount, int num)
{
	if (num > GRADES_COUNT)
		return;

	for (int i = 0; i < studentsCount - 1; i++)
		for (int j = 0; j < studentsCount - i - 1; j++)
			if (students[j].grades[num] < students[j + 1].grades[num])
			{
				Student temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
}

//Находит данные студента по фамилии
void FindStudentBySurname(const Student* students, const int& studentsCount, const char* surname)
{
	bool found = false;

	for (int i = 0; i < studentsCount; i++)
		if (strcmp(students[i].surname, surname) == 0)
		{
			printf_s("Студент найден:\n");
			printf_s("№: %d\n", students[i].number);
			printf_s("Имя: %s\n", students[i].name);
			printf_s("Фамилия: %s\n", students[i].surname);
			printf_s("Отчество: %s\n", students[i].patronymic);
			printf_s("Зачётная книжка ID: %d\n", students[i].gradebookID);
			printf_s("Оценки: ");
			for (int j = 0; j < GRADES_COUNT; j++)
			{
				printf_s("%d ", students[i].grades[j]);
			}
			printf_s("\n");

			found = true;
		}
	

	if (!found)
		printf_s("Студент с фамилией '%s' не найден.\n", surname);
	
}

//Список предметов
void PrintSubjectList()
{
	printf_s("%80sA - Программирование\n", "");
	printf_s("%80sB - История\n", "");
	printf_s("%80sC - Информатика\n", "");
	printf_s("%80sD - Математический анализ\n", "");
	printf_s("%80sE - Дискретная математика\n", "");
}

int main()
{
	system("chcp 1251 & cls");

	Student students[STUDENTS_COUNT];

	char fileName[] = "1.txt";
	int studentsCount = 0;
	int choice = 0;
	char surname[SIZE_FNAME];
	int choiceSubject = 0;

	ReadFile(students, fileName, studentsCount);

	while (true)
	{
	PrintData(students, studentsCount);
	PrintSubjectList();

	printf_s("Сортировать по:\n1 - фамилия\n2 - оценка\n3 - найти студента по фамилии\nДругое - выход\n");

	scanf_s("%d", &choice);
	switch (choice)
	{
	case 1:
		SortSurname(students, studentsCount);
		break;
	case 2:
		system("cls");
		PrintData(students, studentsCount);
		PrintSubjectList();

		printf_s("Сортировать по:\n1 - предмет A\n2 - предмет B\n3 - предмет C\n4 - предмет D\n5 - предмет E\nДругое - вернуться в меню\n");
		scanf_s("%d", &choiceSubject);

			SortGrade(students, studentsCount, choiceSubject - 1);
		break;
	case 3:
		system("cls");
		PrintData(students, studentsCount);
		PrintSubjectList();

		printf_s("Введите фамилию: ");

		scanf("%s", surname);

		FindStudentBySurname(students, studentsCount, surname);
		system("pause");
		break;
	default:
		return 0;
	}
	system("cls");
	}

	return 0;
}