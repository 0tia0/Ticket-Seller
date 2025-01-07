#include "money.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateCountNumber(const char *str1, const char *str2, char *output)
{
    int index = 14;

    for (size_t i = 0; i < 12; i++)
    {
        char char1 = (i < strlen(str1)) ? str1[i] : '0';
        char char2 = (i < strlen(str2)) ? str2[i] : '0';

        int combined = (char1 + char2) % 10;
        output[index++] = '0' + combined;
    }
}

char *createIBAN(char *name, char *surname)
{
    char *IBAN = malloc(28);
    if (!IBAN)
    {
        fprintf(stderr, "Errore di allocazione memoria.\n");
        exit(1);
    }

    srand(time(NULL));

    IBAN[0] = 'I';
    IBAN[1] = 'T';

    IBAN[2] = '0' + (rand() % 10);
    IBAN[3] = '0' + (rand() % 10);

    for (int i = 4; i < 9; i++)
    {
        IBAN[i] = '0' + (rand() % 10);
    }

    for (int i = 9; i < 14; i++)
    {
        IBAN[i] = '0' + (rand() % 10);
    }

    generateCountNumber(name, surname, IBAN);

    IBAN[26] = '\0';

    return IBAN;
}

creditCard createCreditCard(char *name, char *surname, char *IBAN) {
    creditCard cC;

    sprintf(cC.name, "%s", name);
    sprintf(cC.surname, "%s", surname);

    //MagiCard Prefix something like mastercard prefix 5 or visa 4
    cC.CARD_NUMBER[0] = 5;
    cC.CARD_NUMBER[1] = 3;
    cC.CARD_NUMBER[2] = 8;
    cC.CARD_NUMBER[3] = 2;

    for(int i = 0; i<12; i++) {
        cC.CARD_NUMBER[i+4] = IBAN[i+14];
    }

    return cC;
}

bool isTransactionPossible(currentAccount *acc, float moneyAmount)
{
    if (acc->avaibleMoney - moneyAmount >= 0)
    {
        return true;
    }

    return false;
}

bool moveMoney(currentAccount *buyer, currentAccount *seller, float moneyAmount)
{
    if (isTransactionPossible(buyer, moneyAmount))
    {
        buyer->avaibleMoney -= moneyAmount;
        seller->avaibleMoney += moneyAmount;

        return true;
    }

    return false;
}

bool moveCash(Concert *c, float moneyAmount)
{
    currentAccount *seller = &c->seller;
    seller->avaibleMoney += moneyAmount;

    return true;
}

currentAccount newCurrentAccount(char *name, char *surname)
{
    currentAccount cA;

    sprintf(cA.name, "%s", name);
    sprintf(cA.surname, "%s", surname);

    sprintf(cA.IBAN, "%s", createIBAN(name, surname));
    
    cA.avaibleMoney = 0;
    cA.associatedCards[0] = createCreditCard(name, surname, cA.IBAN);
}

bool payWithCreditCard(User u)
{
}