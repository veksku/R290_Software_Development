#pragma once

class Tacka {

public:
    Tacka();
    Tacka(double x, double y);
    ~Tacka();


    double get_x() const;
    double get_y() const;

private:
    double m_x; //pretpostavljam da treba definisati metod dohvatanja koordinata tacke  - dobro pretpostavljas
    double m_y;
};
