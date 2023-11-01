#include <fstream>
#include <iostream>
#include <string>
#include <locale.h>
using namespace std;

void createTextFile(const char* namefile) {
	ofstream fout(namefile);
	for (int x = 1; x <= 10; x++) {
		fout << x << endl;
	}
	fout.close();
}

void displayFileContent(const char* namefile) {
	ifstream fin(namefile);
	if (!fin) {
		cout << "Ошибка при открытии файла." << endl;
		return;
	}

	int x;
	while (fin >> x) {
		cout << x << " ";
	}
	cout << endl;

	fin.close();
}

void appendToFile(const char* namefile, int value) {
	ofstream fout(namefile, ios::app);
	if (!fout) {
		cout << "Ошибка при открытии файла." << endl;
		return;
	}

	fout << value << endl;
	fout.close();
}

int readValueFromFile(const char* namefile, int n) {
	ifstream fin(namefile);
	if (!fin) {
		cout << "Ошибка при открытии файла." << endl;
		return 0;
	}

	int x;
	int count = 0;

	while (fin >> x) {
		count++;
		if (count == n) {
			fin.close();
			return x;
		}
	}

	fin.close();
	return 0;
}

int countNumbersInFile(const char* namefile) {
	ifstream fin(namefile);
	if (!fin) {
		cout << "Ошибка при открытии файла." << endl;
		return 0;
	}

	int x;
	int count = 0;
	while (fin >> x) {
		count++;
	}
	fin.close();
	return count;
}

int main() {
	setlocale(LC_ALL, "Russian");
	const char* filename = "A.txt";
	int choice;

	ifstream fin(filename); // Перенесем объявление сюда
	int valueToAdd; // Перенесем объявление сюда
	int n; // Перенесем объявление сюда
	int value = 0; // Перенесем объявление сюда
	int count = 0; // Перенесем объявление сюда

	do {
		cout << "Выберите действие:" << endl;
		cout << "1. Создать текстовый файл" << endl;
		cout << "2. Вывести содержимое текстового файла" << endl;
		cout << "3. Добавить новую запись в файл" << endl;
		cout << "4. Прочитать значение числа по номеру" << endl;
		cout << "5. Определить количество чисел в файле" << endl;
		cout << "6. Создать новый файл с умноженными значениями" << endl;
		cout << "7. Выход" << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			createTextFile(filename);
			cout << "Текстовый файл создан." << endl;
			break;
		case 2:
			displayFileContent(filename);
			break;
		case 3:
			cout << "Введите число для добавления: ";
			cin >> valueToAdd;
			appendToFile(filename, valueToAdd);
			cout << "Число добавлено в файл." << endl;
			break;
		case 4:
			cout << "Введите номер числа для чтения: ";
			cin >> n;
			value = readValueFromFile(filename, n);
			if (value != 0) {
				cout << "Значение: " << value << endl;
			}
			else {
				cout << "Число с указанным номером не найдено." << endl;
			}
			break;
		case 5:
			count = countNumbersInFile(filename);
			cout << "Количество чисел в файле: " << count << endl;
			break;
		case 6:
			// Создать новый файл с умноженными значениями
			
			if (!fin) {
				cout << "Ошибка при открытии файла." << endl;
				break;
			}

			int first, last;
			int x;
			

			while (fin >> x) {
				if (count == 0) {
					first = x;
				}
				last = x;
				count++;
			}

			if (count < 2) {
				cout << "Недостаточно чисел в файле для вычисления суммы." << endl;
			}
			else {
				fin.close();
				int multiplier = first + last;

				fin.open(filename);
				ofstream fout("B.txt");
				while (fin >> x) {
					fout <<(x * multiplier) << endl;
				}
				fin.close();
				fout.close();
				cout << "Создан новый файл B.txt с умноженными значениями." << endl;
			}
			break;
		case 7:
			cout << "Выход из программы." << endl;
			break;
		default:
			cout << "Неверный выбор. Попробуйте снова." << endl;
			break;
		}
	} while (choice != 7);

	fin.close(); // Закрыть файл при выходе из программы

	return 0;
}
