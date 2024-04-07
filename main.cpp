#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

bool oyunBitti;
const int genislik = 40;
const int yukseklik = 20;
int x, y, meyveX, meyveY, puan; // Değişkenlerin koordinatları
enum eYon { DUR = 0, SOL, SAG, YUKARI, ASAGI };
eYon yon;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void Kurulum() {
    oyunBitti = false;
    yon = DUR;
    x = genislik / 2 - 1;
    y = yukseklik / 2 - 1;
    srand(time(0));
    meyveX = rand() % genislik;
    meyveY = rand() % yukseklik;
}

void Cizim() {
    system("cls"); //system("clear");
    for (int i = 0; i < genislik + 1; i++) // Üst taş
        cout << "#";
    cout << endl;

    for (int i = 0; i < yukseklik; i++) { // Yan taşlar
        for (int j = 0; j < genislik; j++) {
            if (j == 0 || j == genislik - 1) {
                SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
                cout << "#";
            }
            if (i == y && j == x) {
                SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY );
                cout << "O";
            }
            else if (i == meyveY && j == meyveX) {
                SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
                cout << "*";
            }
            else
                cout << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < genislik + 1; i++) // Alt taş
        cout << "#";
    cout << endl;
    cout << "Puan:" << puan << endl;
}

void Giris() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                yon = SOL;
                break;
            case 'd':
                yon = SAG;
                break;
            case 'w':
                yon = YUKARI;
                break;
            case 's':
                yon = ASAGI;
                break;
            case 'x':
                oyunBitti = true;
                break;
        }
    }
}

void Mantik() {
    switch (yon) {
        case SOL:
            x--;
            break;
        case SAG:
            x++;
            break;
        case YUKARI:
            y--;
            break;
        case ASAGI:
            y++;
            break;
    }
    if (x > genislik || x < 0 || y > yukseklik || y < 0)
        oyunBitti = true;
    if (x == meyveX && y == meyveY) {
        puan += 10;
        srand(time(0));
        meyveX = rand() % genislik;
        meyveY = rand() % yukseklik;
    }
}

int main() {
    system("COLOR F0");
    Kurulum();
    while (!oyunBitti) {
        Cizim();
        Giris();
        Mantik();
    }
    cout << "PUANINIZ " << puan << endl;
    system("pause");
    return 0;
}
