#ifndef TEXT_H
#define TEXT_H

#include "header.h"

/**
 * @brief stampa un testo all'interno di una box a carattere scelto con formattazione a scelta
 *
 * @param text il testo che la funzione deve stampare
 * @param externalCall se vero, il testo sarà stampato senza bordi
 */
void printText(const char *text, bool externalCall, int format);

/**
 * @brief pulisci il terminale
 */
void clearScreen();

/**
 * @brief lascia una linea vuota nel terminale
 */
void leaveBlankLine();

#endif 