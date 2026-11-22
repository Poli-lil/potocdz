#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

class FileManager {
private:
    string fileName;

public:
    FileManager(string name) {
        fileName = name;
    }

    void saveGame(int number, int attempts) {
        ofstream file(fileName, ios::app);

        if (file.is_open()) {
            file << "Загаданное число: " << number
                << " | Попыток: " << attempts << '\n';

            file.close();
        }
        else {
            cout << "Ошибка открытия файла!" << '\n';
        }
    }

    void showStatistics() {
        ifstream file(fileName);
        string line;

        if (file.is_open()) {
            cout << "\n СТАТИСТИКА ИГР\n";

            if (file.peek() == EOF) {
                cout << "Статистика пока отсутствует.\n";
            }

            while (getline(file, line)) {
                cout << line << '\n';
            }

            file.close();
        }
        else {
            cout << "Пока нет сохраненных игр.\n";
        }
    }
};


class GuessNumber {
private:
    int secretNumber;
    int attempts;

public:
    GuessNumber() {
        secretNumber = 0;
        attempts = 0;
    }

    void startGame(FileManager& manager) {
        secretNumber = rand() % 500 + 1;
        attempts = 0;

        int guess;

        cout << "\nИГРА УГАДАЙ ЧИСЛО\n";
        cout << "Я загадал число от 1 до 500.\n";

        do {
            cout << "Введите число: ";

            if (!(cin >> guess)) {
                cout << "Введите целое число!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (guess < 1 || guess > 500) {
                cout << "Введите число от 1 до 500!\n";
                continue;
            }

            attempts++;

            if (guess < secretNumber) {
                cout << "Загаданное число БОЛЬШЕ!\n";
            }
            else if (guess > secretNumber) {
                cout << "Загаданное число МЕНЬШЕ!\n";
            }
            else {
                cout << "\nПоздравляю! Вы угадали!\n";
                cout << "Количество попыток: " << attempts << '\n';

                manager.saveGame(secretNumber, attempts);
            }

        } while (guess != secretNumber);
    }
};
int main() {
    setlocale(LC_ALL, "Russian");

    srand(time(0));

    FileManager manager("statistics.txt");
    GuessNumber game;

    int choice;

    do {
        cout << "\nГЛАВНОЕ МЕНЮ \n";
        cout << "1. Начать игру\n";
        cout << "2. Посмотреть статистику\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите корректный пункт меню!\n";
            continue;
        }
        switch (choice) {
        case 1:
            game.startGame(manager);
            break;

        case 2:
            manager.showStatistics();
            break;

        case 0:
            cout << "Выход из программы.\n";
            break;

        default:
            cout << "Неверный пункт меню!\n";
        }

    } while (choice != 0);
}