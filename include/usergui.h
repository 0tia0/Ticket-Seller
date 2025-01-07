#ifndef USERGUI_H
#define USERGUI_H

#include "header.h"
#include "text.h"

/**
 * @brief stampa la schermata di benvenuto
 * 
 * @param time la durata del caricamento emulato
 */
void printWelcomeScreen(int time);

/**
 * @brief stampa un Menu per la richiesta delle credenziali
 * 
 * @param u un puntatore ad una struttura User dove salvare i dati
 */
void checkLoginCredentials(User *u);

/**
 * @brief stampa un Menu per la scelta del concerto
 * 
 * @param c un puntatore ad una struttura Concert dove salvare i dati
 */
void selectConcert(Concert *c);

/**
 * @brief stampa un Menu per richiedere la quantità di biglietti desiderata
 * 
 * @param c il concerto di cui si vogliono acquistare i biglietti
 * @return int il numero di biglietti inseriti, compresi nel range messo a disposizione dal venditore
 */
int ticketSelection(Concert *c);

/**
 * @brief stampa diversi Menu per permettere all'utente di compilare i dati legali dei propri biglietti
 * 
 * @param amount il numero di biglietti acquistati
 * @param c la struttura Concert con le informazioni del concerto scelto
 * @return Ticket* ritorna la lista di strutture Ticket contenenti le varia inforamzioni
 */
Ticket *compileTicketInformation(int amount, Concert c);

/**
 * @brief stampa un Menu per chiedere che tipo di pagamento si desidera utilizzare
 * 
 * @return PAYMENT_TYPE il tipo di pagamento scelto;
 */
int askForPaymentType();

/**
 * @brief stampa un Menu per richedere i dati utili ad effeturare il pagamento + verifica di essi
 * 
 * @param type il tipo di pagamento scelto in precedenza
 */
int askForPaymentData(int type);

bool manageCashPayment(float ticketsPrice, Concert *c);
bool manageCardPayment();
bool manageBonificoPayment();

#endif 