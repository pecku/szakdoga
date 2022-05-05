
### MainWindow

A fő ablak felépítése widgetek, layoutok és splitterek segítségével van megvalósítva, így az ablak méretének változtatásakor dinamikusan igazodik hozzá a tartalom, valamint az egyes részek méretét külön is tudjuk változtatni.

Az init függvények biztosítják, hogy minden eleme a nézetnek megfelelően inicializálva legyen a program indulásakor.

- __initDialogs()__: Létrehozza a dialogusablakokat, betölti a szükséges tartalmakt, valamint összeköti a megfelelő signalokat és slotokat.
- __initActions()__: Létrehozza az akciókat, amelyek a menü és a felületen található gombok működéséhez elengedhetetlenek. Felépíti szükséges signal-slot kapcsolatokat.
- __initMenuBar()__: Létrehozza a menüelemeket, valamint hozzáadja a menüpontokhoz a megfelelő akciókat.
- __initComponentEditorSegment()__: Létrehozza a komponensszerkesztő részhez szükséges elemeket, majd felépíti és összekapcsolja azokat a megfelelő kinézet elérése érdekében. 
- __initListSegment()__: Létrehozza a listához szükséges elemeket, módosítja a lista beállításait a kívánt kinézet és működés elérése érdekében.
- __initSourceSegment()__: Létrehozza a forráskód nézegető, valamint a futtatáshoz és fordításhoz szükséges elemeket.

A MainWindow működése ezen felül főleg slotokkal valósul meg.

- createComponent(): Az új komponens létrehozását segítő dialógusablak által szolgáltatott információk segítségével eldönti, hogy milyen típusú komponenst szeretnénk létrehozni. Ezek alapján létrejön történik egy modell hívás, amely során létrejön egy új komponens a háttérben és ezt követően a megfelelő objektumok létrehozásával a nézet hozzáadja a komponens szerkesztő részhez az adott komponens widgetet, valamint a main listába is bekerül egy új elem, ha ez szükséges.
- deleteComponent(): A jelenleg kijelölt komponenst törli, mind a nézetben való minden megjelenését, mind a modellben róla tárolt adatokat.
- generateSource(): A forráskód generálását elindítő függvény. Minden komponens widgeten lefuttat egy ellenőrzést, hogy minden kötelezően kitöltendő mező ki lett-e töltve. Ha valami hiányzik, a felületen piros keretekkel jelezzük, valamint a forráskód nézegetőben is megjelenik egy üzenet ezzel kapcsolatban.
Ha az ellenőrzés mindent rendben talált, a modell legenerálja a forráskódot, amely ezután forráskód nézegetőben megjelenik.
- changeSelectedComponent(): Amikor a main listában egy elemre kattintunk, a komponens szerkesztő részben a hozzá tartozó komponens (ha van ilyen) kerül nyitott állapotba.
- refresh(): Egy projekt betöltése után ez az a függvény, amely minden adatot, amelyet a modell biztosít, betölt a nézetbe. Létrehoz minden szükséges widgetet és feltölti azokat a megfelelő adatokkal.
- clear(): Egy új létrehozásakor vagy egy projekt betöltése előtt ez a függvény felel minden jelenlegi nézetelem törléséért.

Az itt nem említett függvények nevükből adódó egyértelmű működést biztosítanak.

### ComponentWidget, ProcedureWidget, EnumeratorWidget

A ComponentWidget szolgál a ProcedureWidgetben és az EnumeratorWidgetben található közös elemek és funkciók biztosítására. Az utóbbi kettőben található eltérések főleg a felülírandó metódusokban és egymással való kapcsolatukban valósulnak meg.

### StructWidget

A StructWidget hasonló tulajdonságokkal rendelkezik, mint az előzőekben említett komponens widgetek. A kevesebb funkcionalitás miatt a felépítése egyszerűbb.

### MemberWidget és CustomMethodWidget

Ez a két widget előre meghatározott kinézettel és előre definiált singalokkal rendelkezik. Azért van rájuk szükség, hogy leegyszerűsítse a komponensekben elérhető új adattag és új metódus funkciók működését azzal, hogy egy egységként hozzáadhatóak ezek az elemek.

### PopUpTextEdit és TextInputDialog

A PopUpTextEdit widget egy szövegmező, amelyet az előzőekben említett widgetek használnak. A szövegmező közvetlenül a felületen is megjelenik, de a tartalma ott nem szerkeszthető. Tartalom hozzáadásához rá kell kattintani, így megjelenik egy TextInputDialog, amelyben egy szerkesztő widget található, ahol a szövegmező tartalma szerkeszthető.

