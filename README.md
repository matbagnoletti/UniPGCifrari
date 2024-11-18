<h1 align="center">UniPG: esercizio cifrari</h1>

<p align="center" style="font-family: monospace">Made by <a href="https://github.com/matbagnoletti">@matbagnoletti</a></p>
<p align="center" style="font-family: monospace">Matteo Bagnoletti Tini | matricola n° 377156</p>
<p align="center" style="font-family: monospace">Corso di Programmazione Procedurale I° anno a.a. 2024/2025, <a href="https://www.dmi.unipg.it/didattica/corsi-di-studio-in-informatica/informatica-triennale">UniPG - DMI</a></p>
<p align="center">
    <img src="https://img.shields.io/github/last-commit/matbagnoletti/UniPGCifrari?style=for-the-badge" alt="Ultimo commit">
    <img src="https://img.shields.io/github/languages/top/matbagnoletti/UniPGCifrari?style=for-the-badge" alt="Linguaggio">
</p>

## Descrizione
Esercitazione assegnata nell'ambito del corso di Programmazione Procedurale del primo anno di Informatica presso l'Università degli Studi di Perugia.

## Requisiti
- [gcc](https://www.gcc.gnu.org/) (utilizzata v13.2.0) o altro compilatore C analogo

È possibile visualizzare la versione già presente sul proprio dispositivo mediante il seguente comando:
```bash
gcc -v
```

## Richiesta dell'esercizio
Realizzare un programma in C che permetta all'utente di cifrare un messaggio utilizzando, a scelta, o il [cifrario di Vigenère](https://it.wikipedia.org/wiki/Cifrario_di_Vigen%C3%A8re) o il [cifrario di Playfair](https://it.wikipedia.org/wiki/Cifrario_Playfair).
Per una visione più approfondita del testo e delle richieste del progetto, **consultare il file PDF disponibile al seguente [link](https://francescosantini.sites.dmi.unipg.it/exercises/progI/esercizio2425.pdf)**.

## Soluzione proposta
Il programma permette all'utente di cifrare un messaggio utilizzando il cifrario di Vigenère o il cifrario di Playfair.
Per quanto riguarda il primo, l'utente dovrà inserire una chiave di cifratura (verme) di lunghezza massima 8 caratteri, mentre per il secondo verrà utilizzata la matrice 5x5 di Playfair generata a partire dalla parola "<code>ESEMPIO</code>".

Il programma si occuperà di formattare e ripulire sia il messaggio in chiaro (<code>plaintext</code>) che la chiave di cifratura, in modo tale da avere stringhe composte esclusivamente da caratteri alfabetici inglese in minuscolo (vedi <code>formatted-plaintext</code>).
Infine verrà mostrato a video il messaggio cifrato (<code>ciphertext</code>), nonché informazioni utili quali il numero di caratteri scartati e se il messaggio è stato troncato o meno. 

## Installazione e utilizzo
Per poter utilizzare il programma, è necessario seguire i seguenti passaggi:
1. Effettua il clone della repository con il comando:
   ```bash
   git clone https://www.github.com/matbagnoletti/UniPGCifrari.git
   ```
   In alternativa, effettua il download del file compresso del progetto ed estrailo in una cartella locale del tuo computer.
2. Nel terminale, spostati nella cartella del progetto:
   ```bash
   cd UniPGCifrari
   ```
3. Compila il codice sorgente:
   ```bash
    gcc soluzione.c -o [eseguibile] -std=c11
    ```
4. Esegui il programma:
    ```bash
    ./[eseguibile]
    ```

