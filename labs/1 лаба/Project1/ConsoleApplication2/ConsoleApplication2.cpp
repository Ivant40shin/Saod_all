#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define STUDENT_COUNT 50
#define FIO_LENGTH 15
#define SUBJECTS_COUNT 5

struct studentData
{
	int sequenceNumber;

	char name[FIO_LENGTH];
	char surname[FIO_LENGTH];
	char patronymic[FIO_LENGTH];

	int bookNumber;

	int markList[SUBJECTS_COUNT];

	double averageMark = 0;
};

void AddSpace(char array[])
{
	int tmp = strlen(array);
	while (tmp < FIO_LENGTH)
	{
		array[tmp] = ' ';
		tmp++;
	}
	array[FIO_LENGTH - 1] = 0;
}

int ReadTxt(const char fileName[], studentData studentList[], int& studentCount)
{
	FILE* f = 0;

	if (fopen_s(&f, fileName, "r") != 0)
		return -1;


	while (feof(f) == 0)
	{
		studentCount++;

		fscanf_s(f, "%d", &studentList[studentCount].sequenceNumber);

		fscanf(f, "%s", studentList[studentCount].surname);
		AddSpace(studentList[studentCount].surname);

		fscanf(f, "%s", studentList[studentCount].name);
		AddSpace(studentList[studentCount].name);

		fscanf(f, "%s", studentList[studentCount].patronymic);
		AddSpace(studentList[studentCount].patronymic);


		fscanf_s(f, "%d", &studentList[studentCount].bookNumber);

		for (int i = 0; i < SUBJECTS_COUNT; i++)
			fscanf_s(f, "%d", &studentList[studentCount].markList[i]);

		for (int i = 0; i < SUBJECTS_COUNT; i++)
			studentList[studentCount].averageMark += studentList[studentCount].markList[i];

		studentList[studentCount].averageMark = round(studentList[studentCount].averageMark * 1. / SUBJECTS_COUNT * 10) / 10;

	}

	studentCount++;

	fclose(f);

	return 0;
}

int PrintTable(studentData studentList[], int& studentCount, bool flag, char buffer[])
{
	char head[] = "ID | Surname        Name           Patronymic     | Book ID |";
	int headLen = strlen(head) + 4 * SUBJECTS_COUNT + 9;

	printf_s("%s", head);

	for (int i = 0; i < SUBJECTS_COUNT; i++)
		printf_s(" %c |", 'A' + i);

	printf_s("AV MARK |");

	printf_s("\n");

	for (int i = 0; i < headLen; i++)
		printf_s("-");

	printf_s("\n");

	for (int i = 0; i < studentCount; i++)
	{
		if (studentList[i].sequenceNumber < 10)
			printf_s("0%d | ", studentList[i].sequenceNumber);
		else
			printf_s("%d | ", studentList[i].sequenceNumber);

		if (flag)
		{
			char* tmp1 = strstr(studentList[i].surname, buffer);
			int tmp = (tmp1 - studentList[i].surname) / sizeof(char);
			int stringLen = strlen(buffer);

			for (int j = 0; j < tmp; j++)
				printf_s("%c", studentList[i].surname[j]);

			printf_s("\033[33m");
			for (int j = tmp; j < stringLen + tmp; j++)
				printf_s("%c", studentList[i].surname[j]);
			printf("\033[0m");

			for (int j = stringLen + tmp; j < FIO_LENGTH; j++)
				printf_s("%c", studentList[i].surname[j]);

			printf_s(" ");
		}
		else
			printf_s("%s ", studentList[i].surname);

		printf_s("%s ", studentList[i].name);
		printf_s("%s ", studentList[i].patronymic);

		printf_s("|  %d   | ", studentList[i].bookNumber);

		for (int j = 0; j < SUBJECTS_COUNT; j++)
		{
			printf_s("%d ", studentList[i].markList[j]);
			printf_s("| ");
		}

		printf_s(" %.1lf   |", studentList[i].averageMark);

		printf_s("\n");
	}

	for (int i = 0; i < headLen; i++)
		printf_s("-");

	printf_s("\n");

	return 0;
}

void swap(studentData studentList[], int i, int j)
{
	studentData temp = studentList[i];
	studentList[i] = studentList[j];
	studentList[j] = temp;
}

void SortSurname(studentData studentList[], int studentCount)
{
	bool swapped;

	for (int i = 0; i < studentCount - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < studentCount - i - 1; j++)
		{
			for (int k = 0; studentList[j].surname[k] != ' '; k++)
			{
				if (studentList[j].surname[k] > studentList[j + 1].surname[k])
				{
					swap(studentList, j, j + 1);
					swapped = true;
					break;
				}
				else if (studentList[j].surname[k] != studentList[j + 1].surname[k])
					break;
			}
		}
		if (swapped == false)
			break;
	}
}

void SortSubject(studentData studentList[], int studentCount)
{
	int choice = 0;

	printf_s("Sort by: \n0 - Return");

	for (int i = 0; i < SUBJECTS_COUNT; i++)
		printf_s("\n%d - Subject %c", i + 1, 'A' + i);

	printf_s("\n");

	while (true)
	{
		printf_s("Enter your choice: ");
		scanf_s("%d", &choice);

		if (choice == 0)
			return;

		else if (choice > 0 && choice <= SUBJECTS_COUNT)
		{
			bool swapped = false;

			for (int i = 0; i < studentCount - 1; i++)
			{
				swapped = false;

				for (int j = 0; j < studentCount - i - 1; j++)
				{
					if (studentList[j].markList[choice - 1] < studentList[j + 1].markList[choice - 1])
					{
						swap(studentList, j, j + 1);
						swapped = true;
					}
				}

				if (swapped == false)
					break;
			}

			return;
		}

		else
			printf_s("Invalid value!Try again.\n");
	}
}

void SortAverageMark(studentData studentList[], int studentCount)
{
	bool swapped = false;

	for (int i = 0; i < studentCount - 1; i++)
	{
		swapped = false;

		for (int j = 0; j < studentCount - i - 1; j++)
		{
			if (studentList[j].averageMark < studentList[j + 1].averageMark)
			{
				swap(studentList, j, j + 1);
				swapped = true;
			}
		}

		if (swapped == false)
			break;
	}

}

void FindSurname(studentData studentList[], int studentCount, char buffer[])
{
	studentData dopStudentList[STUDENT_COUNT / 5];
	int dopStudentCount = 0;

	for (int i = 0; i < studentCount; i++)
		if (strstr(studentList[i].surname, buffer))
			dopStudentList[dopStudentCount++] = studentList[i];

	if (dopStudentCount > 0)
		PrintTable(dopStudentList, dopStudentCount, 1, buffer);

	else
		printf_s("There is no such surname.\n");

	system("pause");
}

void GetSurname(char buffer[])
{
	printf_s("Enter surname: ");

	scanf("%s", buffer);
}

int main()
{
	studentData studentList[STUDENT_COUNT];
	int studentCount = -1;
	int choice = 0;
	char buffer[FIO_LENGTH] = { 0 };

	if (ReadTxt("Data.txt", studentList, studentCount) == -1)
	{
		printf_s("Error opening file!\n");
		return -1;
	}

	while (true)
	{
		system("cls");

		PrintTable(studentList, studentCount, 0, buffer);

		printf_s("Sort by:\n");
		printf_s("1 - surname\n");
		printf_s("2 - mark\n");
		printf_s("3 - Find surname\n");
		printf_s("4 - Sort by average mark\n");
		printf_s("0 - exit\n");
		printf_s("Enter your choice: ");


		/*
		Вариант 1 задание 2 в ЭОС
		*/
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 0:
			return 0;

		case 1:
			SortSurname(studentList, studentCount);
			break;

		case 2:
			SortSurname(studentList, studentCount);
			SortSubject(studentList, studentCount);
			break;

		case 3:
			GetSurname(buffer);
			FindSurname(studentList, studentCount, buffer);
			break;

		case 4:
			SortAverageMark(studentList, studentCount);
			break;

		default:
			printf_s("Invalid value! Try again.\n");

		}
	}


	return 0;
}

//#include <iostream>
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//struct Student {
//    int number;
//    char name[50];
//    char studentID[15];
//    int grades[5];
//};
//
//// Функция для считывания данных из файла и вывода на экран
//void readAndPrintData() {
//    FILE* file = fopen("students.txt", "r");
//    if (file == NULL) {
//        printf_s("Ошибка открытия файла!\n");
//        return;
//    }
//
//    struct Student students[10];
//    int numStudents = 0;
//    char line[100];
//
//    while (fgets(line, sizeof(line), file)) {
//        sscanf(line, "%d %s %s %d %d %d %d %d",
//            &students[numStudents].number,
//            students[numStudents].name,
//            students[numStudents].studentID,
//            &students[numStudents].grades[0],
//            &students[numStudents].grades[1],
//            &students[numStudents].grades[2],
//            &students[numStudents].grades[3],
//            &students[numStudents].grades[4]);
//        numStudents++;
//    }
//
//    fclose(file);
//
//    // Вывод данных на экран
//    for (int i = 0; i < numStudents; i++) {
//        printf_s("Студент %d:\n", students[i].number);
//        printf_s("ФИО: %s\n", students[i].name);
//        printf_s("Номер зачетки: %s\n", students[i].studentID);
//        printf_s("Оценки: ");
//        for (int j = 0; j < 5; j++) {
//            printf_s("%d ", students[i].grades[j]);
//        }
//        printf_s("\n\n");
//    }
//}
//
//// Функция для сортировки записей по полю "фамилия"
//void sortByLastName(struct Student students[], int numStudents) {
//    for (int i = 0; i < numStudents - 1; i++) {
//        for (int j = 0; j < numStudents - i - 1; j++) {
//            if (strcmp(students[j].name, students[j + 1].name) > 0) {
//                struct Student temp = students[j];
//                students[j] = students[j + 1];
//                students[j + 1] = temp;
//            }
//        }
//    }
//}
//
//// Функция для сортировки выбранного столбца с оценками
//void sortByGradesColumn(struct Student students[], int numStudents, int column) {
//    for (int i = 0; i < numStudents - 1; i++) {
//        for (int j = 0; j < numStudents - i - 1; j++) {
//            if (students[j].grades[column] > students[j + 1].grades[column]) {
//                struct Student temp = students[j];
//                students[j] = students[j + 1];
//                students[j + 1] = temp;
//            }
//        }
//    }
//}
//
//// Функция для поиска студента по фамилии
//void findStudent(struct Student students[], int numStudents, char lastName[]) {
//    for (int i = 0; i < numStudents; i++) {
//        if (strcmp(students[i].name, lastName) == 0) {
//            printf_s("Информация о студенте:\n");
//            printf_s("ФИО: %s\n", students[i].name);
//            printf_s("Номер зачетки: %s\n", students[i].studentID);
//            printf_s("Оценки: ");
//            for (int j = 0; j < 5; j++) {
//                printf_s("%d ", students[i].grades[j]);
//            }
//            printf_s("\n\n");
//            return;
//        }
//    }
//    printf_s("Студента с фамилией %s не найдено.\n", lastName);
//}
//
//int main() {
//    struct Student students[10];
//    int numStudents = 0;
//    int choice;
//
//    do {
//        printf_s("Выберите задание для выполнения:\n");
//        printf_s("1 - Считать данные из файла и вывести на экран\n");
//        printf_s("2 - Отсортировать записи по полю 'фамилия'\n");
//        printf_s("3 - Отсортировать выбранный столбец с оценками и вывести на экран\n");
//        printf_s("4 - Найти студента и вывести всю информацию о нём\n");
//        printf_s("0 - Выход\n");
//        printf_s("Ваш выбор: ");
//        scanf_s("%d", &choice);
//
//        switch (choice) {
//        case 1:
//            readAndPrintData();
//            break;
//        case 2:
//            sortByLastName(students, numStudents);
//            printf_s("Записи отсортированы по полю 'фамилия'.\n\n");
//            break;
//        case 3:
//            int column;
//            printf_s("Введите номер столбца для сортировки (от 0 до 4): ");
//            scanf_s("%d", &column);
//            sortByGradesColumn(students, numStudents, column);
//            printf_s("Столбец с оценками отсортирован и выведен на экран.\n\n");
//            break;
//        case 4:
//            char lastName[50];
//            printf_s("Введите фамилию студента для поиска: ");
//            scanf_s("%s", lastName);
//            findStudent(students, numStudents, lastName);
//            break;
//        case 0:
//            printf_s("Выход из программы.\n");
//            break;
//        default:
//            printf_s("Неверный выбор. Попробуйте ещё раз.\n");
//            break;
//        }
//    } while (choice != 0);
//
//    return 0;
//}