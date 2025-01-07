#include "admingui.h"
#include "header.h"
#include "text.h"
#include "boxes.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

time_t convertToTimeT(char *dateStr)
{
    struct tm timeStruct;
    int day, month, year;

    dateStr[strcspn(dateStr, "\n")] = '\0';
    sscanf(dateStr, "%2d/%2d/%4d", &day, &month, &year);

    timeStruct.tm_mday = day;
    timeStruct.tm_mon = month - 1; 
    timeStruct.tm_year = year - 1900;

    time_t timeValue = mktime(&timeStruct);
    return timeValue;
}

bool addConcert(currentAccount seller)
{
    Concert concert;
    concert.soldOut = false;

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

    char concertDate[10];

    leaveBlankLine();
    printBoxLines();
    printText("Inserire la data [dd/mm/yyyy]?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(concertDate, sizeof(concertDate) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(concertDate);

    concert.concertDate = convertToTimeT(concertDate);

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

    leaveBlankLine();
    printBoxLines();
    printText("Quanti ticket possono essere acquistati insieme?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &concert.maxTicket);

    leaveBlankLine();
    printBoxLines();
    printText("Quanti ticket sono disponibili?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &concert.remaingTicket);
    fflush(stdin);

    Price under, over, normal;

    leaveBlankLine();
    printBoxLines();
    printText("Inserire il prezzo del biglietto completo?", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%f", &normal.price);
    fflush(stdin);

    normal.age = 0;

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

    concert.fullPrice = normal;
    concert.underPrice = under;
    concert.overPrice = over;

    concert.seller = seller;

    concertList[AVAIBLE_CONCERT] = concert;
    AVAIBLE_CONCERT++;

    saveData(concertFile, userFile);
}

void mainAdminMenu(currentAccount account)
{
    const char *options[] = {
        "Verificare il conto corrente",
        "Creare un concerto",
    };
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    switch (newMenu("Cosa desidera fare:", options, lineCount1, &count) - 1)
    {
    case 0:
        //return Login();
        break;
    case 1:
        addConcert(account);
        break;
    }
}
