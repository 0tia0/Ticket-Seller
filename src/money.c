#include "money.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

///////////////////////////////
//  NON VISIBILE DALL'HEADER //
///////////////////////////////

/**
 * @brief aggiunge una carta di credito ad un conto corrente
 *
 * @param cA il conto corrente
 * @param name nome
 * @param surname cognome
 * @return true esito positivo
 * @return false esito negativo
 */
creditCard createCreditCard(char *name, char *surname, char *IBAN)
{
    creditCard cC;

    // Genera la data di scadenza (5 anni nel futuro)
    time_t today = time(NULL);
    struct tm *today_tm = localtime(&today);
    sprintf(cC.EXPIRE_DATE, "%02d/%d", today_tm->tm_mon + 1, today_tm->tm_year + 1900 + 5);

    // Copia nome e cognome
    strncpy(cC.name, name, sizeof(cC.name) - 1);
    cC.name[sizeof(cC.name) - 1] = '\0'; // Assicurati che la stringa sia terminata

    strncpy(cC.surname, surname, sizeof(cC.surname) - 1);
    cC.surname[sizeof(cC.surname) - 1] = '\0'; // Assicurati che la stringa sia terminata

    // Genera il numero di carta di credito
    srand(time(NULL)); // Inizializza il generatore di numeri casuali

    // Prefisso della carta (MasterCard, ad esempio)
    cC.CARD_NUMBER[0] = '5';
    cC.CARD_NUMBER[1] = '3';

    cC.CARD_NUMBER[2] = IBAN[6];
    cC.CARD_NUMBER[3] = IBAN[8];

    // Genera le restanti 12 cifre casuali
    for (int i = 4; i < 16; i++)
    {
        cC.CARD_NUMBER[i] = '0' + (rand() % 10);
    }
    cC.CARD_NUMBER[16] = '\0'; // Assicurati che la stringa sia terminata

    // Genera il CVC (tra 100 e 999)
    cC.CVC = rand() % 900 + 100;

    return cC;
}

/**
 * @brief genera numeri partendo da due stringa utilizza per creare un iban da nome e cognome
 * 
 * @param str1 nome
 * @param str2 cognome
 * @param output i numeri
 */
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

/**
 * @brief crea un iban basandosi su nome e cognome
 * 
 * @param name nome 
 * @param surname cognome
 * @return char* ritorna l'IBAN
 */
char *createIBAN(char *name, char *surname)
{   
    // Alloca memoria per salvare l'IBAN
    char *IBAN = malloc(28);
    if (!IBAN)
    {
        fprintf(stderr, "Errore di allocazione memoria.\n");
        exit(1);
    }

    // Inizializza la generazione dei numeri
    srand(time(NULL));

    // Prefisso ITaliano
    IBAN[0] = 'I';
    IBAN[1] = 'T';

    // Le classiche prime due cifre casuali
    IBAN[2] = '0' + (rand() % 10);
    IBAN[3] = '0' + (rand() % 10);

    // Codice ABI univoco della banca
    for (int i = 4; i < 9; i++)
    {
        IBAN[i] = '0' + (rand() % 10);
    }

    // Codice CAB
    for (int i = 9; i < 14; i++)
    {
        IBAN[i] = '0' + (rand() % 10);
    }

    // Genera le cifre mancanti basandosi sul nome e cognome
    generateCountNumber(name, surname, IBAN);

    // Terminatore di stringa
    IBAN[26] = '\0';

    return IBAN;
}

///////////////////////////
//  VISIBILE DALL'HEADER //
///////////////////////////

/**
 * @brief controlla se una transazione è fattibile
 *
 * @param acc l'account su cui effetuare la verifica
 * @param moneyAmount la quantita di denaro
 * @return true esito positivo
 * @return false esito negativo
 */
bool isTransactionPossible(currentAccount acc, float moneyAmount)
{
    if (acc.avaibleMoney - moneyAmount >= 0)
    {
        return true;
    }

    return false;
}

/**
 * @brief muove una somma di denaro fra due conti
 *
 * @param buyer il compratore
 * @param seller il venditore
 * @param moneyAmount la quantita di denaro
 * @param moneyAmountSeller la quantita di denaro scalata al venditore
 * @return true esito positivo
 * @return false esito negativo
 */
bool moveMoney(User buyer, User seller, float moneyAmount, float moneyAmountSeller)
{
    int buyerIndex = buyer.index;
    int sellerIndex = seller.index;

    if (isTransactionPossible(buyer.cA, moneyAmount))
    {
        userList[buyerIndex].cA.avaibleMoney -= moneyAmount;
        userList[sellerIndex].cA.avaibleMoney += moneyAmountSeller;
        saveData(concertFile, userFile);

        return true;
    }

    return false;
}

/**
 * @brief muove il contante dell'utente presso il conto del venditore del concerto
 *
 * @param c il concerto
 * @param moneyAmount la quantita di denaro
 * @return true esito positivo
 * @return false esito negativo
 */
bool moveCash(Concert c, float moneyAmount)
{
    int sellerIndex = c.seller.index;

    userList[sellerIndex].cA.avaibleMoney += moneyAmount;
    saveData(concertFile, userFile);

    return true;
}

/**
 * @brief crea un nuovo conto corrente e compila le informazioni
 *
 * @param name nome
 * @param surname cognome
 * @return currentAccount l'account bancario
 */
currentAccount newCurrentAccount(char *name, char *surname)
{
    currentAccount cA;

    sprintf(cA.name, "%s", name);
    sprintf(cA.surname, "%s", surname);

    sprintf(cA.IBAN, "%s", createIBAN(name, surname));

    cA.avaibleMoney = 0;
    cA.associatedCard = createCreditCard(name, surname, cA.IBAN);

    return cA;
}

/**
 * @brief paga utilizzando la carta di credito fornendo due modalita autompilazione o manuale
 *
 * @param seller account del venditore
 * @param buyer account del compratore
 * @param card dati inseriti manualmente di una carta di credito
 * @param moneyAmount la quantita di denaro
 * @param moneyAmountSeller la quantita di denaro scalata al venditore
 * @param autoCompilation se vero autocompila i dati usando la carta del compratore
 * @return true esito positivo
 * @return false esito negativo
 */
bool payWithCreditCard(User seller, User buyer, creditCard card, float moneyAmount, float moneyAmountSeller, bool autoCompilation)
{
    int buyerIndex = buyer.index;
    int sellerIndex = seller.index;

    if (isTransactionPossible(buyer.cA, moneyAmount))
    {
        // Effetua l'operazione se possibile
        if (autoCompilation)
        {
            // Auto compilazione
            moveMoney(buyer, seller, moneyAmount, moneyAmountSeller);
            return true;
        }
        else
        {
            for (int i = 0; i < userList; i++)
            {
                // Manuale
                if (userList[i].cA.associatedCard.CARD_NUMBER == card.CARD_NUMBER && userList[i].cA.associatedCard.EXPIRE_DATE == card.EXPIRE_DATE && userList[i].cA.associatedCard.CVC == card.CVC)
                {
                    moveMoney(userList[i], seller, moneyAmount, moneyAmountSeller);
                    return true;
                }
            }
        }
    }

    return false;
}