# Chucky

Chucky are in componenta senzori pentru mediul inconjurator(temperatura, luminozitate, umiditate), motoare electrice cu cutie de viteza, acestea fiind controlate de un microcontroler(Arduino Uno) , surse de alimentare mobile, senile pentru deplasare, adaptor bluetooth pentru a putea fi controlat cu ajutorul unui smartphone, driver de motoare si un Raspberry Pi pentru distribuirea tuturor datelor folositeare.

Scopul acestuia este de a explora medii neprielnice omului, transmitand date inapoi. Este controlat prin intermediul unei aplicatii Android, printr-o conexiune bluetooth. Datele importante, precum temperatura, luminozitatea, umiditatea, coordonatele si oritarea sunt transmise prin cablu Raspberry Pi-ului, care le preia cu ajutorul unui script si le posteaza in timp real pe un server Apache2 hostat local pe el. Pe acest site sunt diponibile si date despre Chucky.

Chucky foloseste un sistem inteligent prin care stie pozitia si orintarea lui in orice moment fara a folosii orice fel de senzor(accelerometru, GPS), in functie de comenziile pe care le primeste de la utilizator. Folosind coordonatele carteziene si orientarea acesta calculeaza si se intoarce cu succes la punctul de start.

Pentru creearea acestui sistem au fost folosite multiple limbaje de programare, Html, Css, Arduino si Python.
