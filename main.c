#include <stdio.h>
#include <stdlib.h>
#define BOMBA 169
#define COPERTO 178
#define SVELATO 9
#define SEGNALATA 245

int numeriRandom10();
void creazioneGrigliaFiori(int[10][10]);
void creazioneGrigliaCampo(int[10][10]);
void stampaGriglia(int[10][10]);
int chiediCoordinate();
void conteggioBombe(int[10][10]);
void check(int[10][10], int[10][10], int, int, int, int);
void condizioniVittoria(int g_uscita, int g_caselleSvelate, int caselleTotali, int[10][10]);

int g_x, g_y, g_uscita, g_caselleSvelate = 0, g_Segnalate = 0;
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int caselleTotali = 90;
    int grigliaFiori[10][10] = {};
    int grigliaCampo[10][10] = {};
    creazioneGrigliaFiori(grigliaFiori);
    creazioneGrigliaCampo(grigliaCampo);
    conteggioBombe(grigliaFiori);
    do
    {
    stampaGriglia(grigliaCampo);
    //printf("\n\n");
    //stampaGriglia(grigliaFiori);
    int scelta = chiediCoordinate();
    printf("\nHai inserito le coordinate: %d - %d", g_x+1, g_y+1);
    check(grigliaCampo, grigliaFiori, g_x, g_y, caselleTotali, scelta);
    condizioniVittoria(g_uscita, g_caselleSvelate, caselleTotali, grigliaCampo);
    } while (g_uscita == 0);

    return 0;
}

int numeriRandom10()
{
    int x = rand() % 10;
    return x;
}

void creazioneGrigliaFiori(int grigliaFiori[10][10])
{
    int i = 0;
    int j, k;
    do
    {
        j = numeriRandom10();
        k = numeriRandom10();
        if (grigliaFiori[j][k] != BOMBA)
        {
            grigliaFiori[j][k] = BOMBA;
            i++;
        }
    }while (i < 10);

}

void creazioneGrigliaCampo(int grigliaCampo[10][10])
{
    int i, j;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            grigliaCampo[i][j] = COPERTO;
        }
    }
}

void stampaGriglia(int griglia[10][10])
{
    int i, j, k = 1;
    printf("   ");
    for (i = 1; i <= 10; i++)
    {
        printf("  %d ", i);
    }
    printf("\n\n");
    for (i = 0; i < 10; i++)
    {
        printf("%*d ", 2, k);
        k++;
        for (j = 0; j < 10; j++)
        {
            if (griglia[i][j] == BOMBA || griglia[i][j] == COPERTO || griglia[i][j] == 0 || griglia[i][j] == 33 || griglia[i][j] == SEGNALATA)
            {
                printf("| %c ", griglia[i][j]);
            }
            else
            {
                printf("| %d ", griglia[i][j]);
            }
        }
        printf("|\n");
        printf("    -----------------------------------------\n");
    }
}

int chiediCoordinate()
{
    printf("Inserisci le coordinate per scoprire la casella\n");
    do
    {
        printf("Inserisci la riga: ");
        scanf("%d", &g_x);
        g_x--;
        if (g_x < 0 || g_x > 9)
        {
            printf("Il valore deve essere compreso fra 1 e 10\n");
        }
    } while (g_x < 0 || g_x > 9);

    do
    {
        printf("Inserisci la colonna: ");
        scanf("%d", &g_y);
        g_y--;
        if (g_y < 0 || g_y > 9)
        {
            printf("Il valore deve essere compreso fra 1 e 10\n");
        }
    } while (g_y < 0 || g_y > 9);
    printf("Scegli se vuoi\n1. Scoprire la casella\n2. Segnare la bomba\n3. Annullare segnalino\nScegli: ");
    int scelta;
    scanf("%d", &scelta);
    while(scelta != 1 && scelta != 2 && scelta != 3)
    {
        printf("Scelta non valida. Scegli di nuovo: ");
        scanf("%d", &scelta);
    }
    if (scelta == 1)
    {
        return 1;
    }
    else if (scelta == 2)
    {
        return 2;
    }
    else
    {
        return 3;
    }
printf("\n\n");
}

void conteggioBombe(int grigliaFiori[10][10])
{
    int i, j, bombeVicine = 0;
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (grigliaFiori[i][j] != BOMBA)
            {
                if (i == 0 && j == 0) // Angolo alto a sinistra
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }
                if (i == 0 && j > 0 && j < 9) // Bordo in alto
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }
                if ( i == 0 && j == 9) // Angolo in alto a destra
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }

                if (i > 0 && i < 9 && j == 0) // Bordo sinistro
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i-1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }

                if (i == 9 && j == 0) // Angolo basso a sinistra
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i-1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }

                if ( i == 9 && j > 0 && j < 9) // Bordo in basso
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i-1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }

                if (i == 9 && j == 9) // Angolo in basso a destra
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i-1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }

                if (i > 0 && i < 9 && j == 9) // Bordo a destra
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i-1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }

                if (i > 0 && i < 9 && j > 0 && j < 9) // Al centro
                {
                    bombeVicine = 0;
                    if (grigliaFiori[i-1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i-1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j-1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    if (grigliaFiori[i+1][j+1] == BOMBA )
                    {
                        bombeVicine++;
                    }
                    grigliaFiori[i][j] = bombeVicine;
                }
            }
        }
    }
}

void check(int grigliaCampo[10][10], int grigliaFiori[10][10], int x, int y, int caselleTotali, int scelta)
{
    if (scelta == 1)
    {
        if (grigliaFiori[x][y] == 0) // Ricorsione per mostrare tutte le caselle vuote e i limiti con i numeri
        {
            grigliaFiori[x][y] = COPERTO;
            grigliaCampo[x][y] = 0;
            g_caselleSvelate += 1;
            if ((x-1 >= 0 && y-1 >= 0) && grigliaFiori[x-1][y-1] == 0)
            {
                check(grigliaCampo, grigliaFiori, x-1, y-1, caselleTotali, scelta);
            }
            else if ((x-1 >= 0 && y-1 >= 0) && grigliaFiori[x-1][y-1] != 0 && grigliaFiori[x-1][y-1] != BOMBA && grigliaFiori[x-1][y-1] != COPERTO && grigliaFiori[x-1][y-1] != SVELATO)
            {
                grigliaCampo[x-1][y-1] = grigliaFiori[x-1][y-1];
                grigliaFiori[x-1][y-1] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((x-1 >= 0) && grigliaFiori[x-1][y] == 0)
            {
                check(grigliaCampo, grigliaFiori, x-1, y, caselleTotali, scelta);
            }
            else if ((x-1 >= 0) && grigliaFiori[x-1][y] != 0 && grigliaFiori[x-1][y] != BOMBA && grigliaFiori[x-1][y] != COPERTO && grigliaFiori[x-1][y] != SVELATO)
            {
                grigliaCampo[x-1][y] = grigliaFiori[x-1][y];
                grigliaFiori[x-1][y] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((x-1 >= 0) && (y+1 <= 9) && grigliaFiori[x-1][y+1] == 0)
            {
                check(grigliaCampo, grigliaFiori, x-1, y+1, caselleTotali, scelta);
            }
            else if ((x-1 >= 0) && (y+1 <= 9) && grigliaFiori[x-1][y+1] != 0 && grigliaFiori[x-1][y+1] != BOMBA && grigliaFiori[x-1][y+1] != COPERTO && grigliaFiori[x-1][y+1] != SVELATO)
            {
                grigliaCampo[x-1][y+1] = grigliaFiori[x-1][y+1];
                grigliaFiori[x-1][y+1] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((y-1 >= 0) && grigliaFiori[x][y-1] == 0)
            {
                check(grigliaCampo, grigliaFiori, x, y-1, caselleTotali, scelta);
            }
            else if ((y-1 >= 0) && grigliaFiori[x][y-1] != 0 && grigliaFiori[x][y-1] != BOMBA && grigliaFiori[x][y-1] !=COPERTO && grigliaFiori[x][y-1] != SVELATO)
            {
                grigliaCampo[x][y-1] = grigliaFiori[x][y-1];
                grigliaFiori[x][y-1] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((y+1 <= 9) && grigliaFiori[x][y+1] == 0)
            {
                check(grigliaCampo, grigliaFiori, x, y+1, caselleTotali, scelta);
            }
            else if ((y+1 <= 9) && grigliaFiori[x][y+1] != 0 && grigliaFiori[x][y+1] != BOMBA && grigliaFiori[x][y+1] !=COPERTO && grigliaFiori[x][y+1] != SVELATO)
            {
                grigliaCampo[x][y+1] = grigliaFiori[x][y+1];
                grigliaFiori[x][y+1] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((x+1 <= 9 && y-1 >= 0) && grigliaFiori[x+1][y-1] == 0)
            {
                check(grigliaCampo, grigliaFiori, x+1, y-1, caselleTotali, scelta);
            }
            else if ((x+1 <= 9 && y-1 >= 0) && grigliaFiori[x+1][y-1] != 0 && grigliaFiori[x+1][y-1] != BOMBA && grigliaFiori[x+1][y-1] != COPERTO && grigliaFiori[x+1][y-1] != SVELATO)
            {
                grigliaCampo[x+1][y-1] = grigliaFiori[x+1][y-1];
                grigliaFiori[x+1][y-1] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((x+1 <= 9) && grigliaFiori[x+1][y] == 0)
            {
                check(grigliaCampo, grigliaFiori, x+1, y, caselleTotali, scelta);
            }
            else if ((x+1 <= 9) && grigliaFiori[x+1][y] != 0 && grigliaFiori[x+1][y] != BOMBA && grigliaFiori[x+1][y] !=COPERTO && grigliaFiori[x+1][y] != SVELATO)
            {
                grigliaCampo[x+1][y] = grigliaFiori[x+1][y];
                grigliaFiori[x+1][y] = SVELATO;
                g_caselleSvelate += 1;
            }

            if ((x+1 <= 9 && y+1 <= 9) && grigliaFiori[x+1][y+1] == 0)
            {
                check(grigliaCampo, grigliaFiori, x+1, y+1, caselleTotali, scelta);
            }
            else if ((x+1 <= 9 && y+1 <= 9) && grigliaFiori[x+1][y+1] != 0 && grigliaFiori[x+1][y+1] != BOMBA && grigliaFiori[x+1][y+1] != COPERTO && grigliaFiori[x+1][y+1] != SVELATO)
            {
                grigliaCampo[x+1][y+1] = grigliaFiori[x+1][y+1];
                grigliaFiori[x+1][y+1] = SVELATO;
                g_caselleSvelate += 1;
            }
        }
        if (grigliaFiori[x][y] == BOMBA && grigliaCampo[x][y] != SEGNALATA) // Se è una bomba termina il gioco
        {
            grigliaFiori[x][y] = 206;
            g_uscita = 1;
        }
        if (grigliaFiori[x][y] > 0 && grigliaFiori[x][y] < 9 && grigliaCampo[x][y] != SEGNALATA) // Mostra una casella contenente un numero
        {
            grigliaCampo[x][y] = grigliaFiori[x][y];
            grigliaFiori[x][y] = 9;
            g_caselleSvelate += 1;
        }
        if (grigliaCampo[x][y] == SEGNALATA)
        {
            printf("\nNon puoi scoprire una casella segnalata");
        }
    }
    else if (scelta == 2)
        {
            if(grigliaCampo[x][y] == COPERTO)
            {
                grigliaCampo[x][y] = SEGNALATA;
                g_Segnalate++;
            }
            else
            {
                printf("Questa casella non è segnalabile perché non nascosta\n");
            }

        }
        else if (scelta == 3)
        {
            if (grigliaCampo[x][y] == SEGNALATA)
            {
                grigliaCampo[x][y] = COPERTO;
                g_Segnalate--;
            }
            else
            {
                printf("Questa casella non era stata segnalata");
            }
        }

}

void condizioniVittoria(int g_uscita, int g_caselleSvelate, int caselleTotali, int grigliaCampo[10][10])
{
    if (g_uscita == 1)
    {
        stampaGriglia(grigliaCampo);
        printf("\n\nHai colpito una bomba. Mi dispiace, hai perso\n");
    }
    else if (caselleTotali - g_caselleSvelate != 0 && g_uscita != 1)
    {
        printf("\nHai svelato %d caselle. Te ne rimangono %d\n\n", g_caselleSvelate, (caselleTotali - g_caselleSvelate));
    }
    else if (caselleTotali - g_caselleSvelate == 0 && g_Segnalate == 10)
    {
        printf("\nComplimenti, hai Vinto!\n\n");
        g_uscita = 1;
    }
}
