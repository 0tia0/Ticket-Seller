#include "usergui.h"
#include "text.h"
#include "header.h"
#include "boxes.h"
#include "money.h"

///////////////////////////
//  VISIBILE DALL'HEADER //
///////////////////////////

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

//////////////
//  LOGIN   //
//////////////

/**
 * @brief stampa la schermata di benvenuto chiedendo di scegliere fra login e signup
 *
 * @return User utente loggato
 */
User WelcomeScreen()
{
    const char *options[] = {
        "Log In",
        "Sign Up",
    };
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    switch (newMenu("Cosa desideri fare:", options, lineCount1, &count) - 1)
    {
    case 0:
        return Login();
        break;
    case 1:
        return SignUp();
        break;
    }
}

/**
 * @brief permette di effettuare il login
 *
 * @return User utente loggato
 */
User Login()
{
    fflush(stdin);
    clearScreen();

    char email[30];
    char pass[25];
    int i;

    printBoxLines();
    printText("Inserire le proprie credenziali di login", false, CENTER);
    printBoxLines();

    leaveBlankLine();
    printBoxLines();
    printText("Indirizzo email di login", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(email, sizeof(email) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(email);

    leaveBlankLine();
    printBoxLines();
    printText("Indirizzo la password di login", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(pass, sizeof(pass) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(pass);

    for (i = 0; i < userAmount; i++)
    {
        if (strcmp(userList[i].email, email) == 0)
        {
            if (strcmp(userList[i].pass, pass) == 0)
            {
                clearScreen();
                printBoxLines();
                printText("Login avvenuto con successo", false, CENTER);
                printBoxLines();
                Sleep(2000);
                userList[i].isValid = true;
                return userList[i];
            }
        }
    }

    clearScreen();
    printBoxLines();
    printText("Credenziali errate!", false, CENTER);
    printBoxLines();
    Sleep(2000);

    User user = {0};
    return user;
}

/**
 * @brief permette di effettuare il signup e dopo il login
 *
 * @return User utente loggato
 */

User SignUp()
{
    fflush(stdin);
    clearScreen();

    User user;
    int temp;

    printBoxLines();
    printText("Benvenuto nella creazione account, compila le richieste", false, CENTER);
    printBoxLines();

    leaveBlankLine();
    printBoxLines();
    printText("Indirizzo email di login", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(user.email, sizeof(user.email) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(user.email);

    leaveBlankLine();
    printBoxLines();
    printText("Inserisci il tuo nome", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(user.name, sizeof(user.name) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(user.name);

    leaveBlankLine();
    printBoxLines();
    printText("Inserisci il tuo cognome", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(user.surname, sizeof(user.surname) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(user.surname);

    leaveBlankLine();
    printBoxLines();
    printText("Crea la password per l'account", false, CENTER);
    printText("attenzione sara\' visibile per non commettere errori", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(user.pass, sizeof(user.pass) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(user.pass);

    leaveBlankLine();
    printBoxLines();
    printText("Il tuo account sara\' admin?", false, CENTER);
    printText("se no inserisci 0, altrimenti il codice segreto", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &temp);
    fflush(stdin);

    if (temp == 0)
    {
        user.admin = false;
    }
    else if (temp = 29259357)
    {
        user.admin = true;
    }

    user.cA = newCurrentAccount(user.name, user.surname);

    clearScreen();
    printBoxLines();
    printText("Account creato con successo", false, CENTER);
    printBoxLines();
    Sleep(2000);

    user.isValid = true;
    user.index = userAmount;
    userList[userAmount] = user;
    userAmount++;
    saveData(concertFile, userFile);

    return Login();
}

///////////////
//  TICKET   //
///////////////

/**
 * @brief stampa un Menu per la scelta del concerto
 *
 * @param c un puntatore ad una struttura Concert dove salvare i dati
 */
void selectConcert(Concert *c)
{
    int count;
    *c = concertList[concertMenu(&count) - 1];
}

/**
 * @brief stampa un Menu per richiedere la quantità di biglietti desiderata
 *
 * @param c il concerto di cui si vogliono acquistare i biglietti
 * @return int il numero di biglietti inseriti, compresi nel range messo a disposizione dal venditore
 */
int ticketSelection(Concert c)
{
    char question[50];
    int selection;
    int avaibleTicket;

    avaibleTicket = (c.remaingTicket < c.maxTicket) ? c.remaingTicket : c.maxTicket;

    sprintf(question, "Quanti biglietti si desiderano? (1-%d)", avaibleTicket);

    printBoxLines();
    printText(question, false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &selection);
    fflush(stdin);

    if (selection < 1 || selection > avaibleTicket)
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
        fgets(compiledTickets[i].name, sizeof(compiledTickets[i].name) / sizeof(char), stdin);
        fflush(stdin);
        removeNewline(compiledTickets[i].name);

        leaveBlankLine();

        // RICHIESTA COGNOME
        printBoxLines();
        printText("Cognome per il biglietto", false, CENTER);
        printBoxLines();

        printf("\n?:");
        fgets(compiledTickets[i].surname, sizeof(compiledTickets[i].surname) / sizeof(char), stdin);
        fflush(stdin);
        removeNewline(compiledTickets[i].surname);

        leaveBlankLine();

        // RICHIESTA ETA
        printBoxLines();
        printText("Eta\' per il biglietto", false, CENTER);
        printBoxLines();

        printf("\n?:");
        scanf("%d", &compiledTickets[i].age);
        fflush(stdin);

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

//////////////
//  MONEY   //
//////////////

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
 *
 * @param type il tipo di pagamento scelto in precedenza
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

/**
 * @brief Gestisce il pagamento in contanti per l'acquisto di biglietti.
 *
 * @param sellerProfit Il prezzo totale dei biglietti da pagare.
 * @param ticketsPrice Il prezzo totale dei biglietti da pagare.
 * @param c La struttura Concert con le informazioni del concerto.
 * @param u La struttura User con le informazioni dell'utente che effettua il pagamento.
 * @return true Se il pagamento è stato completato con successo.
 * @return false Se il pagamento è fallito.
 */
bool manageCashPayment(float ticketsPrice, float sellerProfit, Concert c, User user)
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

        switch (newMenu(buffer, options, lineCount1, &count) - 1)
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

    if (givenMoney > ticketsPrice)
    {
        clearScreen();
        printBoxLines();
        printText("Raccogliere presso l'erogatore il resto", false, CENTER);
        printBoxLines();
        leaveBlankLine();
        printf("-> Resto erogato %.2f Euro", (givenMoney - ticketsPrice));
        Sleep(3000);
    }

    printBoxLines();
    printText("L'acquisto si è concluso con successo", false, CENTER);
    // printText("Riceverai i biglietti via mail!", false, CENTER);
    printBoxLines();

    leaveBlankLine();
    moveCash(c, sellerProfit);
}

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
bool manageCardPayment(float ticketsPrice, float sellerProfit, Concert c, User u)
{
    // Codice che comprende inserimetno manuale dei dati (da migliorare in futuro)
    /*
    const char *options[] = {
        "Inserisci i dati della carta",
        "Usa la carta associata all'account",
    };
    int lineCount1 = sizeof(options) / sizeof(options[0]);
    int count = 0;
    switch (newMenu("Come desideri pagare:", options, lineCount1, &count) - 1)
    {
    case 0:
        clearScreen();
        if (payWithCreditCard(c.seller, u, readCreditCardData(), ticketsPrice, sellerProfit, false))
        {
            printBoxLines();
            printText("L'acquisto si è concluso con successo", false, CENTER);
            printBoxLines();
        }
        else
        {
            printBoxLines();
            printText("L'acquisto non è andato a buon fine", false, CENTER);
            printText("possibile mancanza di fondi o uso di dati errati", false, CENTER);
            printBoxLines();
        }
        break;
    case 1:
        clearScreen();
        if (payWithCreditCard(c.seller, u, u.cA.associatedCard, ticketsPrice, sellerProfit, true))
        {
            printBoxLines();
            printText("L'acquisto si è concluso con successo", false, CENTER);
            printBoxLines();
        }
        else
        {
            printBoxLines();
            printText("L'acquisto non è andato a buon fine (possibile mancanza di fondi)", false, CENTER);
            printBoxLines();
        }
        break;
    }
    */

    clearScreen();
    if (payWithCreditCard(c.seller, u, u.cA.associatedCard, ticketsPrice, sellerProfit, true))
    {
        printBoxLines();
        printText("L'acquisto si è concluso con successo", false, CENTER);
        printBoxLines();
    }
    else
    {
        printBoxLines();
        printText("L'acquisto non è andato a buon fine (possibile mancanza di fondi)", false, CENTER);
        printBoxLines();
    }

    leaveBlankLine();
    printf("Premi un tasto per tornare indietro...");
    getch();
    clearScreen();
}

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
bool manageBonificoPayment(float ticketsPrice, float sellerProfit, Concert c, User u)
{
    printBoxLines();
    printText("Il sistema invierà un bonifico automatico dal suo account", false, CENTER);
    printText("verso il venditore e succesivamente riceverà i biglietti", false, CENTER);
    printBoxLines();

    Sleep(3000);

    if (moveMoney(u, c.seller, ticketsPrice, sellerProfit))
    {
        printBoxLines();
        printText("L'acquisto si è concluso con successo", false, CENTER);
        printBoxLines();
    }
    else
    {
        printBoxLines();
        printText("L'acquisto non è andato a buon fine (possibile mancanza di fondi)", false, CENTER);
        printBoxLines();
    }

    leaveBlankLine();
    printf("Premi un tasto per tornare indietro...");
    getch();
    clearScreen();
}

/**
 * @brief Legge i dati di una carta di credito inseriti dall'utente.
 *
 * @return creditCard Una struttura creditCard contenente i dati della carta inserita.
 */
creditCard readCreditCardData()
{
    creditCard cC;

    printBoxLines();
    printText("Numero di carta", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(cC.CARD_NUMBER, sizeof(cC.CARD_NUMBER) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(cC.CARD_NUMBER);

    leaveBlankLine();

    printBoxLines();
    printText("Data di scadenza (MM/YYYY)", false, CENTER);
    printBoxLines();

    printf("\n?:");
    fgets(cC.EXPIRE_DATE, sizeof(cC.EXPIRE_DATE) / sizeof(char), stdin);
    fflush(stdin);
    removeNewline(cC.EXPIRE_DATE);

    leaveBlankLine();

    printBoxLines();
    printText("CVC", false, CENTER);
    printBoxLines();

    printf("\n?:");
    scanf("%d", &cC.CVC);

    return cC;
}

/**
 * @brief Recupera le informazioni dell'account dell'utente specificato.
 *
 * @param user La struttura User con i dati dell'utente di cui si vogliono ottenere le informazioni.
 */
void getAccountInformation(User user)
{
    clearScreen();

    // Concatenazione del nome completo
    char fullName[100];
    snprintf(fullName, sizeof(fullName), "%s %s", user.name, user.surname);

    // Formattazione dei fondi disponibili
    char money[15];
    snprintf(money, sizeof(money), "%.2f", user.cA.avaibleMoney);

    // Formattazione del numero di carta di credito
    char formattedCardNumber[20];
    char cardNumber[17];

    snprintf(cardNumber, sizeof(cardNumber), "%s", user.cA.associatedCard.CARD_NUMBER);
    snprintf(formattedCardNumber, sizeof(formattedCardNumber), "%.4s %.4s %.4s %.4s",
             cardNumber, cardNumber + 4, cardNumber + 8, cardNumber + 12);

    // Formattazione delle informazioni della carta
    char cardInformation[50];
    snprintf(cardInformation, sizeof(cardInformation), "%s |  EXP:%s CVC:%d",
             formattedCardNumber,
             user.cA.associatedCard.EXPIRE_DATE,
             user.cA.associatedCard.CVC);

    // Stampa delle informazioni
    printBoxLines();
    printText("", false, CENTER);
    printText("Conto corrente intestato a:", false, CENTER);
    printText(fullName, false, CENTER);
    printText("", false, CENTER);
    printText("IBAN:", false, CENTER);
    printText(user.cA.IBAN, false, CENTER);
    printText("", false, CENTER);
    printText("Fondi disponibili:", false, CENTER);
    printText(money, false, CENTER);
    printText("", false, CENTER);
    printBoxLines();
    printText("", false, CENTER);
    printText("Carte di credito associate:", false, CENTER);
    printText("", false, CENTER);
    printText(cardInformation, false, CENTER);
    printText("", false, CENTER);
    printBoxLines();

    // Uscita
    leaveBlankLine();
    printf("Premi un tasto per tornare indietro...");
    getch();
    clearScreen();
}