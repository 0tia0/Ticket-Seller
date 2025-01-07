#ifndef BOXES_H
#define BOXES_H

#include "header.h"

/**
 * @brief stampa il lati del box
 */
void printBoxSide();

/**
 * @brief stampa la parte superio del box
 */
void printBoxLines();
 
/**
 * @brief stampa diverse linee di testo centrate in un box
 *
 * @param text le linee da stampare
 * @param lineCount la quantita delle linee
 */
void printBox(const char *text[], int lineCount);

#endif