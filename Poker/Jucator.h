#include "Carti.h"

typedef struct{
	struct carti carte[6];
	int highcard;
	int valoarea_mainii;
	float sansa;
}JUCATOR;

void generare_carti_jucator();
void afisare_carti();
void afisare_ordonata();
void determinare_high_card();
void generare_carti_ordonate();
bool culoare_functie(int i);
bool chinta_functie(int i);
bool three_of_a_kind(int i);
bool four_of_a_kind(int i);
void mana();
void determinare_sansa();