// main.cpp
// Created by cch on 2020/5/27.
#include <io.h>

#include <iostream>

#include "Admin.h"
#include "InfoDeal.h"
#include "Menu.h"
#include "User.h"
using namespace std;

int main() {
    system("chcp 65001");
    
    Admin admin;
    admin.showInfo();
    cin.get();
}