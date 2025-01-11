#include "admingui.h"
#include "header.h"
#include "text.h"
#include "boxes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

///////////////////////////////
//  NON VISIBILE DALL'HEADER //
///////////////////////////////

/**
 * @brief stampa a schermo le inforamzioni del concerto
 * 
 * @param c il concerto interessato
 * @param justCreated aggiunge un'ulteriore stringa se è appena stato creato
 */
void concertInfo(Concert c, bool justCreated)
{
    clearScreen();

    // Se appena creato aggiunge la stringa sottostante
    if (justCreated)
    {
        printBoxLines();
        printText("Concerto creato con successo", false, CENTER);
        printBoxLines();

        leaveBlankLine();
    }

    printBoxLines();

    // Nome e autore del concerto
    printText("Concerto:", false, CENTER);
    printText(c.name, false, CENTER);
    printText("", false, CENTER);

    // Date del concerto
    time_t presale = c.preSale;
    time_t concert = c.concertDate;
    char dateBuffer[20];

    // Data del concerto
    struct tm *concertTm = localtime(&concert);
    strftime(dateBuffer, sizeof(dateBuffer), "%d/%m/%Y", concertTm);
    printText("Data del concerto:", false, CENTER);
    printText(dateBuffer, false, CENTER);

    // Data della prevendita
    struct tm *presaleTm = localtime(&presale);
    strftime(dateBuffer, sizeof(dateBuffer), "%d/%m/%Y", presaleTm);
    printText("Prevendita disponibile da:", false, CENTER);
    printText(dateBuffer, false, CENTER);

    printText("", false, CENTER);

    // Stato Sold Out o no
    printText("Stato del concerto:", false, CENTER);
    printText(c.remaingTicket == 0 ? "Sold Out" : "Disponibile", false, CENTER);

    printText("", false, CENTER);

    // Biglietti disponibili 
    char ticketsBuffer[50];
    snprintf(ticketsBuffer, sizeof(ticketsBuffer), "Biglietti acquistabili in un ordine: %d", c.maxTicket);
    printText(ticketsBuffer, false, CENTER);

    snprintf(ticketsBuffer, sizeof(ticketsBuffer), "Biglietti rimanenti: %d", c.remaingTicket);
    printText(ticketsBuffer, false, CENTER);

    printText("", false, CENTER);

    // Prezzi
    char priceBuffer[50];
    snprintf(priceBuffer, sizeof(priceBuffer), "Prezzo intero: %.2f EUR", c.fullPrice.price);
    printText(priceBuffer, false, CENTER);

    snprintf(priceBuffer, sizeof(priceBuffer), "Prezzo ridotto (<%d anni): %.2f EUR", c.underPrice.age, c.underPrice.price);
    printText(priceBuffer, false, CENTER);

    snprintf(priceBuffer, sizeof(priceBuffer), "Prezzo over (>%d anni): %.2f EUR", c.overPrice.age, c.overPrice.price);
    printText(priceBuffer, false, CENTER);

    printBoxLines();

    printf("\n\nPremi un tasto per continuare...");
    getch();
}

/**
 * @brief converte una stringa di testo in un time_t
 * 
 * @param dateStr stringa con la data
 * @return time_t struttura con la data convertita
 */
time_t convertToTimeT(const char *dateStr)
{
    struct tm tm = {0};

    // Supponendo che la data sia nel formato "dd/mm/yyyy" maggiori controlli da implementare in futuro per ora blocca il programma
    if (sscanf(dateStr, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year) != 3)
    {
        // Gestisci errore di input
        return (time_t)(-1);
    }

    tm.tm_mon -= 1;
    // L'anno è rispetto al 1900 non allo 0 quindi sitemo sottraendo 1900
    tm.tm_year -= 1900; 

    // Converti la struttura tm in time_t
    return mktime(&tm);
}

/**
 * @brief permette ad un admin di visualizzare le informazioni di un concerto
 */
viewConcert()
{
    char *options[AVAIBLE_CONCERT];

    // Lista concerti
    for (int i = 0; i < AVAIBLE_CONCERT; i++)
    {
        options[i] = concertList[i].name;
    }

    int count = 0;

    //Visualizzazione informazioni del concerto scelto
    concertInfo(concertList[newMenu("Scegli un concerto:", options, AVAIBLE_CONCERT, &count) - 1], false);
}

///////////////////////////
//  VISIBILE DALL'HEADER //
///////////////////////////

/**
 * @brief permette all'admin di scegliere che tipo di interfaccia visualizzare
 * 
 * @return int il tipo di menu scelto
 */
int adminOrUSer()
{
    const char *options[] = {
        "Panello Amministratore",
        "Panello Utente"};
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    return newMenu("A cosa desidera accedere:", options, lineCount1, &count) - 1;
}


/**
 * @brief permette all'admin di scegliere che tipo di azione svolgere
 * 
 * @param user l'account admin
 */
void mainAdminMenu(User user)
{
    const char *options[] = {
        "Verificare il conto corrente",
        "Creare un concerto",
        "Visualizzare i concerti"};
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    switch (newMenu("Cosa desidera fare:", options, lineCount1, &count) - 1)
    {
    case 0:
        getAccountInformation(user);
        break;
    case 1:
        addConcert(user);
        break;
    case 2:
        viewConcert();
        break;
    }
}

/**
 * @brief funzione che permette ad un admin di creare un nuovo concerto
 * 
 * @return true se la procedura va a buon fine
 * @return false se la procedura incappa in qualche errore
 */
bool addConcert(User seller)
{
    Concert concert;
    concert.soldOut = false;

    // Nome e autore del concerto
    char name[25];
    char author[20];

    printBoxLines();
    printText("Inserire il nome del concerto [max 25 char]?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(name, sizeof(name) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(name);

    leaveBlankLine();
    printBoxLines();
    printText("Inserire l'autore del concerto [max 20 char]?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(author, sizeof(author) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(author);

    sprintf(concert.name, "%s <-> %s", name, author);

    // Data del concerto
    char concertDate[10];

    leaveBlankLine();
    printBoxLines();
    printText("Inserire la data [dd/mm/yyyy]?", false, CENTER);
    printText("(non usare lo zero per le cifre singole 05->5)", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fflush(stdin);
    fgets(concertDate, sizeof(concertDate) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(concertDate);

    concert.concertDate = convertToTimeT(concertDate);

    // Giorni di prevendita
    int ggPrevendita;

    leaveBlankLine();
    printBoxLines();
    printText("Quanti giorni prima deve comnciare la prevendita?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &ggPrevendita);
    fflush(stdin);

    ggPrevendita *= 86400;
    time_t preSale = concert.concertDate - ggPrevendita;

    concert.preSale = preSale;

    // Numero di ticket acquistabili in un solo ordine
    leaveBlankLine();
    printBoxLines();
    printText("Quanti ticket possono essere acquistati insieme?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &concert.maxTicket);

    // Ticket in vendita
    leaveBlankLine();
    printBoxLines();
    printText("Quanti ticket sono disponibili?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &concert.remaingTicket);
    fflush(stdin);

    // Creazione dei prezzi
    Price under, over, normal;

    // Completo
    leaveBlankLine();
    printBoxLines();
    printText("Inserire il prezzo del biglietto completo?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%f", &normal.price);
    fflush(stdin);

    normal.age = 0;

    // Under
    leaveBlankLine();
    printBoxLines();
    printText("Inserire il prezzo del biglietto ridotto (under)?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%f", &under.price);
    fflush(stdin);

    leaveBlankLine();
    printBoxLines();
    printText("Al di sotto di quale eta\'?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &under.age);
    fflush(stdin);

    // Over
    leaveBlankLine();
    printBoxLines();
    printText("Inserire il prezzo del biglietto ridotto (over)?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%f", &over.price);
    fflush(stdin);

    leaveBlankLine();
    printBoxLines();
    printText("Al di sopra di quale eta\'?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &over.age);
    fflush(stdin);

    // Scrittura e salvataggio dati
    concert.fullPrice = normal;
    concert.underPrice = under;
    concert.overPrice = over;

    concert.seller = seller;

    //Stampa le informaizoni prima di confermare la creazione stessa
    concertInfo(concert, true);
    
    concertList[AVAIBLE_CONCERT] = concert;
    AVAIBLE_CONCERT++;
    
    saveData(concertFile, userFile);
}