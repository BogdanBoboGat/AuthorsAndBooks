#include "librarie.h"
/* BUTNARIU Bogdan - 312CB */

/* Verificare cuvant */
bool eCuv(TArb rad)
{
    return rad->SfCuv;
}

/* Verificare frunza arbore */
bool Frunza(TArb rad)
{
    int i;
    for(i = 0; i < dimAlf; i++) // parcurgere fiecare pozitie a vectorului de copii
        if(rad->copii[i])
            return false;
    return true;
}

/* Construire nod nou */
TArb ConstrNod()
{
    int i;
    
    TArb aux;
    aux = malloc(sizeof(TNod));

    if(!aux)
    {
        printf("Eroare la alocare dim. nod.");
        return NULL;
    }
    aux->info = NULL;
    aux->SfCuv = false;

    for(i = 0; i < dimAlf; i++)
        aux->copii[i] = NULL;
    
    return aux;
}

/* Functie care intoare pozitia corespunzatoare a fiecarui caracter in vectorul de copii */
int Indice(char c)
{
    if(c > 47 && c < 58) return (int)c - (int)'0' + 52; // 0-9
    
    if(c > 64 && c < 91) return (int)c - (int)'A' + 26; // A-Z
    
    if(c > 96 && c < 123) return (int)c - (int)'a'; // a-z
    
    switch(c) // .-\?! 
    {
        case '.':
            return 62;

        case '-':
            return 63;
            
        case '\'':
            return 64;
            
        case '?':
            return 65;
            
        case '!':
            return 66;
            
        case ' ':
            return 67;
    }

    return -1; // caz in care se da alt caracter fata de alfabet
}

/* Inserare in T1 */
void InsT1(AArb rad, char *titlu, TCarte *info)
{
    TArb p = *rad, aux;
    int nivel, dim = strlen(titlu), indice;

    /* parcurgere litera cu litera in arbore */
    for(nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(titlu[nivel]);

        if(!p->copii[indice]) // daca nu exista nod, se creeaza unul nou
        {
            aux = ConstrNod();
            if(!aux)
            {
                printf("Inserare esuata in arborele T1.");
                return;
            }

            p->copii[indice] = aux;
        }

        p = p->copii[indice];
    }

    p->SfCuv = true;
    p->info = info; // legare p->info cu struct TCarte
}

/* Inserare in T2 */
void InsT2(AArb rad, char *autor, char *titlu)
{
    int nivel, dim = strlen(autor), indice;
    TArb p = *rad, aux;

    /* parcurgere litera cu litera in arbore */
    for(nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(autor[nivel]);

        if(!p->copii[indice]) // daca nu exista nod, se creeaza unul nou
        {
            aux = ConstrNod();
            if(!aux)
            {
                printf("Inserare esuata in arborele T2.");
                return;
            }

            p->copii[indice] = aux;
        }

        p = p->copii[indice];
    }

    p->SfCuv = true;

    if(!p->info) // daca nu exista nicio carte inserata pentru un autor
    {
        TArb arbore = ConstrNod();
        InsT1(&arbore, titlu, NULL);

        p->info = arbore;
    }

    else
    {
        TArb arbore = infAut(p);
        InsT1(&arbore, titlu, NULL);
    }
}

/* Sterge o cheie din arbore Trie */
TArb SterCheie(TArb rad, char *cheie, int nivel)
{
    if(!rad)
        return NULL;
 
    if(nivel == strlen(cheie)) // cazul in care am ajuns la capatul cuvantului
    {
        if(eCuv(rad))
            rad->SfCuv = false;
 
        if(Frunza(rad))
        {
            free(rad);
            rad = NULL;
        }
 
        return rad;
    }

    int indice = Indice(cheie[nivel]);
    rad->copii[indice] = SterCheie(rad->copii[indice], cheie, nivel + 1); // apelare recursiva in adancime + returnare nod bun pe pozitia potrivita
 
    if(Frunza(rad) && !eCuv(rad)) // stergere litera din cheie
    {
        free(rad);
        rad = NULL;
    }
 
    return rad;
}

/* Cautare cheie in arbore */
bool Cautare(TArb rad, char *cheie)
{
    int nivel, dim = strlen(cheie), indice;
    TArb p = rad;
    
    /* parcurgere litera cu litera in arbore */
    for (nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(cheie[nivel]);
  
        if (!p->copii[indice]) // daca nu se gaseste urm. litera
            return false;
  
        p = p->copii[indice];
    }
    
    if(p != NULL && eCuv(p)) // daca exista litera si e final de cheie
        return true;

    return false;
}

/* Printare arbore */
void PrtArb(TArb rad, char str[], int nivel, FILE *out)
{
    if(eCuv(rad))
    {
        str[nivel] = '\0';
        fprintf(out, "%s\n", str);
    }

    int i;
    for(i = 0; i < dimAlf; i++)
    {
        if(rad->copii[i]) // parcurgere fieare litera inserata pe nivel + decodificare pozitie in litera
        {
            if(i >= 0 && i <= 25)
                str[nivel] = i + 'a';

            else if(i >= 26 && i <= 51)
                str[nivel] = i + 'A' - 26;

            else if(i >= 52 && i <= 61)
                str[nivel] = i + '0' - 52;

            else if(i == 62)
                str[nivel] = '.';

            else if(i == 63)
                str[nivel] = '-';

            else if(i == 64)
                str[nivel] = '\'';

            else if(i == 65)
                str[nivel] = '?';

            else if(i == 66)
                str[nivel] = '!';

            else if(i == 67)
                str[nivel] = ' ';

            PrtArb(rad->copii[i], str,  nivel + 1, out); // apelare recursiva + construire str
        }
    }
}

/* CTRL + V PrtArb, dar printeaza doar primele 3 aparitii */
void Printare3(TArb rad, char str[], int nivel, FILE *out, int *count, char *prefix)
{
    if(eCuv(rad))
    {
        str[nivel] = '\0';
        if(*count == 3)
            return;
        else
        {
            *count = *count + 1;
            fprintf(out, "%s%s\n", prefix, str);
        }         
    }

    int i;
    for(i = 0; i < dimAlf; i++)
    {
        if(rad->copii[i])
        {
            if(i >= 0 && i <= 25)
                str[nivel] = i + 'a';

            else if(i >= 26 && i <= 51)
                str[nivel] = i + 'A' - 26;

            else if(i >= 52 && i <= 61)
                str[nivel] = i + '0' - 52;

            else if(i == 62)
                str[nivel] = '.';

            else if(i == 63)
                str[nivel] = '-';

            else if(i == 64)
                str[nivel] = '\'';

            else if(i == 65)
                str[nivel] = '?';

            else if(i == 66)
                str[nivel] = '!';

            else if(i == 67)
                str[nivel] = ' ';

            Printare3(rad->copii[i], str,  nivel + 1, out, count, prefix);
        }
    }
}

/* Eliberare memorie T1 */
void DistrT1(AArb rad)
{
    TArb p = *rad;
    if(!p) return;

    if(eCuv(p))
    {
        TCarte *aux = infCarte(p);
        if(aux != NULL)
        {
            free(aux->titlu);
            free(aux->autor);
            free(aux->rating);
            free(aux->pagini);
            free(aux);
            aux = NULL;
        }
    }

    int i;    
    for(i = 0; i < dimAlf; i++)
    {
        DistrT1(&p->copii[i]);
    }

    free(p);
    p = NULL;
}

/* Eliberare memorie T2 */
void DistrT2(AArb rad)
{
    TArb p = *rad;
    if(!p) return;

    if(p->SfCuv)
    {
        TArb aux = infAut(p);
        DistrT1(&aux);
    }

    int i;    
    for(i = 0; i < dimAlf; i++)
    {
        DistrT2(&p->copii[i]);
    }

    free(p);
    p = NULL;
}