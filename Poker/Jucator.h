#include "Carti.h"

typedef struct{
	struct carti carte[6];
	int highcard;
}JUCATOR;

void generare_carti_jucator();
void afisare_carti();
void afisare_ordonata();
void determinare_high_card();
void generare_carti_ordonate();
int culoare(int i);
int chinta(int i);
int three_of_a_kind(int i);