Popa Marian-Elvis 323CC

Functia iocla_printf:
Am parcurs input-ul,si am mers pe urmatoarea idee:daca am % ma uit la 
urmatorul caracter,iar daca e tot %  il afisez si trec la mai departe(uramtoarea iteratie).
Daca al doilea caracter nu  e  % atunci incerc cazurile speciale(unsigned int,signed int,char,string,hexa).
Daca nu am niciunul din aceste cazuri atunci afisez fiecare caracter.
Pentru acele cazuri din switch mai intai am folosit va_arg,dupa care am folosit o functie de convertire care facea 
conversia unui numar intr-un string care reprezenta acel numar intr-o baza data de cazurile speciale
La cazul signed int afisam pur si simplu un - si apoi converteam numarul pozitiv,
dupa care il afisam si pe acesta.
Dupa fiecare afisare incrementam variabila in care retineam numarul
de caractere afisate(numberOfCharacters) cu numarul de caractere 
pe care tocmai l-am afisat.
Functia convert:
Am folosti un vector static care avea ca elemente caracterele din baza de numeratie
16 , un buffer si un pointer la char.
Puneam in ptr ceea ce aveam la indexul care era restul impartirii numarului la baza.
Si in final imparteam numarul la baza.Faceam acest lucru cat timp numarul
era diferit de 0,iar la final returnam pointer-ul meu.