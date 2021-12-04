#include "librarie.h"
/* BUTNARIU Bogdan - 312CB */

int main(int argc, char *argv[])
{
    /* Variabile declarate */
    FILE *in, *out;
    char *in_file, *out_file, *functia, *line = NULL, *titlu, *autor, *rating, *pagini, *str;

    size_t len = 0;

    TArb T1, T2;
    
    /* Initializare sir pentru printare */
    str = malloc(51 * sizeof(char));
    if(!str)
    {
        printf("Eroare la alocare sir aditional.");
        return 0;
    }
    
    /* Initializare arbori */
    T1 = ConstrNod();
    if(!T1)
    {
        printf("Eroare la alocare arbore T1.");
        free(str);
        return 0;
    }
        
    T2 = ConstrNod();
    if(!T2)
    {
        printf("Eroare la alocare arbore T2.");
        free(str);
        DistrT1(&T1);
        return 0;
    }

    /* Deschidere fisiere */
    in_file = argv[1];
    out_file = argv[2];

    in = fopen(in_file, "rt");
    out = fopen(out_file, "wt");

    /* Citire linie cu linie din fisierul in */
    while(getline(&line, &len, in) != -1)
    {   
        functia = strtok(line, " "); // Functia citita 

        /* Functiile implementate */
        if(strcmp(functia, "add_book") == 0)
        {
            titlu = strtok(NULL, ":");
            autor = strtok(NULL, ":");
            rating = strtok(NULL, ":");
            pagini = strtok(NULL, "\n"); 
            
            if(!Cautare(T1, titlu))
                add_book(T1, T2, titlu, autor, rating, pagini);

        }

        else if(strcmp(functia, "search_book") == 0)
        {
            titlu = strtok(NULL, "\n");
            
            if(titlu[strlen(titlu) - 1] == '~')
            {
                titlu[strlen(titlu) - 1] = '\0';
                search_book2(T1, titlu, out, str);
            }
            
            else
                search_book(T1, titlu, out);
        }

        else if(strcmp(functia, "list_author") == 0)
        {
            autor = strtok(NULL, "\n");
            
            if(autor[strlen(autor) - 1] == '~')
            {
                autor[strlen(autor) - 1] = '\0';
                list_author2(T2, autor, out, str);
            }
            
            else
                list_author(T2, autor, out, str);
        }

        else if(strcmp(functia, "search_by_author") == 0)
        {
            autor = strtok(NULL, ":\n");
            
            if(autor[strlen(autor) - 1] == '~') // functia search_by_author <prefix_autor>~ = list_author <prefix_autor>~ 
            {
                autor[strlen(autor) - 1] = '\0';
                list_author2(T2, autor, out, str);
            }

            else
            {
                titlu = strtok(NULL, "\n");
                
                if(titlu[strlen(titlu) - 1] == '~')
                {
                    titlu[strlen(titlu) - 1] = '\0';
                    search_by_author2(T2, autor, titlu, out, str);
                }

                else
                    search_by_author(T1, T2, autor, titlu, out);                
                
            }
            
        }

        else if(strcmp(functia, "delete_book") == 0)
        {
            titlu = strtok(NULL, "\n");
            //delete_book(T1, T2, titlu, out);
        }
    }

    /* Eliberare memorie + fisiere */
    //DistrT1(&T1);
    //DistrT2(&T2);
    fclose(in);
    fclose(out);
    free(line);
    free(str);

    return 0;
}