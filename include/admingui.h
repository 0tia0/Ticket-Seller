#ifndef ADMINGUI_H
#define ADMINGUI_H

#include "header.h"
#include "text.h"
#include "boxes.h"

/**
 * @brief funzione che permette ad un admin di creare un nuovo concerto
 * 
 * @return true se la procedura va a buon fine
 * @return false se la procedura incappa in qualche errore
 */
bool addConcert();

/**
 * @brief permette all'admin di scegliere che tipo di azione svolgere
 * 
 * @param user l'account admin
 */
void mainAdminMenu(User user);

/**
 * @brief permette all'admin di scegliere che tipo di interfaccia visualizzare
 * 
 * @return int il tipo di menu scelto
 */
int adminOrUSer();

#endif 