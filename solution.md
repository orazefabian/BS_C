# Betriebssysteme Übungsblatt 2

## Aufgabe 2.2

Erklären Sie wofür die Dateien `/etc/passwd` und `/etc/shadows` in Linux-basierten
Systemen verwendet werden und wie diese aufgebaut sind. Wie kann das
Kommandozeilentool `man` verwendet werden, um Informationen zu diesen Dateien zu
erhalten?

### passwd-file

passwd is the file where the user information is stored.

- field 1: username
- field 2: password
- field 3: user-ID
- field 4: group-ID
- field 5: user information
- field 6: user's home directory

### shadow-file

shadow is the file where important information connected to the passwd-file is stored

- field 1: username
- field 2: hashed password of the user
- field 3-8: user account expiry information
- field 9: reserved for future use

### man

By using `man 5 passwd` you can look up helpful information about the file format and conventions. Same for the shadow file.

### csv-file

Run `./a.out > users.csv` to write the output to a csv-file.

## Aufgabe 2.4

Recherchieren Sie weiters den Begriff "**Header Guards**". Wofür benötigt man diese und worin liegen die Unterschiede zu der Direktive `#pragma once`?

### Header Guards

In the C and C++ programming languages, an `#include guard`, sometimes called a macro guard, **header guard** or file guard, is a particular construct used to avoid the problem of *double inclusion* when dealing with the include directive.

*Double inclusion* is a case, where two or more copies of code were indirectly included, which causes a **compilation error**.

**#pragma once**: To avoid the difficult and cumbersome way, in which header guards are written manually, most C implementations provide a non-standard `#pragma once` directive. This directive, inserted at the top of a header file, will ensure that the file is included only once.

## Aufgabe 2.5

Ein Kollege von Ihnen möchte ein C-Programm mit folgender Funktionalität schreiben:

- Es werden entweder 3 oder 4 Integer-Werte vom Benutzer eingelesen und in einem Array gespeichert.
- Das Programm zählt dabei wie oft der Benutzer den Wert 0 eingegeben hat.
- Im zweiten Schritt wird das Array auf die doppelte Größe erweitert, wobei einfach jeder Wert doppelt hintereinander vorkommen soll.

Sie finden seine Implementierung (bzw. seinen „Implementierungsversuch“) in der Datei
`debugging-with-valgrind.c`. Das Programm lässt sich kompilieren, funktioniert aber
nicht richtig.

1. Welche Fehler/Probleme können Sie in der Implementierung erkennen?
    - Array wird statisch mit Größe 4 angelegt.
    - zeros ist ein Pointer, obwohl ein int ausreichen würde.
    - Zeile 26: newarr Speicher wird mit Größe von int pointer erstellt, obwohl es integers beinhalten soll
    - Zeile 14: i < cnt und nicht <=
    - Zeile 15: nicht arr++, sondern arr + i, sonst laufen wir aus unserem Speicherbereich raus
    - Zeile 17: *zeros++; erhöht den zeros pointer und nicht den Wert, (*zeros)++; erhöht den Wert
    - Zeile 27: die lokale Variable newarr wird in der Methode mit neuer Adresse überschrieben und muss deshalb am Ende zurückgegeben werden.
    - Allokierter Speicher wird nicht wieder freigegeben!
2. Erklären Sie, welche Variablen des gegebenen Programms in welchem Speicherbereich abgelegt werden (Stack oder Heap).
    - Heap: zeros und newarr, da diese mit malloc dynamisch angelegt werden.
    - .bss (uninitialized data segment): static int cnt = 0; liegt hier
    - Stack: alle anderen Variablen, da diese lokal angelegt werden.
3. Verwenden Sie das Tool **valgrind**, um die Probleme des Programms aufzuspüren und korrigieren Sie diese. Lösen Sie dabei die Fehler Schritt für Schritt (aufgrund der Ausgabe von Valgrind) und beschreiben Sie die Ursachen der Fehler.
4. Welche Speicherzugriffsfehler konnten Sie mit Valgrind nicht finden und warum?
