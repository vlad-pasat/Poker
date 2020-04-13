/*Exista „T” jucatori” in care programul care va calcula sansa fiecaruia stie de cele de 2 doua „hole cards”.
La masa ex1sta „X” „dead cards”. 1<=X<=10
 https://www.cardplayer.com/poker-tools/odds-calculator/texas-holdem
Deasemenea exista si 3 carti cu fata in sus „community cards”

Sa se calculeze aproximativ sansa ca oricare participant sa castige.


Avem N jucatori, pentru fiecare jucator, vom genera 2 carti, deci N seturi de carti a cate 2.


*/

#define _CRT_SECURE_NO_WARNINGS
#define AS 1,11
#include "Jucator.h"

JUCATOR jucator[11];
CARTE community_cards[4];
int x,n;
//char toate_cartile[10000][10000]={"1 INIMAROSIE", "1 ROMB", "1 INIMANEAGRA", "1 TREFLA","2 INIMAROSIE","2 ROMB","2 INIMANEAGRA","2 TREFLA","3 INIMAROSIE", "3 ROMB", "3 INIMANEAGRA", "3 TREFLA" }

int nr_cartiinimaneagra[1000] = {-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int nr_cartiinimarosie[1000] = {-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int nr_cartitrefla[1000] = {-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
int nr_cartiromb[1000] = {-1,1,2,3,4,5,6,7,8,9,10,11,12,13,14};

int main()
{
    /*
        Fiecare mana va avea o anumita valoare in ordine crescatoare:

        1. Highcard - Cartea cu numarul cel mai mare din mana.
        2. Pair - Numar identic cu cartile din mana/community cards.
        3. Two pair - 2 carti cu nr identic din mana, 2 carti comunitare cu nr identic.
        4. Three of a kind - Trei carti cu acelasi numar. 
        5. Chinta - 5 carti consecutive.
        6. Culoare - 5 carti de aceeasi culoare (si figura). Exemplu: "ROMB" "ROMB" ROMB" ROMB" ROMB". NU MERGE "ROMB" "INIMAROSIE" "ROMB" "ROMB" "ROMB", CHIAR DACA SUNT DE ACEEASI CULOARE.
        7. Full house - Combinatie dintre Three of a kind si pereche. Exemplu: 14 14 7 7 7.
        8. Four of a kind - Patru carti cu acelasi numar.
        9. Chinta culoare - Combinatie dintre chinta si culoare. Exemplu: 5 TREFLA 6 TREFLA 7 TREFLA 8 TREFLA 9 TREFLA
        10. Chinta regala - Chinta culoare de la 10 pana la As. Exemplu: 10 ROSU 12 ROSU 13 ROSU 14 ROSU AS ROSU
    
    */

    printf("Cati jucatori sunt la masa? ");
    scanf("%d", &n);
    while (n <= 0 || n >= 11){
        printf("Sunt maxim 10 jucatori la masa. De asemnea nu pot sa fie jucatori cu minus.\nCati jucatori sunt la masa? ");
        scanf("%d", &n);
    } 
    generare_carti_jucator();
    afisare_carti();
 
    return 0;
}


void generare_carti_jucator()
{
    srand((time(NULL)));
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
    //Aici generam 3 community cards. Folosin aceeasi metoda ca mai sus (cea a generari in seturilor de 2 carti).
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
    //Aici adaugam fiecarui jucator in mana cele 3 community cards. Stiu, cam ciobaneste facuta.
    //Daca stai sa te gandesti, asta e un fel de Frankenstein dintre Texas Hold'em si pokerul cu 5 carti jucat de pensionari(cel cu 5 carti in mana avea doar cartile de la 7 in sus).
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

void afisare_carti()
{
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        printf("\nJucatorul %d are cartile: \n\n", i + 1);
        for (int j = 0; j < 2; j++)
        {
            printf("%d ", jucator[i].carte[j].numar);
            printf("%s\n", jucator[i].carte[j].culoare);
        }
    }
    printf("\nCommunity cards sunt: \n\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", community_cards[i].numar);
        printf("%s\n", community_cards[i].culoare);
    }
}

 