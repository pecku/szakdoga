<table>
    <tr>
        <td rowspan="3">1.1</td>
        <td rowspan="3">Alkalmazás indítása</td>
        <td>GIVEN</td>
        <td>A program telepítve van.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A program indítása.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Megjelenik a kezdő ablak.</td>
    </tr>
    <tr>
        <td rowspan="3">1.2</td>
        <td rowspan="3">Kilépés</td>
        <td>GIVEN</td>
        <td>Az alkalmazás fut.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az ablak bezáró ikonjára kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Az alkalmazás bezáródik.</td>
    </tr>
    <tr>
        <td rowspan="3">2.1</td>
        <td rowspan="3">Új projekt</td>
        <td>GIVEN</td>
        <td>Az alkalmazás fut.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az új projekt menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Az alkalmazás figyelmeztet, hogy a nem mentett dolgok elveszhetnek.</td>
    </tr>
    <tr>
        <td rowspan="3">2.2</td>
        <td rowspan="3">Projekt betöltése</td>
        <td>GIVEN</td>
        <td>Az alkalmazás fut.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A projekt megnyitása menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Az alkalmazás figyelmeztet, hogy a nem mentett dolgok elveszhetnek.</td>
    </tr>
    <tr>
        <td rowspan="3">2.3</td>
        <td rowspan="3">Projekt mentése</td>
        <td>GIVEN</td>
        <td>Az alkalmazás fut.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A projekt mentése menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A projekt mentésre kerül, amennyiben korábban már meg volt adva a projekt mentési helye. Ha most mentjük először a projektet, az alkalmazás bekéri a projekt mentési helyét.</td>
    </tr>
    <tr>
        <td rowspan="3">2.4</td>
        <td rowspan="3">Adatok elvesztésének elfogadása</td>
        <td>GIVEN</td>
        <td>Új projekt létrehozása vagy projekt betöltése közben megjelenik a nem mentett adatok elvesztésére figyelmeztető felugró ablak.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A felugró ablakon az igen gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Elfogadtuk, hogy a folyamat során el fognak veszni a jelenleg nem mentett adatok.</td>
    </tr>
    <tr>
        <td rowspan="3">2.5</td>
        <td rowspan="3">Adatok elvesztésének elutasítása</td>
        <td>GIVEN</td>
        <td>Új projekt létrehozása vagy projekt betöltése közben megjelenik a nem mentett adatok elvesztésére figyelmeztető felugró ablak.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A felugró ablakon a nem gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A folyamat megszakad. Nem történik semmilyen változás.</td>
    </tr>
    <tr>
        <td rowspan="3">3.1</td>
        <td rowspan="3">Új komponens létrehozása</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A komponens szerkesztő részben az új komponens gombra, vagy a Create menüben az új komponens menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Megjelenik a komponens létrehozásához szükséges adatokat bekérő dialógusablak.</td>
    </tr>
    <tr>
        <td rowspan="3">3.2</td>
        <td rowspan="3">Új komponens létrehozásának megszakítása</td>
        <td>GIVEN</td>
        <td>Aktív az új komponens létrehozása dialógusablak.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az ablakon a vissza gombra kattintunk</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A folyamat megszakad. Nem történik semmilyen változás.</td>
    </tr>
    <tr>
        <td rowspan="3">3.3</td>
        <td rowspan="3">Új komponens létrehozása hiányos vagy helytelen adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív az új komponens létrehozása dialógusablak.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az ablakon lévő valamelyik mezőt nem töltjük ki, vagy helytelenül és az ok gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Az ablakon megjelenő hibaüzenet jelzi, hogy mit rontottunk el, ezen kívül történik változás.</td>
    </tr>
    <tr>
        <td rowspan="3">3.4</td>
        <td rowspan="3">Új komponens létrehozása helyes adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív az új komponens létrehozása dialógusablak.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az ablakon lévő mezőket helyesen kitöltöttük és az ok gombra kattintunk</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Eltűnik a dialógusablak és létrejön egy új komponens mind a nézeten, mind a háttérlogikában.</td>
    </tr>
    <tr>
        <td rowspan="3">3.5</td>
        <td rowspan="3">Egy komponens adat módosítása</td>
        <td>GIVEN</td>
        <td>Van legalább egy létrehozott komponens, amit szerkesztünk.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A komponens szerkesztő részben egy adott komponensben egy adatot módosítunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Az adat megváltozik mind a nézetben, mind a háttérlogikában.</td>
    </tr>
    <tr>
        <td rowspan="3">3.6</td>
        <td rowspan="3">Új adattag hozzáadása egy komponenshez</td>
        <td>GIVEN</td>
        <td>Van legalább egy létrehozott komponens, amit szerkesztünk.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A komponens szerkesztő részben egy adott komponensben rákattintunk az új adattag létrehozása gombra.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A komponensben megjelenik két új szövegbeviteli mező valamint az adattag törlésére szolgáló gomb.</td>
    </tr>
    <tr>
        <td rowspan="3">3.7</td>
        <td rowspan="3">Új metódus hozzáadása egy komponenshez</td>
        <td>GIVEN</td>
        <td>Van legalább egy létrehozott komponens, amit szerkesztünk.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A komponens szerkesztő részben egy adott komponensben rákattintunk az új metódus létrehozása gombra.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A komponensben megjelenik két új szövegbeviteli mező valamint a metódus törlésére szolgáló gomb.</td>
    </tr>
    <tr>
        <td rowspan="3">4.1</td>
        <td rowspan="3">Új kódblokk hozzáadása a main listához</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A main lista szerkesztő részben az új kódblokk gombra vagy a Create menüben az új kódblokk gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A listában megjelenik egy új üres listaelem.</td>
    </tr>
    <tr>
        <td rowspan="3">4.2</td>
        <td rowspan="3">Kódblokk szerkesztése</td>
        <td>GIVEN</td>
        <td>A main listában van legalább egy kódblokk.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Kiválasztjuk a szerkeszteni kívánt kódblokkot és duplán kattintunk rá.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A listaelem szerkeszthetővé válik és várja az új szöveg beírását.</td>
    </tr>
    <tr>
        <td rowspan="3">4.3</td>
        <td rowspan="3">Kódblokk szerkesztése</td>
        <td>GIVEN</td>
        <td>A main listában egy kódblokk szerkesztési módban van.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Beírjuk a kívánt kódrészletet és entert nyomunk vagy elkattintunk valahova.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A listaelem szerkesztése befejeződik, a kódblokk tartalma megváltozik mind a nézetben, mind a háttérlogikában.</td>
    </tr>
    <tr>
        <td rowspan="3">4.4</td>
        <td rowspan="3">Listaelem törlése</td>
        <td>GIVEN</td>
        <td>A main listában szerepel legalább egy listaelem.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Kijelölünk egy listaelemet és a törlés gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Felugrik egy ablak, amely megerősítést vár, hogy biztosan törölni szeretnénk-e az adott komponenst, vagy kódblokkot.</td>
    </tr>
    <tr>
        <td rowspan="3">4.5</td>
        <td rowspan="3">Törlés dialógusablak beleegyezés</td>
        <td>GIVEN</td>
        <td>A törlésre való megerősítést kérő dialógusablak aktív.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az ablakon az igen gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A kiválasztott elem törlésre kerül mind a nézeten, mind a háttérlogikában.</td>
    </tr>
    <tr>
        <td rowspan="3">4.6</td>
        <td rowspan="3">Törlés dialógusablak visszalépés</td>
        <td>GIVEN</td>
        <td>A törlésre való megerősítést kérő dialógusablak aktív.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>Az ablakon a nem gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A folyamat befejeződik, nem történik semmilyen változás.</td>
    </tr>
    <tr>
        <td rowspan="3">5.1</td>
        <td rowspan="3">Forráskód generálása</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Minden kötelezően kitöltendő mező ki van töltve.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A forráskód generálása gombra vagy a Generate menüben a forráskód generálása menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>Legenerálódik a forráskód, benne mindennel, amit a felületen megadtunk és beállítottunk.</td>
    </tr>
    <tr>
        <td rowspan="3">5.2</td>
        <td rowspan="3">Forráskód generálása</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Nem minden kötelezően kitöltendő mező ki van töltve.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A forráskód generálása gombra vagy a Generate menüben a forráskód generálása menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A forráskód szöveges mezőben megjelenik egy hibaüzenet, amely arra kér, hogy minden kötelezően kitöltendő mezőt töltsünk ki.</td>
    </tr>
    <tr>
        <td rowspan="3">6.1</td>
        <td rowspan="3">Fordítás helyes adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Minden kötelezően kitöltendő mező ki van töltve és a kódunk helyes.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A fordítás gombra vagy a Build menüben a fordítás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A fordítás kimenetét megjelenítő szövegmezőben nem jelenik meg semmi, ezzel jelezve, hogy nem fordult elő semmilyen hiba a fordítás során.</td>
    </tr>
    <tr>
        <td rowspan="3">6.2</td>
        <td rowspan="3">Fordítás helytelen adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Minden kötelezően kitöltendő mező ki van töltve és a kódunk helyetelen.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A fordítás gombra vagy a Build menüben a fordítás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A fordítás kimenetét megjelenítő szövegmezőben megjelenik a fordítás kimenete, amely tartalmazza a kódban rejtőző hibákat.</td>
    </tr>
    <tr>
        <td rowspan="3">6.3</td>
        <td rowspan="3">Fordítás hiányzó adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Nincs minden kötelezően kitöltendő mező kitöltve.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A fordítás gombra vagy a Build menüben a fordítás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A forráskód szöveges mezőben megjelenik egy hibaüzenet, amely arra kér, hogy minden kötelezően kitöltendő mezőt töltsünk ki.</td>
    </tr>
    <tr>
        <td rowspan="3">6.4</td>
        <td rowspan="3">Fordítás fordító konfiguráció nélkül</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Nincsenek megadva a fordító adatai.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A fordítás gombra vagy a Build menüben a fordítás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A fordítás kimenetét megjelenítő szövegmezőben megjelenik egy hibaüzenet, ami arra kér, hogy állítsuk be a fordító adatait.</td>
    </tr>
    <tr>
        <td rowspan="3">6.1</td>
        <td rowspan="3">Futtatás helyes adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Minden kötelezően kitöltendő mező ki van töltve és a kódunk helyes.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A futtatás gombra vagy a Build menüben a futtatás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A futtatás kimenetét megjelenítő szövegmezőben megjelenik a futtatott program kimenete.</td>
    </tr>
    <tr>
        <td rowspan="3">6.2</td>
        <td rowspan="3">Futtatás helytelen adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Minden kötelezően kitöltendő mező ki van töltve és a kódunk helyetelen.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A futtatás gombra vagy a Build menüben a futtatás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A futtatás kimenetét megjelenítő szövegmezőben megjelenik a fordítás kimenete, amely tartalmazza a kódban rejtőző hibákat.</td>
    </tr>
    <tr>
        <td rowspan="3">6.3</td>
        <td rowspan="3">Futtatás hiányzó adatokkal</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Nincs minden kötelezően kitöltendő mező kitöltve.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A futtatás gombra vagy a Build menüben a futtatás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A forráskód szöveges mezőben megjelenik egy hibaüzenet, amely arra kér, hogy minden kötelezően kitöltendő mezőt töltsünk ki.</td>
    </tr>
    <tr>
        <td rowspan="3">6.4</td>
        <td rowspan="3">Futtatás fordító konfiguráció nélkül</td>
        <td>GIVEN</td>
        <td>Aktív mentett vagy nem mentett projektben vagyunk. Nincsenek megadva a fordító adatai.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A futtatás gombra vagy a Build menüben a futtatás menüpontra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A futtatás kimenetét megjelenítő szövegmezőben megjelenik egy hibaüzenet, ami arra kér, hogy állítsuk be a fordító adatait.</td>
    </tr>
    <tr>
        <td rowspan="3">7.1</td>
        <td rowspan="3">Futtatás vagy fordítás leállítása</td>
        <td>GIVEN</td>
        <td>Elindítottunk egy fordítást vagy egy futtatást, amely éppen aktív.</td>
    </tr>
    <tr>
        <td>WHEN</td>
        <td>A leállítás gombra kattintunk.</td>
    </tr>
    <tr>
        <td>THEN</td>
        <td>A program leállítja a fordításért vagy futtatásért felelős háttérfolyamatot.</td>
    </tr>
</table>