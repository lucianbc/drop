# Ball Fall game
Jocul ales de mine se numește “Ball Drop” și constă într-o minge aflată în cădere și în zone solide, generate de către joc, care se deplasează în sus. Bila poate fi împinsă în sus de o astfel de zonă solidă, iar jocul se termină atunci când bila este împinsă de o zonă solidă în afara ecranului.
Jocul va folosi o matrice de led-uri ca mediu de desfășurare al jocului și un display LCD pentru informații suplimentare, cum ar fi scorul sau mesajul inițial adresat jucătorului. Controlul se va realiza printr-un joystick și printr-un buton
Inițial, jucătorului îi este prezentată o configurație în care bila este așezată pe o zonă solidă ce se întinde pe întreaga lățime a matricei. Bila poate fi deplasată, dar deplasarea zonelor solide și începutul jocului așteaptă apăsarea butonului din partea utilizatorului.
Odată ce jocul se încheie, pe matrice este desenat un model ce înștiințează jucătorul, iar restartul așteaptă apăsarea butonului.
Cu fiecare nivel coborât de bilă scorul jucătorului crește cu o unitate, iar la anumite scoruri viteza de urcare a zonelor solide crește, astfel crescând dificultatea jocului. Tot la un anumit număr de puncte, variabil în funcție de dificultatea curentă, jocul va genera puncte care pot fi colectate de jucător, acesta obținând vieți extra pentru ele. 
Mi-as dori ca, în funcție de timpul și resursele disponibile, să implementez și o metodă de persistare a scorurilor pe un card de memorie sau chiar într-o bază de date remote, accesată printr-un modul wi-fi.

