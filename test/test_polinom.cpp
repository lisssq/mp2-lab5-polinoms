#include "..\polinom\Polinom.h"
#include "..\polinom\Monom.h"
#include "..\polinom\List.h"
#include <string>
#include "gtest.h"






// два полинома по 3 монома, разные случаи 
// оператор сравнния так же
// оператор присваивания (как у очереди)
// 






// Проверка создания монома по умолчанию
TEST(Monom, can_create_monom_with_default_constructor)
{
    ASSERT_NO_THROW(Monom m);
}

// Проверка создания монома с параметрами
TEST(Monom, can_create_monom_with_parameters)
{
    ASSERT_NO_THROW(Monom m(3.5, 2, 1, 0));
}

// Проверка оператора сравнения "<"
TEST(Monom, can_compare_monom_with_less_operator) 
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m2 < m1);
}

// Проверка оператора сравнения ">"
TEST(Monom, can_compare_monom_with_greater_operator) 
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(5.0, 1, 2, 3);
    EXPECT_TRUE(m1 > m2);
}

// Проверка оператора "=="
TEST(Monom, can_compare_monom_with_equality_operator) 
{
    Monom m1(3.5, 2, 1, 0);
    Monom m2(3.5, 2, 1, 0);
    EXPECT_TRUE(m1 == m2);
}





///////////////////////////////////////////////////////////////






// Проверка создания полинома по умолчанию
TEST(Polinom, can_create_polinom_with_default_constructor) 
{
    ASSERT_NO_THROW(Polinom p);
}

// Проверка добавления монома в полином
TEST(Polinom, can_add_monom_to_polinom) 
{
    Polinom p;
    Monom m(2.5, 2, 1, 0);
    ASSERT_NO_THROW(p.addMonom(m));
}

// Проверка сложения одинаковых мономов
TEST(Polinom, can_sum_monom_with_same_degree)
{
    Polinom p;
    Monom m1(2.5, 2, 1, 0);
    Monom m2(1.5, 2, 1, 0);

    p.addMonom(m1);
    p.addMonom(m2);

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "4x^2y^1z^0"); // Ожидаем сумму коэффициентов
}





// --- ДОБАВЛЕНИЕ МОНОМОВ В РАЗНЫЕ ПОЗИЦИИ ---

// Добавление в начало
TEST(Polinom, can_add_monom_to_beginning)
{
    Polinom p;
    p.addMonom(Monom(1.0, 2, 1, 0)); // Первый моном
    p.addMonom(Monom(3.0, 3, 2, 1)); // Должен встать в начало

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3x^3y^2z^1 + 1x^2y^1z^0");
}



// Добавление в конец
TEST(Polinom, can_add_monom_to_end)
{
    Polinom p;
    p.addMonom(Monom(3.0, 3, 2, 1));
    p.addMonom(Monom(1.0, 1, 0, 0)); // Должен встать в конец

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "3x^3y^2z^1 + 1x^1y^0z^0");
}

// Добавление в середину
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



// --- УДАЛЕНИЕ МОНОМОВ ---

// Удаление монома с нулевым коэффициентом
TEST(Polinom, can_remove_monom_with_zero_coefficient)
{
    Polinom p;
    p.addMonom(Monom(2.5, 1, 2, 3));
    p.addMonom(Monom(-2.5, 1, 2, 3)); // Должен обнулить моном

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0"); // Ожидаем пустой полином
}








// --- ТЕСТЫ ОПЕРАТОРОВ --- 


// Сложение двух полиномов
TEST(Polinom, can_add_polinoms)
{
    Polinom p1, p2;
    p1.addMonom(Monom(2.0, 3, 1, 0));
    p2.addMonom(Monom(3.0, 2, 1, 0));

    Polinom result = p1 + p2;

    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "2x^3y^1z^0 + 3x^2y^1z^0");
}

// Вычитание двух полиномов
TEST(Polinom, can_subtract_polinoms)
{
    Polinom p1, p2;
    p1.addMonom(Monom(5.0, 2, 1, 0));
    p2.addMonom(Monom(3.0, 2, 1, 0));

    Polinom result = p1 - p2;

    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "2x^2y^1z^0");
}

// Умножение полинома на число
TEST(Polinom, can_multiply_polinom_by_constant)
{
    Polinom p;
    p.addMonom(Monom(2.0, 2, 1, 0));

    Polinom result = p * 3.0;

    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "6x^2y^1z^0");
}

// Умножение полинома на моном
TEST(Polinom, can_multiply_polinom_by_monom)
{
    Polinom p;
    p.addMonom(Monom(2.0, 2, 1, 0));

    Monom m(3.0, 1, 0, 2);
    Polinom result = p * m;

    std::stringstream ss;
    ss << result;
    EXPECT_EQ(ss.str(), "6x^3y^1z^2");
}