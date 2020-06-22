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
                cout << "-----------任意键返回-----------\n";
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
        "            | 添 加 |\n"
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
        cout << "请输入电影名(0退出)：";
        getline(cin, sname);
        if (sname == "0") {
            cout << "--退出添加--\n";
            cout << "-----------任意键返回-----------" << endl;
            getch();
            return;
        }
        strcpy(temp.name, sname.c_str());
        cout << "请输入日期(2020 1 1)：";
        cin >> temp.year >> temp.month >> temp.day;
        cout << "1. 8:30-10:30   2. 11:00-13:00\n"
                "3. 13:30-15:30  4. 16:00-18:00\n"
                "5. 18:30-20:30  6. 21:00-23:00\n"
                "7. 23:30-1:30\n";
        cout << "请选择场次：";
        cin >> choice;
        temp.playNum = choice;
        for (it = deal.finfo.begin(); it < deal.finfo.end(); it++) {
            if (temp.year == it->year && temp.month == it->month &&
                temp.day == it->day && temp.playNum == it->playNum) {
                break;
            }
        }
        if (it != deal.finfo.end()) {
            cout << "该日期的第" << choice << "场次已有其他电影\n";
            cout << "请重新添加\n";
            cout << "-----------任意键继续-----------" << endl;
            getch();
            cin.ignore();
            continue;
        }
        temp.hour = playNum[choice][0];
        temp.minute = playNum[choice][1];
        cout << "请输入票价：";
        cin >> temp.price;
        cout << "请输入VIP折扣(7.5)：";
        cin >> temp.discount;
        cout << "确定添加?(y/n)：";
        if (deal.yesOrNo()) {
            deal.finfo.push_back(temp);
            cout << "保存成功，是否继续添加?(y/n)：";
        } else {
            cout << "取消保存，是否继续添加?(y/n)：";
        }
        if (deal.yesOrNo()) {
            continue;
        } else {
            deal.filmSave();
            cout << "-----------任意键返回-----------" << endl;
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
        cout << "请输入修改的编号(0退出)：";
        cin >> n;
        while (n > m) {
            cout << "编号不存在，请重新输入";
            cout << "请输入需要删除的电影编号（0退出）：";
            cin >> n;
        }
        if (n == 0) {
            cout << "--退出修改--" << endl;
            cout << "-----------任意键返回-----------\n";
            getch();
            return;
        }
        if (deal.finfo[--n].rest != 100) {
            cout << "此电影已售出电影票不可修改\n";
            cout << "-----------任意键继续-----------\n";
            getch();
            continue;
        }
        FilmsInfo temp = deal.finfo[n];
        cout << "1. 电影名  2. 日期" << endl;
        cout << "3. 场次    4. 价格" << endl;
        cout << "5. 折扣" << endl;
        cout << "请选择修改的信息：";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "请输入电影名：";
                cin.ignore();
                cin >> temp.name;
                break;
            case 2:
                cout << "请输入日期(2020 1 1)：";
                cin >> temp.year >> temp.month >> temp.day;
                break;
            case 3:
                cout << "1. 08:30-10:30  2. 11:00-13:00\n"
                        "3. 13:30-15:30  4. 16:00-18:00\n"
                        "5. 18:30-20:30  6. 21:00-23:00\n"
                        "7. 23:30-01:30\n";
                cout << "请选择场次：";
                int choice2;
                cin >> choice2;
                cin.ignore();
                temp.playNum = choice2;
                temp.hour = playNum[choice2][0];
                temp.minute = playNum[choice2][1];
            case 4:
                cout << "请输入价格：";
                cin >> temp.price;
                break;
            case 5:
                cout << "请输入VIP折扣(7.5)：";
                cin >> temp.discount;
                break;
            default:
                cout << "选择错误！" << endl;
                continue;
        }
        cout << "确认修改?(y/n)：";
        if (deal.yesOrNo()) {
            deal.finfo[n] = temp;
            cout << "修改成功\n";
            cout << "--------------------------------\n";
        } else {
            cout << "--取消修改--" << endl;
        }
        cout << "是否继续修改?(y/n)：";
        if (deal.yesOrNo()) {
            continue;
        } else {
            deal.filmSave();
            cout << "-----------任意键返回-----------" << endl;
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
        cout << "请输入需要删除的电影编号(0退出)：";
        cin >> n;
        while (n > m) {
            cout << "编号不存在，请重新输入\n";
            cout << "请输入需要删除的电影编号（0退出）：";
            cin >> n;
        }
        if (n == 0) {
            cout << "--退出删除--" << endl;
            cout << "-----------任意键返回-----------" << endl;
            getch();
            return;
        }
        n--;
        if (((it + n)->rest != 100) && (it + n)->play == 0) {
            cout << "该电影未上映且已售出票，不可删除\n";
            cout << "请联系用户进行退票操作后再删除\n";
            Sleep(500);
            cout << "是否继续删除其他电影(y/n)?：";
            if (deal.yesOrNo()) {
                continue;
            } else {
                cout << "--退出删除--" << endl;
                cout << "-----------任意键返回-----------" << endl;
                getch();
                return;
            }
        }
        cout << "确认删除?(y/n):";
        if (deal.yesOrNo()) {
            deal.finfo.erase(it + n);
            deal.filmSave();
            cout << "删除成功，是否继续?(y/n):";
        } else {
            cout << "取消删除，是否继续?(y/n):";
        }
        if (deal.yesOrNo()) {
            continue;
        } else {
            cout << "-----------任意键返回-----------" << endl;
            getch();
            return;
        }
    }
}

void Admin::count() {
    if (deal.finfo.size() == 0) {
        cout << "没有电影信息，无法统计\n";
        cout << "-----------任意键返回-----------" << endl;
        getch();
        return;
    }
    string menu = {
        "                                ----------\n"
        "                                | 统  计 |\n"
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
        cout << "可统计日期有：\n";
        for (i = 1; i <= mdate.size(); i++) {
            cout << i << ". " << mdate[i] << endl;
        }
        int choice;
        while (true) {
            cout << "请选择日期(0退出)：";
            cin >> choice;
            if (choice == 0) {
                cout << "--退出统计--\n";
                cout << "-----------任意键返回-----------" << endl;
                getch();
                return;
            }
            if (choice < 0 || choice > mdate.size()) {
                cout << "日期不存在\n";
                cout << "-----------任意键继续-----------" << endl;
                getch();
                continue;
            }
            break;
        }
        cout << "-----------------------------------------"
                "---------------------------------\n";
        cout << mdate[choice] << "统计结果如下：\n\n";
        string str = mdate[choice];
        fit = deal.finfo.begin();
        for (fit; fit != deal.finfo.end(); fit++) {
            if (strDate(*fit) == str) {
                break;
            }
        }
        fit2 = fit;
        for (i = 1; i <= 7; i++) {
            cout << "第" << i << "场次 " << mpnum[i] << " ";
            if ((fit != deal.finfo.end()) && (strDate(*fit) == str) &&
                (fit->playNum == i)) {
                cout << "电影《" << fit->name << "》\n";
                cout << "已售：" << 100 - fit->rest;
                cout << "  销售额：" << fit->sumSales << "￥\n\n";
                fit++;
            } else {
                cout << "无电影\n\n";
            }
        }
        cout << "--------------------------------\n";
        cout << "是否导出(y/n)?：";
        if (deal.yesOrNo()) {
            string path;
            path = "statistics\\" + str + ".txt";
            ofstream oFile{path, ios::out | ios::trunc};
            SYSTEMTIME st;
            GetLocalTime(&st);
            oFile << str << "统计结果 统计时间：";
            oFile << st.wYear << "-" << st.wMonth << "-" << st.wDay << " ";
            oFile << st.wHour << ":" << st.wMinute << ":" << st.wSecond << endl;
            for (i = 1; i <= 7; i++) {
                oFile << "第" << i << "场次 " << mpnum[i] << " ";
                if ((fit2 != deal.finfo.end()) && (strDate(*fit2) == str) &&
                    (fit2->playNum == i)) {
                    oFile << "电影《" << fit2->name << "》\n";
                    oFile << "已售：" << 100 - fit2->rest;
                    oFile << " 销售额：" << fit2->sumSales << "￥\n\n";
                    fit2++;
                } else {
                    oFile << "无电影\n\n";
                }
            }
            oFile.close();
            cout << "已成功导出到" << str << ".txt\n";
        }
        cout << "是否统计其他日期(y/n)?：";
        if (deal.yesOrNo()) {
            continue;
        } else {
            cout << "--退出统计--\n";
            cout << "-----------任意键返回-----------" << endl;
            getch();
            return;
        }
    }
}