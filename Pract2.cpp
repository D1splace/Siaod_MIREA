#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Product {
    string country;
    string code;
    string factoryName;
    double price;
};
void makeBinaryFile(const string& name) {
    ifstream file("ASCII.txt");
    ofstream binaryFile(name, ios_base::binary | ios_base::app);
    if (!file ||!binaryFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        size_t len = line.size();
        binaryFile.write((char*)&len, sizeof(size_t));
        binaryFile.write(line.c_str(), len);
    }

    file.close();
    binaryFile.close();
}

void saveBinaryInTxt(const string& nameBinaryFile, const string& nameTxtFile) {
    ifstream binaryFile(nameBinaryFile, ios_base::in | ios_base::binary);
    ofstream textFile(nameTxtFile, ios_base::binary | ios_base::app);

    if (!binaryFile  ||!textFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    string line;
    while (getline(binaryFile, line)) {
        size_t len = line.size();
        textFile.write((char*)&len, sizeof(size_t));
        textFile.write(line.c_str(), len);
    }

    binaryFile.close();
    textFile.close();
}

void readBinaryFile(const string& name) {
    ifstream binaryFile(name, ios_base::in | ios_base::binary);

    if (!binaryFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    string line;
    while (!binaryFile.eof()) {
        size_t len;
        if (!binaryFile.read((char*)&len, sizeof(size_t)))
            break;
        line.resize(len);
        binaryFile.read(&line[0], len);
        cout << line << " ";
    }
    cout << endl;

    binaryFile.close();
}

void findNumByOrder(const string& name, int order) {
    ifstream binaryFile(name, ios_base::in | ios_base::binary);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    string line;
    int count = 0;
    while (!binaryFile.eof()) {
        size_t len;
        if (!binaryFile.read((char*)&len, sizeof(size_t)))
            break;
        line.resize(len);
        binaryFile.read(&line[0], len);
        count++;

        if (count == order) {
            cout << line << " ";
            break;
        }
    }
    binaryFile.close();
}

void deleteTextByKey(const string& name, string key) {
    ofstream binaryFile(name, ios_base::trunc | ios_base::binary);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла!";
        return;
    }

    size_t len = key.size();
    binaryFile.write((char*)&len, sizeof(size_t));
    binaryFile.write(key.c_str(), len);
    binaryFile.close();
}

//Доп операция #1 (6 вариант)
void structOfProducts(const string& name) {
    ofstream binaryFile(name, ios_base::binary | ios_base::app);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    Product product;


    cout << "Введите код: ";
    cin >> product.code;
    cin.ignore(); // Сбрасываем символ новой строки.

    cout << "Введите название страны: ";
    getline(cin, product.country);

    cout << "Введите название завода: ";
    getline(cin, product.factoryName);

    cout << "Введите цену: ";
    cin >> product.price;

    // Записываем структуру Product в файл.
    binaryFile.write((char*)&product, sizeof(Product));

    binaryFile.close();

    // Выводим информацию о записанном продукте.
    cout << "Записан продукт:" << endl;
    cout << "страна: " << product.country<< endl;
    cout << "Код: " << product.code << endl;
    cout << "Название завода: " << product.factoryName << endl;
    cout << "Цена: " << product.price << endl;
}

//Доп операция #2 (6 вариант)
void newRecording(const string& name) {
    ofstream binaryFile(name, ios_base::binary | ios_base::app);
    if (!binaryFile) {
        cerr << "Ошибка открытия файла!";
        return;
    }

    Product product;


    cout << "Введите код: ";
    cin >> product.code;
    cin.ignore(); // Сбрасываем символ новой строки.

    cout << "Введите название страны: ";
    getline(cin, product.country);

    cout << "Введите название завода: ";
    getline(cin, product.factoryName);

    cout << "Введите цену: ";
    cin >> product.price;

    // Записываем структуру Product в файл.
    binaryFile.write((char*)&product, sizeof(Product));

    binaryFile.close();

    cout << "Записан продукт:" << endl;
    cout << "страна: " << product.country << endl;
    cout << "Код: " << product.code << endl;
    cout << "Название завода: " << product.factoryName << endl;
    cout << "Цена: " << product.price << endl;
}


int main() {
    setlocale(LC_ALL, "ru");
    cout << "Выберите действие от 0 до 9" << endl
        << "0 - Завершить работу программы" << endl
        << "1 - Создать двоичный файл и записать в него данные из ASCII.txt" << endl
        << "2 - Сохранить двоичный файл в файле формата txt" << endl
        << "3 - Вывести данные из двоичного файла на экран" << endl
        << "4 - Найти слово по порядковому номеру" << endl
        << "5 - Удалить все данные из двоичного файла и записать в него последнее введенное слово" << endl
        << "6 - Записать структуру товара" << endl
        << "7 - Добавить слово в файл" << endl;
    string name, nameTxt, key, word, newName;
    int choise, order;
    cout << "Введите название файла с расширением .bin" << endl;
    cin >> name;
    while (true) {
        cout << "Выберите действие" << endl;
        cin >> choise;
        switch (choise)
        {
        case 0:
            return 0;
            break;
        case 1:
            makeBinaryFile(name);
            cout << "Бинарный файл успешно записан!" << endl;
            break;
        case 2:
            cout << "Введите название файла с расширением .txt" << endl;
            cin >> nameTxt;
            saveBinaryInTxt(name, nameTxt);
            cout << "Текстовый файл успешно записан!" << endl;
            break;
        case 3:
            readBinaryFile(name);
            break;
        case 4:
            cout << "Введите порядковый номер" << endl;
            cin >> order;
            cout << "Найденное слово: ";
            findNumByOrder(name, order);
            cout << endl;
            break;
        case 5:
            cout << "Внимание, после этого выполнения данной функции, все данные из двоичного файла сотрутся!" << endl;
            cout << "Введите последнее слово, которое хотите добавить" << endl;
            cin >> key;
            deleteTextByKey(name, key);
            break;
        case 6:
            cout << "Введите название новго файла:";
            cin >> newName;
            structOfProducts(newName);
            break;
        case 7:
            newRecording(newName);
            cout << "Товар успешно добавлено!" << endl;
            break;
        
        default:
            cout << "Такого действия не существует!" << endl;
            break;
        }
    }
}