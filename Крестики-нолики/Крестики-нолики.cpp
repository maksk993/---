#include <iostream>
#include <vector>
#include <algorithm>

const char X = 'X';
const char O = 'O';

enum class Winner { No_winner, X, O, Draw };

void startPvP() {
    std::cout << "\nИгроки ходят по очереди. Первыми начинают крестики\n";
    std::cout << "Для того, чтобы сделать ход, нужно указать клетку с помощью цифры от 1 до 9: \n\n";
    std::cout << " 1 | 2 | 3 \n";
    std::cout << " 4 | 5 | 6 \n";
    std::cout << " 7 | 8 | 9 \n\n";
    std::cout << "Для начала игры выберите клетку. Удачи!\n\n";
}

void startPvE() {
    std::cout << "\nИгрок и компьютер ходят по очереди. Первыми начинают крестики\n";
    std::cout << "Для того, чтобы сделать ход, нужно указать клетку с помощью цифры от 1 до 9: \n\n";
    std::cout << " 1 | 2 | 3 \n";
    std::cout << " 4 | 5 | 6 \n";
    std::cout << " 7 | 8 | 9 \n\n";
}

void display(std::vector<char>& field) {
    for (int i = 0; i < field.size(); i++) {
        std::cout << " " << field[i];
        if ((1 + i) % 3 != 0) {
            std::cout << " |";
        }
        else {
            std::cout << std::endl;
        }
    }
}

bool checkFree(std::vector<char>& field, int choice) { return field[choice - 1] == ' '; }

int checkEnter(std::vector<char>& field) {
    int choice;
    std::cin >> choice;

    while ((choice < 1 || choice > 9) || checkFree(field, choice) != true) {
        if (choice < 1 || choice > 9) {
            std::cout << "\nВводите числа только от 1 до 9!\n\n";
        }
        else if (checkFree(field, choice) == false) {
            std::cout << "\nДанная клетка уже занята!\n\n";
        }
        std::cin >> choice;
    }

    return choice;
}

void Xcharge(std::vector<char>&field) {
    int choice = checkEnter(field);
    field[choice - 1] = X;
    display(field);
}

void Ocharge(std::vector<char>& field) {
    int choice = checkEnter(field);
    field[choice - 1] = O;
    display(field);
}

Winner checkWinner(std::vector<char>& field, char symbol) {
    if (
        (field[0] == field[1] && field[1] == field[2] && field[0] != ' ') ||
        (field[3] == field[4] && field[4] == field[5] && field[3] != ' ') ||
        (field[6] == field[7] && field[7] == field[8] && field[6] != ' ') ||
        (field[0] == field[3] && field[3] == field[6] && field[0] != ' ') ||
        (field[1] == field[4] && field[4] == field[7] && field[1] != ' ') ||
        (field[2] == field[5] && field[5] == field[8] && field[2] != ' ') ||
        (field[0] == field[4] && field[4] == field[8] && field[0] != ' ') ||
        (field[2] == field[4] && field[4] == field[6] && field[2] != ' ')
        ) {
        if (symbol == X)
            return Winner::X;
        else 
            return Winner::O;
    }
    else if (find(field.begin(), field.end(), ' ') == field.end()) {
        return Winner::Draw;
    }

    return Winner::No_winner;
}

void announceWinner(Winner winner) {
    if (winner == Winner::X)
        std::cout << "\nПобедил игрок, играющий за X" << std::endl << std::endl;
    else if (winner == Winner::O) std::cout << "\nПобедил игрок, играющий за O" << std::endl << std::endl;
    else std::cout << "\nНичья!" << std::endl << std::endl;

    std::cout << "Спасибо за игру!\n";
}

void PvP(int charge, Winner winner, std::vector<char>& field) {
    while (true) {
        if (charge == 0) {
            Xcharge(field);
            winner = checkWinner(field, X);
            if (winner != Winner::No_winner) {
                announceWinner(winner);
                break;
            }
            charge++;
        }
        if (charge == 1) {
            Ocharge(field);
            winner = checkWinner(field, O);
            if (winner != Winner::No_winner) {
                announceWinner(winner);
                break;
            }
            charge--;
        }
    }
}

int computerExtraCharge(std::vector<char> field, char computerSymbol, char playerSymbol) {
    for (int i = 0; i < field.size(); i++) { // если компьютер может победить следующим ходом, он ставит символ так, чтобы победить
        if (checkFree(field, i + 1) == true) {
            field[i] = computerSymbol;
            if (checkWinner(field, computerSymbol) != Winner::No_winner) {
                return ++i;
            }
            else field[i] = ' ';
        }
    }
    // если компьютер не может победить следующим ходом, то проверяется, может ли он проиграть следующим ходом
    for (int i = 0; i < field.size(); i++) {
        if (checkFree(field, i + 1) == true) {
            field[i] = playerSymbol;
            if (checkWinner(field, playerSymbol) != Winner::No_winner) return ++i;
            else field[i] = ' ';
        }
    }
    return 0;
}

void computerCharge(std::vector<char>& field, char computerSymbol, char playerSymbol) {
    int choice = computerExtraCharge(field, computerSymbol, playerSymbol); // первым делом проверяется, может ли победить компьютер следующим ходом или проиграть
    
    if (choice != 0) field[choice - 1] = computerSymbol;
    else { // если ни одно из условий не выполняется, то компьютер ходит на свободную клетку в определенном порядке
        std::vector<int> order{ 5,1,3,7,9,2,4,6,8 };

        for (auto& i : order) {
            if (checkFree(field, i) == true) {
                choice = i;
                field[choice - 1] = computerSymbol;
                break;
            }
        }
    }

    std::cout << "\nКомпьютер ходит на клетку " << choice << "\n\n";
    display(field);
}

void playerCharge(std::vector<char>& field, char playerSymbol) {
    int choice = checkEnter(field);
    field[choice - 1] = playerSymbol;
    display(field);
}

void PvE(int charge, Winner winner, std::vector<char>& field) {
    char playerSymbol;
    std::cout << "\nВыберите символ (X или O): \n";
    std::cin >> playerSymbol;

    while (playerSymbol != X && playerSymbol != O) {
        std::cout << "\nВводите только X или O\n";
        std::cin >> playerSymbol;
    }

    char computerSymbol;
    if (playerSymbol == X) computerSymbol = O;
    else computerSymbol = X;

    if (playerSymbol == X) std::cout << "\nДля начала игры выберите клетку. Удачи!\n\n";
    else charge = 1;

    while (true) {
        if (charge == 0) {
            playerCharge(field, playerSymbol);
            winner = checkWinner(field, playerSymbol);
            if (winner != Winner::No_winner) {
                announceWinner(winner);
                break;
            }
            charge++;
        }
        if (charge == 1) {
            computerCharge(field, computerSymbol, playerSymbol);
            winner = checkWinner(field, computerSymbol);
            if (winner != Winner::No_winner) {
                announceWinner(winner);
                break;
            }
            charge--;
        }
    }
}

void start() {
    std::vector<char> field(9, ' ');
    int charge = 0;
    Winner winner = Winner::No_winner;

    std::cout << "Игра \"Крестики-нолики\".\n\n";
    std::cout << "Выберите режим игры: \n\n";
    std::cout << "1. Игрок против игрока\n";
    std::cout << "2. Игрок против компьютера\n\n";

    int choiceOpp;
    std::cin >> choiceOpp;

    while (choiceOpp != 1 && choiceOpp != 2) {
        std::cout << "\nВведите цифру 1 или 2!\n\n";
        std::cin >> choiceOpp;
    }

    if (choiceOpp == 1) {
        startPvP();
        PvP(charge, winner, field);
    }
    else {
        startPvE();
        PvE(charge, winner, field);
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    start();
  
    return 0;
}