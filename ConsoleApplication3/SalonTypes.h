#ifndef SALON_TYPES_H
#define SALON_TYPES_H

#include <string>
using namespace std;

struct Service {
    string name;
    string direction;
    double price;
};

struct Visit {
    string clientSurname;
    string clientName;
    string clientPatronymic;
    string masterSurname;
    string masterName;
    string masterPatronymic;
    string serviceName;
    string date;
    double paidAmount;
};

extern Service* services;
extern int serviceCount;
extern Visit* visits;
extern int visitCount;

// Функції для послуг
void printService(const Service& s, int index);
void printAllServices();
void addService();
void deleteService();
void editService();
void searchServiceByName();
void sortServicesByPrice();
void sortServicesByName();

// Функції для візитів
void printVisit(const Visit& v, int index);
void printAllVisits();
void registerVisit();
void editVisit();
void deleteVisit();
void searchVisitByClient();
void searchVisitByMaster();
void searchVisitByDate();
void calculateTotalIncome();
void sortVisitsByDate();
void sortVisitsByAmount();

// Файлові операції
void saveToFile();
void loadFromFile();

#endif