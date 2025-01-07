#include "usergui.h"
#include "text.h"
#include "header.h"
#include "boxes.h"
#include "money.h"

/**
 * @brief stampa la schermata di benvenuto
 *
 * @param time la durata del caricamento emulato
 */
void printWelcomeScreen(int time)
{
    const char *welcomeScreen[] = {
        "Vendita dei biglietti",
        "",
        "MagiTicketer"};

    int lineCount = sizeof(welcomeScreen) / sizeof(welcomeScreen[0]);

    for (float i = time; i >= 0; i -= 0.5)
    {
        clearScreen();

        printBox(welcomeScreen, lineCount);
        leaveBlankLine();

        char buffer[30];
        snprintf(buffer, sizeof(buffer), "LOADING - TIME LEFT: %.1f", i);
        printText(buffer, true, CENTER);

        Sleep(time * 100);
    }
    system("cls");
}

/**
 * @brief stampa un Menu per la richiesta delle credenziali
 *
 * @param u un puntatore ad una struttura User dove salvare i dati
 */
void checkLoginCredentials(User *u)
{
    const char *login[] = {
        "Login",
        "",
        "devi effetuare il login prima",
        "di usare il sistema di ticket"};
    int lineCount0 = sizeof(login) / sizeof(login[0]); // Calcolo del numero di righe
    printBox(login, lineCount0);
    Sleep(3000);
    clearScreen();

    const char *options[] = {
        "Utente",
        "Venditore",
    };
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    u->type = newMenu("Esegui il login come:", options, lineCount1, &count) - 1;

    // Login Credentials checking will be implemented in a next version
    u->auth = true;
}

/**
 * @brief stampa un Menu per la scelta del concerto
 *
 * @param c un puntatore ad una struttura Concert dove salvare i dati
 */
void selectConcert(Concert *c)
{
    char *options[MAX_CONCERT_AVAIBLE];

    for (int i = 0; i < AVAIBLE_CONCERT; i++)
    {
        options[i] = concertList[i].name;
    }

    int count = 0;
    *c = concertList[newMenu("Scegli un concerto:", options, AVAIBLE_CONCERT, &count) - 1];
}

/**
 * @brief stampa un Menu per richiedere la quantità di biglietti desiderata
 *
 * @param c il concerto di cui si vogliono acquistare i biglietti
 * @return int il numero di biglietti inseriti, compresi nel range messo a disposizione dal venditore
 */
int ticketSelection(Concert *c)
{
    char question[50];
    int selection;

    sprintf(question, "Quanti biglietti si desiderano? (1-%d)", c->maxTicket);

    printBoxLines();
    printText(question, false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &selection);

    if (selection < 1 || selection > c->maxTicket)
    {
        clearScreen();
        ticketSelection(c);
    }

    return selection;
}

/**
 * @brief stampa diversi Menu per permettere all'utente di compilare i dati legali dei propri biglietti
 *
 * @param amount il numero di biglietti acquistati
 * @param c la struttura Concert con le informazioni del concerto scelto
 * @return Ticket* ritorna la lista di strutture Ticket contenenti le varia inforamzioni
 */
Ticket *compileTicketInformation(int amount, Concert c)
{
    Ticket *compiledTickets = malloc(amount * sizeof(Ticket));

    for (int i = 0; i < amount; i++)
    {
        char question[50];

        // TITOLO
        sprintf(question, "Biglietto N: %d", i + 1);

        printBoxLines();
        printText(question, false, CENTER);
        printBoxLines();

        leaveBlankLine();

        // RICHIESTA NOME
        printBoxLines();
        printText("Nome per il biglietto", false, CENTER);
        printBoxLines();

        printf("\n?:");
        fflush(stdin);
        scanf("%s", &compiledTickets[i].name);

        leaveBlankLine();

        // RICHIESTA COGNOME
        printBoxLines();
        printText("Cognome per il biglietto", false, CENTER);
        printBoxLines();

        printf("\n?:");
        fflush(stdin);
        scanf("%s", &compiledTickets[i].surname);

        leaveBlankLine();

        // RICHIESTA ETA
        printBoxLines();
        printText("Eta\' per il biglietto", false, CENTER);
        printBoxLines();

        printf("\n?:");
        fflush(stdin);
        scanf("%d", &compiledTickets[i].age);

        // AGGIUNTA PREZZI
        if (compiledTickets[i].age < c.underPrice.age)
        {
            compiledTickets[i].price = c.underPrice.price;
            compiledTickets[i].reduced = true;
        }
        else if (compiledTickets[i].age > c.overPrice.age)
        {
            compiledTickets[i].price = c.overPrice.price;
            compiledTickets[i].reduced = true;
        }
        else
        {
            compiledTickets[i].price = c.fullPrice.price;
            compiledTickets[i].reduced = false;
        }

        clearScreen();
    }

    return compiledTickets;
}

/**
 * @brief stampa un Menu per chiedere che tipo di pagamento si desidera utilizzare
 *
 * @return PAYMENT_TYPE il tipo di pagamento scelto;
 */
int askForPaymentType()
{
    const char *options[] = {
        "Contanti",
        "Carta di Credito",
        "Bonifico Bancario"};
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    return newMenu("Scegli il metodo di pagamento:", options, lineCount1, &count);
}

/**
 * @brief stampa un Menu per richedere i dati utili ad effeturare il pagamento + verifica di essi
 */
int askForPaymentData(int type)
{
    switch (type)
    {
    case CASH:
        /* code */
        break;
    case CREDIT_CARD:
        /* code */
        break;
    case BONIFICO:
        /* code */
        break;
    default:
        break;
    }
}

bool manageCashPayment(float ticketsPrice, Concert *c)
{
    const char *options[] = {
        "0.01 Euro",
        "0.02 Euro",
        "0.05 Euro",
        "0.10 Euro",
        "0.20 Euro",
        "0.50 Euro",
        "1 Euro",
        "2 Euro",
        "5 Euro",
        "10 Euro",
        "20 Euro",
        "50 Euro",
        "100 Euro"};
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;

    float givenMoney = 0;

    while (givenMoney < ticketsPrice)
    {
        char buffer[60];
        sprintf(buffer, "%s - Euro inseriti: %.2f / %.2f", "Inserisci moneta o banconota", givenMoney, ticketsPrice);

        switch (newMenu(buffer, options, lineCount1, &count) -1)
        {
        case 0:
            givenMoney += 0.01;
            break;
        case 1:
            givenMoney += 0.02;
            break;
        case 2:
            givenMoney += 0.05;
            break;
        case 3:
            givenMoney += 0.1;
            break;
        case 4:
            givenMoney += 0.2;
            break;
        case 5:
            givenMoney += 0.5;
            break;
        case 6:
            givenMoney += 1;
            break;
        case 7:
            givenMoney += 2;
            break;
        case 8:
            givenMoney += 5;
            break;
        case 9:
            givenMoney += 10;
            break;
        case 10:
            givenMoney += 20;
            break;
        case 11:
            givenMoney += 50;
            break;
        case 12:
            givenMoney += 100;
            break;
        default:
            break;
        }
    }

    if (givenMoney > ticketsPrice) {
        clearScreen();
        printBoxLines();
        printText("Raccogliere presso l'erogatore il resto", false, CENTER);
        printBoxLines();
        leaveBlankLine();
        printf("-> Resto erogato %.2f Euro", (givenMoney-ticketsPrice));
    }

    leaveBlankLine();
    moveCash(c, ticketsPrice);
} 