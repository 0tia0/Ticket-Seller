#ifndef MONEY_H
#define MONEY_H

#include "header.h"

bool isTransactionPossible(currentAccount *acc, float moneyAmount);

bool moveMoney(currentAccount *buyer, currentAccount *seller, float moneyAmount);

bool moveCash(Concert *c, float moneyAmount);

#endif 