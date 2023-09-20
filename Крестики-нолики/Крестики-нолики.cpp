// Крестики-нолики.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const char X = 'X';
const char O = 'O';

int start() {
    cout << "Игра \"Крестики-нолики\".\n\n";
    cout << "Выберите режим игры: \n\n";
    cout << "1. Игрок против игрока\n";
    cout << "2. Игрок против компьютера\n\n";
    int choiceOpp;
    cin >> choiceOpp;
    while (choiceOpp != 1 && choiceOpp != 2) {
        cout << "\nВведите цифру 1 или 2!\n\n";
        cin >> choiceOpp;
    }
    return choiceOpp;
}

void startPvP() {
    cout << "\nИгроки ходят по очереди. Первыми начинают крестики\n";
    cout << "Для того, чтобы сделать ход, нужно указать клетку с помощью цифры от 1 до 9: \n\n";
    cout << " 1 | 2 | 3 \n";
    cout << " 4 | 5 | 6 \n";
    cout << " 7 | 8 | 9 \n\n";
    cout << "Для начала игры выберите клетку. Удачи!\n\n";
}

void startPvE() {
    cout << "\nИгрок и компьютер ходят по очереди. Первыми начинают крестики\n";
    cout << "Для того, чтобы сделать ход, нужно указать клетку с помощью цифры от 1 до 9: \n\n";
    cout << " 1 | 2 | 3 \n";
    cout << " 4 | 5 | 6 \n";
    cout << " 7 | 8 | 9 \n\n";
}

void display(vector<char>& field) {
    for (int i = 0; i < field.size(); i++) {
        cout << " " << field[i];
        if ((1 + i) % 3 != 0) {
            cout << " |";
        }
        else {
            cout << endl;
        }
    }
}

int checkUsed(vector<char>& field, int choice) {
    if (field[choice - 1] != ' ') {
        return 0;
    }
    return 1;
}

int checkEnter(vector<char>& field) {
    int choice;
    cin >> choice;
    
    while ((choice < 1 || choice > 9) || checkUsed(field, choice) != 1) {
        if (choice < 1 || choice > 9) {
            cout << "\nВводите числа только от 1 до 9!\n\n";
        }
        else if (checkUsed(field, choice) != 1) {
            cout << "\nДанная клетка уже занята!\n\n";
        }
        cin >> choice;
    }
    return choice;
}

void Xcharge(vector<char>&field) {
    int choice = checkEnter(field);
    field[choice - 1] = X;
    display(field);
}

void Ocharge(vector<char>& field) {
    int choice = checkEnter(field);
    field[choice - 1] = O;
    display(field);
}

char checkWinner(vector<char>& field, int charge) {
    vector<char>::iterator iter;
    iter = find(field.begin(), field.end(), ' ');
    if (
        (field[0] == field[1] && field[1] == field[2] && field[0] != ' ') ||
        (field[3] == field[4] && field[4] == field[5] && field[3] != ' ') ||
        (field[6] == field[7] && field[7] == field[8] && field[6] != ' ') ||
        (field[0] == field[3] && field[3] == field[6] && field[0] != ' ') ||
        (field[1] == field[4] && field[4] == field[7] && field[1] != ' ') ||
        (field[2] == field[5] && field[5] == field[8] && field[2] != ' ') ||
        (field[0] == field[4] && field[4] == field[8] && field[0] != ' ') ||
        (field[2] == field[4] && field[4] == field[6] && field[2] != ' ')
        ) 
    {
        if (charge == 0)
            return X;
        else 
            return O;
    }
    else if (iter == field.end()) {
        return '1';
    }
    return '0';
}

void announceWinner(char winner) {
    if (winner == X)
        cout << "\nПобедил игрок, играющий за X" << endl << endl;
    else if (winner == O)
        cout << "\nПобедил игрок, играющий за O" << endl << endl;
    else
        cout << "\nНичья!" << endl << endl;
}

void PvP(int charge, char winner, vector<char>& field) {
    vector<char>::iterator iter;
    iter = find(field.begin(), field.end(), ' ');

    while (iter != field.end())
    {
        if (charge == 0) {
            Xcharge(field);
            winner = checkWinner(field, charge);
            if (winner != '0') {
                announceWinner(winner);
                break;
            }
            charge++;
        }
        if (charge == 1) {
            Ocharge(field);
            winner = checkWinner(field, charge);
            if (winner != '0') {
                announceWinner(winner);
                break;
            }
            charge--;
        }
    }
}

int computerExtraCharge(vector<char> field, char computerSymbol, char playerSymbol) {
    int choice = 0;
    for (int i = 0; i < field.size(); i++) { // если компьютер может победить следующим ходом, он ставит символ так, чтобы победить
        if (checkUsed(field, i + 1) == 1) {
            field[i] = computerSymbol;
            if (checkWinner(field, 1) != '0' || checkWinner(field, 0) != '0') {
                choice = i + 1;
                field[i] = ' ';
                return choice;
            }
            else
                field[i] = ' ';
        }
    }
    // если компьютер не может победить следующим ходом, то проверяется, может ли он проиграть следующим ходом
    for (int i = 0; i < field.size(); i++) { // если компьютер может победить следующим ходом, он ставит символ так, чтобы победить
        if (checkUsed(field, i + 1) == 1) {
            field[i] = playerSymbol;
            if (checkWinner(field, 1) != '0' || checkWinner(field, 0) != '0') {
                choice = i + 1;
                field[i] = ' ';
                return choice;
            }
            else
                field[i] = ' ';
        }
    }
    return choice;
}

void computerCharge(vector<char>& field, char computerSymbol, char playerSymbol) {
    int choice = computerExtraCharge(field, computerSymbol, playerSymbol); // первым делом проверяется, может ли победить компьютер следующим ходом или проиграть
    if (choice != 0) {
        field[choice - 1] = computerSymbol;
        cout << "\nКомпьютер ходит на клетку " << choice << endl << endl;
        display(field);
    }
    else { // если ни одно из условий не выполняется, то компьютер ходит на свободную клетку в определенном порядке
        choice = 5;
        if (checkUsed(field, choice) == 0) {
            choice = 1;
            if (checkUsed(field, choice) == 0) {
                choice = 3;
            }
            if (checkUsed(field, choice) == 0) {
                choice = 7;
            }
            if (checkUsed(field, choice) == 0) {
                choice = 9;
            }
            if (checkUsed(field, choice) == 0) {
                choice = 2;
            }
            if (checkUsed(field, choice) == 0) {
                choice = 4;
            }
            if (checkUsed(field, choice) == 0) {
                choice = 6;
            }
            if (checkUsed(field, choice) == 0) {
                choice = 8;
            }
        }
        if (checkUsed(field, choice) == 1) {
            field[choice - 1] = computerSymbol;
        }
    cout << "\nКомпьютер ходит на клетку " << choice << endl << endl;
    display(field);
    }
}

void playerCharge(vector<char>& field, char playerSymbol) {
    int choice = checkEnter(field);
    field[choice - 1] = playerSymbol;
    display(field);
}

void PvE(int charge, char winner, vector<char>& field) {
    vector<char>::iterator iter;
    iter = find(field.begin(), field.end(), ' ');

    char playerSymbol;
    cout << "\nВыберите символ (X или O): \n";
    cin >> playerSymbol;
    while (playerSymbol != X && playerSymbol != O)
    {
        cout << "\nВводите только X или O\n";
        cin >> playerSymbol;
    }

    char computerSymbol;
    if (playerSymbol == X) {
        computerSymbol = O;
    }
    else
        computerSymbol = X;

    if (playerSymbol == X) {
        charge = 0;
        cout << "\nДля начала игры выберите клетку. Удачи!\n\n";
    }
    else
        charge = 1;

    while (iter != field.end())
    {
        if (charge == 0) {
            playerCharge(field, playerSymbol);
            winner = checkWinner(field, charge);
            if (winner != '0') {
                announceWinner(winner);
                break;
            }
            charge++;
        }
        if (charge == 1) {
            computerCharge(field, computerSymbol, playerSymbol);
            if (computerSymbol == X) {
                winner = checkWinner(field, 0);
            } else
                winner = checkWinner(field, charge);
            if (winner != '0') {
                announceWinner(winner);
                break;
            }
            charge--;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<char> field = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    
    int charge = 0;
    char winner = '0';

    int choiceOpp = start();
    if (choiceOpp == 1) {
        startPvP();
        PvP(charge, winner, field);
    }
    else {
        startPvE();
        PvE(charge, winner, field);
    }
  
    cout << "Спасибо за игру!\n";
    
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
