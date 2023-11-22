    .global main            ;Diese Direktive ist notwendig damit das Hauptprogramm global sichtbar wird und somit vom Linker verarbeitet (gefunden) werden kann.

main:                       ;Label - Hauptprogamm

    ;Anschlusspin PB5 als Ausgang definieren
    LDI ?, ?                ;Die Kostante PB5 (Stellenwert des LED-Anschlusspins) wird in ein ALU-Register geladen
    OUT ?, ?                ;Der Wert PB5 kann nun mit der ALU auf das Data Direction Register B (DDRB) geschrieben werden.
    
loop:                       ;Label - Endlosschleife

    ;Übergabeparameter (=Wartezeiten) für delay definieren
    LDI ?, ?                ;0 in R17 laden
    LDI ?, ?                ;0 in R18 laden
    LDI ?, ?                ;80 in R19 laden
    
    sbi ?, ?;               ;LED-Toggeln and PORTB

    ? ?                 	;Das Unterprogramm delay aufrufen            
    rjmp ?					;Zum Anfang der Schleife springen

delay:
    ? r17                 	;R17 dekrementieren. Hinweis R17 hat nach dem Überlauf wieder den Wert 0
    ? delay              	;Sprung auf delay ausführen wenn das Zero-Flag (Z) nicht gesetzt wurde

    ? r18                 	;R18 dekrementieren  
    brne delay              ;

    ? r19                 	;R19 dekrementeiren
    brne delay              ;

    ?                       ;Unterprogramm delay verlassen und zum Hauptprogramm zurückkehren
