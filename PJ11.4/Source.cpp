#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Структура Zodiac
struct Zodiac {
    string surname;
    string name;
    string zodiacSign;
    int birthday[3]; // [0] - день, [1] - місяць, [2] - рік
};

// Функція для введення даних про людину
void InputData(Zodiac& person) {
    cout << "Введiть прiзвище: ";
    cin >> person.surname;
    cout << "Введiть iм'я: ";
    cin >> person.name;
    cout << "Введiть знак зодiаку: ";
    cin >> person.zodiacSign;
    cout << "Введiть дату народження (день мiсяць рiк через пробiл): ";
    cin >> person.birthday[0] >> person.birthday[1] >> person.birthday[2];
}

// Функція для читання даних із файлу
void ReadFromFile(const string& fileName, vector<Zodiac>& people) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    Zodiac person;
    while (file >> person.surname >> person.name >> person.zodiacSign
        >> person.birthday[0] >> person.birthday[1] >> person.birthday[2]) {
        people.push_back(person);
    }

    file.close();
}

// Функція для запису даних у файл
void WriteToFile(const string& fileName, const vector<Zodiac>& people) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cout << "Помилка відкриття файлу!" << endl;
        return;
    }

    for (const auto& person : people) {
        file << person.surname << " " << person.name << " " << person.zodiacSign << " "
            << person.birthday[0] << " " << person.birthday[1] << " " << person.birthday[2] << endl;
    }

    file.close();
}

// Функція для пошуку людини за прізвищем
void FindPerson(const vector<Zodiac>& people, const string& surname) {
    auto it = find_if(people.begin(), people.end(), [&surname](const Zodiac& person) {
        return person.surname == surname;
        });

    if (it != people.end()) {
        cout << "Знайдено: " << it->surname << " " << it->name << ", знак зодiаку: "
            << it->zodiacSign << ", дата народження: "
            << it->birthday[0] << "." << it->birthday[1] << "." << it->birthday[2] << endl;
    }
    else {
        cout << "Людину з таким прізвищем не знайдено." << endl;
    }
}

// Основна функція
int main() {
    setlocale(LC_ALL, "ukr");

    string fileName;
    cout << "Введіть ім'я файлу для запису даних: ";
    cin >> fileName;

    vector<Zodiac> people;
    int n;
    cout << "Скільки записів ви хочете додати? ";
    cin >> n;

    // Введення даних
    for (int i = 0; i < n; ++i) {
        Zodiac person;
        cout << "Введіть дані для людини " << i + 1 << ":" << endl;
        InputData(person);
        people.push_back(person);
    }

    // Запис у файл
    WriteToFile(fileName, people);

    // Зчитування даних із файлу
    vector<Zodiac> loadedPeople;
    ReadFromFile(fileName, loadedPeople);

    // Сортування за датами народження
    sort(loadedPeople.begin(), loadedPeople.end(), [](const Zodiac& a, const Zodiac& b) {
        if (a.birthday[2] != b.birthday[2])
            return a.birthday[2] < b.birthday[2];
        if (a.birthday[1] != b.birthday[1])
            return a.birthday[1] < b.birthday[1];
        return a.birthday[0] < b.birthday[0];
        });

    cout << "Дані відсортовано за датами народження!" << endl;

    // Пошук людини за прізвищем
    string searchSurname;
    cout << "Введіть прізвище для пошуку: ";
    cin >> searchSurname;
    FindPerson(loadedPeople, searchSurname);

    return 0;
}
