Client HTTP

- Baza temei a fost laboratorul de HTTP, de unde sunt folosite sursele
buffer.c, buffer.h, request.c, request.h, helpers.c, helpers.h cu mici modificari pentru a se potrivi cerintelor

- Pentru a mentine conexiunea deschisa, in fiecare iteratie a buclei while, se redeschide conexiunea cu serverul
- Pentru a reduce numarul de request-uri invalide catre server, fiecare comanda executa o verificare a parametrilor, dar si a
permisiunilor de acces
- Astfel, clientul nu va emite o cerere catre server de tipul 'add_book', 'delete_book', 'get_book' sau 'get_books' fara 
a avea permisiunile necesare de acces la biblioteca sau fara a fi logat
- Clientul nu va emite cereri catre server de tipul 'enter_library' sau 'logout' daca nu este logat
- Clientul nu va emite cereri cu id-uri invalide de carti si nu va adauga carti cu parametri "empty"
- Dupa fiecare cerere, clientul va astepta un raspund
- Daca raspunsul este de tipul "400 Bad Request", clientul va afisa un mesaj de eroare si
va printa raspunsul json primit de la server
- Toate payload-urile primite de la server sunt parsate si afisate in format json


