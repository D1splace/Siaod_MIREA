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
        cerr << "������ �������� �����!" << endl;
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
        cerr << "������ �������� �����!" << endl;
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
        cerr << "������ �������� �����!" << endl;
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
        cerr << "������ �������� �����!" << endl;
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
        cerr << "������ �������� �����!";
        return;
    }

    size_t len = key.size();
    binaryFile.write((char*)&len, sizeof(size_t));
    binaryFile.write(key.c_str(), len);
    binaryFile.close();
}

//��� �������� #1 (6 �������)
void structOfProducts(const string& name) {
    ofstream binaryFile(name, ios_base::binary | ios_base::app);
    if (!binaryFile) {
        cerr << "������ �������� �����!" << endl;
        return;
    }

    Product product;


    cout << "������� ���: ";
    cin >> product.code;
    cin.ignore(); // ���������� ������ ����� ������.

    cout << "������� �������� ������: ";
    getline(cin, product.country);

    cout << "������� �������� ������: ";
    getline(cin, product.factoryName);

    cout << "������� ����: ";
    cin >> product.price;

    // ���������� ��������� Product � ����.
    binaryFile.write((char*)&product, sizeof(Product));

    binaryFile.close();

    // ������� ���������� � ���������� ��������.
    cout << "������� �������:" << endl;
    cout << "������: " << product.country<< endl;
    cout << "���: " << product.code << endl;
    cout << "�������� ������: " << product.factoryName << endl;
    cout << "����: " << product.price << endl;
}

//��� �������� #2 (6 �������)
void newRecording(const string& name) {
    ofstream binaryFile(name, ios_base::binary | ios_base::app);
    if (!binaryFile) {
        cerr << "������ �������� �����!";
        return;
    }

    Product product;


    cout << "������� ���: ";
    cin >> product.code;
    cin.ignore(); // ���������� ������ ����� ������.

    cout << "������� �������� ������: ";
    getline(cin, product.country);

    cout << "������� �������� ������: ";
    getline(cin, product.factoryName);

    cout << "������� ����: ";
    cin >> product.price;

    // ���������� ��������� Product � ����.
    binaryFile.write((char*)&product, sizeof(Product));

    binaryFile.close();

    cout << "������� �������:" << endl;
    cout << "������: " << product.country << endl;
    cout << "���: " << product.code << endl;
    cout << "�������� ������: " << product.factoryName << endl;
    cout << "����: " << product.price << endl;
}


int main() {
    setlocale(LC_ALL, "ru");
    cout << "�������� �������� �� 0 �� 9" << endl
        << "0 - ��������� ������ ���������" << endl
        << "1 - ������� �������� ���� � �������� � ���� ������ �� ASCII.txt" << endl
        << "2 - ��������� �������� ���� � ����� ������� txt" << endl
        << "3 - ������� ������ �� ��������� ����� �� �����" << endl
        << "4 - ����� ����� �� ����������� ������" << endl
        << "5 - ������� ��� ������ �� ��������� ����� � �������� � ���� ��������� ��������� �����" << endl
        << "6 - �������� ��������� ������" << endl
        << "7 - �������� ����� � ����" << endl;
    string name, nameTxt, key, word, newName;
    int choise, order;
    cout << "������� �������� ����� � ����������� .bin" << endl;
    cin >> name;
    while (true) {
        cout << "�������� ��������" << endl;
        cin >> choise;
        switch (choise)
        {
        case 0:
            return 0;
            break;
        case 1:
            makeBinaryFile(name);
            cout << "�������� ���� ������� �������!" << endl;
            break;
        case 2:
            cout << "������� �������� ����� � ����������� .txt" << endl;
            cin >> nameTxt;
            saveBinaryInTxt(name, nameTxt);
            cout << "��������� ���� ������� �������!" << endl;
            break;
        case 3:
            readBinaryFile(name);
            break;
        case 4:
            cout << "������� ���������� �����" << endl;
            cin >> order;
            cout << "��������� �����: ";
            findNumByOrder(name, order);
            cout << endl;
            break;
        case 5:
            cout << "��������, ����� ����� ���������� ������ �������, ��� ������ �� ��������� ����� ��������!" << endl;
            cout << "������� ��������� �����, ������� ������ ��������" << endl;
            cin >> key;
            deleteTextByKey(name, key);
            break;
        case 6:
            cout << "������� �������� ����� �����:";
            cin >> newName;
            structOfProducts(newName);
            break;
        case 7:
            newRecording(newName);
            cout << "����� ������� ���������!" << endl;
            break;
        
        default:
            cout << "������ �������� �� ����������!" << endl;
            break;
        }
    }
}