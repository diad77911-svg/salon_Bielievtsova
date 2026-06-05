#define _CRT_SECURE_NO_WARNINGS
#include "SalonTypes.h"
#include "ArrayTemplate.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>
using namespace std;

// ========== ГЛОБАЛЬНІ МАСИВИ ==========
Service* services = nullptr;
int serviceCount = 0;
Visit* visits = nullptr;
int visitCount = 0;

// ========== ДОПОМІЖНІ ФУНКЦІЇ ==========
void splitFullName(const string& full, string& surname, string& name, string& patronymic) {
    size_t firstSpace = full.find(' ');
    size_t lastSpace = full.rfind(' ');
    if (firstSpace == string::npos) {
        surname = full; name = ""; patronymic = "";
    }
    else if (firstSpace == lastSpace) {
        surname = full.substr(0, firstSpace);
        name = full.substr(firstSpace + 1);
        patronymic = "";
    }
    else {
        surname = full.substr(0, firstSpace);
        name = full.substr(firstSpace + 1, lastSpace - firstSpace - 1);
        patronymic = full.substr(lastSpace + 1);
    }
}

string getCurrentDate() {
    time_t t = time(nullptr);
    struct tm buf;
#ifdef _MSC_VER
    localtime_s(&buf, &t);  
#else
    struct tm* now = localtime(&t);
    buf = *now;
#endif
    char dateStr[11];
    strftime(dateStr, sizeof(dateStr), "%d.%m.%Y", &buf);
    return string(dateStr);
}

// ========== ПОСЛУГИ ==========
void printService(const Service& s, int index) {
    cout << index + 1 << ". " << s.name << " | " << s.direction << " | " << s.price << " грн" << endl;
}

void printAllServices() {
    if (serviceCount == 0) {
        cout << "Список послуг порожній.\n";
        return;
    }
    cout << "\n===== СПИСОК ПОСЛУГ =====\n";
    for (int i = 0; i < serviceCount; i++)
        printService(services[i], i);
}

void addService() {
    Service s;
    cin.ignore();
    cout << "Назва послуги: "; getline(cin, s.name);
    cout << "Напрямок: "; getline(cin, s.direction);
    cout << "Вартість: "; cin >> s.price;
    addItemBack(services, serviceCount, s);
    cout << "Послугу додано!\n";
}

void deleteService() {
    printAllServices();
    if (serviceCount == 0) return;
    cout << "Номер послуги для видалення: ";
    int idx; cin >> idx; idx--;
    if (idx < 0 || idx >= serviceCount) {
        cout << "Невірний номер.\n";
        return;
    }
    removeItemAt(services, serviceCount, idx);
    cout << "Послугу видалено!\n";
}

void editService() {
    printAllServices();
    if (serviceCount == 0) return;
    cout << "Номер послуги для редагування: ";
    int idx; cin >> idx; idx--;
    if (idx < 0 || idx >= serviceCount) return;
    cin.ignore();
    cout << "Нова назва (" << services[idx].name << "): ";
    string tmp; getline(cin, tmp); if (!tmp.empty()) services[idx].name = tmp;
    cout << "Новий напрямок (" << services[idx].direction << "): ";
    getline(cin, tmp); if (!tmp.empty()) services[idx].direction = tmp;
    cout << "Нова вартість (" << services[idx].price << "): ";
    cin >> services[idx].price;
    cout << "Оновлено!\n";
}

void searchServiceByName() {
    cin.ignore();
    cout << "Назва послуги: ";
    string key; getline(cin, key);
    bool found = false;
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].name == key) {
            printService(services[i], i);
            found = true;
        }
    }
    if (!found) cout << "Не знайдено.\n";
}

// Компаратори для сортування (const посилання)
bool cmpServicePriceAsc(const Service& a, const Service& b) { return a.price > b.price; }
bool cmpServicePriceDesc(const Service& a, const Service& b) { return a.price < b.price; }
bool cmpServiceNameAsc(const Service& a, const Service& b) { return a.name > b.name; }
bool cmpServiceNameDesc(const Service& a, const Service& b) { return a.name < b.name; }

void sortServicesByPrice() {
    if (serviceCount < 2) return;
    mySort(services, serviceCount, cmpServicePriceAsc);
    cout << "Послуги відсортовано за ціною (зростання).\n";
    printAllServices();
}

void sortServicesByName() {
    if (serviceCount < 2) return;
    mySort(services, serviceCount, cmpServiceNameAsc);
    cout << "Послуги відсортовано за назвою (А-Я).\n";
    printAllServices();
}

// ========== ВІЗИТИ ==========
void printVisit(const Visit& v, int index) {
    cout << index + 1 << ". Клієнт: " << v.clientSurname << " " << v.clientName << " " << v.clientPatronymic
        << " | Майстер: " << v.masterSurname << " " << v.masterName << " " << v.masterPatronymic
        << " | Послуга: " << v.serviceName << " | Дата: " << v.date
        << " | Сума: " << v.paidAmount << " грн" << endl;
}

void printAllVisits() {
    if (visitCount == 0) {
        cout << "Візитів немає.\n";
        return;
    }
    cout << "\n===== ВІЗИТИ =====\n";
    for (int i = 0; i < visitCount; i++)
        printVisit(visits[i], i);
}

void registerVisit() {
    if (serviceCount == 0) {
        cout << "Спочатку додайте хоча б одну послугу!\n";
        return;
    }
    Visit v;
    cin.ignore();

    // Клієнт одним рядком
    cout << "ПІБ клієнта (Прізвище Ім'я По-батькові): ";
    string fullClient; getline(cin, fullClient);
    splitFullName(fullClient, v.clientSurname, v.clientName, v.clientPatronymic);

    // Майстер одним рядком
    cout << "ПІБ майстра (Прізвище Ім'я По-батькові): ";
    string fullMaster; getline(cin, fullMaster);
    splitFullName(fullMaster, v.masterSurname, v.masterName, v.masterPatronymic);

    // Вибір послуги зі списку
    cout << "\nДоступні послуги:\n";
    for (int i = 0; i < serviceCount; ++i)
        cout << "  " << i + 1 << ". " << services[i].name << " (" << services[i].price << " грн)\n";
    int servChoice;
    cout << "Виберіть номер послуги: ";
    cin >> servChoice;
    while (servChoice < 1 || servChoice > serviceCount) {
        cout << "Невірний номер, спробуйте ще: ";
        cin >> servChoice;
    }
    v.serviceName = services[servChoice - 1].name;
    double defaultPrice = services[servChoice - 1].price;

    // Дата (Enter = сьогодні)
    cin.ignore();
    cout << "Дата (ДД.ММ.РРРР) [Enter - сьогодні]: ";
    string dateInput; getline(cin, dateInput);
    v.date = dateInput.empty() ? getCurrentDate() : dateInput;

    // Сума (Enter = ціна послуги)
    cout << "Сума (" << defaultPrice << " грн) [Enter - залишити]: ";
    string amountInput; getline(cin, amountInput);
    v.paidAmount = amountInput.empty() ? defaultPrice : stod(amountInput);

    addItemBack(visits, visitCount, v);
    cout << "Візит зареєстровано!\n";
}

void editVisit() {
    printAllVisits();
    if (visitCount == 0) return;
    cout << "Номер візиту для редагування: ";
    int idx; cin >> idx; idx--;
    if (idx < 0 || idx >= visitCount) {
        cout << "Невірний номер.\n";
        return;
    }
    Visit& v = visits[idx];
    cin.ignore();
    string input;

    cout << "ПІБ клієнта (зараз: " << v.clientSurname << " " << v.clientName << " " << v.clientPatronymic << ")\n";
    cout << "Нове ПІБ (Enter – залишити): ";
    getline(cin, input);
    if (!input.empty()) splitFullName(input, v.clientSurname, v.clientName, v.clientPatronymic);

    cout << "ПІБ майстра (зараз: " << v.masterSurname << " " << v.masterName << " " << v.masterPatronymic << ")\n";
    cout << "Нове ПІБ (Enter – залишити): ";
    getline(cin, input);
    if (!input.empty()) splitFullName(input, v.masterSurname, v.masterName, v.masterPatronymic);

    if (serviceCount > 0) {
        cout << "\nДоступні послуги:\n";
        for (int i = 0; i < serviceCount; ++i)
            cout << "  " << i + 1 << ". " << services[i].name << " (" << services[i].price << " грн)\n";
        cout << "Нова послуга (номер, Enter – залишити \"" << v.serviceName << "\"): ";
        getline(cin, input);
        if (!input.empty()) {
            int servChoice = stoi(input);
            if (servChoice >= 1 && servChoice <= serviceCount)
                v.serviceName = services[servChoice - 1].name;
        }
    }

    cout << "Нова дата (зараз: " << v.date << ", Enter – залишити): ";
    getline(cin, input);
    if (!input.empty()) v.date = input;

    cout << "Нова сума (зараз: " << v.paidAmount << ", Enter – залишити): ";
    getline(cin, input);
    if (!input.empty()) v.paidAmount = stod(input);

    cout << "Візит оновлено.\n";
}

void deleteVisit() {
    printAllVisits();
    if (visitCount == 0) return;
    cout << "Номер візиту для видалення: ";
    int idx; cin >> idx; idx--;
    if (idx < 0 || idx >= visitCount) return;
    removeItemAt(visits, visitCount, idx);
    cout << "Візит видалено.\n";
}

void searchVisitByClient() {
    cin.ignore();
    cout << "Прізвище клієнта: ";
    string key; getline(cin, key);
    bool found = false;
    for (int i = 0; i < visitCount; i++) {
        if (visits[i].clientSurname == key) {
            printVisit(visits[i], i);
            found = true;
        }
    }
    if (!found) cout << "Не знайдено.\n";
}

void searchVisitByMaster() {
    cin.ignore();
    cout << "Прізвище майстра: ";
    string key; getline(cin, key);
    bool found = false;
    for (int i = 0; i < visitCount; i++) {
        if (visits[i].masterSurname == key) {
            printVisit(visits[i], i);
            found = true;
        }
    }
    if (!found) cout << "Не знайдено.\n";
}

void searchVisitByDate() {
    cin.ignore();
    cout << "Дата (ДД.ММ.РРРР): ";
    string key; getline(cin, key);
    bool found = false;
    for (int i = 0; i < visitCount; i++) {
        if (visits[i].date == key) {
            printVisit(visits[i], i);
            found = true;
        }
    }
    if (!found) cout << "Не знайдено.\n";
}

void calculateTotalIncome() {
    double total = 0;
    for (int i = 0; i < visitCount; i++)
        total += visits[i].paidAmount;
    cout << "Загальний дохід: " << total << " грн\n";
}

// Компаратори для візитів
bool cmpVisitDate(const Visit& a, const Visit& b) { return a.date > b.date; }
bool cmpVisitAmount(const Visit& a, const Visit& b) { return a.paidAmount > b.paidAmount; }

void sortVisitsByDate() {
    if (visitCount < 2) return;
    mySort(visits, visitCount, cmpVisitDate);
    cout << "Візити відсортовано за датою (від найновіших).\n";
    printAllVisits();
}

void sortVisitsByAmount() {
    if (visitCount < 2) return;
    mySort(visits, visitCount, cmpVisitAmount);
    cout << "Візити відсортовано за сумою (спадання).\n";
    printAllVisits();
}

// ========== ФАЙЛИ ==========
void saveToFile() {
    ofstream file("salon_data.txt");
    if (!file) { cout << "Помилка запису!\n"; return; }
    file << serviceCount << "\n";
    for (int i = 0; i < serviceCount; i++) {
        file << services[i].name << "\n"
            << services[i].direction << "\n"
            << services[i].price << "\n";
    }
    file << visitCount << "\n";
    for (int i = 0; i < visitCount; i++) {
        file << visits[i].clientSurname << "\n"
            << visits[i].clientName << "\n"
            << visits[i].clientPatronymic << "\n"
            << visits[i].masterSurname << "\n"
            << visits[i].masterName << "\n"
            << visits[i].masterPatronymic << "\n"
            << visits[i].serviceName << "\n"
            << visits[i].date << "\n"
            << visits[i].paidAmount << "\n";
    }
    file.close();
    cout << "Дані збережено в salon_data.txt\n";
}

void loadFromFile() {
    ifstream file("salon_data.txt");
    if (!file) {
        cout << "Файл не знайдено. Починаємо з порожніми даними.\n";
        return;
    }
    file >> serviceCount; file.ignore();
    delete[] services;
    services = new Service[serviceCount];
    for (int i = 0; i < serviceCount; i++) {
        getline(file, services[i].name);
        getline(file, services[i].direction);
        file >> services[i].price; file.ignore();
    }
    file >> visitCount; file.ignore();
    delete[] visits;
    visits = new Visit[visitCount];
    for (int i = 0; i < visitCount; i++) {
        getline(file, visits[i].clientSurname);
        getline(file, visits[i].clientName);
        getline(file, visits[i].clientPatronymic);
        getline(file, visits[i].masterSurname);
        getline(file, visits[i].masterName);
        getline(file, visits[i].masterPatronymic);
        getline(file, visits[i].serviceName);
        getline(file, visits[i].date);
        file >> visits[i].paidAmount; file.ignore();
    }
    file.close();
    cout << "Дані завантажено з файлу.\n";
}