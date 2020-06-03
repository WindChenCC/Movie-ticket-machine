// Admin.cpp
// Created by cch on 2020/5/28.

#include "Admin.h"

#include <conio.h>
#include <windows.h>

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

void Admin::del() {
    int n;
    int m = static_cast<int>(finfo.size());
    char ch;
    vector<FilmsInfo>::iterator it;
    showInfo();
    while (true) {
        showInfo();
        it = finfo.begin();
        cout << "\n请输入需要删除的电影编号（0退出）：";
        cin >> n;
        while (n > m) {
            cout << "编号不存在，请重新输入";
            cout << "请输入需要删除的电影编号（0退出）：";
            cin >> n;
        }
        if (n == 0) {
            cout << "退出删除" << endl;
            cout << "-----------任意键返回-----------";
            getch();
            return;
        }
        while (true) {
            cout << "确认删除?(y/n):";
            cin >> ch;
            if (ch == 'y') {
                finfo.erase(it + n - 1);
                cout << "删除成功，未上映的将自动退款给用户，是否继续?(y/n):";
                break;
            } else if (ch == 'n') {
                cout << "取消删除，是否继续?(y/n):";
                break;
            } else {
                cout << "输入错误，请再次确认\n";
                continue;
            }
        }
        cin >> ch;
        if (ch == 'y') {
            continue;
        } else {
            fileSave();
            cout << "-----------任意键返回-----------";
            getch();
            break;
        }
    }
}

void Admin::add() {
    string menu = {
        "            ---------\n"
        "            | 添 加 |\n"
        "            ---------\n"
        "--------------------------------\n"};
    string str;
    if (finfo.size() == 0) {
        printf("没有电影信息，请先添加\n");
        return;
    }
    int choice;
    char ch;
    while (true) {
        system("cls");
        cout << menu;
        FilmsInfo temp;
        memset(temp.seat, 1, sizeof(temp.seat));
        cout << "请输入电影名：";
        getline(cin, temp.moviename);
        cout << "请输入日期(2020-1-1)：";
        cin >> temp.year >> ch >> temp.month >> ch >> temp.day;
        cout << "1. 8:30-10:30   2. 11:00-13:00\n"
                "3. 13:30-15:30  4. 16:00-18:00\n"
                "5. 18:30-20:30  6. 21:00-23:00\n"
                "7. 23:30-1:30\n";
        cout << "请选择时间段：";
        cin >> choice;
        switch (choice) {
            case 1:
                temp.hour = 8;
                temp.minute = 30;
                break;
            case 2:
                temp.hour = 11;
                temp.minute = 0;
                break;
            case 3:
                temp.hour = 13;
                temp.minute = 30;
                break;
            case 4:
                temp.hour = 16;
                temp.minute = 0;
                break;
            case 5:
                temp.hour = 18;
                temp.minute = 30;
                break;
            case 6:
                temp.hour = 21;
                temp.minute = 0;
                break;
            case 7:
                temp.hour = 23;
                temp.minute = 30;
                break;
            default:
                cout << "输入错误\n";
                break;
        }
        cout << "请输入票价：";
        cin >> temp.price;
        cout << "请输入VIP折扣(7.5)：";
        cin >> temp.sale;
        cin.ignore();
        cout << "确定添加?(y/n)：";
        cin >> ch;
        cin.ignore();
        if (ch == 'y') {
            finfo.push_back(temp);
            cout << "保存成功，是否继续添加?(y/n)：";
        } else {
            cout << "取消保存，是否继续添加?(y/n)：";
        }
        cin >> ch;
        cin.ignore();
        if (ch == 'y') {
            continue;
        } else {
            sort(finfo.begin(), finfo.end(), cmp);
            fileSave();
            cout << "-----------任意键返回-----------";
            getch();
            break;
        }
    }
}

void Admin::showInfo() {
    string str;
    int size = static_cast<int>(finfo.size());
    system("cls");
    printf("                               ----------\n");
    printf("                               | 信  息 |\n");
    printf("                               ----------\n");
    printf(
        "----------------------------------------------------------------------"
        "---\n");
    if (finfo.size() == 0) {
        printf("没有电影信息，请先添加\n");
        printf("-----------任意键返回-----------");
        getch();
        return;
    }
    printf("%-8s%-20s\t", "编号", "电影名");
    printf("%-13s%-10s", "日期", "时间");
    printf("%-10s%-10s", "价格", "VIP折扣");
    printf("%-10s%-10s\n", "剩余", "状态");
    for (int i = 0; i < size; i++) {
        str = to_string(i + 1) + ".";
        printf("%-5s", str.c_str());
        str = "《" + finfo[i].moviename + "》";
        printf("%-20s\t", str.c_str());
        str = to_string(finfo[i].year) + "-" + to_string(finfo[i].month) + "-" +
              to_string(finfo[i].day);
        printf("%-11s", str.c_str());
        str = to_string(finfo[i].hour) + ":";
        if (finfo[i].minute == 0) {
            str += "00";
        } else {
            str += to_string(finfo[i].minute);
        }
        printf("%-8s", str.c_str());
        printf("%-8.1f", finfo[i].price);
        printf("%-8.1f", finfo[i].sale);
        printf("%-8d", finfo[i].rest);
        if (finfo[i].play) {
            printf("%s\n", "已上映");
        } else {
            printf("%s\n", "未上映");
        }
    }
    printf(
        "----------------------------------------------------------------------"
        "---\n");
}

void Admin::change() {
    string menu = {"\n--------------------------------\n"};
    int choice;
    int n;
    int m = static_cast<int>(finfo.size());
    char ch;
    vector<FilmsInfo>::iterator it;
    showInfo();
    it = finfo.begin();
    cout << menu;
    cout << "请输入修改的编号（0退出）：";
    cin >> n;
    while (n > m) {
        cout << "编号不存在，请重新输入";
        cout << "请输入需要删除的电影编号（0退出）：";
        cin >> n;
    }
    if (n == 0) {
        cout << "退出修改" << endl;
        cout << "-----------任意键返回-----------\n";
        getch();
        return;
    }
    it = it + n - 1;
    FilmsInfo temp = *it;
    while (true) {
        cout << "1. 电影名  2. 日期" << endl;
        cout << "3. 时间    4. 价格" << endl;
        cout << "5. 折扣" << endl;
        cout << "请选择修改的信息：";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "请输入电影名：";
                cin.ignore();
                getline(cin, temp.moviename);
                break;
            case 2:
                cout << "请输入日期(2020-1-1)：";
                cin >> temp.year >> ch >> temp.month >> ch >> temp.day;
                break;
            case 3:
                cout << "1. 8:30-10:30   2. 11:00-13:00\n"
                        "3. 13:30-15:30  4. 16:00-18:00\n"
                        "5. 18:30-20:30  6. 21:00-23:00\n"
                        "7. 23:30-1:30\n";
                cout << "请选择时间段：";
                int choice2;
                cin >> choice2;
                cin.ignore();
                switch (choice2) {
                    case 1:
                        temp.hour = 8;
                        temp.minute = 30;
                        break;
                    case 2:
                        temp.hour = 11;
                        temp.minute = 0;
                        break;
                    case 3:
                        temp.hour = 13;
                        temp.minute = 30;
                        break;
                    case 4:
                        temp.hour = 16;
                        temp.minute = 0;
                        break;
                    case 5:
                        temp.hour = 18;
                        temp.minute = 30;
                        break;
                    case 6:
                        temp.hour = 21;
                        temp.minute = 0;
                        break;
                    case 7:
                        temp.hour = 23;
                        temp.minute = 30;
                        break;
                    default:
                        cout << "输入错误\n";
                        break;
                }
            case 4:
                cout << "请输入价格：";
                cin >> temp.price;
                break;
            case 5:
                cout << "请输入折扣(7.5)：";
                cin >> temp.sale;
                break;
        }
        cout << "确认修改?(y/n)：";
        cin >> ch;
        cin.ignore();
        if (ch == 'y') {
            *it = temp;
            cout << "修改成功" << endl;
        } else {
            cout << "取消修改" << endl;
        }
        cout << "是否继续修改该编号其他信息?(y/n)：";
        cin >> ch;
        cin.ignore();
        if (ch == 'y') {
            continue;
        } else {
            sort(finfo.begin(), finfo.end(), cmp);
            fileSave();
            showInfo();
            cout << "-----------任意键返回-----------";
            getch();
            return;
        }
    }
}
