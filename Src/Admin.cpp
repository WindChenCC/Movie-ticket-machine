// Admin.cpp
// // Created by cch on 2020/6/16.
#include "Admin.h"

#include <conio.h>
#include <io.h>
#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>

#include "Menu.h"
using namespace std;

string Admin::strDate(const FilmsInfo& film) {
    string str;
    str = to_string(film.year);
    str += "-";
    if (film.month < 10) str += "0";
    str += to_string(film.month);
    str += "-";
    if (film.day < 10) str += "0";
    str += to_string(film.day);
    return str;
}

void Admin::menuChoice() {
    char ch;
    int choice;
    Menu menu;
    while (true) {
        menu.adminMenu();
        cin >> ch;
        cin.ignore();
        choice = ch - 48;
        switch (choice) {
            case 0: {
                return;
            }
            case 1: {
                showFInfo();
                cout << "-----------���������-----------\n";
                getch();
                break;
            }
            case 2: {
                add();
                break;
            }
            case 3: {
                change();
                break;
            }
            case 4: {
                del();
                break;
            }
            case 5: {
                count();
                break;
            }
        }
    }
}

void Admin::add() {
    int playNum[8][2]{{0, 0},  {8, 30},  {11, 0}, {13, 30},
                      {16, 0}, {18, 30}, {21, 0}, {23, 30}};
    string menu = {
        "            ---------\n"
        "            | �� �� |\n"
        "            ---------\n"
        "--------------------------------\n"};
    string str;
    int choice;
    char ch;
    while (true) {
        system("cls");
        cout << menu;
        FilmsInfo temp;
        string sname;
        vector<FilmsInfo>::iterator it;
        cout << "�������Ӱ��(0�˳�)��";
        getline(cin, sname);
        if (sname == "0") {
            cout << "--�˳����--\n";
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
        strcpy(temp.name, sname.c_str());
        cout << "����������(2020 1 1)��";
        cin >> temp.year >> temp.month >> temp.day;
        cout << "1. 8:30-10:30   2. 11:00-13:00\n"
                "3. 13:30-15:30  4. 16:00-18:00\n"
                "5. 18:30-20:30  6. 21:00-23:00\n"
                "7. 23:30-1:30\n";
        cout << "��ѡ�񳡴Σ�";
        cin >> choice;
        temp.playNum = choice;
        for (it = deal.finfo.begin(); it < deal.finfo.end(); it++) {
            if (temp.year == it->year && temp.month == it->month &&
                temp.day == it->day && temp.playNum == it->playNum) {
                break;
            }
        }
        if (it != deal.finfo.end()) {
            cout << "�����ڵĵ�" << choice << "��������������Ӱ\n";
            cout << "���������\n";
            cout << "-----------���������-----------" << endl;
            getch();
            cin.ignore();
            continue;
        }
        temp.hour = playNum[choice][0];
        temp.minute = playNum[choice][1];
        cout << "������Ʊ�ۣ�";
        cin >> temp.price;
        cout << "������VIP�ۿ�(7.5)��";
        cin >> temp.discount;
        cout << "ȷ�����?(y/n)��";
        if (deal.yesOrNo()) {
            deal.finfo.push_back(temp);
            cout << "����ɹ����Ƿ�������?(y/n)��";
        } else {
            cout << "ȡ�����棬�Ƿ�������?(y/n)��";
        }
        if (deal.yesOrNo()) {
            continue;
        } else {
            deal.filmSave();
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
    }
}

void Admin::showFInfo() {
    system("cls");
    deal.showFInfo();
}

void Admin::change() {
    int playNum[8][2]{{0, 0},  {8, 30},  {11, 0}, {13, 30},
                      {16, 0}, {18, 30}, {21, 0}, {23, 30}};
    int choice;
    int n;
    int m = static_cast<int>(deal.finfo.size());
    while (true) {
        system("cls");
        showFInfo();
        cout << "\n--------------------------------\n";
        cout << "�������޸ĵı��(0�˳�)��";
        cin >> n;
        while (n > m) {
            cout << "��Ų����ڣ�����������";
            cout << "��������Ҫɾ���ĵ�Ӱ��ţ�0�˳�����";
            cin >> n;
        }
        if (n == 0) {
            cout << "--�˳��޸�--" << endl;
            cout << "-----------���������-----------\n";
            getch();
            return;
        }
        if (deal.finfo[--n].rest != 100) {
            cout << "�˵�Ӱ���۳���ӰƱ�����޸�\n";
            cout << "-----------���������-----------\n";
            getch();
            continue;
        }
        FilmsInfo temp = deal.finfo[n];
        cout << "1. ��Ӱ��  2. ����" << endl;
        cout << "3. ����    4. �۸�" << endl;
        cout << "5. �ۿ�" << endl;
        cout << "��ѡ���޸ĵ���Ϣ��";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "�������Ӱ����";
                cin.ignore();
                cin >> temp.name;
                break;
            case 2:
                cout << "����������(2020 1 1)��";
                cin >> temp.year >> temp.month >> temp.day;
                break;
            case 3:
                cout << "1. 08:30-10:30  2. 11:00-13:00\n"
                        "3. 13:30-15:30  4. 16:00-18:00\n"
                        "5. 18:30-20:30  6. 21:00-23:00\n"
                        "7. 23:30-01:30\n";
                cout << "��ѡ�񳡴Σ�";
                int choice2;
                cin >> choice2;
                cin.ignore();
                temp.playNum = choice2;
                temp.hour = playNum[choice2][0];
                temp.minute = playNum[choice2][1];
            case 4:
                cout << "������۸�";
                cin >> temp.price;
                break;
            case 5:
                cout << "������VIP�ۿ�(7.5)��";
                cin >> temp.discount;
                break;
            default:
                cout << "ѡ�����" << endl;
                continue;
        }
        cout << "ȷ���޸�?(y/n)��";
        if (deal.yesOrNo()) {
            deal.finfo[n] = temp;
            cout << "�޸ĳɹ�\n";
            cout << "--------------------------------\n";
        } else {
            cout << "--ȡ���޸�--" << endl;
        }
        cout << "�Ƿ�����޸�?(y/n)��";
        if (deal.yesOrNo()) {
            continue;
        } else {
            deal.filmSave();
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
    }
}

void Admin::del() {
    int n;
    int m = static_cast<int>(deal.finfo.size());
    vector<FilmsInfo>::iterator it;
    while (true) {
        system("cls");
        it = deal.finfo.begin();
        showFInfo();
        cout << "\n--------------------------------\n";
        cout << "��������Ҫɾ���ĵ�Ӱ���(0�˳�)��";
        cin >> n;
        while (n > m) {
            cout << "��Ų����ڣ�����������\n";
            cout << "��������Ҫɾ���ĵ�Ӱ��ţ�0�˳�����";
            cin >> n;
        }
        if (n == 0) {
            cout << "--�˳�ɾ��--" << endl;
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
        n--;
        if (((it + n)->rest != 100) && (it + n)->play == 0) {
            cout << "�õ�Ӱδ��ӳ�����۳�Ʊ������ɾ��\n";
            cout << "����ϵ�û�������Ʊ��������ɾ��\n";
            Sleep(500);
            cout << "�Ƿ����ɾ��������Ӱ(y/n)?��";
            if (deal.yesOrNo()) {
                continue;
            } else {
                cout << "--�˳�ɾ��--" << endl;
                cout << "-----------���������-----------" << endl;
                getch();
                return;
            }
        }
        cout << "ȷ��ɾ��?(y/n):";
        if (deal.yesOrNo()) {
            deal.finfo.erase(it + n);
            deal.filmSave();
            cout << "ɾ���ɹ����Ƿ����?(y/n):";
        } else {
            cout << "ȡ��ɾ�����Ƿ����?(y/n):";
        }
        if (deal.yesOrNo()) {
            continue;
        } else {
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
    }
}

void Admin::count() {
    if (deal.finfo.size() == 0) {
        cout << "û�е�Ӱ��Ϣ���޷�ͳ��\n";
        cout << "-----------���������-----------" << endl;
        getch();
        return;
    }
    string menu = {
        "                                ----------\n"
        "                                | ͳ  �� |\n"
        "                                ----------\n"
        "-----------------------------------------"
        "---------------------------------\n"};
    map<int, string> mpnum{{1, "08:30-10:30"}, {2, "11:00-13:00"},
                           {3, "13:30-15:30"}, {4, "16:00-18:00"},
                           {5, "18:30-20:30"}, {6, "21:00-23:00"},
                           {7, "23:30-01:30"}};
    map<int, string> mdate;

    set<string> dateSet;
    set<string>::iterator sit;
    vector<FilmsInfo>::iterator fit, fit2;
    int i = 1;
    for (fit = deal.finfo.begin(); fit < deal.finfo.end(); fit++) {
        dateSet.insert(strDate(*fit));
    }
    for (sit = dateSet.begin(); sit != dateSet.end(); sit++) {
        mdate[i++] = *sit;
    }
    while (true) {
        system("cls");
        cout << menu;
        cout << "��ͳ�������У�\n";
        for (i = 1; i <= mdate.size(); i++) {
            cout << i << ". " << mdate[i] << endl;
        }
        int choice;
        while (true) {
            cout << "��ѡ������(0�˳�)��";
            cin >> choice;
            if (choice == 0) {
                cout << "--�˳�ͳ��--\n";
                cout << "-----------���������-----------" << endl;
                getch();
                return;
            }
            if (choice < 0 || choice > mdate.size()) {
                cout << "���ڲ�����\n";
                cout << "-----------���������-----------" << endl;
                getch();
                continue;
            }
            break;
        }
        cout << "-----------------------------------------"
                "---------------------------------\n";
        cout << mdate[choice] << "ͳ�ƽ�����£�\n\n";
        string str = mdate[choice];
        fit = deal.finfo.begin();
        for (fit; fit != deal.finfo.end(); fit++) {
            if (strDate(*fit) == str) {
                break;
            }
        }
        fit2 = fit;
        for (i = 1; i <= 7; i++) {
            cout << "��" << i << "���� " << mpnum[i] << " ";
            if ((fit != deal.finfo.end()) && (strDate(*fit) == str) &&
                (fit->playNum == i)) {
                cout << "��Ӱ��" << fit->name << "��\n";
                cout << "���ۣ�" << 100 - fit->rest;
                cout << "  ���۶" << fit->sumSales << "��\n\n";
                fit++;
            } else {
                cout << "�޵�Ӱ\n\n";
            }
        }
        cout << "--------------------------------\n";
        cout << "�Ƿ񵼳�(y/n)?��";
        if (deal.yesOrNo()) {
            string path;
            path = "statistics\\" + str + ".txt";
            ofstream oFile{path, ios::out | ios::trunc};
            SYSTEMTIME st;
            GetLocalTime(&st);
            oFile << str << "ͳ�ƽ�� ͳ��ʱ�䣺";
            oFile << st.wYear << "-" << st.wMonth << "-" << st.wDay << " ";
            oFile << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
            for (i = 1; i <= 7; i++) {
                oFile << "��" << i << "���� " << mpnum[i] << " ";
                if ((fit2 != deal.finfo.end()) && (strDate(*fit2) == str) &&
                    (fit2->playNum == i)) {
                    oFile << "��Ӱ��" << fit2->name << "��\n";
                    oFile << "���ۣ�" << 100 - fit2->rest;
                    oFile << " ���۶" << fit2->sumSales << "��\n\n";
                    fit2++;
                } else {
                    oFile << "�޵�Ӱ\n\n";
                }
            }
            oFile.close();
            cout << "�ѳɹ�������" << str << ".txt\n";
        }
        cout << "�Ƿ�ͳ����������(y/n)?��";
        if (deal.yesOrNo()) {
            continue;
        } else {
            cout << "--�˳�ͳ��--\n";
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
    }
}