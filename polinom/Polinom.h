#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "Monom.h"
#include "List.h"

class Polinom : public List<Monom>
{
public:
	Polinom();                                      // конструктор по умолчанию
	Polinom(Monom* p, int size);                    // конструктор с массивом мономов

	void addMonom(Monom m);                        // добавление монома в полином

    Polinom operator+(Polinom& other);          // для сложения полиномов
    Polinom operator-(Polinom& other);          // для вычитания полиномов
    Polinom operator*(double constanta);       // умножение полинома на константу
    Polinom operator*(Monom& m);              // умножение полинома на моном

    friend std::ostream& operator<<(std::ostream& out, const Polinom& p);


};

// сделать чтоб сложение (или умножение??) полинома и тд было умным - не было двойного прохода, чтоб если нашли, продолжали поиск с места где остановились 









