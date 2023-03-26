#include "CacheSim.h"
#include <stdio.h>

//Mi simulador per Write through i no allocate
/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

typedef struct {
	unsigned int v;
	int tag;
} linia_cache;

linia_cache cache [128]; // cache de 2 a la 7 linees especificada per l'enunciat

int n_hits = 0;
int n_miss = 0;
int n_writes = 0;


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
	/* Escriu aqui el teu codi */
	for (int i = 0; i < 128; ++i) cache[i].v = -1;

}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	/* Escriu aqui el teu codi */
	lec_mp = 0;
	esc_mp = 0;
	mida_lec_mp = 0;
	mida_esc_mp = 0;
	replacement = 0;

	byte = (address & 0x0000001F);		 		//bits 27 - 31
	bloque_m = address >> 5;  					//bits 0 - 26
	linea_mc = (address & 0x00000FE0) >> 5;		//btis 20 - 26
	tag = address >> 12;						//bits 0 - 19

	// Dada vàlida
	if (cache[linea_mc].v == 1) {
		
		// Coincideix el TAG --> HIT
		if (cache[linea_mc].tag == tag) { 
			miss = 0;
			++n_hits;
			
			// Lectura no llegeix de memòria principal
			
			if (LE == 1) { // Escriptura
				esc_mp = 1;
				mida_esc_mp = 1;
				++n_writes;
			}
		}
		
		// NO coincideix el TAG --> MISS
		else {
			miss = 1;
			++n_miss;
			
			if (LE == 0) { // Lectura
				replacement = 1;
				lec_mp = 1;
				mida_lec_mp = 32;
				tag_out = cache[linea_mc].tag;
				cache[linea_mc].tag = tag;
			}
			else { // Escriptura
				esc_mp = 1;
				mida_esc_mp = 1;
				++n_writes;
			}
		}
	}
	
	// Dada no valida --> MISS (primer acces)
	else {
		miss = 1;
		++n_hits;
		
		if (LE == 0) { // Lectura
			lec_mp = 1;
			mida_lec_mp = 32;
			cache[linea_mc].v = 1;
			cache[linea_mc].tag = tag;
			
		}
		else { // Escriptura
			esc_mp = 1;
			mida_esc_mp = 1;
			++n_writes;
		}
	}







	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final ()
{
 	/* Escriu aqui el teu codi */ 
	printf("N_Hits = %d, N_Misses = %d, N_EscrituresMP = %d\n", n_hits, n_miss, n_writes);
}
