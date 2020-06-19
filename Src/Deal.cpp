// Deal.cpp
// Created by cch on 2020/6/16.
#include "Deal.h"

#include <conio.h>
#include <io.h>
#include <time.h>
#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

Deal::Deal() { filmRead(); }

Deal::~Deal() { filmSave(); }

ostream& operator<<(ostream& os, const FilmsInfo& film) {
    string str;
    os << setiosflags(ios::left);
    str = "《";
    str += film.name;
    str += "》";
    os << setw(17) << str;

    str = to_string(film.year) + "-";
    if (film.month < 10) str += "0";
    str += (to_string(film.month) + "-");
    if (film.day < 10) str += "0";
    str += to_string(film.day);
    os << setw(12) << str;

    str.clear();
    if (film.hour < 10) str = "0";
    str += (to_string(film.hour) + ":");
    if (film.minute < 10) str += "0";
    str += to_string(film.minute);
    os << setw(7) << str;

    os << setw(6) << film.playNum;
    os.precision(1);
    os.setf(os.showpoint | ios::fixed);
    os << setw(6) << film.price;
    os << setw(9) << film.discount;
    os << setw(6) << film.rest;
    if (film.play) {
        os << setw(8) << "已上映" << endl;
    } else {
        os << setw(8) << "未上映" << endl;
    }
    return os;
}

bool Deal::yesOrNo() {
    char ch;
    cin >> ch;
    cin.ignore();
    if (ch == 'y') {
        return true;
    } else {
        return false;
    }
}

bool Deal::fcmp(const FilmsInfo& a, const FilmsInfo& b) {
    if (a.year != b.year) {
        return (a.year < b.year);
    } else if (a.month != b.month) {
        return (a.month < b.month);
    } else if (a.day != b.day) {
        return (a.day < b.day);
    } else if (a.hour != b.hour) {
        return (a.hour < b.hour);
    } else {
        return (a.minute < b.minute);
    }
}

bool Deal::cmpTime(const FilmsInfo& film) {
    time_t tt;
    time(&tt);
    tt += 8 * 3600;
    tm* t = gmtime(&tt);
    if (film.year != (t->tm_year + 1900)) {
        return (film.year < (t->tm_year + 1900));
    } else if (film.month != (t->tm_mon + 1)) {
        return (film.month < (t->tm_mon + 1));
    } else if (film.day != t->tm_mday) {
        return (film.day < t->tm_mday);
    } else if (film.hour != t->tm_hour) {
        return (film.hour < t->tm_hour);
    } else {
        return (film.minute < t->tm_min);
    }
}

void Deal::wait() {
    Sleep(200);
    for (int i = 0; i < 3; i++) {
        cout << ".";
        Sleep(200);
    }
}

void Deal::showFInfo(int n) {
    string menu = {
        "                                ----------\n"
        "                                | 信  息 |\n"
        "                                ----------\n"
        "-----------------------------------------"
        "---------------------------------\n"};
    if (finfo.size() == 0) {
        cout << "-------------------------------\n";
        cout << "     没有电影信息，请先添加\n";
        return;
    }
    cout << menu;
    cout << setiosflags(ios::left);
    cout << setw(6) << "编号" << setw(16) << "电影名";
    cout << setw(12) << "日期" << setw(7) << "时间";
    cout << setw(6) << "场次";
    cout << setw(6) << "价格" << setw(9) << "VIP折扣";
    cout << setw(6) << "剩余" << setw(8) << "状态" << endl;
    for (int i = n; i < finfo.size(); i++) {
        cout << setw(5) << i - n + 1;
        cout << finfo[i];
    }
    cout << "-------------------------------------"
            "-------------------------------------\n";
}

void Deal::filmSave() {
    sort(finfo.begin(), finfo.end(), fcmp);
    ofstream oFile{"films\\films.dat", ios::binary | ios::trunc};
    if (!oFile) {
        cout << "save error!\n";
        return;
    }
    for (int i = 0; i < finfo.size(); i++) {
        if (cmpTime(finfo[i])) {
            finfo[i].play = true;
        } else {
            finfo[i].play = false;
        }
        oFile.write((char*)&finfo[i], sizeof(FilmsInfo));
    }
    oFile.close();
}

void Deal::filmRead() {
    FilmsInfo temp;
    ifstream iFile{"films\\films.dat", ios::binary | ios::in};
    if (!iFile) {
        cout << "read error!\n";
        return;
    }
    iFile.read((char*)&temp, sizeof(FilmsInfo));
    while (!iFile.eof()) {
        if (cmpTime(temp)) {
            temp.play = true;
        } else {
            temp.play = false;
        }
        finfo.push_back(temp);
        iFile.read((char*)&temp, sizeof(FilmsInfo));
    }
    iFile.close();
}