#include "..\polinom\List.h"
#include "..\polinom\Monom.h"
#include "..\polinom\Polinom.h"
#include <string>
#include <iostream>
#include <string.h>
#include <string>
#include <cmath>
#include <vector>
#include "gtest.h"


// --- Тесты для класса Моном --- 

// тест 1: проверка создания монома по умолчанию
TEST(Monom, can_create_default_monom) 
{
    ASSERT_NO_THROW(Monom m);
}

// тест 2: проверка что моном созданный по умолчанию имеет нулевые значения
TEST(Monom, default_monom_has_zero_values)
{
    Monom m;
    EXPECT_EQ(0, m.coeff);
    EXPECT_EQ(0, m.x);
    EXPECT_EQ(0, m.y);
    EXPECT_EQ(0, m.z);
}

// тест 3: проверка что можно создать моном с параметрами
TEST(Monom, can_create_monom_with_parameters)
{
    ASSERT_NO_THROW(Monom m(2.5, 3, 1, 2));
}

// тест 4: проверка что моном созданный с параметрами имеет корректные значения каддого из них
TEST(Monom, monom_with_parameters_has_correct_values)
{
    Monom m(2.5, 3, 1, 2);
    EXPECT_DOUBLE_EQ(2.5, m.coeff);
    EXPECT_EQ(3, m.x);
    EXPECT_EQ(1, m.y);
    EXPECT_EQ(2, m.z);
}

// тест 5: проверка установки коэфф. монома
TEST(Monom, can_set_coeff) 
{
    Monom m;
    m.SetCoeff(3.5);
    EXPECT_DOUBLE_EQ(3.5, m.coeff);
}

// тест 6: проверка установки степеней монома
TEST(Monom, can_set_xyz) 
{
    Monom m;
    m.SetXYZ(1, 2, 3);
    EXPECT_EQ(1, m.x);
    EXPECT_EQ(2, m.y);
    EXPECT_EQ(3, m.z);
}

//тест 7: проверка оператора сравнения "<"
TEST(Monom, can_compare_monom_with_less_operator) 
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m2 < m1);
}

//тест 8: проверка оператора сравнения "8"
TEST(Monom, can_compare_monom_with_greater_operator)
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m1 > m2);
}

//тест 9: проверка оператора сравнения "=="
TEST(Monom, can_compare_monom_with_equality_operator)
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(3.5, 2, 1, 0);
    EXPECT_TRUE(m1 == m2);
}



///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


// --- Тесты для класса Polinom ---


// тест 1: проверка создания полинома по умолчанию
TEST(Polinom, can_create_default_polinom)
{
    ASSERT_NO_THROW(Polinom p);
}
// тест 2: проверка что созданный по умолчанию полином пустой
TEST(Polinom, default_polinom_is_empty) 
{
    Polinom p;
    EXPECT_TRUE(p.isEmpty());
}

// тест 3: проверка что в полином можно добавить моном и что он перестает быть пустым
TEST(Polinom, can_add_monom_to_polinom) 
{
    Polinom p;
    Monom m(1, 1, 1, 1);
    ASSERT_NO_THROW(p.addMonom(m));
    EXPECT_FALSE(p.isEmpty());
}

// тест 4: проверка добавления и упорядоченности мономов в полиноме
TEST(Polinom, can_add_monoms_and_they_are_ordered) 
{
    Polinom p;
    p.addMonom(Monom(1, 2, 1, 0));
    p.addMonom(Monom(2, 1, 2, 0));
    p.addMonom(Monom(3, 1, 1, 0));

    // проверяем, что мономы отсортированы правильно:
    p.reset();                          // установка указателя на первый моном
    EXPECT_EQ(2, p.getCurrent().x);     // проверка что степень первого монома = 2, что говорит о том что на первом месте стоит моном 1
    p.goNext();
    EXPECT_EQ(1, p.getCurrent().x);
    EXPECT_EQ(2, p.getCurrent().y);
    p.goNext();
    EXPECT_EQ(1, p.getCurrent().x);
    EXPECT_EQ(1, p.getCurrent().y);
}

//тест 5: проверка на добавление мономов с одинаковыми коэффф. и последующее их сложение
TEST(Polinom, can_add_same_monom_and_coefficients_are_summed)
{
    Polinom p;
    p.addMonom(Monom(1, 1, 1, 0));
    p.addMonom(Monom(2, 1, 1, 0));

    p.reset();
    EXPECT_DOUBLE_EQ(3, p.getCurrent().coeff);
}


// тест 6: проверка удаления монома с нулевым коэфф.
TEST(Polinom, can_add_same_monom_and_zero_coefficient_is_deleted)
{
    Polinom p;
    p.addMonom(Monom(1, 1, 1, 0));
    p.addMonom(Monom(-1, 1, 1, 0));

    EXPECT_TRUE(p.isEmpty());
}

// тест 7: проверка на корректное отображение полинома
TEST(Polinom, can_add_monoms_and_polinom_is_correctly_displayed)
{
    Polinom p;
    p.addMonom(Monom(1, 1, 1, 0));
    p.addMonom(Monom(2, 2, 0, 0));

    std::stringstream ss;
    ss << p;
    EXPECT_EQ("2x^2y^0z^0 + 1x^1y^1z^0", ss.str());
}

// тест 8: проверка на корректное отображение пустого полинома
TEST(Polinom, can_add_monoms_and_polinom_is_correctly_displayed_for_zero_polinom)
{
    Polinom p;
    std::stringstream ss;
    ss << p;
    EXPECT_EQ("0", ss.str());
}

// тест 9: проверка сложения двух полиномов через "+"
TEST(Polinom, can_add_polinoms)
{
    Polinom p1, p2;
    p1.addMonom(Monom(1, 1, 1, 0));
    p2.addMonom(Monom(2, 1, 1, 0));

    Polinom sum = p1 + p2;
    sum.reset();
    EXPECT_DOUBLE_EQ(3, sum.getCurrent().coeff);
}

// тест 10: проверка сложения двух полиномов через "+="
TEST(Polinom, can_add_assign_polinoms) 
{
    Polinom p1, p2;
    p1.addMonom(Monom(1, 1, 1, 0));
    p2.addMonom(Monom(2, 1, 1, 0));

    p1 += p2;
    p1.reset();
    EXPECT_DOUBLE_EQ(3, p1.getCurrent().coeff);
}

// тест 11: проверка вычитания двух полиномов
TEST(Polinom, can_subtract_polinoms)
{
    Polinom p1, p2;
    p1.addMonom(Monom(3, 1, 1, 0));
    p2.addMonom(Monom(2, 1, 1, 0));

    Polinom diff = p1 - p2;
    diff.reset();
    EXPECT_DOUBLE_EQ(1, diff.getCurrent().coeff);
}

// тест 12: проверка умножения полинома на число
TEST(Polinom, can_multiply_polinom_by_constant) 
{
    Polinom p;
    p.addMonom(Monom(2, 1, 1, 0));

    Polinom scaled = p * 3.0;
    scaled.reset();
    EXPECT_DOUBLE_EQ(6, scaled.getCurrent().coeff);
}

// тест 13: проверка умножения полинома на моном
TEST(Polinom, can_multiply_polinom_by_monom)
 {
    Polinom p;
    p.addMonom(Monom(2, 1, 1, 0));
    Monom m(3, 1, 0, 0);
    Polinom product = p * m;
    product.reset();
    EXPECT_DOUBLE_EQ(6, product.getCurrent().coeff);
    EXPECT_EQ(2, product.getCurrent().x);
    EXPECT_EQ(1, product.getCurrent().y);
}


// тест 14: проверка добавление пустого монома
TEST(Polinom, can_add_empty_polinom) 
{
    Polinom P;
    Polinom Q; // пустой
    P += Q;

    std::stringstream ss;
    ss << P;
    EXPECT_EQ(ss.str(), "0"); // Должно остаться пустым
}

// тест 15: проверка прибавление полинома без общих мономов
TEST(Polinom, can_add_polinom_without_common_monomials)
{
    Polinom P, Q;
    P.addMonom(Monom(2.0, 1, 0, 0)); // 2x
    P.addMonom(Monom(3.0, 0, 1, 0)); // 3y

    Q.addMonom(Monom(1.0, 0, 0, 2)); // z²
    Q.addMonom(Monom(5.0, 2, 0, 0)); // 5x²

    P += Q;

    std::stringstream ss;
    ss << P;
    EXPECT_EQ(ss.str(), "5x^2y^0z^0 + 2x^1y^0z^0 + 3x^0y^1z^0 + 1x^0y^0z^2"); // Правильный порядок
}

// тест 16: проверка прибавление полинома с общими мономами
TEST(Polinom, can_add_polinom_with_common_monomials)
{
    Polinom P, Q;
    P.addMonom(Monom(2.0, 1, 0, 0));  // 2x
    P.addMonom(Monom(3.0, 0, 1, 0));  // 3y

    Q.addMonom(Monom(-2.0, 1, 0, 0)); // -2x
    Q.addMonom(Monom(4.0, 0, 1, 0));  // 4y

    P += Q;

    std::stringstream ss;
    ss << P;

    EXPECT_EQ(ss.str(), "7x^0y^1z^0"); // x аннулируется, остается 7y
}

// тест 17: проверка добавления монома в начало полинома
TEST(Polinom, can_add_monom_to_beginning)
{
    Polinom p;
    p.addMonom(Monom(1.0, 2, 1, 0)); // Первый моном
    p.addMonom(Monom(3.0, 3, 2, 1)); 
    p.addMonom(Monom(5.0, 5, 6, 7)); // Должен встать в начало

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "5x^5y^6z^7 + 3x^3y^2z^1 + 1x^2y^1z^0");
}   

// тест 18: проверка добавления монома в конец полинома
TEST(Polinom, can_add_monom_to_end)
{
    Polinom p;
    p.addMonom(Monom(3.0, 3, 2, 1));
    p.addMonom(Monom(1.0, 1, 5, 0)); 
    p.addMonom(Monom(7.0, 0, 1, 5));// Должен встать в конец

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3x^3y^2z^1 + 1x^1y^5z^0 + 7x^0y^1z^5");
}

// тест 19: проверка добавления монома в середину полинома
TEST(Polinom, can_add_monom_to_middle)
{
    Polinom p;
    p.addMonom(Monom(3.0, 3, 2, 1)); // Больший
    p.addMonom(Monom(1.0, 1, 0, 0)); // Меньший
    p.addMonom(Monom(2.0, 2, 1, 0)); // Должен встать между

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3x^3y^2z^1 + 2x^2y^1z^0 + 1x^1y^0z^0");
}

// тест 20: проверка оператора присваивания полиномов
TEST(Polinom, assignment_operator_works_correctly)
{
    Polinom p1, p2;
    p1.addMonom(Monom(1.0, 1, 0, 0));
    p1.addMonom(Monom(2.0, 2, 0, 0));
    p1.addMonom(Monom(3.0, 3, 0, 0));

    p2 = p1;

    std::stringstream ss1, ss2;
    ss1 << p1;
    ss2 << p2;
    EXPECT_EQ(ss1.str(), ss2.str());
}

// тест 21: проверка оператора сравнения полиномов
TEST(Polinom, equality_operator_returns_true_for_equal_polinoms) {
    Polinom p1, p2, p3;
    p1.addMonom(Monom(1.0, 1, 0, 0));
    p1.addMonom(Monom(2.0, 2, 0, 0));
    p1.addMonom(Monom(3.0, 3, 0, 0));

    p2.addMonom(Monom(1.0, 1, 0, 0));
    p2.addMonom(Monom(2.0, 2, 0, 0));
    p2.addMonom(Monom(3.0, 3, 0, 0));

    p3.addMonom(Monom(3.0, 3, 0, 0));
    p3.addMonom(Monom(2.0, 2, 0, 0));

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// тест 22: проверка корректного отображения полинома с отрицательным мономом в середине
TEST(Polinom, display_negative_monom_in_middle) 
{
    Polinom p;
    p.addMonom(Monom(3, 3, 0, 0));
    p.addMonom(Monom(-2, 2, 0, 0));
    p.addMonom(Monom(1, 1, 1, 0));

    std::stringstream ss;
    ss << p;
    EXPECT_EQ("3x^3y^0z^0 - 2x^2y^0z^0 + 1x^1y^1z^0", ss.str());
}

// тест 23: проверка корректного отображения полинома с отрицательным мономом в начале
TEST(Polinom, display_negative_monom_at_beginning)
{
    Polinom p;
    p.addMonom(Monom(-2, 2, 0, 0));
    p.addMonom(Monom(1, 1, 1, 0));

    std::stringstream ss;
    ss << p;
    EXPECT_EQ("-2x^2y^0z^0 + 1x^1y^1z^0", ss.str());
}