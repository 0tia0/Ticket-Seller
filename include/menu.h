#ifndef MENU_H
#define MENU_H

#include "header.h"

/**
 * @brief stampa un menu "a tendina" utilizzabile che permette all'utente di scegliere un valore in una lista
 * 
 * @param question la domanda da mettere al di sopra delle opzioni
 * @param text le opzioni
 * @param lineCount il numero di opzioni
 * @param count la conta del numero di volte che si ha inserito un output, puo essere un valore passato e inizializzato pari a 0
 * @return int la voce scelta nella listsa
 */
int newMenu(char *question, const char *text[], int lineCount, int *count);

#endif