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
        if (ch == 8) {  // �����˸��ʱɾ��һ���ַ�
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
    cout << "VIP���ܹ�Ʊ�Żݣ��������99��\n";
    cout << "�Ƿ�ͨ����VIP(y/n)?��";
    if (deal.yesOrNo()) {
        cout << "�ȴ�֧��";
        deal.wait();
        cout << "\n--֧���ɹ�--\n";
        cout << "��ϲ���ɹ�Ϊ����VIP��ף����Ӱ��죡\n";
        cout << "--------------------------------\n";
        return true;
    } else {
        cout << "ȡ����ͨVIP��ף����Ӱ��죡\n";
        cout << "--------------------------------\n";
        return false;
    }
}

void User::showSeat(const FilmsInfo& film) {
    cout << "                         ---------" << endl;
    cout << "                         | �� Ļ |" << endl;
    cout << "                         ---------" << endl;
    cout << "     01�� 02�� 03�� 04�� 05�� 06�� 07�� 08�� 09�� 10�� " << endl;
    cout << "    ---------------------------------------------------" << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (j == 0) {
                if (i != 9) cout << "0";
                cout << i + 1 << "��|";
            }
            if (film.seat[i][j] == true) {
                cout << "[��]";
            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "[��]";
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
    str = "��";
    str += ticket.name;
    str += "��";
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
    str += (to_string(ticket.seat[0] + 1) + "��");
    if (ticket.seat[1] + 1 < 10) str += "0";
    str += (to_string(ticket.seat[1] + 1) + "��");
    os << setw(10) << str;

    if (ticket.play) {
        os << setw(8) << "����ӳ" << endl;
    } else {
        os << setw(8) << "δ��ӳ" << endl;
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
        cout << "       ��ǰû�пɹ����Ӱ\n";
        return -1;
    }
    deal.showFInfo(begin);
    return begin;
}

void User::signUp() {
    string menu{
        "            ---------\n"
        "            | ע �� |\n"
        "            ---------\n"
        "--------------------------------\n"};
    string warning{"����������\n--------------------------------\n"};
    system("cls");
    cout << menu;
    while (true) {
        string path;
        string id;
        string pw, repw;
        cout << "���û��������ո񣬲��ִ�Сд,0�˳���\n";
        cout << "�������û�����";
        getline(cin, id);
        if (id == "0") {
            cout << "--�˳�ע��--\n";
            cout << "-----------���������-----------" << endl;
            getch();
            return;
        }
        if (id == "admin") {
            system("cls");
            cout << menu;
            cout << "   ���û�������ע�ᣬ" << warning;
            continue;
        }
        if (id.find(' ') != string::npos) {
            system("cls");
            cout << menu;
            cout << "  �û������ɰ����ո�" << warning;
            continue;
        }
        path = "users\\" + id + ".dat";
        if (_access(path.c_str(), 0) == 0) {
            system("cls");
            cout << menu;
            cout << "   ���û����Ѵ��ڣ�" << warning;
            continue;
        }
        cout << "������6λ�������Ҳ����ո�\n";
        cout << "���������룺";
        pwInput(pw);
        if (pw.find(' ') != string::npos) {
            system("cls");
            cout << menu;
            cout << "    ���벻�ɰ����ո�" << warning;
            continue;
        }
        if (pw.size() < 6) {
            system("cls");
            cout << menu;
            cout << "   �������6λ�����ϣ�" << warning;
            continue;
        }
        cout << "���ٴ��������룺";  // ����ȷ��
        pwInput(repw);
        if (pw != repw) {
            system("cls");
            cout << menu;
            cout << "   �������벻һ�£�" << warning;
            continue;
        }
        cout << "����ע�ᣬ���Ժ�";
        deal.wait();
        cout << endl << id << " ע��ɹ���" << endl;
        uinfo.vip = membership();
        strcpy(uinfo.idName, id.c_str());
        strcpy(uinfo.password, pw.c_str());

        ofstream oFile{path, ios::binary | ios::trunc};
        oFile.write((char*)&uinfo, sizeof(UserInfo));
        oFile.close();
        cout << "-----------���������-----------" << endl;
        getch();
        return;
    }
}

string User::login() {
    string menu{
        "            ---------\n"
        "            | �� ½ |\n"
        "            ---------\n"
        "--------------------------------\n"};
    system("cls");
    cout << menu;
    while (true) {
        string id;
        string pw;
        string path;
        cout << "�������û���(0�˳�)��";
        getline(cin, id);
        if (id == "0") {
            cout << "--�˳���½--\n";
            cout << "-----------���������-----------" << endl;
            getch();
            return string{"-1"};
        }
        cout << "���������룺";
        pwInput(pw);
        if (id == "admin" && pw == "admin") {
            cout << "���ڵ�½�����Ժ�";
            deal.wait();
            cout << "\n��ӭ����Աadmin!" << endl;
            cout << "-----------�������ת-----------" << endl;
            getch();
            return string{"admin"};
        }
        path = "users\\" + id + ".dat";
        if (_access(path.c_str(), 0) != 0) {
            system("cls");
            cout << menu;
            cout << " �û������������\n";
            cout << "--------------------------------\n";
            continue;
        }
        ifstream iFile{path.c_str(), ios::binary | ios::in};
        iFile.read((char*)&uinfo, sizeof(UserInfo));
        if (strcmp(pw.c_str(), uinfo.password) == 0) {
            iFile.close();
            cout << "���ڵ�½�����Ժ�";
            deal.wait();
            cout << "\n��ӭ";
            if (uinfo.vip) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                cout << "VIP";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            cout << "�û���" << id << endl;
            cout << "-----------�������ת-----------" << endl;
            getch();
            userRead(id);
            return id;
        } else {
            iFile.close();
            system("cls");
            cout << menu;
            cout << " �û������������\n";
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
        cout << "�������Ӱ���(0�˳�)��";
        cin >> choice;
        if (choice == 0) {
            cout << "--�˳���Ʊ--\n";
            cout << "-----------���������-----------\n";
            getch();
            return;
        }
        choice = choice + begin - 1;
        if (choice < begin || choice > size) {
            cout << "��Ų����ڣ�����������\n";
            continue;
        }
        if (deal.finfo[choice].rest == 0) {
            cout << "�˵�Ӱ����������ѡ��������Ӱ\n";
            continue;
        }
        break;
    }
    showSeat(deal.finfo[choice]);
    cout << "��ɫ����Ϊ��ѹ�Ӱ�������֧��20%\n";
    while (true) {
        cout << "�Ƿ����ѡ��(y/n)��";
        if (!deal.yesOrNo()) {
            cout << "--�˳�ѡ��--\n";
            break;
        }
        cout << "��ѡ����λ(1 1)��";
        cin >> x >> y;
        cin.ignore();
        x--;
        y--;
        if (x < 0 || x > 9 || y < 0 || y > 9) {
            cout << "��λ������\n";
            continue;
        } else if (deal.finfo[choice].seat[x][y] == true) {
            cout << "�������ۣ���ѡ��������λ\n";
            continue;
        }
        // �Ƿ���ѹ�Ӱ��
        if (x >= 2 && x <= 5 && y >= 2 && y <= 7) {
            isBest = true;
            cout << "��ѡ��Ϊ " << x + 1 << "��" << y + 1
                 << "��������ѹ�Ӱ�������֧��20%" << endl;
            ticPrice = deal.finfo[choice].price * 1.2;
        } else {
            isBest = false;
            cout << "��ѡ��Ϊ " << x + 1 << "��" << y + 1 << "��\n";
            ticPrice = deal.finfo[choice].price;
        }
        if (uinfo.vip) {
            ticPrice = ticPrice * deal.finfo[choice].discount / 10;
            cout << "��ΪVIP�û���Ʊ�۴�" << deal.finfo[choice].discount
                 << "��\n";
        }
        cout << "Ʊ�ۣ�" << ticPrice << endl;
        if (!uinfo.vip) {
            uinfo.vip = membership();
            if (uinfo.vip) {
                ticPrice = ticPrice * deal.finfo[choice].discount / 10;
                cout << "����ͨ��VIP��Ʊ�۴�" << deal.finfo[choice].discount
                     << "��\n";
                cout << "Ʊ�ۣ�" << ticPrice << "��\n"; 
            }
        }
        cout << "�Ƿ�֧��(y/n)����";
        if (deal.yesOrNo()) {
            cout << "�ȴ�֧��";
            deal.wait();
            cout << "\n֧���ɹ�!\n";

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
            cout << "--ȡ��֧��--\n";
            continue;
        }
    }
    cout << "-----------���������-----------\n";
    getch();
    return;
}

void User::refund() {
    string menu = {
        "                                ----------\n"
        "                                | ��  Ʊ |\n"
        "                                ----------\n"
        "-----------------------------------------"
        "---------------------------------\n"};
    if (tic.size() == 0) {
        cout << "�����˻��޵�ӰƱ��Ϣ\n";
        cout << "-----------���������-----------\n";
        getch();
        return;
    }
    system("cls");
    cout << menu;
    cout << "������ĵ�ӰƱ���£�\n";
    cout << setiosflags(ios::left);
    cout << setw(6) << "���" << setw(16) << "��Ӱ��";
    cout << setw(12) << "����" << setw(7) << "ʱ��";
    cout << setw(6) << "����" << setw(6) << "�۸�";
    cout << setw(10) << "��λ" << setw(8) << "״̬" << endl;
    for (int i = 0; i < tic.size(); i++) {
        cout << setw(5) << i + 1;
        cout << tic[i];
    }
    cout << "-----------------------------------------"
            "---------------------------------\n";
    int choice;
    while (true) {
        cout << "--------------------------------\n";
        cout << "��������Ʊ���(0�˳�)��";
        cin >> choice;
        if (choice == 0) {
            cout << "--�˳���Ʊ--\n";
            cout << "-----------���������-----------\n";
            getch();
            return;
        }
        if (choice < 0 || choice > tic.size()) {
            cout << "��Ų�����\n";
            continue;
        }
        if (tic[--choice].play) {
            cout << "��Ʊ�ѹ��ڣ������˿�\n";
            continue;
        }
        break;
    }
    cout << "ȷ���˵���Ʊ(y/n)?��";
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
        cout << "��Ʊ�ɹ����˿�" << tit->price << "��\n";
        tic.erase(tit);
        deal.filmSave();
        userSave();
        cout << "-----------���������-----------\n";
        getch();
        return;
    } else {
        cout << "--ȡ����Ʊ--\n";
        cout << "-----------���������-----------\n";
        getch();
        return;
    }
}

void User::printTicket(const Ticket& ticket) {
    string fname = ticket.name;
    int i = 5 - fname.size() / 8;
    cout << "------------------------------------------------\n";
    cout << "���ڴ�ӡ��ӰƱ";
    deal.wait();
    cout << "\n------------------------------------------------\n";
    cout << "_________________________________________________\n";
    cout << "|                   C C H Ӱ ��                 |\n";
    cout << "|\t\t\t\t\t\t|\n";
    cout << "| Ƭ����" << fname;
    for (int j = 1; j <= i; j++) {
        cout << "\t";
    }
    cout << "|\n";
    cout << "| Ӱ����1����\t\tʱ�䣺";
    cout << ticket.year << "-" << ticket.month << "-" << ticket.day;
    cout << " " << ticket.hour << ":" << (ticket.minute == 0 ? "00" : "30")
         << "\t|\n";
    cout << "| ��λ��" << ticket.seat[0] << " �� " << ticket.seat[1] << "��\t";
    cout << "���ࣺ" << (ticket.isBest ? "�����" : "��ͨ��") << "\t\t|\n";
    cout << "| Ʊ�ۣ�";
    cout.precision(2);
    cout.setf(cout.showpoint | ios::fixed);
    cout << ticket.price << "��\t\t�û����ͣ�";
    cout << (uinfo.vip ? "VIP" : "��ͨ") << "\t\t|\n";
    cout << "|\t\t\t\t\t\t|\n";
    cout << "|                  �� Ӱ �� ��                  |\n";
    cout << "|              | |||| ||||| ||| ||              |\n";
    cout << "|              x xxxx xxxxx xxx xx              |\n";
    cout << "|_______________________________________________|\n";
    cout << "------------------------------------------------\n";
}
