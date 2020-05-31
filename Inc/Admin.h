// Admin.h
// Created by cch on 2020/5/27.
#pragma once
#include "InfoDeal.h"

class Admin : public InfoDeal {
   public:
    // 删除
    void del();
    // 添加
    void add();
    // 修改
    void change();
    // 显示电影信息 管理员版
    void showInfo();
};