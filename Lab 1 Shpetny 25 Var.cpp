#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // �� ����
    double diameter, depth, feedRate, maxForce, K_p, length, P_max, T, speedCoefficient, resistance, speed, cuttingMoment, power, angle;
    double P_main = 7.5, C_p = 68, q_p = 1, y_p = 0.7, O_b = 70, n_p = 0.75, C_v = 1.6, q_v = 0.4, m_v = 0.2, y_v = 0.5, C_m = 1, C_m2 = 0.0345, q_m = 2, y_m2 = 0.8, K_nv = 1, n_v = 0.9, pi = 3.1415;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "������ ��������: 2�132�" << endl << "" << endl << "" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    cout << "��������� ������� ��������� ������� �� �������� ���������: " << P_main << "���" << endl << "" << endl;
input_diameter:
    cout << "������ ������ ������� �����������, ��: ";
    cin >> diameter;
    if (diameter <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "ĳ����� ������� ���� ����� 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    cout << "������ ������� ��������� l, ��: ";
    cin >> length;
    if (length <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "������� ��������� ������� ���� ����� 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    cout << "������ ������ ������� s, ��/��: ";
    cin >> feedRate;
    if (feedRate <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "������ ������� ������� ���� ����� 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    cout << "������ ����������� �������� ������ �������� ���� ������, ��������� ��������� ������ ��������: ";
    cin >> maxForce;
    if (maxForce <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "����������� ���� ������ ������� ���� ����� 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    K_p = pow((O_b / 75), n_p);
    cout << "����������� ���������� ���� ������: " << K_p << endl << "" << endl;
    P_max = C_p * pow(diameter, q_p) * pow(feedRate, y_p) * K_p;
    cout << "�������� ������ �� ������� ��������� ����� ������ P0: " << P_max << endl << "" << endl;

    if (P_max > maxForce)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "�������� �������� S0!!!" << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << "�� �������� � ����!" << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    cout << "������ ������� ������� �� ���������� � �������: ";
    cin >> T;
    if (T <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "������� ������� ������� ���� ����� 0." << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_diameter;
    }
    resistance = length / diameter;
    speedCoefficient = 1 * pow((75 / O_b), n_v);
    speed = ((C_v * pow(diameter, q_v)) / (pow(T, m_v) * pow(feedRate, y_v))) * speedCoefficient;
    angle = (1000 * speed) / (pi / diameter);
    cout << "����������, �� ������� ������� ��������� Kmv: " << speedCoefficient << endl << "" << endl;
    cout << "����������, �� ������� ������� ��������� Klv: " << resistance << endl << "" << endl;
    cout << "����������, �� ������� ������� ��������� Knv: " << K_nv << endl << "" << endl;
    cout << "����������� ���������� �������� ��������� ���� ������ Kv: " << speed << endl << "" << endl;
    cout << "�������� ��������� ���� ������, �� ����������� ������� ������������� �������: " << angle << endl << "" << endl;
input_speed:
    cout << "������� ��������� ��������, ��^-1, �� ������� �������� �������� ��������� ���� ������: " << angle << endl << "" << endl;
    cout << "������ ������� ��������� �������� �� ��������� ���������������� ��������: ";
    cin >> angle;
    if (angle <= 0) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << "������� ��������� �������� ������� ���� ����� 0." << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_speed;
    }
    speed = (pi * diameter * angle) / 1000;
    cout << "ĳ���� �������� ��������� ���� ������: " << speed << endl << "" << endl;
    cuttingMoment = 9.81 * C_m2 * pow(diameter, q_m) * pow(feedRate, y_m2) * K_p;
    cout << "M����� �� ��� ����� ������ ��� �������: " << cuttingMoment << endl << "" << endl;
    power = (cuttingMoment * angle) / 975;
    cout << "���������, ��������������� ��� ������: ";
    if (power > P_main)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout << power << endl << "" << endl;
        cout << "�������� �������� ��������Ҳ!!!" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        goto input_speed;
    }
    else
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout << power << endl << "" ;
        cout << "�������� ��������� ����������� � ����!" << endl << "" << endl;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    return 0;
}