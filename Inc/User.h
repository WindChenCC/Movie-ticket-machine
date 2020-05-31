// User.h
// Created by cch on 2020/5/27.
#pragma once
#include <string>

#include "FilmsInfo.h"

class User : public FilmsInfo {
   private:
    std::string idName;
    std::string password;
    bool vip = false;
    void pwInput(std::string& str);

   public:
    void login();
    void signUp();
};