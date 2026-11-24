#include "Units.h"
using namespace std;

Soldier::Soldier(int x, int y) : Assault(x, y, Health(200), Armor(50), Attack(20), UnitType::Assault) {}

string Soldier::getType() const {
	return "Soldier";
}

unique_ptr<Unit> Soldier::clone() const {
	return make_unique<Soldier>(*this);
}


Heavy::Heavy(int x, int y) : Assault(x, y, Health(300), Armor(100), Attack(25), UnitType::Assault) {}

string Heavy::getType() const {
	return "Heavy";
}

unique_ptr<Unit> Heavy::clone() const {
	return make_unique<Heavy>(*this);
}


Rifleman::Rifleman(int x, int y) : Assault(x, y, Health(180), Armor(40), Attack(25), UnitType::Assault) {}

string Rifleman::getType() const {
	return "Rifleman";
}

unique_ptr<Unit> Rifleman::clone() const {
	return make_unique<Rifleman>(*this);
}


Grenadier::Grenadier(int x, int y) : Assault(x, y, Health(160), Armor(30), Attack(40), UnitType::Assault) {}

string Grenadier::getType() const {
	return "Grenadier";
}

unique_ptr<Unit> Grenadier::clone() const {
	return make_unique<Grenadier>(*this);
}







Sniper::Sniper(int x, int y) : Marksman(x, y, Health(120), Armor(15), Attack(60), UnitType::Marksman) {}

string Sniper::getType() const {
	return "Sniper";
}

unique_ptr<Unit> Sniper::clone() const {
	return make_unique<Sniper>(*this);
}





Pyro::Pyro(int x, int y) : Specialist(x, y, Health(150), Armor(30), Attack(35), UnitType::Specialist) {}

string Pyro::getType() const {
	return "Pyro";
}

unique_ptr<Unit> Pyro::clone() const {
	return make_unique<Pyro>(*this);
}


Engineer::Engineer(int x, int y) : Specialist(x, y, Health(180), Armor(120), Attack(15), UnitType::Specialist) {}

string Engineer::getType() const {
	return "Engineer";
}

unique_ptr<Unit> Engineer::clone() const {
	return make_unique<Engineer>(*this);
}


Medic::Medic(int x, int y) : Specialist(x, y, Health(150), Armor(20), Attack(10), UnitType::Specialist) {}

string Medic::getType() const {
	return "Medic";
}

unique_ptr<Unit> Medic::clone() const {
	return make_unique<Medic>(*this);
}


FieldMedic::FieldMedic(int x, int y) : Specialist(x, y, Health(130), Armor(20), Attack(12), UnitType::Specialist) {}

string FieldMedic::getType() const {
	return "FieldMedic";
}

unique_ptr<Unit> FieldMedic::clone() const {
	return make_unique<FieldMedic>(*this);
}




JetpackTrooper::JetpackTrooper(int x, int y) : JetpackUnit(x, y, Health(170), Armor(35), Attack(30), UnitType::JetpackUnit) {}

string JetpackTrooper::getType() const {
	return "JetpackTrooper";
}

unique_ptr<Unit> JetpackTrooper::clone() const {
	return make_unique<JetpackTrooper>(*this);
}

Infantry::Infantry(int x, int y)
	: Assault(x, y, Health(200), Armor(40), Attack(20), UnitType::Assault) {
}

string Infantry::getType() const {
	return "Infantry";
}

unique_ptr<Unit> Infantry::clone() const {
	return make_unique<Infantry>(*this);
}


Scout::Scout(int x, int y)
	: Marksman(x, y, Health(120), Armor(15), Attack(35), UnitType::Marksman) {
}

string Scout::getType() const {
	return "Scout";
}

unique_ptr<Unit> Scout::clone() const {
	return make_unique<Scout>(*this);
}


Tank::Tank(int x, int y)
	: Assault(x, y, Health(350), Armor(120), Attack(30), UnitType::Assault) {
}

string Tank::getType() const {
	return "Tank";
}

unique_ptr<Unit> Tank::clone() const {
	return make_unique<Tank>(*this);
}


Worker::Worker(int x, int y)
	: Specialist(x, y, Health(130), Armor(20), Attack(10), UnitType::Specialist) {
}

string Worker::getType() const {
	return "Worker";
}

unique_ptr<Unit> Worker::clone() const {
	return make_unique<Worker>(*this);
}
