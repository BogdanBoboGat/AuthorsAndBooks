#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
/* BUTNARIU Bogdan - 312CB */

#define dimAlf (68)
#define infCarte(p) ((TCarte*)(p->info))
#define infAut(p) ((TArb)(p->info))

typedef struct{

    char *titlu;
    char *autor;
    char *rating;
    char *pagini;

}TCarte;

typedef struct nod{

    void *info;
    struct nod *copii[dimAlf];
    bool SfCuv;

}TNod, *TArb, **AArb;

/* Functii Tema */
void add_book(TArb T1, TArb T2, char *titlu, char *autor, char *rating, char *pagini);
void search_book(TArb T1, char *titlu, FILE *out);
void search_book2(TArb T1, char *prefix, FILE *out, char str[]);
void list_author(TArb T2, char *autor, FILE *out, char str[]);
void list_author2(TArb T2, char *autor, FILE *out, char str[]);
void search_by_author(TArb T1, TArb T2, char *autor, char *titlu, FILE *out);
void search_by_author2(TArb T2, char *autor, char *titlu, FILE *out, char str[]);
void delete_book(TArb T1, TArb T2, char *titlu, FILE *out);

/* Functii Trie */
bool eCuv(TArb rad);
bool Frunza(TArb rad);
TArb ConstrNod();
int Indice(char c);
void InsT1(AArb rad, char *titlu, TCarte *info);
void InsT2(AArb rad, char *autor, char *titlu);
TArb SterCheie(TArb rad, char *cheie, int nivel);
bool Cautare(TArb rad, char *cheie);
void PrtArb(TArb rad, char str[], int nivel, FILE *out);
void Printare3(TArb rad, char str[], int nivel, FILE *out, int *count, char *prefix);
void DistrT1(AArb rad);
void DistrT2(AArb rad);