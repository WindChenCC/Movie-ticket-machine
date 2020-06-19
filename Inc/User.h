// User.h
// Created by cch on 2020/6/15.
#pragma once

#include "Deal.h"

class User {
   private:
    Deal deal;
    UserInfo uinfo;           // 用户信息
    std::vector<Ticket> tic;  // 票容器

    void pwInput(std::string& pw);
    // 开通会员
    bool membership();
    // 显示座位
    void showSeat(const FilmsInfo& film);
    // 比较时间
    bool cmpTime(const Ticket& ticket);
    // 读取用户信息
    void userRead(std::string name);
    // 保存用户信息
    void userSave();
    // 用户电影票排序
    static bool tcmp(const Ticket& a, const Ticket& b);
    // 重载<< 输出票信息
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);

   public:
    // 功能选择
    void menuChoice();
    // 显示可购买电影 返回第一个大于系统时间的电影下标
    int showFInfo();
    // 注册
    void signUp();
    // 登陆
    std::string login();
    // 购票
    void book();
    // 退票
    void refund();
    // 打印电影票
    void printTicket(const Ticket& ticket);
};