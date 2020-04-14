#include <stdio.h>
#include <stdlib.h>

#define NUM 11

int compute(int* arr, int len)
{
    int sum = 0;
    int squares = 0;

    for (int i = 0; i < len; i++) {
        sum += arr[i];
        squares += arr[i] * arr[i];
    }
    return squares / sum;
}

int main(int argc, char** argv)
{
    int arr[NUM];

    for (int i = 0; i < NUM; ++i) {
        arr[i] = NUM / 2 - i;
    }

    printf("%d \n", compute(arr, NUM));

    return 0;
}

/*
Ein Core Dump ist eine Datei des dokumentierten Speichers eines Computers, wenn ein Programm oder ein Computer abgestürzt ist.
Neben dem Systemspeichers kann ein core dump folgende informationen beinhalten:
– Der Status des Prozessors
– Der Inhalt des Prozessorregisters
– Speicherverwaltungsinformationen
– Der Zähler und der Stapelzeiger des Programms
– Betriebssystem- und Prozessorinformationen und Flags

GNU ist der standard debugger bei linux systemen. GDB bietet die üblichen Möglichkeiten zur Ablaufverfolgung wie Breakpoints
oder die Ausgabe des Stacktrace, und ermöglicht ein Eingreifen in die Ausführung von Programmen.

Create core dump:
1. ulimit -c unlimited
<<<<<<< HEAD:Blatt_3/compute.c
2. call programm
3. gdb Programm -c core.PID  == a)
*/
=======
2. call gcc -g compute.c -o debug
3. gdb debug
4. Breakpoint 1, compute (arr=0x7fffffffddf0, len=11) at compute.c:15
15	    return squares / sum;
(gdb) p squares
$1 = 110
(gdb) p sum
$2 = 0
(gdb) Quit
(gdb)

*/
>>>>>>> a89bef25962b65039cf88ecf178ca98437a22c63:compute.c
