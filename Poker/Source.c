/*Exista „T” jucatori” in care programul care va calcula sansa fiecaruia stie de cele de 2 doua „hole cards”.
La masa ex1sta „X” „dead cards”. 1<=X<=10
 https://www.cardplayer.com/poker-tools/odds-calculator/texas-holdem

Deasemenea exista si 3 carti cu fata in sus „community cards”

Sa se calculeze aproximativ sansa ca oricare participant sa castige.

Avem N jucatori, pentru fiecare jucator, vom genera 2 carti, deci N seturi de carti a cate 2.
*/

#define _CRT_SECURE_NO_WARNINGS
#define AS 1
#include "Jucator.h"

JUCATOR jucator[11],jucator_ordonat[20];
CARTE community_cards[4],dead_cards[11];
int x,y,n,nr_dead_cards;

//Acesta este pachetul de carti. 13 carti in fiecare pachet (nu il includem pe 11). 13*4=52
//Cartile cu -1 sunt cartile care nu sunt posibile/sunt luate deja de jucator/community cards/dead cards.
int nr_cartiinimaneagra[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};
int nr_cartiinimarosie[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};
int nr_cartitrefla[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};
int nr_cartiromb[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};

int main()
{

    printf("\nCati jucatori sunt la masa? (maxim 10) ");
    scanf("%d", &n);
    while (n <= 0 || n >= 11) {
        printf("Sunt maxim 10 jucatori la masa. De asemnea nu pot sa fie jucatori cu minus.\nCati jucatori sunt la masa? ");
        scanf("%d", &n);
    }

    printf("\nCate dead cards sunt la masa? (maxim 10) ");
    scanf("%d", &nr_dead_cards);
    while (nr_dead_cards <= 0 || nr_dead_cards >= 11)
    {
        printf("\nDead cards apartine [1,10].\nDati un numar intre 1 si 10: ");
        scanf("%d", &nr_dead_cards);
    }

    generare_carti_jucator();
    determinare_high_card();
    generare_carti_ordonate();
    afisare_carti();
    //afisare_ordonata();
 
    return 0;
}



void generare_carti_jucator()
{
    srand((time(NULL)));

    //START - GENERAREA DEAD CARDS.
    //DEAD CARDS = Carti care nu vor fi date nici jucatorului, nici la community cards.
    for (int i = 0; i < nr_dead_cards; i++)
    {
        x = rand() % 4;
        if (x == 0) strcpy(dead_cards[i].culoare, "INIMAROSIE");
        if (x == 1) strcpy(dead_cards[i].culoare, "ROMB");
        if (x == 2) strcpy(dead_cards[i].culoare, "INIMANEAGRA");
        if (x == 3) strcpy(dead_cards[i].culoare, "TREFLA");

        if (strcmp(dead_cards[i].culoare, "INIMAROSIE") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartiinimarosie[x] == -1);
            dead_cards[i].numar = nr_cartiinimarosie[x];
            nr_cartiinimarosie[x] = -1;
        }
        if (strcmp(dead_cards[i].culoare, "INIMANEAGRA") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartiinimaneagra[x] == -1);
            dead_cards[i].numar = nr_cartiinimaneagra[x];
            nr_cartiinimaneagra[x] = -1;
        }
        if (strcmp(dead_cards[i].culoare, "ROMB") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartiromb[x] == -1);
            dead_cards[i].numar = nr_cartiromb[x];
            nr_cartiromb[x] = -1;
        }
        if (strcmp(dead_cards[i].culoare, "TREFLA") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartitrefla[x] == -1);
            dead_cards[i].numar = nr_cartitrefla[x];
            nr_cartitrefla[x] = -1;
        }
    }
    //END - GENERAREA DEAD CARDS.

    //Folosim aceasta metoda pentru  a ne asigura ca nu exista 2 carti identice, adica sa nu aiba un jucator in mana ceva de genul 14 ROMB 14 ROMB, sau 14 ROMB in mana si 14 ROMB in community cards.

    //START - GENERAREA CELOR 2 CARTI UNICE DIN MANA FIECARUI JUCATOR.
    //Fiecare jucator are cate 2 carti generate aleatoriu in mana sa.
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            x = rand() % 4;
            if (x == 0) strcpy(jucator[i].carte[j].culoare, "INIMAROSIE");
            if (x == 1) strcpy(jucator[i].carte[j].culoare, "ROMB");
            if (x == 2) strcpy(jucator[i].carte[j].culoare, "INIMANEAGRA");
            if (x == 3) strcpy(jucator[i].carte[j].culoare, "TREFLA");

            if (strcmp(jucator[i].carte[j].culoare, "INIMAROSIE") == 0)
            {
                do {
                    x = rand() % 15;
                } while (x == 0 || x == 11 || nr_cartiinimarosie[x]==-1);
                jucator[i].carte[j].numar = nr_cartiinimarosie[x];
                nr_cartiinimarosie[x] = -1;
            }
            if (strcmp(jucator[i].carte[j].culoare, "INIMANEAGRA") == 0)
            {
                do {
                    x = rand() % 15;
                } while (x == 0 || x == 11 || nr_cartiinimaneagra[x] == -1);
                jucator[i].carte[j].numar = nr_cartiinimaneagra[x];
                nr_cartiinimaneagra[x] = -1;
            }
            if (strcmp(jucator[i].carte[j].culoare, "ROMB") == 0)
            {
                do {
                    x = rand() % 15;
                } while (x == 0 || x == 11 || nr_cartiromb[x] == -1);
                jucator[i].carte[j].numar = nr_cartiromb[x];
                nr_cartiromb[x] = -1;
            }
            if (strcmp(jucator[i].carte[j].culoare, "TREFLA") == 0)
            {
                do {
                    x = rand() % 15;
                } while (x == 0 || x == 11 || nr_cartitrefla[x] == -1);
                jucator[i].carte[j].numar = nr_cartitrefla[x];
                nr_cartitrefla[x] = -1;
            }
        }
    }    
    //END - GENERAREA CELOR 2 CARTI UNICE DIN MANA FIECARUI JUCATOR.

    //START - GENERAREA COMMUNITY CARDS.
    //COMMUNITY CARDS = 3 carti puse cu fata in sus pe masa, pe care jucatorii le pot folosi pentru a face pereche, chinta, culoare, doua perechi etc...
    for (int i = 0; i < 3; i++)
    {
        x = rand() % 4;
        if (x == 0) strcpy(community_cards[i].culoare, "INIMAROSIE");
        if (x == 1) strcpy(community_cards[i].culoare, "ROMB");
        if (x == 2) strcpy(community_cards[i].culoare, "INIMANEAGRA");
        if (x == 3) strcpy(community_cards[i].culoare, "TREFLA");

        if (strcmp(community_cards[i].culoare, "INIMAROSIE") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartiinimarosie[x] == -1);
            community_cards[i].numar = nr_cartiinimarosie[x];
            nr_cartiinimarosie[x] = -1;
        }
        if (strcmp(community_cards[i].culoare, "INIMANEAGRA") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartiinimaneagra[x] == -1);
            community_cards[i].numar = nr_cartiinimaneagra[x];
            nr_cartiinimaneagra[x] = -1;
        }
        if (strcmp(community_cards[i].culoare, "ROMB") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartiromb[x] == -1);
            community_cards[i].numar = nr_cartiromb[x];
            nr_cartiromb[x] = -1;
        }
        if (strcmp(community_cards[i].culoare, "TREFLA") == 0)
        {
            do {
                x = rand() % 15;
            } while (x == 0 || x == 11 || nr_cartitrefla[x] == -1);
            community_cards[i].numar = nr_cartitrefla[x];
            nr_cartitrefla[x] = -1;
        }
 
    }
    //END - GENERAREA COMMUNITY CARDS.

    //Aici adaugam fiecarui jucator in mana cele 3 community cards pentru simplitate la chinta. Stiu, cam ciobaneste facuta.
    //Daca stai sa te gandesti, asta e un fel de Frankenstein dintre Texas Hold'em si pokerul cu 5 carti jucat de pensionari (cel cu 5 carti in mana avea doar cartile de la 7 in sus).
    for (int i = 0; i < n; i++)
    {
        jucator[i].carte[2].numar = community_cards[0].numar;
        jucator[i].carte[3].numar = community_cards[1].numar;
        jucator[i].carte[4].numar = community_cards[2].numar;
        strcpy(jucator[i].carte[2].culoare, community_cards[0].culoare);
        strcpy(jucator[i].carte[3].culoare, community_cards[1].culoare);
        strcpy(jucator[i].carte[4].culoare, community_cards[2].culoare);
    }
}

void generare_carti_ordonate()
{
    //Aici ordonam cartile crescator pentru a ne ajuta la chinta.

    int aux;
    char caux[100];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 5; j++)
        {
            jucator_ordonat[i].carte[j].numar = jucator[i].carte[j].numar;
            strcpy(jucator_ordonat[i].carte[j].culoare, jucator[i].carte[j].culoare);
        }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = j + 1; k < 5; k++)
            {
                if (jucator_ordonat[i].carte[j].numar > jucator_ordonat[i].carte[k].numar)
                {
                    aux = jucator_ordonat[i].carte[j].numar;
                    jucator_ordonat[i].carte[j].numar = jucator_ordonat[i].carte[k].numar;
                    jucator_ordonat[i].carte[k].numar = aux;

                    strcpy(caux, jucator_ordonat[i].carte[j].culoare);
                    strcpy(jucator_ordonat[i].carte[j].culoare, jucator_ordonat[i].carte[k].culoare);
                    strcpy(jucator_ordonat[i].carte[k].culoare, caux);
                }
            }
        }
    }
}

void determinare_high_card()
{
    //Aici returnam high cardul in mana jucatorului. De asmenea adaugam un jucator_ordonat pentru simplitate la four of a kind si three of a kind.
    for (int i = 0; i < n; i++)
    {
        if (jucator[i].carte[0].numar == 1 || jucator[i].carte[1].numar == 1)
        {
            jucator[i].highcard = 1;
            jucator_ordonat[i].highcard = 1;
        }
        else {
            if (jucator[i].carte[0].numar > jucator[i].carte[1].numar)
            {
                jucator[i].highcard = jucator[i].carte[0].numar;
                jucator_ordonat[i].highcard = jucator[i].highcard;
            }
            else {
                jucator[i].highcard = jucator[i].carte[1].numar;
                jucator_ordonat[i].highcard = jucator[i].highcard;
            }
        }
    }

}

bool four_of_a_kind(int i)
{
    //vedem daca cartea 0 este egala cu cartea 1 este egala cu 2 este egala cu 3.
    if (jucator_ordonat[i].carte[0].numar == jucator_ordonat[i].carte[1].numar && jucator_ordonat[i].carte[1].numar == jucator_ordonat[i].carte[2].numar && jucator_ordonat[i].carte[2].numar == jucator_ordonat[i].carte[3].numar)
        return true;
    if (jucator_ordonat[i].carte[1].numar == jucator_ordonat[i].carte[2].numar && jucator_ordonat[i].carte[2].numar == jucator_ordonat[i].carte[3].numar && jucator_ordonat[i].carte[3].numar == jucator_ordonat[i].carte[4].numar)
        return true;
    return false;
}

bool culoare_functie(int i)
{
    //vedem daca 5 carti au aceeasi culoare.
    if ((strcmp(jucator[i].carte[0].culoare, jucator[i].carte[1].culoare) == 0) && (strcmp(jucator[i].carte[1].culoare, jucator[i].carte[2].culoare) == 0) && (strcmp(jucator[i].carte[2].culoare, jucator[i].carte[3].culoare) == 0) && (strcmp(jucator[i].carte[3].culoare, jucator[i].carte[4].culoare) == 0))
        return true;
    return false;
}

bool chinta_functie(int i)
{
    //vedem daca exista 5 carti consecutive in mana jucatorului.
    if (jucator[i].carte[0].numar+1 == jucator[i].carte[1].numar /**/&& jucator[i].carte[1].numar+1 == jucator[i].carte[2].numar /**/ && jucator[i].carte[2].numar+1 == jucator[i].carte[3].numar && jucator[i].carte[3].numar+1 == jucator[i].carte[4].numar)
        return true;
    return false;
}

bool three_of_a_kind_functie(int i)
{
    if (jucator_ordonat[i].carte[0].numar == jucator_ordonat[i].carte[1].numar && jucator_ordonat[i].carte[1].numar == jucator_ordonat[i].carte[2].numar)
        return true;
    if (jucator_ordonat[i].carte[1].numar == jucator_ordonat[i].carte[2].numar && jucator_ordonat[i].carte[2].numar == jucator_ordonat[i].carte[3].numar)
        return true;
    if (jucator_ordonat[i].carte[2].numar == jucator_ordonat[i].carte[3].numar && jucator_ordonat[i].carte[3].numar == jucator_ordonat[i].carte[4].numar)
        return true;
    return false;
}

bool two_pair(int i)
{
    bool pair[2] = { false,false };
    for (int j = 0; j < 2; j++)
        for (int k = 2; k < 5; k++)
            if (jucator[i].carte[j].numar == jucator[i].carte[k].numar)
            {
                pair[j] = true;
                break;
            }
    if (pair[0] == true && pair[1] == true)
        return true;
    return false;
}

bool pair(int i)
{
    for (int j = 0; j < 4; j++)
        for (int k = j+1; k < 5; k++)
            if (jucator[i].carte[j].numar == jucator[i].carte[k].numar)
                return true;
    return false;
    //3 2 J 9 J
}



void mana()
{
/*
    Fiecare mana va avea o anumita valoare in ordine crescatoare:

    1. Highcard - Cartea cu numarul cel mai mare din mana.
    2. Pair - Numar identic cu cartile din mana/community cards.
    3. Two pair - Exemplu: J 5 J 7 5 
    4. Three of a kind - Trei carti cu acelasi numar.
    5. Chinta - 5 carti consecutive.
    6. Culoare - 5 carti de aceeasi culoare (si figura). Exemplu: "ROMB" "ROMB" ROMB" ROMB" ROMB". NU MERGE "ROMB" "INIMAROSIE" "ROMB" "ROMB" "ROMB", CHIAR DACA SUNT DE ACEEASI CULOARE.
    7. Full house - Combinatie dintre Three of a kind si pereche. Exemplu: 14 14 7 7 7.
    8. Four of a kind - Patru carti cu acelasi numar.
    9. Chinta culoare - Combinatie dintre chinta si culoare. Exemplu: 5 TREFLA 6 TREFLA 7 TREFLA 8 TREFLA 9 TREFLA
    10. Chinta regala - Chinta culoare de la 10 pana la As. Exemplu: 10 ROSU 12 ROSU 13 ROSU 14 ROSU AS ROSU

    De ex, cei cu high card vor avea un procentaj mai mic de castig, pe cand cei cu pereche vor avea un procentaj mai mare etc.

    Pentru high card, vom aduna ceea ce are in mana, pentru cazuri de genul: Jucatorul 1 are Q 4, iar Jucatorul 3 are Q 3. Astfel, adunandu-le vom stii cine are sansa mai mare.

    Ce mana are un jucator(highcard sau perecte etc) va fi o constanta cu care vom inmulti pt a determina sansa de castig.
    Exemplu: High card ca vi 1*....
            Pereche va fi 2*....
*/
    for (int i = 0; i < n; i++)
    {
        
    }
}

void afisare_carti()
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nJucatorul %d are cartile: \n\n", i + 1);
        for (int j = 0; j < 2; j++)
        {
            if (jucator[i].carte[j].numar == 1)
                printf("AS ");
            else printf("%d ", jucator[i].carte[j].numar);
            printf("%s\n", jucator[i].carte[j].culoare);
        }
        //printf("\nHigh cardul jucatorului %d este: ", i + 1);
        //if (jucator[i].highcard == AS)
        //    printf("AS\n");
        //else
        //    printf("%d\n", jucator[i].highcard);
    }

    printf("\nCommunity cards sunt: \n\n");
    for (int i = 0; i < 3; i++)
    {
        if (community_cards[i].numar == 1)
            printf("AS ");
        else printf("%d ", community_cards[i].numar);
        printf("%s\n", community_cards[i].culoare);
    }

    printf("\nDead cards sunt: \n\n");
    {
        for (int i = 0; i < nr_dead_cards; i++)
        {
            if (dead_cards[i].numar == 1)
                printf("AS ");
            else printf("%d ", dead_cards[i].numar);
            printf("%s   ", dead_cards[i].culoare);
        }
    }
    printf("\n\n\n\n\n\n\n\n");
}

void afisare_ordonata()
{
    printf("\n-------------AFISARE ORDONATA---------------------");
    for (int i = 0; i < n; i++)
    {
        printf("\nJucatorul %d are cartile: \n\n", i + 1);
        for (int j = 0; j < 5; j++)
        {
            if (jucator_ordonat[i].carte[j].numar == AS)
                printf("AS ");
            else printf("%d ", jucator_ordonat[i].carte[j].numar);
            printf("%s\n", jucator_ordonat[i].carte[j].culoare);
        }
    }
 }