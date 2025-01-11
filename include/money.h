#ifndef MONEY_H
#define MONEY_H

#include "header.h"

/**
 * @brief controlla se una transazione è fattibile
 * 
 * @param acc l'account su cui effetuare la verifica
 * @param moneyAmount la quantita di denaro
 * @return true esito positivo
 * @return false esito negativo
 */
bool isTransactionPossible(currentAccount acc, float moneyAmount);

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
bool moveMoney(User buyer, User seller, float moneyAmount, float moneyAmountSeller);

/**
 * @brief muove il contante dell'utente presso il conto del venditore del concerto
 * 
 * @param c il concerto
 * @param moneyAmount la quantita di denaro
 * @return true esito positivo
 * @return false esito negativo
 */
bool moveCash(Concert c, float moneyAmount);

/**
 * @brief crea un nuovo conto corrente e compila le informazioni
 * 
 * @param name nome
 * @param surname cognome
 * @return currentAccount l'account bancario
 */
currentAccount newCurrentAccount(char *name, char *surname);

/**
 * @brief aggiunge una carta di credito ad un conto corrente
 * 
 * @param cA il conto corrente
 * @param name nome
 * @param surname cognome
 * @return true esito positivo
 * @return false esito negativo
 */
bool addCreditCard(currentAccount cA, char *name, char *surname);

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
bool payWithCreditCard(User seller, User buyer, creditCard card, float moneyAmount, float moneyAmountSeller, bool autoCompilation);

#endif 