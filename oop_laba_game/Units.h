#pragma once
#include "UnitTypes.h"

class Soldier : public Assault {
public:
    Soldier(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Heavy : public Assault {
public:
    Heavy(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Rifleman : public Assault {
public:
    Rifleman(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Grenadier : public Assault {
public:
    Grenadier(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Sniper : public Marksman {
public:
    Sniper(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Pyro : public Specialist {
public:
    Pyro(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Engineer : public Specialist {
public:
    Engineer(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Medic : public Specialist {
public:
    Medic(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class FieldMedic : public Specialist {
public:
    FieldMedic(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class JetpackTrooper : public JetpackUnit {
public:
    JetpackTrooper(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Infantry : public Assault {
public:
    Infantry(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Scout : public Marksman {
public:
    Scout(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Tank : public Assault {
public:
    Tank(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};

class Worker : public Specialist {
public:
    Worker(int x, int y);

    std::string getType() const override;
    std::unique_ptr<Unit> clone() const override;
};