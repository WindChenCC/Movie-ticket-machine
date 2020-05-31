// FilmsInfo.h
// Created by cch on 2020/5/27.
#pragma once
#include <string>

class FilmsInfo {
   public:
    std::string moviename;
    bool seat[10][10];  // 座位情况
    double price;       // 价格
    double sale;        // 折扣
    int rest = 100;     // 剩余座位
    int year;
    int month;
    int day;
    int hour;
    int minute;
    bool play = 0;
};