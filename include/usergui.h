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
 * @brief stampa la schermata di benvenuto chiedendo di scegliere fra login e signup
 * 
 * @return User utente loggato
 */
User WelcomeScreen();

/**
 * @brief permette di effettuare il login
 *  
 * @return User utente loggato
 */
User Login();

/**
 * @brief permette di effettuare il signup e dopo il login
 * 
 * @return User utente loggato
 */
User SignUp();

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
int ticketSelection(Concert c);

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

/**
 * @brief Gestisce il pagamento in contanti per l'acquisto di biglietti.
 * 
 * @param ticketsPrice Il prezzo totale dei biglietti da pagare.
 * @param c La struttura Concert con le informazioni del concerto.
 * @param u La struttura User con le informazioni dell'utente che effettua il pagamento.
 * @return true Se il pagamento è stato completato con successo.
 * @return false Se il pagamento è fallito.
 */
bool manageCashPayment(float ticketsPrice, Concert c, User u);

/**
 * @brief Gestisce il pagamento con carta di credito per l'acquisto di biglietti.
 * 
 * @param ticketsPrice Il prezzo totale dei biglietti da pagare.
 * @param sellerProfit Il prezzo di guadagno in percentuale del venditore
 * @param c La struttura Concert con le informazioni del concerto.
 * @param u La struttura User con le informazioni dell'utente che effettua il pagamento.
 * @return true Se il pagamento è stato completato con successo.
 * @return false Se il pagamento è fallito.
 */
bool manageCardPayment(float ticketsPrice, float sellerProfit, Concert c, User u);

/**
 * @brief Gestisce il pagamento tramite bonifico bancario per l'acquisto di biglietti.
 * 
 * @param ticketsPrice Il prezzo totale dei biglietti da pagare.
 * @param sellerProfit Il prezzo di guadagno in percentuale del venditore
 * @param c La struttura Concert con le informazioni del concerto.
 * @param u La struttura User con le informazioni dell'utente che effettua il pagamento.
 * @return true Se il pagamento è stato completato con successo.
 * @return false Se il pagamento è fallito.
 */
bool manageBonificoPayment(float ticketsPrice, float sellerProfit, Concert c, User u);

/**
 * @brief Legge i dati di una carta di credito inseriti dall'utente.
 * 
 * @return creditCard Una struttura creditCard contenente i dati della carta inserita.
 */
creditCard readCreditCardData();

/**
 * @brief Recupera le informazioni dell'account dell'utente specificato.
 * 
 * @param user La struttura User con i dati dell'utente di cui si vogliono ottenere le informazioni.
 */
void getAccountInformation(User user);


#endif 