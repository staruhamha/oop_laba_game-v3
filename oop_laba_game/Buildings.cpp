#include "Buildings.h"

#include <iostream>

using namespace std;

Barracks::Barracks(int id, int x, int y)
	: Building(id, "Barracks", 200, x, y) {
}

void Barracks::update() {
	cout << "Казармы обновлены" << endl;
}

void Barracks::produce(const string& unitType) {
	cout << "Казармы произвели юнита: " << unitType << endl;
}

PowerPlant::PowerPlant(int id, int x, int y)
	: Building(id, "PowerPlant", 150, x, y) {
}

void PowerPlant::update() {
	cout << "Электростанция обновлена" << endl;
}

void PowerPlant::produce(const string& unitType) {
	cout << "Электростанция не может производить юнитов" << endl;
}

Laboratory::Laboratory(int id, int x, int y)
	: Building(id, "Laboratory", 250, x, y) {
}

void Laboratory::update() {
	cout << "Лаборатория обновлена" << endl;
}

void Laboratory::produce(const string& unitType) {
	cout << "Лаборатория не может производить юнитов" << endl;
}

Warehouse::Warehouse(int id, int x, int y)
	: Building(id, "Warehouse", 100, x, y) {
}

void Warehouse::update() {
	cout << "Склад обновлён" << endl;
}

void Warehouse::produce(const string& unitType) {
	cout << "Склад не может производить юнитов" << endl;
}

Hospital::Hospital(int id, int x, int y)
	: Building(id, "Hospital", 180, x, y) {
}

void Hospital::update() {
	cout << "Госпиталь обновлён" << endl;
}

void Hospital::produce(const string& unitType) {
	cout << "Госпиталь не может производить юнитов" << endl;
}
