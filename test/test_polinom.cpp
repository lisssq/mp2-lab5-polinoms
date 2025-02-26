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

// Проверка удаления монома с нулевым коэффициентом
TEST(Polinom, can_remove_monom_with_zero_coefficient) 
{
    Polinom p;
    Monom m1(2.5, 1, 2, 3);
    Monom m2(-2.5, 1, 2, 3);

    p.addMonom(m1);
    p.addMonom(m2);

    std::stringstream ss;
    ss << p;
    EXPECT_EQ(ss.str(), "0"); // Ожидаем пустой полином
}