#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum menu { VIGENERE = 1, PLAYFAIR = 2, TERMINA = 3 } Menu;
typedef char* string;
typedef unsigned short int ushort;
    
// caratteri scartati durante la formattazione del testo
ushort scartati = 0;
// flag per indicare se il testo ricevuto in input è stato troncato
bool troncato = false;

// matrice di cifratura di Playfair
const char mPlayfair[5][5] = { "esemp", "olayf", "rbcdg", "hknqt", "uvwxz" };

// pulisce il buffer di input dopo aver letto un valore in input con fgets() (credits: https://stackoverflow.com/questions/7898215/how-can-i-clear-an-input-buffer-in-c)
void pulisciBufferInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* 
    Formatta il testo in chiaro per il cifrario di Playfair.
	Ogni coppia di lettere del testo in chiaro viene cifrata come unità.
	Se una coppia ha lettere identiche, si introduce una "X" tra di esse per separarle. 
	Se il testo ha un numero dispari di lettere, si aggiunge una "X" alla fine. 
*/
void formattaPlayFair(char *stringa) {
    char sFormattata[25] = "";
    ushort j = 0;
    
    for (int i = 0; stringa[i] != '\0'; i++) {
        char c1 = stringa[i];
        char c2 = stringa[i + 1];

        if (c1 == 'j'){
          c1 = 'i';
          printf("Attenzione: rilevata lettera non supportata ('j'). Sostituita con 'i'.\n");
        }

        sFormattata[j++] = c1;

        if (c1 == c2) {
            sFormattata[j++] = 'x';
        }
    }
    
    // se il testo ha un numero dispari di lettere, si aggiunge una "X" alla fine
    if (j % 2 != 0) {
        sFormattata[j++] = 'x';
    }
    
    sFormattata[j] = '\0';
    strcpy(stringa, sFormattata);
}

// elimina tutti i caratteri che non fanno parte dell’alfabeto inglese e rende tutti i caratteri in maiuscolo in minuscolo
void ripulisciEFormatta(char *stringa, bool mantieniScartati) {
    char sFormattata[25] = "";
    ushort j = 0;
    if (!mantieniScartati) scartati = 0;

    for (int i = 0; stringa[i] != '\0'; i++) {
        if (isalpha(stringa[i])) {
            sFormattata[j++] = (char) tolower(stringa[i]);
        } else {
            scartati++;
        }
    }
    
    sFormattata[j] = '\0';
    strcpy(stringa, sFormattata);
}

// stampa l'esito della cifratura e il testo in chiaro, informando l'utente dei caratteri scartati
void stampaEsito(const char *plaintext, const char *cyphertext) {
    printf("\n");
    printf("[!] Input troncato (più di 24 caratteri)        |  %s\n", troncato ? "Sì" : "No");
    printf("[!] Caratteri scartati al fine della cifratura  |  %d\n", scartati);
    printf("[!] Testo da processare (formatted-plaintext)   |  %s\n", plaintext);
    printf("[!] Testo cifrato (cyphertext)                  |  %s\n", cyphertext);
}

/* 
    cifra un testo opportunamente formattato secondo il cifrario di Vigenere 
    (credits: https://it.wikipedia.org/wiki/Cifrario_di_Vigen%C3%A8re)
 */
void cifrarioVigenere(const char *plaintext, char *cyphertext) {
    // chiave di cifratura
    char k[9] = "";

    printf("-- Inserisci la chiave di cifratura (8 caratteri): ");
    fgets(k, sizeof(k), stdin);
    // rimuove il carattere di newline (credits: https://www.ibm.com/docs/it/i/7.5?topic=functions-strcspn-find-offset-first-character-match)
    k[strcspn(k, "\n")] = '\0';
    ripulisciEFormatta(k, true);

    ushort j = 0;

    for (int i = 0; i < (int) strlen(plaintext); i++) {
        /* 
            CALCOLO MATEMATICO:

            plaintext[i] - 'a' individua la posizione numerica di ciascun carattere del plaintext tra 0 e 25 (dove il carattere ASCII 'a' corrisponderà a 0 invece che 97 e 'z' a 25 invece che 122)
            k[j] - 'a' individua la posizione numerica di ciascun carattere della chiave tra 0 e 25 (come sopra)
            sommando i due valori e facendo il modulo 26 si ottiene la posizione del carattere cifrato, cui viene riposizionato rispetto all'alfabeto ASCII (+ 'a')

            MECCANISMO con MATRICE: non implementato.
         */
        cyphertext[i] = (char) ((plaintext[i] - 'a' + k[j] - 'a') % 26 + 'a');
        j = (ushort) ((j + 1) %  strlen(k));
    }
        
    cyphertext[strlen(plaintext)] = '\0';
}

/* 
    cifra un testo opportunamente formattato secondo il cifrario di Playfair 
    (credits: https://it.wikipedia.org/wiki/Cifrario_Playfair)
 */
void cifrarioPlayfair(char *plaintext, char *cyphertext) {
    // viene utilizzata come matrice la variabile mPlayfair
    ushort colonna1 = 0, riga1 = 0, colonna2 = 0, riga2 = 0;
    
    formattaPlayFair(plaintext);
    
    // per ogni coppia di lettere del plaintext
    for(ushort i = 0; i < (ushort) strlen(plaintext); i += 2) {
        // individua la posizione (riga-colonna) di ciascuna lettera nella matrice mPlayfair
        for(ushort r = 0; r < 5; r++) {
            for(ushort c = 0; c < 5; c++) {
                if (mPlayfair[r][c] == plaintext[i]) {
                    riga1 = r;
                    colonna1 = c;
                }
                
                // individua la posizione della lettera successiva nel plaintext nella matrice mPlayfair
                if (i + 1 < (ushort) strlen(plaintext) && mPlayfair[r][c] == plaintext[i + 1]) {
                    riga2 = r;
                    colonna2 = c;
                }
            }
        }
        
        if (riga1 == riga2) {
            // se le lettere sono sulla stessa riga, si sostituisce la lettera con quella immediatamente a destra (ciclando a sinistra se necessario)
            cyphertext[i] = mPlayfair[riga1][(colonna1 + 1) % 5];
            cyphertext[i + 1] = mPlayfair[riga2][(colonna2 + 1) % 5];
        } else if (colonna1 == colonna2) {
            // se le lettere sono sulla stessa colonna, si sostituisce con quella immediatamente sotto
            cyphertext[i] = mPlayfair[(riga1 + 1) % 5][colonna1];
            cyphertext[i + 1] = mPlayfair[(riga2 + 1) % 5][colonna2];
        } else {
            // se le lettere non sono sulla stessa riga o colonna, ciascuna lettera viene rimpiazzata secondo il meccanismo del 'rettangolo' formato dalle due lettere
            cyphertext[i] = mPlayfair[riga1][colonna2];
            cyphertext[i + 1] = mPlayfair[riga2][colonna1];
        }
    }
    
    cyphertext[strlen(plaintext)] = '\0';
}

int main() {
    // flag per terminare il programma
    bool termina = false;
    // testo in chiaro e testo cifrato rispettivamente (max 24 caratteri + terminatore)
    char plaintext[25] = "";
    char cyphertext[25] = "";
    // modalità di cifratura scelta dall'utente
    int scelta = 0;
    
    printf("UniPG: esercizio cifrari. Made by https://www.github.com/matbagnoletti\n");
        
    while (!termina) {
        printf("\n**********************************************************************\n\n");
        printf("-- Seleziona il metodo di cifratura:\n");
        printf("1. Cifrario di Vigenere\n");
        printf("2. Cifrario di Playfair\n");
        printf("3. Termina\n\nScelta: ");
        scanf("%d", &scelta);
        pulisciBufferInput();
      
        switch(scelta) {
            case VIGENERE:
            case PLAYFAIR:
                printf("\n-- Inserisci il testo da cifrare (plaintext): ");
                if (fgets(plaintext, sizeof(plaintext), stdin)) {
                    if (strchr(plaintext, '\n') == NULL) { // controlla se il testo è stato troncato (credits: https://www.ibm.com/docs/it/i/7.5?topic=functions-strchr-search-character)
                        troncato = true;
                        pulisciBufferInput();
                    }
                    plaintext[strcspn(plaintext, "\n")] = '\0'; // rimuove il carattere di newline (credits: https://www.ibm.com/docs/it/i/7.5?topic=functions-strcspn-find-offset-first-character-match)
                } else {
                    printf("-- Errore durante la lettura del testo. Riprova.\n");
                    continue;
                }
      
                plaintext[strcspn(plaintext, "\n")] = '\0'; // rimuove il carattere di newline (credits: https://www.ibm.com/docs/it/i/7.5?topic=functions-strcspn-find-offset-first-character-match)
                ripulisciEFormatta(plaintext, false);
          
                if (scelta == VIGENERE) {
                    cifrarioVigenere(plaintext, cyphertext);
                } else {
                    cifrarioPlayfair(plaintext, cyphertext);
                }
                
                stampaEsito(plaintext, cyphertext);
                break;
          
            case TERMINA:
                termina = true;
                printf("\n**********************************************************************\n\n");
                break;
          
            default:
                printf("-- Scelta non valida. Riprova.\n");
                break;
        }
    }
        
    return 0;
}
