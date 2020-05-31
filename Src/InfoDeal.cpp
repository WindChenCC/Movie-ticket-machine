// InfoDeal.cpp
// Created by cch on 2020/5/31.
#include "InfoDeal.h"

#include <io.h>
#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

bool InfoDeal::cmp(const FilmsInfo& a, const FilmsInfo& b) {
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

InfoDeal::InfoDeal() {
    cout << "正在读取信息..." << endl;
    Sleep(1000);
    fileRead();
}

InfoDeal::~InfoDeal() {
    cout << "正在保存信息..." << endl;
    fileSave();
    Sleep(1000);
}

void InfoDeal::fileRead() {
    string path;
    if (_access("users", 0) == -1) {
        path = "md users";
        system(path.c_str());
    }
    if (_access("films", 0) == -1) {
        path = "md films";
        system(path.c_str());
    }
    if (_access("films\\films.txt", 0) == -1) {
        ofstream oFile{"films\\films.txt"};
        oFile.close();
        return;
    }
    ifstream inFile{"films\\films.txt"};
    while (!inFile.eof()) {
        FilmsInfo temp;
        string str;
        long long playTime = 0;
        int k = 0;
        inFile >> temp.moviename;
        inFile >> temp.year;
        inFile >> temp.month;
        inFile >> temp.day;
        inFile >> temp.hour;
        inFile >> temp.minute;
        inFile >> temp.price;
        inFile >> temp.sale;
        inFile >> temp.rest;
        inFile >> temp.play;
        inFile >> str;
        temp.rest = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (str[k] == '1') {
                    temp.seat[i][j] = true;
                    temp.rest++;
                } else {
                    temp.seat[i][j] = false;
                }
                k++;
            }
        }
        playTime = temp.year;
        playTime = playTime * 100 + temp.month;
        playTime = playTime * 100 + temp.day;
        playTime = playTime * 100 + temp.hour;
        playTime = playTime * 100 + temp.minute;
        if (get_time() > playTime) {
            temp.play = 1;
        } else {
            temp.play = 0;
        }
        finfo.push_back(temp);
    }
    finfo.pop_back();
    inFile.close();
    sort(finfo.begin(), finfo.end(), cmp);
}

void InfoDeal::fileSave() {
    sort(finfo.begin(), finfo.end(), cmp);
    ofstream oFile{"films\\films.txt", ios::trunc};
    int i = static_cast<int>(finfo.size());
    for (i = 0; i < finfo.size(); i++) {
        oFile << finfo[i].moviename << " ";
        oFile << finfo[i].year << " " << finfo[i].month << " " << finfo[i].day
              << " ";
        oFile << finfo[i].hour << " " << finfo[i].minute << " ";
        oFile << finfo[i].price << " " << finfo[i].sale << " ";
        oFile << finfo[i].rest << " ";
        oFile << finfo[i].play << endl;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                oFile << finfo[i].seat[j][k];
            }
        }
        oFile << endl;
    }
    oFile.close();
}

void InfoDeal::showSeat(int n) {
    cout << "                         ---------" << endl;
    cout << "                         | 屏 幕 |" << endl;
    cout << "                         ---------" << endl;
    cout << "     01列 02列 03列 04列 05列 06列 07列 08列 09列 10列 " << endl;
    cout << "    ---------------------------------------------------" << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 0) {
                if (i != 9) cout << "0";
                cout << i + 1 << "排|";
            }
            if (finfo[n].seat[i][j] == false) {
                cout << "[满]";
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "[空]";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            if ((2 <= i && i <= 5) && (1 <= j && j <= 7)) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                cout << "|";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            } else {
                cout << "|";
            }
        }
        cout << endl;
    }
    cout << "    ---------------------------------------------------" << endl;
}

long long InfoDeal::get_time() {
    long long time;
    SYSTEMTIME st;
    GetLocalTime(&st);
    time = st.wYear;
    time = time * 100 + st.wMonth;
    time = time * 100 + st.wDay;
    time = time * 100 + st.wHour;
    time = time * 100 + st.wMinute;
    return time;
}
