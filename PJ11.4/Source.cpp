#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ��������� Zodiac
struct Zodiac {
    string surname;
    string name;
    string zodiacSign;
    int birthday[3]; // [0] - ����, [1] - �����, [2] - ��
};

// ������� ��� �������� ����� ��� ������
void InputData(Zodiac& person) {
    cout << "����i�� ��i�����: ";
    cin >> person.surname;
    cout << "����i�� i�'�: ";
    cin >> person.name;
    cout << "����i�� ���� ���i���: ";
    cin >> person.zodiacSign;
    cout << "����i�� ���� ���������� (���� �i���� �i� ����� ����i�): ";
    cin >> person.birthday[0] >> person.birthday[1] >> person.birthday[2];
}

// ������� ��� ������� ����� �� �����
void ReadFromFile(const string& fileName, vector<Zodiac>& people) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "������� �������� �����!" << endl;
        return;
    }

    Zodiac person;
    while (file >> person.surname >> person.name >> person.zodiacSign
        >> person.birthday[0] >> person.birthday[1] >> person.birthday[2]) {
        people.push_back(person);
    }

    file.close();
}

// ������� ��� ������ ����� � ����
void WriteToFile(const string& fileName, const vector<Zodiac>& people) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "������� �������� �����!" << endl;
        return;
    }

    for (const auto& person : people) {
        file << person.surname << " " << person.name << " " << person.zodiacSign << " "
            << person.birthday[0] << " " << person.birthday[1] << " " << person.birthday[2] << endl;
    }

    file.close();
}

// ������� ��� ������ ������ �� ��������
void FindPerson(const vector<Zodiac>& people, const string& surname) {
    auto it = find_if(people.begin(), people.end(), [&surname](const Zodiac& person) {
        return person.surname == surname;
        });

    if (it != people.end()) {
        cout << "��������: " << it->surname << " " << it->name << ", ���� ���i���: "
            << it->zodiacSign << ", ���� ����������: "
            << it->birthday[0] << "." << it->birthday[1] << "." << it->birthday[2] << endl;
    }
    else {
        cout << "������ � ����� �������� �� ��������." << endl;
    }
}

// ������� �������
int main() {
    setlocale(LC_ALL, "ukr");

    string fileName;
    cout << "������ ��'� ����� ��� ������ �����: ";
    cin >> fileName;

    vector<Zodiac> people;
    int n;
    cout << "������ ������ �� ������ ������? ";
    cin >> n;

    // �������� �����
    for (int i = 0; i < n; ++i) {
        Zodiac person;
        cout << "������ ��� ��� ������ " << i + 1 << ":" << endl;
        InputData(person);
        people.push_back(person);
    }

    // ����� � ����
    WriteToFile(fileName, people);

    // ���������� ����� �� �����
    vector<Zodiac> loadedPeople;
    ReadFromFile(fileName, loadedPeople);

    // ���������� �� ������ ����������
    sort(loadedPeople.begin(), loadedPeople.end(), [](const Zodiac& a, const Zodiac& b) {
        if (a.birthday[2] != b.birthday[2])
            return a.birthday[2] < b.birthday[2];
        if (a.birthday[1] != b.birthday[1])
            return a.birthday[1] < b.birthday[1];
        return a.birthday[0] < b.birthday[0];
        });

    cout << "��� ����������� �� ������ ����������!" << endl;

    // ����� ������ �� ��������
    string searchSurname;
    cout << "������ ������� ��� ������: ";
    cin >> searchSurname;
    FindPerson(loadedPeople, searchSurname);

    return 0;
}
