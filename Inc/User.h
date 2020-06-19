// User.h
// Created by cch on 2020/6/15.
#pragma once

#include "Deal.h"

class User {
   private:
    Deal deal;
    UserInfo uinfo;           // �û���Ϣ
    std::vector<Ticket> tic;  // Ʊ����

    void pwInput(std::string& pw);
    // ��ͨ��Ա
    bool membership();
    // ��ʾ��λ
    void showSeat(const FilmsInfo& film);
    // �Ƚ�ʱ��
    bool cmpTime(const Ticket& ticket);
    // ��ȡ�û���Ϣ
    void userRead(std::string name);
    // �����û���Ϣ
    void userSave();
    // �û���ӰƱ����
    static bool tcmp(const Ticket& a, const Ticket& b);
    // ����<< ���Ʊ��Ϣ
    friend std::ostream& operator<<(std::ostream& os, const Ticket& ticket);

   public:
    // ����ѡ��
    void menuChoice();
    // ��ʾ�ɹ����Ӱ ���ص�һ������ϵͳʱ��ĵ�Ӱ�±�
    int showFInfo();
    // ע��
    void signUp();
    // ��½
    std::string login();
    // ��Ʊ
    void book();
    // ��Ʊ
    void refund();
    // ��ӡ��ӰƱ
    void printTicket(const Ticket& ticket);
};