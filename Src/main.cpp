// main.cpp
// Created by cch on 2020-6-15
#include <conio.h>
#include <io.h>
#include <windows.h>

#include <fstream>
#include <iostream>

#include "Admin.h"
#include "Menu.h"
#include "User.h"
using namespace std;

int enterChoice() {
    char ch;
    cin >> ch;
    cin.ignore();
    return (static_cast<int>(ch) - 48);
}

int main() {
    system("chcp 936");
    system("mode con cols=78 lines=35");
    system("cls");
    if (_access("users", 0) == -1) {
        system("md users");
    }
    if (_access("films", 0) == -1) {
        system("md films");
    }
    if (_access("statistics", 0) == -1) {
        system("md statistics");
    }

    Menu menu;
    User* user;
    Admin* admin;
    int choice;
    menu.cover();
    while (true) {
        menu.mainMenu();
        choice = enterChoice();
        switch (choice) {
            case 1: {
                user = new User;
                user->showFInfo();
                cout << "-----------任意键返回-----------\n";
                getch();
                delete user;
                break;
            }
            case 2: {
                user = new User;
                string name;
                name = user->login();
                if (name == "-1") {
                    break;
                } else if (name == "admin") {
                    delete user;
                    admin = new Admin;
                    admin->menuChoice();
                    delete admin;
                } else {
                    user->menuChoice();
                    delete user;
                }
                break;
            }
            case 3: {
                user = new User;
                user->signUp();
                break;
            }
            case 0: {
                cout << "--即将退出--" << endl;
                Sleep(500);
                return 0;
            }
            default: {
                cout << "功能不存在，请重新选择\n";
                Sleep(500);
                break;
            }
        }
    }
}