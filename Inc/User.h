// User.h
// Created by cch on 2020/5/27.
#pragma once
#include <string>

#include "InfoDeal.h"

class User : public InfoDeal {
   private:
    std::string idName;
    std::string password;
    bool vip = false;
    void pwInput(std::string& str);

   public:
    // 电影信息显示 用户版
    void showInfo();
    // 登陆
    void login();
    // 注册
    void signUp();
    // 订票
    void book();
    // 退票
    void refund();
};