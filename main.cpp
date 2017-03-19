#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include "Notice.h"

#define RANDOMMELODY TRUE //Generation of random melody by notification

/*
To implement:
Creation of config file with explaionation how to use one
*/

using namespace std;

int readConfig(Notice**);

void tabulation(char[], boolean*);

void log(char[]);

HWND GetConsoleHwnd();

void fnExit (void)
{
    log("Program ended work");
}

int main() {
    atexit(fnExit);
    HWND handlerToWindow = GetConsoleHwnd();
    char establishedTime[6];
    char lastEstablishedTime[6];
    int muteSounds = 0;
    boolean timeWasShown = TRUE;
    boolean flash = FALSE;
    time_t timeT = time(NULL);
    Notice *top;
    Notice *current;
    top = NULL;
    log("Program started work");

    //SetConsoleTitle(pszNewWindowTitle);
    system("title Notifier 0.11.6 by Nikdoge&color 03"); //&color f0
    strftime(establishedTime, 6, "%H:%M", localtime(&timeT));
    strcpy(lastEstablishedTime, establishedTime);
    cout << establishedTime << ' ' << "Program started" << '\n' << '\n';
    cout << "     " << ' ' << "Press R to reload config file" << '\n';
    cout << "     " << ' ' << "Press O to open config file" << '\n';
    cout << "     " << ' ' << "Press M to turn sounds off (for 6 hours) or on" << '\n';
    cout << "     " << ' ' << "Press Esc to exit safely" << '\n' << endl;
    readConfig(&top);
    
    /*
    To implement:
    Rusification

    short int i,datasize=13,cop;
    char **firstdata=new char*[datasize];
    for(i=3; i<datasize; i++)
        firstdata[i-3]=new char[80];
    firstdata[3]="В заданное время Alarmclock запускает воспроизведение";
    firstdata[4]="файла 'alarm.mp3' из папки, где расположен Alarmclock.exe";
    firstdata[5]="Введите время будильника:";
    firstdata[6]="После ввода нажмите \tEnter";
    firstdata[7]="Ошибка: Невозможно найти файл 'alarm.mp3'!";
    firstdata[8]="Системное время:";
    firstdata[9]="Перезагрузить настройки \tR";
    firstdata[10]="Открыть настройки \tO";
    firstdata[11]="Выйти из программы \tEsc";
    firstdata[12]="Активация";
    char **data=new char*[datasize];
    for(i=0; i<datasize; i++)
        data[i]=new char[80];
    for(i=3; i<datasize; i++)CharToOem(firstdata[i],data[i]);
    for(i=0; i<datasize; i++)delete[]firstdata[i];
    data[0]="title Alarmclock 4.1 by NIKDOG&color f0";
    data[1]="cls";
    data[2]="alarm.mp3";
    system(data[0]);
    */
    
    do {
        //Waiting for a moment, when last established time will differ from time of last notify call
        while (!strcmp(establishedTime, lastEstablishedTime)) {
            /*
            Checking for pressure of keys
            R - Reload of config file readConfig(&top);
            O - Open config file system("notice_config.txt");
            M - Mute sounds
            Esc - Escape from program (safe deletion of data from heap)
            */
            if (kbhit())
                switch (getch()) {
                    case 'r':
                    case 'R':
                    case 170: //к
                    case 138: //К
                    {
                        tabulation(establishedTime, &timeWasShown);
                        cout << "Reloading config" << endl;
                        readConfig(&top);
                        break;
                    }
                    case 'o':
                    case 'O':
                    case 233: //щ
                    case 153: //Щ
                    {
                        tabulation(establishedTime, &timeWasShown);
                        cout << "Opening config file" << '\n' << endl;
                        system("start Notifier.txt");
                        break;
                    }
                    case 27: //Esc
                    {
                        // deletion START
                        do {
                            current = top;
                            top = current->getNext();
                            delete current;
                        }
                        while (top);
                        // deletion END
                        return 0;
                    }
                    case 'm':
                    case 'M':
                    case 236: //ь
                    case 156: //Ь
                    {
                        if (muteSounds == 0) {
                            muteSounds = 360; // After which time sound must be turned on again (360 min = 6 hours)
                            tabulation(establishedTime, &timeWasShown);
                            cout << "Sounds: OFF" << '\n' << endl;
                            log("Sound was turned off");
                        }
                        else {
                            muteSounds = 0;
                            tabulation(establishedTime, &timeWasShown);
                            cout << "Sounds: ON\a" << '\n' << endl;
                            log("Sound was turned on");
                        }
                    }
                        break;
                    default: {
                        tabulation(establishedTime, &timeWasShown);
                        cout << "Undefined key pressed\a" << '\n' << endl;
                    }
                }
            if(flash == TRUE) //Flashing, if there was unread notifies (if user didn't open window)
            {
                if(handlerToWindow != GetForegroundWindow())FlashWindow(handlerToWindow,true); //IsIconic();
                else flash = FALSE;
            }
            Sleep(500);
            timeT = time(&timeT);
            strftime(establishedTime, 6, "%H:%M", localtime(&timeT));
        }
        //Saving of current time as time of last notify call
        strcpy(lastEstablishedTime, establishedTime);
        timeWasShown = 0;

        current = top;
        do {
            if (current->call(establishedTime)) {
                tabulation(establishedTime, &timeWasShown);
                cout << current->getTitle() << endl;
            }
            current = current->getNext();
        }
        while (current);

        if (timeWasShown) //If at least one notify was shown
        {
            if (muteSounds == 0) {
                if (RANDOMMELODY == TRUE) {
                    for (int i = 0; i < 5; i++) {
                        switch (rand() % 5) {
                            case 0:
                                Beep(1300, 400);
                                break;
                            case 1:
                                Beep(1200, 200);
                                break;
                            case 2:
                                Beep(1300, 200);
                                break;
                            case 3:
                                Beep(1500, 200);
                                break;
                            case 4:
                                Beep(1300, 400);
                                break;
                        }
                    }
                }
                else {
                    Beep(1300, 400);
                    Beep(1200, 200);
                    Beep(1300, 200);
                    Beep(1300, 200);
                    Beep(1300, 400);
                }

            }
            cout << endl;
            flash = TRUE;
        }
        if (muteSounds > 0) //If mute timer value is positive
        {
            muteSounds--;
            if(muteSounds == 0) log("Sound was turned on automatically");
        }
    } while (true);
}

int readConfig(Notice **top) {
    char buffer[255];
    boolean isWait;
    //boolean isNumber;
    Notice *current;
    FILE *file = fopen("Notifier.txt", "r");
    if (!file) {
        cout << "     " << ' ' << "Cannot open config file" << endl;
        fclose(file);

        file = fopen("Notifier.txt", "w");
        if (!file) {
            cout << "     " << ' ' << "Cannot create config file" << endl;
            fclose(file);
        } else {
            cout << "     " << ' ' << "Creating example config file" << endl;
            fprintf(file, "2 First example\n");
            fprintf(file, "12:00 Second example");
            fclose(file);

            file = fopen("Notifier.txt", "r");
            if (!file) {
                cout << "     " << ' ' << "Cannot open config file" << endl;
                fclose(file);
            } else {
                cout << "     " << ' ' << "Change example config file by pressing O!" << endl;
            }
        }
    }
    if (!file)return 0;

    // deletion START
    while (*top) {
        current = *top;
        *top = current->getNext();
        delete current;
    }
    // deletion END

    do {
        current = new Notice(*top);
        int j = 0;
        isWait = TRUE;

        //Reading time parameter of notify (time or time period)
        do {
            buffer[j] = (char)fgetc(file);
            if (buffer[j] == ':') {
                //if(isWait == FALSE)break;
                isWait = FALSE; //Dumb check, if readed value is number of minutes or time in HH:MM format
            }
            j++;
        }while (!feof(file) && buffer[j - 1] != ' ' && buffer[j - 1] != '\n' && j < 10);
        if(buffer[j - 1] == '\n'){
            delete current;
            continue;
        }
        buffer[j - 1] = '\0';
        //|| (isWait == FALSE && !(atoi(&buffer[0]) && atoi(&buffer[1]) && buffer[2] == ':' && atoi(&buffer[3]) && atoi(&buffer[4])))
        if (!(j < 9 && strlen(buffer) > 0 &&
                (isWait == TRUE || (isWait == FALSE &&
                        (strlen(buffer) == 5 || strlen(buffer) == 4))))) {
            delete current;
            buffer[0] = ' ';
            while(!feof(file) && buffer[0] != '\n')buffer[0] = (char)fgetc(file); //Переход к следующей строке
            continue;
        }
        if (isWait == TRUE )current->setWait(atoi(buffer));
        else current->setTime(buffer);

        j = 0;
        do  //Reading notify message
        {
            buffer[j] = (char)fgetc(file);
            j++;
        }
        while (!feof(file) && buffer[j - 1] != '\n' && j < 255);
        buffer[j - 1] = '\0';
        current->setTitle(buffer);

        /*
        To implement:
        Checking data adequacy 
        */
        *top = current;
        current = NULL;
    }
    while (!feof(file));
    fclose(file);

    cout << "     " << ' ' << "Successfully loaded:" << endl;
    current = *top;
    do {
        if (current->getWait() == -1)
            cout << "     " << ' ' << "At " << current->getTime() << " \"" << current->getTitle() << "\"" << endl;
        else
            cout << "     " << ' ' << "Every " << current->getWait() << " minute(s) \"" << current->getTitle() <<
            "\"" << endl;

        current = current->getNext();
    }
    while (current);
    cout << endl;
    return 1;
}

void tabulation(char establishedTime[], boolean *timeWasShown) {
    if (*timeWasShown == 0) {
        cout << establishedTime << ' ';
        *timeWasShown = TRUE;
    } else cout << "     " << ' ';
}

void log(char message[]) {
    int currentTimeLenght = 25;
    char currentTime[currentTimeLenght];
    time_t timeT = time(NULL);
    strftime(currentTime, (size_t)currentTimeLenght, "%Y-%m-%d %H:%M:%S", localtime(&timeT)); //%H:%M:%S

    ofstream file;
    file.open("Notifier.log", ios_base::app);
    if(file.is_open()) {
        file << '[';
        file << currentTime;
        file << ']' << ' ';
        file << message;
        file << '\n';
    }
    file.close();
}

//Source: https://support.microsoft.com/en-us/kb/124103
HWND GetConsoleHwnd(void)
{
    int MY_BUFSIZE = 1024; // Buffer size for console window titles.
    HWND hwndFound;         // This is what is returned to the caller.
    char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
    // WindowTitle.
    char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
    // WindowTitle.

    // Fetch current window title.
    GetConsoleTitle(pszOldWindowTitle, (DWORD)MY_BUFSIZE);

    // Format a "unique" NewWindowTitle.
    wsprintf(pszNewWindowTitle,"%d/%d",
             GetTickCount(),
             GetCurrentProcessId());

    // Change current window title.
    SetConsoleTitle(pszNewWindowTitle);

    // Ensure window title has been updated.
    Sleep(40);

    // Look for NewWindowTitle.
    hwndFound = FindWindow(NULL, pszNewWindowTitle);

    // Restore original window title.
    SetConsoleTitle(pszOldWindowTitle);

    return(hwndFound);
}
