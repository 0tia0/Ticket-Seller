#ifndef HEADER_H
#define HEADER_H

/*
    Libraries inclusion
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>

/*
    Structs
*/

typedef struct
{
    float price;
    int age;
} Price;

typedef struct
{
    float price;
    bool reduced;

    char name[50];
    char surname[50];
    int age;
} Ticket;

typedef struct
{
    char name[50];
    char surname[50];
    
    char CARD_NUMBER[16];
    int CVC;
    char EXPIRE_DATE[7];
} creditCard;

typedef struct
{
    char name[50];
    char surname[50];

    float avaibleMoney;
    char IBAN[27];

    creditCard associatedCard;
} currentAccount;

typedef struct
{
    currentAccount cA;

    char email[30];
    char name[30];
    char surname[30];
    char pass[25];

    bool admin;
    bool isValid;

    int index;
} User;

typedef struct
{
    time_t concertDate;
    time_t preSale;

    char name[50];
    bool soldOut;

    int maxTicket;
    int remaingTicket;
    int selledTicket;

    Price fullPrice;
    Price underPrice;
    Price overPrice;

    User seller;

    int index;
} Concert;

/*
    Enums
*/

enum TEXT_FORMAT
{
    LEFT,
    CENTER,
    RIGHT
};

enum PAYMENT_TYPE
{
    CASH,
    CREDIT_CARD,
    BONIFICO
};

/*
    Global definitions
*/

#define BOX_CHAR '-'
#define BOX_SIDE '#'
#define BOX_WIDTH 70

#define MAX_CONCERT_AVAIBLE 10

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER_KEY 13
#define ESC_KEY 27

#define SECRET_KEY 39

/*
     Global Variables (declaration only)
*/

extern int AVAIBLE_CONCERT;
extern Concert concertList[MAX_CONCERT_AVAIBLE];

extern int userAmount;
extern User userList[20];

extern const char *concertFile;
extern const char *userFile;


void saveData(const char *concertFile, const char *userFile);
void loadData(const char *concertFile, const char *userFile);

void removeNewline(char *str);

#endif