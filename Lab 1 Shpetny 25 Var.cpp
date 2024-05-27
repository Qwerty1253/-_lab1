#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Всі змінні
    double diameter, depth, feedRate, maxForce, K_p, length, P_max, T, speedCoefficient, resistance, speed, cuttingMoment, power, angle;
    double P_main = 7.5, C_p = 68, q_p = 1, y_p = 0.7, O_b = 70, n_p = 0.75, C_v = 1.6, q_v = 0.4, m_v = 0.2, y_v = 0.5, C_m = 1, C_m2 = 0.0345, q_m = 2, y_m2 = 0.8, K_nv = 1, n_v = 0.9, pi = 3.1415;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Модель верстата: 2С132Ц" << endl << "" << endl << "" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "Потужність двигуна головного двигуна за технічним паспортом: " << P_main << "кВт" << endl << "" << endl;
input_diameter:
    cout << "Введіть діаметр ріжучого інструменту, мм: ";
    cin >> diameter;
    if (diameter <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Діаметр повинен бути більше 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    cout << "Введіть глибину свердління l, мм: ";
    cin >> length;
    if (length <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Глибина свердління повинна бути більше 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    cout << "Введіть подачу обробки s, мм/об: ";
    cin >> feedRate;
    if (feedRate <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Подача обробки повинна бути більше 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    cout << "Введіть максимальне значення осьової складової сили різання, допустимої механізмом подачі верстата: ";
    cin >> maxForce;
    if (maxForce <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Максимальна сила різання повинна бути більше 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    K_p = pow((O_b / 75), n_p);
    cout << "Поправковий коефіцієнт сили різання: " << K_p << endl << "" << endl;
    P_max = C_p * pow(diameter, q_p) * pow(feedRate, y_p) * K_p;
    cout << "Прийнята подача за осьовою складовою силою різання P0: " << P_max << endl << "" << endl;

    if (P_max > maxForce)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "КРИТИЧНЕ ЗНАЧЕННЯ S0!!!" << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "Всі значення у нормі!" << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    cout << "Введіть стійкість свердла за значеннями з таблиці: ";
    cin >> T;
    if (T <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Стійкість свердла повинна бути більше 0." << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    resistance = length / diameter;
    speedCoefficient = 1 * pow((75 / O_b), n_v);
    speed = ((C_v * pow(diameter, q_v)) / (pow(T, m_v) * pow(feedRate, y_v))) * speedCoefficient;
    angle = (1000 * speed) / (pi / diameter);
    cout << "Коефіцієнт, що враховує глибину свердління Kmv: " << speedCoefficient << endl << "" << endl;
    cout << "Коефіцієнт, що враховує глибину свердління Klv: " << resistance << endl << "" << endl;
    cout << "Коефіцієнт, що враховує глибину свердління Knv: " << K_nv << endl << "" << endl;
    cout << "Поправковий коефіцієнт швидкості головного руху різання Kv: " << speed << endl << "" << endl;
    cout << "Швидкість головного руху різання, що допускається ріжучими властивостями свердла: " << angle << endl << "" << endl;
input_speed:
    cout << "Частота обертання шпинделя, хв^-1, що відповідає знайденій швидкості головного руху різання: " << angle << endl << "" << endl;
    cout << "Введіть частоту обертання шпинделя за технічними характеристиками верстата: ";
    cin >> angle;
    if (angle <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "Частота обертання шпинделя повинна бути більше 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_speed;
    }
    speed = (pi * diameter * angle) / 1000;
    cout << "Дійсна швидкість головного руху різання: " << speed << endl << "" << endl;
    cuttingMoment = 9.81 * C_m2 * pow(diameter, q_m) * pow(feedRate, y_m2) * K_p;
    cout << "Mомент від сил опору різання при обробці: " << cuttingMoment << endl << "" << endl;
    power = (cuttingMoment * angle) / 975;
    cout << "Потужність, використовувана для різання: ";
    if (power > P_main)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << power << endl << "" << endl;
        cout << "КРИТИЧНЕ ЗНАЧЕННЯ ПОТУЖНОСТІ!!!" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_speed;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << power << endl << "" ;
        cout << "Значення потужності знаходиться у нормі!" << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    return 0;
}