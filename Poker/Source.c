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

int nr_cartiinimaneagra[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};
int nr_cartiinimarosie[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};
int nr_cartitrefla[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};
int nr_cartiromb[1000] = {-1,1,2,3,4,5,6,7,8,9,10,-1,12,13,14};

int main()
{

    printf("Cati jucatori sunt la masa? ");
    scanf("%d", &n);
    while (n <= 0 || n >= 11) {
        printf("Sunt maxim 10 jucatori la masa. De asemnea nu pot sa fie jucatori cu minus.\nCati jucatori sunt la masa? ");
        scanf("%d", &n);
    }

    printf("Cate dead cards sunt la masa? ");
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
    //Mai intai generam dead cards [1,10].
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
    //Folosim aceasta metoda pentru  a ne asigura ca nu exista 2 carti identice, adica sa nu aiba un jucator in mana ceva de genul 14 ROMB 14 ROMB, sau 14 ROMB in mana si 14 ROMB in community cards.

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

    int aux;
    char caux[100];


    //ordonam cartile crescator.
    for (int i = 0; i < n; i++)
    {
        if (jucator[i].carte[0].numar != 1 && jucator[i].carte[1].numar != 1)
        {
            if (jucator[i].carte[0].numar > jucator[i].carte[1].numar)
            {
                //5 3
                jucator_ordonat[i].carte[0].numar = jucator[i].carte[1].numar;
                strcpy(jucator_ordonat[i].carte[0].culoare, jucator[i].carte[1].culoare);
                jucator_ordonat[i].carte[1].numar = jucator[i].carte[0].numar;
                strcpy(jucator_ordonat[i].carte[1].culoare, jucator[i].carte[0].culoare);
            }
            else {
                //3 5
                jucator_ordonat[i].carte[0].numar = jucator[i].carte[0].numar;
                strcpy(jucator_ordonat[i].carte[0].culoare, jucator[i].carte[0].culoare);
                jucator_ordonat[i].carte[1].numar = jucator[i].carte[1].numar;
                strcpy(jucator_ordonat[i].carte[1].culoare, jucator[i].carte[1].culoare);
            }
        }
        //---------PRIMELE 2 CARTI DIN MANA JUCATORULUI---------
        if (jucator[i].carte[0].numar == AS)
        {
            jucator_ordonat[i].carte[1].numar = jucator[i].carte[0].numar;
            strcpy(jucator_ordonat[i].carte[1].culoare, jucator[i].carte[0].culoare);
            jucator_ordonat[i].carte[0].numar = jucator[i].carte[1].numar;
            strcpy(jucator_ordonat[i].carte[0].culoare, jucator[i].carte[1].culoare);
        }
        if (jucator[i].carte[1].numar == AS)
        {
            jucator_ordonat[i].carte[1].numar = jucator[i].carte[1].numar;
            strcpy(jucator_ordonat[i].carte[1].culoare, jucator[i].carte[1].culoare);
            jucator_ordonat[i].carte[0].numar = jucator[i].carte[0].numar;
            strcpy(jucator_ordonat[i].carte[0].culoare, jucator[i].carte[0].culoare);
        }

        //---------PRIMELE 2 CARTI DIN MANA JUCATORULUI--------

        //---------ULTIMELE 3 CARTI (COMMUNITY CARDS) DIN MANA JUCATORULUI--------
        if (jucator[i].carte[2].numar != 1 && jucator[i].carte[3].numar != 1 && jucator[i].carte[4].numar != 1)
        {
            if (jucator[i].carte[2].numar == 1 && jucator[i].carte[3].numar == 1 && jucator[i].carte[4].numar == 1)
            {
                //cazul in care avem 3 asi la community cards.
                //AS AS AS
                jucator_ordonat[i].carte[4].numar = jucator[i].carte[4].numar;
                strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[4].culoare);
                jucator_ordonat[i].carte[3].numar = jucator[i].carte[3].numar;
                strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[3].culoare);
                jucator_ordonat[i].carte[2].numar = jucator[i].carte[2].numar;
                strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[2].culoare);
            }
            else
            {
                if (jucator[i].carte[2].numar == 1 && jucator[i].carte[3].numar == 1)
                {
                    //cazurile in care avem doi asi in community cards.
                    //AS AS 5
                    jucator_ordonat[i].carte[4].numar = jucator[i].carte[2].numar;
                    strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[2].culoare);

                    jucator_ordonat[i].carte[3].numar = jucator[i].carte[3].numar;
                    strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[3].culoare);

                    jucator_ordonat[i].carte[2].numar = jucator[i].carte[4].numar;
                    strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[4].culoare);
                }
                else if (jucator[i].carte[2].numar == 1 && jucator[i].carte[4].numar == 1)
                {
                    //AS 5 AS
                    jucator_ordonat[i].carte[4].numar = jucator[i].carte[4].numar;
                    strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[4].culoare);

                    jucator_ordonat[i].carte[3].numar = jucator[i].carte[2].numar;
                    strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[2].culoare);

                    jucator_ordonat[i].carte[2].numar = jucator[i].carte[3].numar;
                    strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[3].culoare);
                }
                else if (jucator[i].carte[3].numar == 1 && jucator[i].carte[4].numar == 1)
                {
                    //5 AS AS
                    jucator_ordonat[i].carte[4].numar = jucator[i].carte[4].numar;
                    strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[4].culoare);

                    jucator_ordonat[i].carte[3].numar = jucator[i].carte[3].numar;
                    strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[3].culoare);

                    jucator_ordonat[i].carte[2].numar = jucator[i].carte[2].numar;
                    strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[2].culoare);
                }
                else
                {
                    //CAZURI CU UN AS
                    if (jucator[i].carte[2].numar == 1)
                    {
                        //cazul unde primul community card este as. 
                        //Exemplu: AS 5 3
                        jucator_ordonat[i].carte[4].numar = jucator[i].carte[2].numar;
                        strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[2].culoare);
                        if (jucator[i].carte[3].numar > jucator[i].carte[4].numar)
                        {
                            jucator_ordonat[i].carte[3].numar = jucator[i].carte[3].numar;
                            strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[3].culoare);

                            jucator_ordonat[i].carte[2].numar = jucator[i].carte[4].numar;
                            strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[4].culoare);
                        }
                        else {
                            //AS 3 5
                            jucator_ordonat[i].carte[3].numar = jucator[i].carte[4].numar;
                            strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[4].culoare);

                            jucator_ordonat[i].carte[2].numar = jucator[i].carte[3].numar;
                            strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[3].culoare);
                        }
                    }
                    if (jucator[i].carte[3].numar == 1)
                    {
                        //cazul unde al doilea community card este as
                        //5 AS 3
                        jucator_ordonat[i].carte[4].numar = jucator[i].carte[3].numar;
                        strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[3].culoare);
                        if (jucator[i].carte[2].numar > jucator[i].carte[4].numar)
                        {
                            jucator_ordonat[i].carte[3].numar = jucator[i].carte[2].numar;
                            strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[2].culoare);

                            jucator_ordonat[i].carte[2].numar = jucator[i].carte[4].numar;
                            strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[4].culoare);
                        }
                        else {
                            //3 AS 5
                            jucator_ordonat[i].carte[2].numar = jucator[i].carte[2].numar;
                            strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[2].culoare);

                            jucator_ordonat[i].carte[3].numar = jucator[i].carte[4].numar;
                            strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[4].culoare);
                        }
                    }
                    if (jucator[i].carte[4].numar == 1)
                    {
                        jucator_ordonat[i].carte[4].numar = jucator[i].carte[4].numar;
                        strcpy(jucator_ordonat[i].carte[4].culoare, jucator[i].carte[4].culoare);
                        if (jucator[i].carte[2].numar > jucator[i].carte[3].numar)
                        {
                            //5 3 AS
                            jucator_ordonat[i].carte[2].numar = jucator[i].carte[3].numar;
                            strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[3].culoare);

                            jucator_ordonat[i].carte[3].numar = jucator[i].carte[2].numar;
                            strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[2].culoare);
                        }
                        else
                        {
                            //3 5 AS
                            jucator_ordonat[i].carte[2].numar = jucator[i].carte[2].numar;
                            strcpy(jucator_ordonat[i].carte[2].culoare, jucator[i].carte[2].culoare);

                            jucator_ordonat[i].carte[3].numar = jucator[i].carte[3].numar;
                            strcpy(jucator_ordonat[i].carte[3].culoare, jucator[i].carte[3].culoare);
                        }
                    }
                }
            }
        }
        //---------ULTIMELE 3 CARTI (COMMUNITY CARDS) DIN MANA JUCATORULUI--------

       

        //Copiem community cards din mana jucatorului in mana jucatorului ordonat pentru sortare.
        //DACA NU SUNT ASI IN COMMUNITY CARDS
        if (jucator[i].carte[2].numar != 1 && jucator[i].carte[3].numar != 1 && jucator[i].carte[4].numar != 1)
        {
            for (int j = 2; j < 5; j++)
            {
                jucator_ordonat[i].carte[j].numar = jucator[i].carte[j].numar;
                strcpy(jucator_ordonat[i].carte[j].culoare, jucator[i].carte[j].culoare);
            }

            for (int j = 2; j < 4; j++)
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
        //------DACA NU EXISTA ASI------
    }
    //---------COMMUNITY CARDS---------
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

int four_of_a_kind(int i)
{
    //vedem daca cartea 0 este egala cu cartea 1 este egala cu 2 este egala cu 3.
    if (jucator_ordonat[i].carte[0].numar == jucator_ordonat[i].carte[1].numar && jucator_ordonat[i].carte[1].numar == jucator_ordonat[i].carte[2].numar && jucator_ordonat[i].carte[2].numar == jucator_ordonat[i].carte[3].numar)
        return 1;
    if (jucator_ordonat[i].carte[1].numar == jucator_ordonat[i].carte[2].numar && jucator_ordonat[i].carte[2].numar == jucator_ordonat[i].carte[3].numar && jucator_ordonat[i].carte[3].numar == jucator_ordonat[i].carte[4].numar)
        return 1;
    return 0;
}

int culoare(int i)
{
    //vedem daca 5 carti au aceeasi forma.
    if ((strcmp(jucator[i].carte[0].culoare, jucator[i].carte[1].culoare) == 0) && (strcmp(jucator[i].carte[1].culoare, jucator[i].carte[2].culoare) == 0) && (strcmp(jucator[i].carte[2].culoare, jucator[i].carte[3].culoare) == 0) && (strcmp(jucator[i].carte[3].culoare, jucator[i].carte[4].culoare) == 0))
        return 1;
    return 0;
}

int chinta(int i)
{
    //vedem daca exista 5 carti consecutive in mana jucatorului.
    if (jucator[i].carte[0].numar+1 == jucator[i].carte[1].numar /**/&& jucator[i].carte[1].numar+1 == jucator[i].carte[2].numar /**/ && jucator[i].carte[2].numar+1 == jucator[i].carte[3].numar && jucator[i].carte[3].numar+1 == jucator[i].carte[4].numar)
        return 1;
    return 0;
}

int three_of_a_kind(int i)
{
}

void mana()
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
    printf("\n\n\n\n\n");
}

//void afisare_ordonata()
//{
//    printf("\n-------------AFISARE ORDONATA---------------------");
//    for (int i = 0; i < n; i++)
//    {
//        printf("\nJucatorul %d are cartile: \n\n", i + 1);
//        for (int j = 0; j < 5; j++)
//        {
//            if (jucator_ordonat[i].carte[j].numar == AS)
//                printf("AS ");
//            else printf("%d ", jucator_ordonat[i].carte[j].numar);
//            printf("%s\n", jucator_ordonat[i].carte[j].culoare);
//        }
//    }
//    //printf("\nCommunity cards sunt: \n\n");
//    //for (int i = 0; i < 3; i++)
//    //{
//    //    printf("%d ", community_cards[i].numar);
//    //    printf("%s\n", community_cards[i].culoare);
//    //}
// }