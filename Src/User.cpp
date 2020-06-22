// User.cpp
// Created by cch on 2020/6/17.
#include "User.h"

#include <conio.h>
#include <io.h>
#include <time.h>
#include <windows.h>

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "Menu.h"
using namespace std;

void User::pwInput(std::string& pw) {
    while (true) {
        char ch;
        ch = getch();
        if (ch == 8) {  // 输入退格键时删除一个字符
            if (!pw.empty()) {
                pw.pop_back();
                cout << "\b \b";
            }
            continue;
        } else if (ch == 13) {
            cout << endl;
            break;
        } else {
            pw.push_back(ch);
            cout << "*";
        }
    }
}

bool User::membership() {
    cout << "--------------------------------\n";
    cout << "VIP享受购票优惠，终身仅需99￥\n";
    cout << "是否开通终身VIP(y/n)?：";
    if (deal.yesOrNo()) {
        cout << "等待支付";
        deal.wait();
        cout << "\n--支付成功--\n";
        cout << "恭喜您成功为终身VIP，祝您观影愉快！\n";
        cout << "--------------------------------\n";
        return true;
    } else {
        cout << "取消开通VIP，祝您观影愉快！\n";
        cout << "--------------------------------\n";
        return false;
    }
}

void User::showSeat(const FilmsInfo& film) {
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
            if (film.seat[i][j] == true) {
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

bool User::cmpTime(const Ticket& ticket) {
    time_t tt;
    time(&tt);
    tt += 8 * 3600;
    tm* t = gmtime(&tt);
    if (ticket.year != (t->tm_year + 1900)) {
        return (ticket.year < (t->tm_year + 1900));
    } else if (ticket.month != (t->tm_mon + 1)) {
        return (ticket.month < (t->tm_mon + 1));
    } else if (ticket.day != t->tm_mday) {
        return (ticket.day < t->tm_mday);
    } else if (ticket.hour != t->tm_hour) {
        return (ticket.hour < t->tm_hour);
    } else {
        return (ticket.minute < t->tm_min);
    }
}

void User::userSave() {
    string path = uinfo.idName;
    path = "users\\" + path + ".dat";
    ofstream oFile{path, ios::binary | ios::trunc};
    sort(tic.begin(), tic.end(), tcmp);
    if (!oFile) {
        return;
    }
    oFile.write((char*)&uinfo, sizeof(UserInfo));
    for (int i = 0; i < tic.size(); i++) {
        if (cmpTime(tic[i])) {
            tic[i].play = true;
        } else {
            tic[i].play = false;
        }
        oFile.write((char*)&tic[i], sizeof(Ticket));
    }
    oFile.close();
}

void User::userRead(string name) {
    tic.clear();
    string path = "users\\" + name + ".dat";
    Ticket temp;
    ifstream iFile{path, ios::binary | ios::in};
    if (!iFile) {
        return;
    }
    iFile.read((char*)&uinfo, sizeof(UserInfo));
    iFile.read((char*)&temp, sizeof(Ticket));
    while (!iFile.eof()) {
        if (cmpTime(temp)) {
            temp.play = true;
        } else {
            temp.play = false;
        }
        tic.push_back(temp);
        iFile.read((char*)&temp, sizeof(Ticket));
    }
    iFile.close();
}

bool User::tcmp(const Ticket& a, const Ticket& b) {
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

ostream& operator<<(ostream& os, const Ticket& ticket) {
    string str;
    os << setiosflags(ios::left);
    str = "《";
    str += ticket.name;
    str += "》";
    os << setw(17) << str;

    str = to_string(ticket.year) + "-";
    if (ticket.month < 10) str += "0";
    str += (to_string(ticket.month) + "-");
    if (ticket.day < 10) str += "0";
    str += to_string(ticket.day);
    os << setw(12) << str;

    str.clear();
    if (ticket.hour < 10) str = "0";
    str += (to_string(ticket.hour) + ":");
    if (ticket.minute < 10) str += "0";
    str += to_string(ticket.minute);
    os << setw(7) << str;

    os << setw(6) << ticket.playNum;
    os.precision(1);
    os.setf(os.showpoint | ios::fixed);
    os << setw(6) << ticket.price;

    str.clear();
    if (ticket.seat[0] + 1 < 10) str = "0";
    str += (to_string(ticket.seat[0] + 1) + "排");
    if (ticket.seat[1] + 1 < 10) str += "0";
    str += (to_string(ticket.seat[1] + 1) + "座");
    os << setw(10) << str;

    if (ticket.play) {
        os << setw(8) << "已上映" << endl;
    } else {
        os << setw(8) << "未上映" << endl;
    }
    return os;
}

void User::menuChoice() {
    char ch;
    int choice;
    Menu menu;
    while (true) {
        menu.userMenu();
        cin >> ch;
        cin.ignore();
        choice = ch - 48;
        switch (choice) {
            case 0: {
                return;
            }
            case 1: {
                book();
                break;
            }
            case 2: {
                refund();
                break;
            }
        }
    }
}

int User::showFInfo() {
    int begin;
    int size = static_cast<int>(deal.finfo.size());
    for (begin = 0; begin < size; begin++) {
        if (deal.finfo[begin].play == false) {
            break;
        }
    }
    system("cls");
    if (begin == size) {
        cout << "--------------------------------\n";
        cout << "       当前没有可购买电影\n";
        return -1;
    }
    deal.showFInfo(begin);
    return begin;
}

void User::signUp() {
    string menu{
        "            ---------\n"
        "            | 注 册 |\n"
        "            ---------\n"
        "--------------------------------\n"};
    string warning{"请重新输入\n--------------------------------\n"};
    system("cls");
    cout << menu;
    while (true) {
        string path;
        string id;
        string pw, repw;
        cout << "（用户名不含空格，不分大小写,0退出）\n";
        cout << "请输入用户名：";
        getline(cin, id);
        if (id == "0") {
            cout << "--退出注册--\n";
            cout << "-----------任意键返回-----------" << endl;
            getch();
            return;
        }
        if (id == "admin") {
            system("cls");
            cout << menu;
            cout << "   该用户名不可注册，" << warning;
            continue;
        }
        if (id.find(' ') != string::npos) {
            system("cls");
            cout << menu;
            cout << "  用户名不可包含空格，" << warning;
            continue;
        }
        path = "users\\" + id + ".dat";
        if (_access(path.c_str(), 0) == 0) {
            system("cls");
            cout << menu;
            cout << "   该用户名已存在，" << warning;
            continue;
        }
        cout << "（密码6位及以上且不含空格）\n";
        cout << "请输入密码：";
        pwInput(pw);
        if (pw.find(' ') != string::npos) {
            system("cls");
            cout << menu;
            cout << "    密码不可包含空格，" << warning;
            continue;
        }
        if (pw.size() < 6) {
            system("cls");
            cout << menu;
            cout << "   密码必须6位及以上，" << warning;
            continue;
        }
        cout << "请再次输入密码：";  // 密码确认
        pwInput(repw);
        if (pw != repw) {
            system("cls");
            cout << menu;
            cout << "   两次密码不一致，" << warning;
            continue;
        }
        cout << "正在注册，请稍后";
        deal.wait();
        cout << endl << id << " 注册成功！" << endl;
        uinfo.vip = membership();
        strcpy(uinfo.idName, id.c_str());
        strcpy(uinfo.password, pw.c_str());

        ofstream oFile{path, ios::binary | ios::trunc};
        oFile.write((char*)&uinfo, sizeof(UserInfo));
        oFile.close();
        cout << "-----------任意键返回-----------" << endl;
        getch();
        return;
    }
}

string User::login() {
    string menu{
        "            ---------\n"
        "            | 登 陆 |\n"
        "            ---------\n"
        "--------------------------------\n"};
    system("cls");
    cout << menu;
    while (true) {
        string id;
        string pw;
        string path;
        cout << "请输入用户名(0退出)：";
        getline(cin, id);
        if (id == "0") {
            cout << "--退出登陆--\n";
            cout << "-----------任意键返回-----------" << endl;
            getch();
            return string{"-1"};
        }
        cout << "请输入密码：";
        pwInput(pw);
        if (id == "admin" && pw == "admin") {
            cout << "正在登陆，请稍后";
            deal.wait();
            cout << "\n欢迎管理员admin!" << endl;
            cout << "-----------任意键跳转-----------" << endl;
            getch();
            return string{"admin"};
        }
        path = "users\\" + id + ".dat";
        if (_access(path.c_str(), 0) != 0) {
            system("cls");
            cout << menu;
            cout << " 用户名或密码错误\n";
            cout << "--------------------------------\n";
            continue;
        }
        ifstream iFile{path.c_str(), ios::binary | ios::in};
        iFile.read((char*)&uinfo, sizeof(UserInfo));
        if (strcmp(pw.c_str(), uinfo.password) == 0) {
            iFile.close();
            cout << "正在登陆，请稍后";
            deal.wait();
            cout << "\n欢迎";
            if (uinfo.vip) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                cout << "VIP";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            cout << "用户：" << id << endl;
            cout << "-----------任意键跳转-----------" << endl;
            getch();
            userRead(id);
            return id;
        } else {
            iFile.close();
            system("cls");
            cout << menu;
            cout << " 用户名或密码错误\n";
            cout << "--------------------------------\n";
            continue;
        }
    }
}

void User::book() {
    int x, y;
    int begin;
    int choice;
    int size = static_cast<int>(deal.finfo.size());
    bool isBest = false;
    double ticPrice;
    begin = showFInfo();
    if (begin == -1) return;
    while (true) {
        cout << "请输入电影编号(0退出)：";
        cin >> choice;
        if (choice == 0) {
            cout << "--退出购票--\n";
            cout << "-----------任意键返回-----------\n";
            getch();
            return;
        }
        choice = choice + begin - 1;
        if (choice < begin || choice > size) {
            cout << "编号不存在，请重新输入\n";
            continue;
        }
        if (deal.finfo[choice].rest == 0) {
            cout << "此电影已满座，请选择其他电影\n";
            continue;
        }
        break;
    }
    showSeat(deal.finfo[choice]);
    cout << "红色区域为最佳观影区，须多支付20%\n";
    while (true) {
        cout << "是否继续选座(y/n)：";
        if (!deal.yesOrNo()) {
            cout << "--退出选座--\n";
            break;
        }
        cout << "请选择座位(1 1)：";
        cin >> x >> y;
        cin.ignore();
        x--;
        y--;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            cout << "座位不存在\n";
            continue;
        } else if (deal.finfo[choice].seat[x][y] == true) {
            cout << "此座已售，请选择其他座位\n";
            continue;
        }
        // 是否最佳观影区
        if (x >= 2 && x <= 5 && y >= 2 && y <= 7) {
            isBest = true;
            cout << "您选的为 " << x + 1 << "排" << y + 1
                 << "座，是最佳观影区，须多支付20%" << endl;
            ticPrice = deal.finfo[choice].price * 1.2;
        } else {
            isBest = false;
            cout << "您选的为 " << x + 1 << "排" << y + 1 << "座\n";
            ticPrice = deal.finfo[choice].price;
        }
        if (uinfo.vip) {
            ticPrice = ticPrice * deal.finfo[choice].discount / 10;
            cout << "您为VIP用户，票价打" << deal.finfo[choice].discount
                 << "折\n";
        }
        cout << "票价：" << ticPrice << endl;
        if (!uinfo.vip) {
            uinfo.vip = membership();
            if (uinfo.vip) {
                ticPrice = ticPrice * deal.finfo[choice].discount / 10;
                cout << "您开通了VIP，票价打" << deal.finfo[choice].discount
                     << "折\n";
                cout << "票价：" << ticPrice << "￥\n"; 
            }
        }
        cout << "是否支付(y/n)？：";
        if (deal.yesOrNo()) {
            cout << "等待支付";
            deal.wait();
            cout << "\n支付成功!\n";

            Ticket temp;
            deal.finfo[choice].seat[x][y] = true;
            deal.finfo[choice].rest--;
            deal.finfo[choice].sumSales += ticPrice;
            strcpy(temp.name, deal.finfo[choice].name);
            temp.year = deal.finfo[choice].year;
            temp.month = deal.finfo[choice].month;
            temp.day = deal.finfo[choice].day;
            temp.hour = deal.finfo[choice].hour;
            temp.minute = deal.finfo[choice].minute;
            temp.playNum = deal.finfo[choice].playNum;
            temp.seat[0] = x;
            temp.seat[1] = y;
            temp.price = ticPrice;
            temp.isBest = isBest;
            tic.push_back(temp);
            printTicket(temp);
            deal.filmSave();
            userSave();
        } else {
            cout << "--取消支付--\n";
            continue;
        }
    }
    cout << "-----------任意键返回-----------\n";
    getch();
    return;
}

void User::refund() {
    string menu = {
        "                                ----------\n"
        "                                | 退  票 |\n"
        "                                ----------\n"
        "-----------------------------------------"
        "---------------------------------\n"};
    if (tic.size() == 0) {
        cout << "您的账户无电影票信息\n";
        cout << "-----------任意键返回-----------\n";
        getch();
        return;
    }
    system("cls");
    cout << menu;
    cout << "您购买的电影票如下：\n";
    cout << setiosflags(ios::left);
    cout << setw(6) << "编号" << setw(16) << "电影名";
    cout << setw(12) << "日期" << setw(7) << "时间";
    cout << setw(6) << "场次" << setw(6) << "价格";
    cout << setw(10) << "座位" << setw(8) << "状态" << endl;
    for (int i = 0; i < tic.size(); i++) {
        cout << setw(5) << i + 1;
        cout << tic[i];
    }
    cout << "-----------------------------------------"
            "---------------------------------\n";
    int choice;
    while (true) {
        cout << "--------------------------------\n";
        cout << "请输入退票编号(0退出)：";
        cin >> choice;
        if (choice == 0) {
            cout << "--退出退票--\n";
            cout << "-----------任意键返回-----------\n";
            getch();
            return;
        }
        if (choice < 0 || choice > tic.size()) {
            cout << "编号不存在\n";
            continue;
        }
        if (tic[--choice].play) {
            cout << "此票已过期，不可退款\n";
            continue;
        }
        break;
    }
    cout << "确定退掉此票(y/n)?：";
    if (deal.yesOrNo()) {
        vector<Ticket>::iterator tit = tic.begin() + choice;
        vector<FilmsInfo>::iterator fit = deal.finfo.begin();
        for (fit; fit < deal.finfo.end(); fit++) {
            if (fit->year == tit->year && fit->month == tit->month &&
                fit->day == tit->day && fit->playNum == tit->playNum) {
                break;
            }
        }
        if (fit == deal.finfo.end()) {
            cout << "refund find error!\n";
            return;
        }
        fit->rest++;
        fit->seat[tit->seat[0]][tit->seat[1]] = false;
        fit->sumSales -= tit->price;
        cout << "退票成功，退款" << tit->price << "￥\n";
        tic.erase(tit);
        deal.filmSave();
        userSave();
        cout << "-----------任意键返回-----------\n";
        getch();
        return;
    } else {
        cout << "--取消退票--\n";
        cout << "-----------任意键返回-----------\n";
        getch();
        return;
    }
}

void User::printTicket(const Ticket& ticket) {
    string fname = ticket.name;
    int i = 5 - fname.size() / 8;
    cout << "------------------------------------------------\n";
    cout << "正在打印电影票";
    deal.wait();
    cout << "\n------------------------------------------------\n";
    cout << "_________________________________________________\n";
    cout << "|                   C C H 影 城                 |\n";
    cout << "|\t\t\t\t\t\t|\n";
    cout << "| 片名：" << fname;
    for (int j = 1; j <= i; j++) {
        cout << "\t";
    }
    cout << "|\n";
    cout << "| 影厅：1号厅\t\t时间：";
    cout << ticket.year << "-" << ticket.month << "-" << ticket.day;
    cout << " " << ticket.hour << ":" << (ticket.minute == 0 ? "00" : "30")
         << "\t|\n";
    cout << "| 座位：" << ticket.seat[0] << " 排 " << ticket.seat[1] << "座\t";
    cout << "座类：" << (ticket.isBest ? "最佳区" : "普通区") << "\t\t|\n";
    cout << "| 票价：";
    cout.precision(2);
    cout.setf(cout.showpoint | ios::fixed);
    cout << ticket.price << "￥\t\t用户类型：";
    cout << (uinfo.vip ? "VIP" : "普通") << "\t\t|\n";
    cout << "|\t\t\t\t\t\t|\n";
    cout << "|                  观 影 愉 快                  |\n";
    cout << "|              | |||| ||||| ||| ||              |\n";
    cout << "|              x xxxx xxxxx xxx xx              |\n";
    cout << "|_______________________________________________|\n";
    cout << "------------------------------------------------\n";
}
