#ifndef MONEY_H
#define MONEY_H

#include "header.h"

bool isTransactionPossible(currentAccount *acc, float moneyAmount);

bool moveMoney(currentAccount *buyer, currentAccount *seller, float moneyAmount);

bool moveCash(Concert *c, float moneyAmount);

currentAccount newCurrentAccount(char *name, char *surname);

bool addCreditCard(currentAccount cA, char *name, char *surname);

bool payWithCreditCard(User u);

#endif 