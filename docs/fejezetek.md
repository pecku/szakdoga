1. Bevezetés, mely tartalmazza
    - a témaválasztás indoklását, 
    - és a megoldandó feladat rövid, közérthető leírását.

2. Felhasználói dokumentáció, mely tartalmazza
    - a megoldott probléma rövid megfogalmazását,
    - a felhasznált módszerek rövid leírását,
    - a program használatához szükséges összes információt.

    - A feladat rövid ismertetése (mire való a szoftver)
    - Célközönség (kik, mikor, mire használhatják a programot)
    - A rendszer használatához szükséges minimális, illetve optimális HW/SW környezet
    - Első üzembe helyezés leírása – ha van ilyen –, a program indítása (kivéve, ha nem egy önálló alkalmazásról, hanem egy meglévő rendszer új komponenséről van szó). Itt ellenőrizzük, hogy a telepítési útmutató megfelel-e a valóságos telepítési folyamatnak.
    - Általános felhasználói tájékoztató (például a szokásostól eltérő képernyő-, billentyű-, illetve egérkezelés leírása, teendők hibaüzenetek esetén stb.).
    - A rendszer funkcióinak ismertetése. A feladat jellegéből fakadóan célszerű lehet ezt folyamatszerűen, képernyőképekkel alátámasztva bemutatni. A funkciókat ajánlatos a felhasználói szintek szerint csoportosítani. Itt vegyük figyelembe, hogy a leírás a fejlesztői dokumentációban meghatározott részfeladathoz illeszkedik-e, az ott meghatározott funkciókat/használati eseteket írja-e le?
    - A rendszer futás közbeni üzenetei (hibaüzenetek, figyelmeztető üzenetek, felszólító üze-netek stb.) és azok magyarázata – az esetleges üzemeltetési teendőkkel együtt. Itt vegyük figyelembe, hogy tartalmaz-e biztonsági, illetve hibaelhárítási előírásokat?
    - Egyéb, a szoftver használatához szükséges információk.


3. Fejlesztői dokumentáció, mely tartalmazza
    - a probléma részletes specifikációját,
    - a felhasznált módszerek részletes leírását, a használt fogalmak definícióját,
    - a program logikai és fizikai szerkezetének leírását (adatszerkezetek, adatbázisok, modulfelbontás),
    - a tesztelési tervet és a tesztelés eredményeit.

    Megoldási terv:
    - Rendszer architektúrájának leírását (alrendszerek, rétegek bemutatása, az alkalmazott szabványok, technológiák, fejlesztő módszerek megadása, felhasznált eszközök és kész komponensek definiálása). Az értékelésnél vegyük figyelembe, hogy mennyire válnak szét az alkalmazás rétegei (például felhasználói felület, logika, adat¬for¬rás)?
    - Az adatbázis – feltéve, hogy van – leírását. Érdemes egy áttekintő diagammal szemléltetni a táblákat és a köztük levő kapcsolatokat, majd külön táblázatokban megadni az egyes táblák mezőszerkezeti leírását, az esetleges tárolt eljárások, függvények, triggerek, stb leírását.
    - Modul és/vagy osztályszerkezet (fontosabb modulok és/vagy osztályok és azok metódusai, továbbá ezek kapcsolatának) leírását. Az egyes csomagok fő eljárásait illetve a fontos osztályok fő metódusait bemenő-, kimenőadat, tevékenység hármassal jellemezni kell.
    - A felhasználói felület – feltéve, hogy van –  tervét (a képernyő- és listaterveket, valamint a menütervet). Legyen egy áttekintő ábra, amely mutatja a képernyők (ablakok, weblapok) közti navigálási lehetőségeket, irányokat. Ki kell emelni a fontosabb felhasználói eseménykezeléseket.

    Tesztelés:
    - Tartalmaz-e tesztelési terveket, teszteseteket (Ezeket csoportosíthatja rendszerteszt és modultesztek szerint illetve fekete és fehérdoboz megközelítéssel)?
    - Beszámol-e olyan tanulságokról, amelyek alapján meg kellett változtatni a korábbi implementációs döntéseket, esetleg a terv egyes elemeit (az ilyen tapasztalatok nem rontják a dolgozat értékét)?
    - Tartalmazza-e nagy adattömeg melletti futtatások értékelését?
    - Elemzi-e a program által adott eredmény helyességét (különösen olyan optimalizációs feladatok esetén, ahol több helyes megoldást valamilyen célfüggvénnyel lehet rangsorolni)?
    - Elemzi-e a program futásának hatékonyságát?


4. Irodalomjegyzék (ha a téma szükségessé teszi): A szakdolgozatnak tartalmaznia kell azon forrásmunkákra való hivatkozásokat, amelyeket a hallgató a megoldás során felhasznált.

```
A könyvek idézésének formája a következő:
[<hivatkozási azonosítója>] <szerző neve>: <a könyv címe>, <a kiadó neve>, <a kiadás éve>, [<terjedelme>], <ISBN szám>. Például: [2] Jan Sommerville: Software Engineering, Addison Wesley, 1988, [742], ISBN-0201-42765-6.
Folyóiratcikk idézésének formája a következő:
[<hivatkozási azonosítója>] <szerző neve>: <a cikk címe>, <a folyóirat címe>, <Vol. száma>, <évszám>, [terjedelme].
Hálózaton elérhető forrásmunka esetén a „link” megadása után adjuk meg az elérés dátumát!
```

5. Mellékletek

