
#include <iostream>
#include <vector>
#include <locale.h>
#include "Monom.h"
#include "Polinom.h"

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<Polinom> polinoms;

    while (true) {
        std::cout << "�������� ��������:" << std::endl;
        std::cout << "1. ������ �������" << std::endl;
        std::cout << "2. ��������� �������� ��� ����������" << std::endl;
        std::cout << "3. ������� ��� ��������" << std::endl;
        std::cout << "0. �����" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1: {
            Polinom p;
            std::cout << "������� �������:" << std::endl;
            std::cin >> p;
            polinoms.push_back(p);
            std::cout << "������� ��������." << std::endl;
            break;
        }
        case 2: {
            if (polinoms.size() < 2) {
                std::cout << "���������� ������ ��� ������� ��� ��������." << std::endl;
                break;
            }

            std::cout << "�������� ��������:" << std::endl;
            std::cout << "1. �������� ���������" << std::endl;
            std::cout << "2. ��������� ���������" << std::endl;
            std::cout << "3. ��������� �������� �� ���������" << std::endl;
            std::cout << "4. ��������� �������� �� �����" << std::endl;
            std::cout << "5. ��������� ���������" << std::endl;

            int operation;
            std::cin >> operation;

            std::cout << "������� ������ ��������� (������� � 0): ";
            int index1, index2;
            std::cin >> index1 >> index2;

            if (index1 < 0 || index1 >= polinoms.size() || index2 < 0 || index2 >= polinoms.size()) {
                std::cout << "������������ ������� ���������." << std::endl;
                break;
            }

            switch (operation) {
            case 1: {
                Polinom sum = polinoms[index1] + polinoms[index2];
                std::cout << "����� ���������: " << sum << std::endl;
                break;
            }
            case 2: {
                Polinom diff = polinoms[index1] - polinoms[index2];
                std::cout << "�������� ���������: " << diff << std::endl;
                break;
            }
            case 3: {
                double constant;
                std::cout << "������� ���������: ";
                std::cin >> constant;
                Polinom scaled = polinoms[index1] * constant;
                std::cout << "��������� ��������� �� ���������: " << scaled << std::endl;
                break;
            }
            case 4: {
                Monom mon;
                std::cout << "������� ����� ��� ���������: " << std::endl;
                std::cin >> mon;
                Polinom product = polinoms[index1] * mon;
                std::cout << "��������� ��������� �� �����: " << product << std::endl;
                break;
            }
           /* case 5: {
                Polinom product = polinoms[index1] * polinoms[index2];
                std::cout << "��������� ��������� ���������: " << product << std::endl;
                break;
            }*/
            default:
                std::cout << "������������ ����� ��������." << std::endl;
            }
            break;
        }
        case 3: {
            if (polinoms.empty()) {
                std::cout << "�������� �� �������." << std::endl;
            }
            else {
                for (size_t i = 0; i < polinoms.size(); ++i) {
                    std::cout << "������� " << i << ": " << polinoms[i] << std::endl;
                }
            }
            break;
        }
        default:
            std::cout << "������������ �����." << std::endl;
        }
    }

    return 0;
}