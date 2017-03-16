//
// Created by Nikdoge on 21.03.2016.
//

#ifndef NOTIFIER_NOTICE_H
#define NOTIFIER_NOTICE_H

#include <iostream>

using namespace std;

class Notice {

private:
    string title;
    char time[6];
    int wait;
    int counter;
    Notice *next;

public:
    Notice() {
        counter = 0;
        wait = -1;
        time[0] = '\0';
        next = 0;
    }

    Notice(Notice *notice_next) {
        counter = 0;
        wait = -1;
        time[0] = '\0';
        next = notice_next;
    }

    void temporalf() {
        cout << "DATA" << endl;
        cout << "TITLE : " << title << endl;
        cout << "WAIT : " << wait << endl;
        cout << "TIME : " << time << endl;
        if (next)cout << "NEXTTITLE : " << next->getTitle() << endl;
    }

    void setTitle(string notice_title) {
        title = notice_title;
    }

    string getTitle() {
        return title;
    }

    void setWait(int notice_wait) {
        wait = notice_wait;
    }

    int getWait() {
        return wait;
    }

    void setTime(char *notice_time) {
        strcpy(time, notice_time);
    }

    string getTime() {
        return string(time);
    }

    int call(char stm[]) {
        if (wait == -1) {
            if (!strcmp(stm, time))return 1;
            return 0;
        }
        counter++;
        if (wait == counter) {
            counter = 0;
            return 1;
        }
        return 0;
    }

    void setNext(Notice *notice_next) {
        next = notice_next;
    }

    Notice *getNext() {
        return next;
    }

    ~Notice() { }
};

#endif //NOTIFIER_NOTICE_H

