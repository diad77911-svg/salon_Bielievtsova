#include "SalonTypes.h"
#include <iostream>
using namespace std;

void servicesMenu() {
    int choice;
    do {
        cout << "\n===== ПОСЛУГИ =====\n";
        cout << "1. Переглянути всі\n";
        cout << "2. Додати\n";
        cout << "3. Видалити\n";
        cout << "4. Редагувати\n";
        cout << "5. Пошук за назвою\n";
        cout << "6. Сортувати за ціною\n";
        cout << "7. Сортувати за назвою\n";
        cout << "0. Назад\n-> ";
        cin >> choice;
        switch (choice) {
        case 1: printAllServices(); break;
        case 2: addService(); break;
        case 3: deleteService(); break;
        case 4: editService(); break;
        case 5: searchServiceByName(); break;
        case 6: sortServicesByPrice(); break;
        case 7: sortServicesByName(); break;
        case 0: break;
        default: cout << "Невірний вибір!\n";
        }
    } while (choice != 0);
}

void visitsMenu() {
    int choice;
    do {
        cout << "\n===== ВІЗИТИ =====\n";
        cout << "1. Переглянути всі\n";
        cout << "2. Зареєструвати\n";
        cout << "3. Редагувати\n";
        cout << "4. Видалити\n";
        cout << "5. Пошук за клієнтом\n";
        cout << "6. Пошук за майстром\n";
        cout << "7. Пошук за датою\n";
        cout << "8. Загальний дохід\n";
        cout << "9. Сортувати за датою\n";
        cout << "10. Сортувати за сумою\n";
        cout << "0. Назад\n-> ";
        cin >> choice;
        switch (choice) {
        case 1: printAllVisits(); break;
        case 2: registerVisit(); break;
        case 3: editVisit(); break;
        case 4: deleteVisit(); break;
        case 5: searchVisitByClient(); break;
        case 6: searchVisitByMaster(); break;
        case 7: searchVisitByDate(); break;
        case 8: calculateTotalIncome(); break;
        case 9: sortVisitsByDate(); break;
        case 10: sortVisitsByAmount(); break;
        case 0: break;
        default: cout << "Невірний вибір!\n";
        }
    } while (choice != 0);
}

int main() {
    loadFromFile();
    int choice;
    do {
        cout << "\n===== САЛОН КРАСИ =====\n";
        cout << "1. Робота з послугами\n";
        cout << "2. Робота з візитами\n";
        cout << "3. Зберегти дані\n";
        cout << "0. Вихід\n-> ";
        cin >> choice;
        switch (choice) {
        case 1: servicesMenu(); break;
        case 2: visitsMenu(); break;
        case 3: saveToFile(); break;
        case 0: saveToFile(); cout << "До побачення!\n"; break;
        default: cout << "Невірний вибір!\n";
        }
    } while (choice != 0);

    delete[] services;
    delete[] visits;
    return 0;
}