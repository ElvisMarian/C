Am creat o lista de directoare si una de fisiere.Am creat un director root si l-am alocat.
Prin delete_root l-am sters si am iesit din program
Am facut mai intai functia touch si apoi am facut exact aceeasi functie ,doar ca am adaptat-o pentru directoare.
Au fost cele mai grele de implementat.Mi-a luat ceva timp sa desenez pe foaie toate cazurile...
Cand am introdus elemente in liste(in cea de fisiere si in cea de directoare) am avut grija sa le sortez punand fiecare
fisier/director exact acolo unde ii este locul(ordine lexicografica).
La functia ls nu a trebuit decat sa parcurg cele doua liste si sa afisez numele fisierelor si directoarelor.
Functia pwd am implementat-o recursiv punand conditia ca directorul curent sa fie valid
Functia tree a fost destul de greu de implementat(din cauza ca am ales sa o fac recursiva).
Printam fisierele si apoi directorul curent(care trecea prin toate directoarele)
Pentru stergerea fisierlor a trebuit sa am grija sa dezaloc ceea ce am alocat in comanda touch si sa refac legaturile
in cazul in care fisierul care trebuia sters era la inceput sau prin lista.
Functia rmdir am implementat-o exact ca pe cea rm doar ca am adaptat-o la directoare.

