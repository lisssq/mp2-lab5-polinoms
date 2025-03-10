#include <iostream>
#include <vector>
#include <locale.h>
#include "Monom.h"
#include "Polinom.h"

int main() 
{
    setlocale(LC_ALL, "Russian");

    std::vector<Polinom> polinoms;              // ������ ������� ������� ����� ������� ����������� (������� ���� "�������")

    while (true)
    {
        std::cout << "������ ��������:" << std::endl;
        std::cout << "1. ������ �������" << std::endl;
        std::cout << "2. ��������� �������� ��� ����������" << std::endl;
        std::cout << "3. ������� ��� ��������" << std::endl;
        std::cout << "0. �����" << std::endl;

        int num;        // ����� ��������
        std::cin >> num;

        if (num == 0)
        {
            break;
        }

        switch (num)
        {
        case 1:                                             // ���� "������ �������"
        {
            Polinom p;
            std::cout << "������� �������:" << std::endl;
            std::cin >> p;                                  // ������ �������
            polinoms.push_back(p);
            std::cout << "������� ��������." << std::endl;
            break;
        }
        case 2:                                             // ���� "��������� �������� ��� ����������"
        {
            if (polinoms.empty())                           // ���� ������ ��������� ����
            {
                std::cout << "���������� ������ ���� �� ���� �������." << std::endl;
                break;
            }

            std::cout << "�������� ��������:" << std::endl;
            std::cout << "1. �������� ���������" << std::endl;
            std::cout << "2. ��������� ���������" << std::endl;
            std::cout << "3. ��������� �������� �� ���������" << std::endl;
            std::cout << "4. ��������� �������� �� �����" << std::endl;
            //std::cout << "5. ��������� ���������" << std::endl;

            int operation;
            std::cin >> operation;                          // ������ ����� ��������

            if (operation == 1 || operation == 2 || operation == 5)
            {
                if (polinoms.size() < 2)                    // ���� ��������� ��� �������� �� ����������
                {
                    std::cout << "��� ���� �������� ���������� ������� ��� ��������." << std::endl;
                    break;
                }
            }


            std::cout << "������� ����� ������� �������� (������� � 0): ";
            int index1, index2 = 0;                         // ������� ��������� � ������� ��������
            std::cin >> index1;                             // ������ ����� ������� �������� � ��������� ������������

            if (index1 < 0 || index1 >= polinoms.size())
            {
                std::cout << "������������ ������ ��������." << std::endl;
                break;
            }


            if (operation == 1 || operation == 2 || operation == 5)     // ���� �������� ���� ���, �� ������ ������ ����� ��������
            {
                std::cin >> index2;
                if (index2 < 0 || index2 >= polinoms.size())
                {
                    std::cout << "������������ ������ ��������." << std::endl;
                    break;
                }
            }

            switch (operation)
            {
            case 1:
            {
                Polinom sum = polinoms[index1] + polinoms[index2];
                std::cout << "����� ���������: " << sum << std::endl;

                polinoms.push_back(sum);        // ��������� ��������� � ������
                std::cout << "��������� �������� � ������ ���������." << std::endl;
                break;
            }
            case 2:
            {
                Polinom sub = polinoms[index1] - polinoms[index2];
                std::cout << "�������� ���������: " << sub << std::endl;

                polinoms.push_back(sub);       // ��������� ��������� � ������
                std::cout << "��������� �������� � ������ ���������." << std::endl;
                break;
            }
            case 3:
            {
                double constant;
                std::cout << "������� ���������: ";
                std::cin >> constant;
                Polinom mulByConst = polinoms[index1] * constant;
                std::cout << "��������� ��������� �� ���������: " << mulByConst << std::endl;

                polinoms.push_back(mulByConst);     // ��������� ��������� � ������    
                std::cout << "��������� �������� � ������ ���������." << std::endl;
                break;
            }
            case 4:
            {
                Monom mon;
                std::cout << "������� ����� ��� ���������: " << std::endl;
                std::cin >> mon;
                Polinom mulByMonom = polinoms[index1] * mon;
                std::cout << "��������� ��������� �� �����: " << mulByMonom << std::endl;

                polinoms.push_back(mulByMonom); // ��������� ��������� � ������
                std::cout << "��������� �������� � ������ ���������." << std::endl;
                break;
            }
            // case 5:
            //{
            //     Polinom mulByPolinom = polinoms[index1] * polinoms[index2];
            //     std::cout << "��������� ��������� ���������: " << mulByPolinom << std::endl;

            //     polinoms.push_back(mulByPolinom); // ��������� ��������� � ������
            //     std::cout << "��������� �������� � ������ ���������." << std::endl;
            //     break;
            // }
            }
            break;
        }
        case 3:
        {
            if (polinoms.empty())
            {
                std::cout << "�������� �� �������." << std::endl;
            }
            else
            {
                for (int i = 0; i < polinoms.size(); i++)
                {
                    std::cout << "������� " << i << ": " << polinoms[i] << std::endl;
                }
            }
            break;
        }

        }
    }

    return 0;
}


// ������� �������� -=