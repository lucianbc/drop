# Ball Fall
## Proiect Introducere in Robotica cu Arduino
Ball Fall este un joc dezvoltat pentru platforma Arduino si consta intr-o minge ce se deplaseaza in jos si o serie de palete ce se deplaseaza in sens opus. Scopul jocului este de a cadea pe o distanta cat mai mare, evitand paletele ce pot scoate mingea de pe suprafata display-ului in partea de sus.

### Gameplay
Initial jocul se afla in starea `INTRO`. Jucatorul poate deplasa bila pe directia x. Prin apasarea butonului de pe joystick jocul trece in starea `PLAYING`. La fiecare nivel coborat de bila, scorul jucatorului creste cu un punct. La fiecare 40 de puncte, viteza de urcare a paletelor creste cu 10 ms pana la limita de 200 ms. La fiecare 120 de puncte, jucatorul primeste o noua viata. De fiecare data cand bila este scoasa de pe suprafata de joc in partea de sus, jucatorul pierde o viata, iar cand acesta ajunge la 0 vieti, jocul trece in starea `OVER`. Aici jucatorul isi vede scorul, iar prin apasarea butonului, jocul este resetat si trecut in starea `PLAYING`.

## #Cerinte hardware
Jocul necesita o placuta Arduino, o matrice de LED-uri 8x8 controlata printr-un driver MAX 7219, un display LCD compatibil cu driver-ul Hitachi HD44780 si un joystick.

### Librarii externe
Jocul foloseste librariile LedControl, EventManager si LiquidCrystal pentru contrlul matricei de LED-uri, gestionarea evenimentelor intr-un mod asemanator asincron respectiv pentru controlul display-ului LCD. Primele doua se gasesc in folder-ul jocului, iar cea de-a treia este distribuita impreuna cu Arduino IDE.

### Descriere cod
Nucrelul jocului este implementat in clasa `ball_fall`. Aceasta pastreaza starea curenta a jocului, asupra careia pot fi efectuate urmatoarele comenzi:
* `move_ball(direction)`
* `drop_ball()` - returneaza scorul curent
* `pads_up()` - returneaza `true` daca jocul contrinua, `false` altfel
* `reset()`
* `add_life()`
Starea jocului poate fi interogata prin functiile:
* `get_lifes()`
* `get_score()`
* `print_matrix(char[8][8])` - seteaza parametrul cu ceea ce afiseaza jocul
* `print(char screen[8])` - seteaza parametrul cu ce afiseaza jocul formatat ca sir de octeti, special pentru afisarea pe matricea de LED-uri

Desfasurarea jocului pe implementarea hardware se gaseste in fisierul *ball_fall.ino* de unde sunt apelate comenzile si interogarile pe nucleul jocului, gestionate resursele hardware (display-uri, joystick), gestionata dificultatea prin rata la care sunt apelate comenzile si starea in care se afla jocul la un moment dat (INTRO, PLAYING, OVER).

Pentru programarea evenimentelor la anumite momente in timp este implementata clasa lifecycle_manager ce pastreaza o coada de pointeri de functii cu prioritatea data de momentul la care acestea se executa. Coada este implementata intr-o structura de tip min-heap. Capacitatea acestui heap poate fi setata prin redefinirea constantei `EVENT_COUNT`, setata la valoarea predefinita 20.

Pentru gestionarea evenimentelor de *buton apasat* si *game over* se foloseste libraria *EventManager*.
