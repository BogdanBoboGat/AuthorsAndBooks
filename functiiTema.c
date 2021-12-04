#include "librarie.h"
/* BUTNARIU Bogdan - 312CB */

/* Funtcia add_book */
void add_book(TArb T1, TArb T2, char *titlu, char *autor, char *rating, char *pagini)
{
    TCarte *info;
    info = malloc(sizeof(TCarte));
    if(!info)
    {
        printf("Eroare la alocare structura carte.");
        return;
    }

    info->titlu = malloc(51 * sizeof(char));
    if(!info->titlu)
    {
        printf("Eroare la alocare titlu carte.");
        free(info);
        return;
    }

    info->autor = malloc(41 * sizeof(char));
    if(!info->autor)
    {
        printf("Eroare la alocare autor carte.");
        free(info->titlu);
        free(info);
        return;
    }

    info->rating = malloc(3 * sizeof(char));
    if(!info->rating)
    {
        printf("Eroare la alocare rating carte.");
        free(info->titlu);
        free(info->autor);
        free(info);
        return;
    }

    info->pagini = malloc(10 * sizeof(char));
    if(!info->rating)
    {
        printf("Eroare la alocare pagini carte.");
        free(info->titlu);
        free(info->autor);
        free(info->rating);
        free(info);
        return;
    }
                
    strcpy(info->titlu, titlu);
    strcpy(info->autor, autor);
    strcpy(info->rating, rating);
    strcpy(info->pagini, pagini); // copiere informatie

    InsT1(&T1, titlu, info);
    InsT2(&T2, autor, titlu); // functii de inserare in arb. T1 si T2
}

/* Funtcia search_book */
void search_book(TArb T1, char *titlu, FILE *out)
{
    if(Cautare(T1, titlu)) // daca exista cartea
    {
        TArb p = T1;
        int nivel, dim = strlen(titlu), indice;
        
        /* parcurgere in T1 pana la p->info */
        for(nivel = 0; nivel < dim; nivel++)
        {
            indice = Indice(titlu[nivel]);
            p = p->copii[indice];
        } 

        /* printare + castare p->info (void * -> TCarte *) */
        fprintf(out, "Informatii recomandare: %s, %s, %s, %s\n", infCarte(p)->titlu, infCarte(p)->autor, infCarte(p)->rating, infCarte(p)->pagini);
    }

    else
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
}

/* Functia search_book ~ */
void search_book2(TArb T1, char *prefix, FILE *out, char str[])
{
    TArb p = T1;
    int nivel, dim = strlen(prefix), indice, count = 0;

    /* parcurge litera cu litera in arbore */
    for(nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(prefix[nivel]);

        if(!p->copii[indice])
        {
            fprintf(out, "Nicio carte gasita.\n"); // cazul in care nu se gaseste urm. litera
            return;
        }

        p = p->copii[indice];
    }
    
    Printare3(p, str, 0, out, &count, prefix); // functie care printeaza prefix + primele 3 sufixe alfabetic
}

/* Functia list_author */
void list_author(TArb T2, char *autor, FILE *out, char str[])
{
    if(Cautare(T2, autor)) // daca exista autorul
    {
        TArb p = T2;
        int nivel, dim = strlen(autor), indice;
        
        /* parcurgere in T2 pana la p->info */
        for(nivel = 0; nivel < dim; nivel++)
        {
            indice = Indice(autor[nivel]);
            p = p->copii[indice];
        }

        PrtArb(infAut(p), str, 0, out); // cast la p->info (void * -> TArb)
    }

    else
        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor);
}

/* Functia list_author ~ */
void list_author2(TArb T2, char *autor, FILE *out, char str[])
{
    TArb p = T2;
    int nivel, dim = strlen(autor), indice, count = 0;

    /* parcurge litera cu litera in arbore */
    for(nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(autor[nivel]);

        if(!p->copii[indice])
        {
            fprintf(out, "Niciun autor gasit.\n"); // cazul in care nu se gaseste urm. litera
            return;
        }

        p = p->copii[indice];
    }

    Printare3(p, str, 0, out, &count, autor); // functie care printeaza prefix + primele 3 sufixe alfabetic
}

/* Functia search_by_author */
void search_by_author(TArb T1, TArb T2, char *autor, char *titlu, FILE *out)
{
    if(Cautare(T2, autor)) // daca exista autorul
    {
        if(Cautare(T1, titlu)) // daca exista cartea
        {
            TArb p = T1;
            int nivel, dim = strlen(titlu), indice;
            
            /* parcurgere in T1 pana la p->info */
            for(nivel = 0; nivel < dim; nivel++)
            {
                indice = Indice(titlu[nivel]);
                p = p->copii[indice];
            }

            /* printare + castare p->info (void * -> TCarte *) */
            fprintf(out, "Informatii recomandare: %s, %s, %s, %s\n", infCarte(p)->titlu, infCarte(p)->autor, infCarte(p)->rating, infCarte(p)->pagini);
        }
        else
            fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
                
    }
    else
        fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor);
}

/* Functia search_by_author autor:titlu~ */
void search_by_author2(TArb T2, char *autor, char *titlu, FILE *out, char str[])
{
    TArb p = T2;
    int nivel, dim = strlen(autor), indice;
    
    /* parcurge litera cu litera in arbore */
    for(nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(autor[nivel]);
        if(!p->copii[indice])
        {
            fprintf(out, "Autorul %s nu face parte din recomandarile tale.\n", autor); // cazul in care nu se gaseste urm. litera
            return;
        }

        p = p->copii[indice];
    }
    
    search_book2(infAut(p), titlu, out, str); // apelare searc_book2 pentru p->info si titlul corespunzator
}

/* Functia delete_book */
void delete_book(TArb T1, TArb T2, char *titlu, FILE *out)
{
    TArb p = T1;
    int nivel, dim = strlen(titlu), indice;
    char *autor;
    
    /* parcurge litera cu litera in arborele T1 */
    for(nivel = 0; nivel < dim; nivel++)
    {
        indice = Indice(titlu[nivel]);
        if(!p->copii[indice])
        {
            fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
            return;
        }

        p = p->copii[indice];
    }

    if(eCuv(p)) // verificare daca exista cartea sau este componenta unei alte carti
    {
            autor = malloc(51 * sizeof(char));
            strcpy(autor, infCarte(p)->autor);

            /* stergere structura TCarte */
            free(infCarte(p)->titlu);
            free(infCarte(p)->autor);
            free(infCarte(p)->rating);
            free(infCarte(p)->pagini);
            free(infCarte(p));
            p->info = NULL; 

            p = T2;
            dim = strlen(autor);
            
            /* parcurge litera cu litera in arborele T2 */
            for(nivel = 0; nivel < dim; nivel++)
            {
                indice = Indice(autor[nivel]);
                p = p->copii[indice];
            }

            TArb arbCarte = infAut(p); // castare p->info 
            arbCarte = SterCheie(arbCarte, titlu, 0); // stergere din cartile autorului
                
            if(!arbCarte) // daca autorul nu mai are carti
            {
                free(arbCarte);
                SterCheie(T2, autor, 0);
            }
            
            SterCheie(T1, titlu, 0); // stergere titlu din T1
            free(autor);
    }
    
    else
    {
        fprintf(out, "Cartea %s nu exista in recomandarile tale.\n", titlu);
        return;
    }

}