#ifndef FILE_H
#define FILE_H

#include "header.h"

/**
 * @brief salva una lista di strutture Concert all'interno di un file
 *  
 * @param fileName nome del file per il salvataggio dei dati
 * @param c lista dei concerti da salvare
 */
void saveConcertToFile(char *fileName, Concert *c);
 
/**
 * @brief carica una lista di strutture Concert da un file
 *  
 * @param fileName nome del file per la lettura dei dati
 * @param list lista dei concerti dove salvare i dati letti
 */
void loadConcertsFromFile(char *fileName, Concert *list);

/**
 * @brief conta quanti concerti sono presenti un file
 * 
 * @param fileName il file dove effetuare il controllo
 * @return int numero di concerti
 */
int countConcertsInFile(char *fileName);

#endif