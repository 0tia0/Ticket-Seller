#include "money.h"

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