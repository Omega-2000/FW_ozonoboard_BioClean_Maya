# FW_ozonoboard_BioClean_Maya

**HARDWARE**
- Scheda BioClean / Scheda Maya
- Microcontrollore ESP32-C3 ( chip "ESP32-C3FN4" su scheda BioClean - modulo "ESP32-C3-MINI-1U" su scheda Maya )
- Alimentazione 220V AC necessaria per far funzionare l'uscita del triac, mentre il resto viene alimentato a 5V o 3V3
- Alimentazione collegata alla scheda BioClean tramite connettore "minifit" 1x2, mentre è collegata alla scheda Maya tramite morsetto dedicato
- Scheda collegata in ingresso al flussometro tramite connettore "JST" bianco, in uscita al led tramite connettore "MODU II" e sempre in uscita alle 2 uscite 220V AC tramite connettore "minifit" 2x2 sulla scheda BioClean, oppure tramite morsetti sulla scheda Maya

**AMBIENTE DI SVILUPPO**
- Visual Studio Code con estensione "PlatformIO"
- Ambiente e librerie di Arduino

**LINGUAGGIO DI PROGRAMMAZIONE**
- C++

**LIBRERIE**
- PIN_CONFIG : definizione gpio dei vari pin
- VAR_CONFIG : inizializzazione delle variabili e delle caratteristiche riguardanti il pwm
- PWM_CONFIG : inizializzazione delle caratteristiche inerenti al pwm dei colori dei 2 stati che il led può assumere, basata sulla libreria "PWM-MANAGER-3"

**FUNZIONAMENTO IN SINTESI**
- Il programma attenderà l'attivazione dell'interrupt che indicherà i "millis()" in cui il flussometro ha cambiato stato e di conseguenza il "loop()" cambierà stato dell'uscita dell'ozonizzatore (ATTIVA = quando l'acqua passa all'interno del flussometro , SPENTA = quando il flussometro è fermo) e cambierà colore al led in base allo stato attuale della macchina (VERDE = ozonizzatore spento, BLU = ozonizzatore attivo)

**FUNZIONAMENTO CODICE**
- IRAM_ATTR aux_isr() : funzione di interrupt che salverà i millis() in cui viene attivato e assegnerà lo stesso valore alla variabile "last_ok" (utilizzata all'interno del loop() per determinare lo stato della macchina) se vengono soddisfatte due condizioni

- setup() : inizializzazione pin, timer utilizzato dal pwm, colore dello stato del led e dell'interrupt

- loop() : a seconda del valore assunto dalla variabile "last_ok", e dai millisecondi passati dall'ultima attivazione dell'interrupt, il programma cambierà il colore del led e cambierà lo stato dell'uscita dell'ozonizzatore

**VERSIONI E DIFFERENZE**

La prima versione del FW di entrambe le schede aveva un'unica differenza: il tempo di spegnimento era di 2000ms e non di 100ms (era di 5000ms nei primi test)

**PROGRAMMAZIONE E PREPARAZIONE SCHEDE**

ISTRUZIONI PRESENTI ALL'INTERNO DEL FILE "MODIFICHE_V1.1.txt":

- PER RISOLVERE I PROBLEMI DI AVVIO IN UNA BOOT MODE SBAGLIATA
    - Rimuovere C4 su "BOOT" (gpio9)

- PER RISOLVERE IL PROBLEMA DEL LED ROSSO ALL'AVVIO -> DISABILITARE IL JTAG
    - Inviare da linea di comando di ESP-IDF : espefuse.py --port COMx burn_efuse DIS_PAD_JTAG 1
