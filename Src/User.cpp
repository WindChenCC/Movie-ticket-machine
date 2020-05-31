// User.cpp
// Created by cch on 2020/5/28.
#include "User.h"

#include <conio.h>
#include <io.h>
#include <windows.h>

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void User::pwInput(string& str) {
    while (true) {
        char ch;
        ch = getch();
        if (ch == 8) {
            if (str.empty() == 0) {  // 输入退格键时删除一个字符
                str.pop_back();
                cout << "\b \b";
            }
            continue;
        } else if (ch == 13) {
            cout << endl;
            break;
        } else {
            str.push_back(ch);
            cout << "*";
        }
    }
}

void User::login() {
    string menu{
        "            ---------\n"
        "            | 登 陆 |\n"
        "            ---------\n"
        "--------------------------------\n"};
    cout << menu;
    while (true) {
        password.clear();
        idName.clear();

        cout << "请输入用户名：";
        getline(cin, idName);
        cout << "请输入密码：";
        pwInput(password);
        if (idName == "admin" && password == "admin") {
            cout << "欢迎管理员admin！" << endl;
            return;
        }
        if (_access(("users\\" + idName + ".txt").c_str(), 0) != 0) {
            system("cls");
            cout << menu;
            cout << "  用户名或密码错误，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        } else {
            ifstream iFile{"users\\" + idName + ".txt"};
            string pw;
            iFile >> pw >> pw;
            if (password == pw) {
                cout << "正在登陆，请稍后";
                Sleep(500);
                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    Sleep(500);
                }
                iFile.seekg(4, ios::cur);  // 跳过文件中的 VIP:
                iFile >> vip;
                cout << endl << "登陆成功，欢迎";
                if (vip) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "vip用户:";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                }
                cout << idName << endl;
                cout << "-----------任意键跳转-----------";
                getch();
                break;
            } else {
                system("cls");
                cout << menu;
                cout << "  用户名或密码错误，请重新输入" << endl;
                cout << "--------------------------------" << endl;
                continue;
            }
        }
    }
}

void User::signUp() {
    string id;
    string path;
    string repassword;
    string menu{
        "            ---------\n"
        "            | 注 册 |\n"
        "            ---------\n"
        "--------------------------------\n"};
    if (_access("users", 0) == -1) {
        path = "md users";
        system(path.c_str());
    }
    if (_access("films", 0) == -1) {
        path = "md films";
        system(path.c_str());
    }
    cout << menu;
    while (true) {
        password.clear();
        repassword.clear();
        cout << "请输入注册用户名(不包含空格)" << endl;
        cout << "用户名：";
        getline(cin, idName);
        if (idName == "admin") {
            system("cls");
            cout << menu;
            cout << " 该用户名不可被注册，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        if (idName.find(' ') != string::npos) {
            system("cls");
            cout << menu;
            cout << " 用户名不可包含空格，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        if (idName.size() == 0) {
            system("cls");
            cout << menu;
            cout << "   用户名不能为空，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        id = idName;
        idName += ".txt";
        if (_access(("users\\" + idName).c_str(), 0) == 0) {
            system("cls");
            cout << menu;
            cout << "   该用户名已存在，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        cout << "输入密码(6位及以上且不包含空格)" << endl;
        cout << "密码：";
        pwInput(password);
        if (password.find(' ') != string::npos) {  // 检测密码是否带空格
            system("cls");
            cout << menu;
            cout << "  密码不可包含空格，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        if (password.size() < 6) {
            system("cls");
            cout << menu;
            cout << " 密码必须6位及以上，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        cout << "请再次输入密码" << endl;  // 密码确认
        cout << "密码：";
        pwInput(repassword);
        if (password != repassword) {
            system("cls");
            cout << menu;
            cout << "   两次密码不一致，请重新输入" << endl;
            cout << "--------------------------------" << endl;
            continue;
        }
        cout << "正在注册，请稍后";
        Sleep(500);
        for (int i = 0; i < 3; i++) {
            cout << ".";
            Sleep(500);
        }
        cout << endl << id << " 注册成功！" << endl;

        while (true) {
            cout << "--------------------------------" << endl;
            cout << "是否开通终身VIP，享受购票优惠?(y/n)" << endl;
            Sleep(500);
            cout << "注册优惠仅需80￥" << endl;
            Sleep(500);
            cout << "您的选择：";
            char vchoic;
            cin >> vchoic;
            if (vchoic == 'y') {
                cout << "等待支付";
                Sleep(500);
                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    Sleep(500);
                }
                vip = true;
                cout << endl << "支付成功！" << endl;
                cout << "恭喜您成为终身VIP，祝您观影愉快！" << endl;
                break;
            } else if (vchoic == 'n') {
                vip = false;
                cout << "感谢您的注册，祝您观影愉快！" << endl;
                break;
            } else {
                system("cls");
                cout << "--------------------------------" << endl;
                cout << "       请输入y或n进行选择" << endl;
                continue;
            }
        }
        ofstream oFile{"users\\" + idName};
        oFile << "password: " << password << " ";
        oFile << "VIP: " << vip << endl;
        oFile.close();
        cout << "-----------任意键返回-----------";
        getch();
        break;
    }
}
