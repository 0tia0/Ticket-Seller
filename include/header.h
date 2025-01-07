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

/*
    Structs
*/

typedef struct
{
    int username;
    int type;
    char pass[25];
    bool auth;
} User;
 
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
} creditCard;

typedef struct
{
    char name[50];
    char surname[50];

    float avaibleMoney;
    char IBAN[34];

    creditCard associatedCards[5];
} currentAccount;

typedef struct
{
    time_t concertDate;
    time_t preSale;

    char name[50];
    bool soldOut;

    int maxTicket;
    int remaingTicket;

    Price fullPrice;
    Price underPrice;
    Price overPrice;

    currentAccount seller;
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
#define BOX_WIDTH 60

#define MAX_CONCERT_AVAIBLE 10

#define UP_ARROW 72
#define DOWN_ARROW 80
#define ENTER_KEY 13
#define ESC_KEY 27

/*
     Global Variables (declaration only)
*/

extern int AVAIBLE_CONCERT;
extern Concert concertList[MAX_CONCERT_AVAIBLE];

#endif