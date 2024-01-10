# Prog2 gyakorló-konzi

[Mi ez az egész?](#mi-ez-az-egész) - [Hogyan navigálj?](#hogyan-navigálj) - [Expozíció](#expozíció) - [Probléma esetén](#probléma-esetén)

### Hasznos források

Ha már egyszer ide keveredtél, nem untatlak a tantárgyi oldallal (persze érdemes ott kezdeni), így a következőkben pár szubjektív kedvenc jön, amik számomra nagyban megkönnyítették a tárgy teljesítését.

- <https://prog2.cppftw.org/> - Dobra Gábor jegyzete, ami aztán (szerencsére) kinőtte magát. Rendkívül alaposan, de közérthetően magyarázza el a tárgyban megtalálható anyagot. 

- [C++ by The Cherno](https://www.youtube.com/playlist?list=PLlrATfBNZ98dudnM48yfGUldqGD0S4FFb) - YouTube videósorozat angolul, ami a nyelv legtöbb alapvető részét körüljárja 10-20 perces videókban, így könnyen emészthető is marad.

- <https://en.cppreference.com/> - általános referenciaoldal. Nem kell szeretni, de könnyen olvasható, és főleg STL tárolókhoz nagy segítség.

+1: [C++ Weekly With Jason Turner](https://www.youtube.com/@cppweekly) - Amennyiben komolyabban is érdekel a (modern) C++, a csatornán rengeteg rövidebb de érdekes témákat körüljáró videót találhatsz.

## Mi ez az egész?

A projekt célja a sok év alatt tapasztalt szükséges segítség megadása a hallgatóknak a Prog2 tárgy teljesítéséhez.
Az alapötlet egy olyan aszinkron környezet megteremtése, ahol a hallgatók saját tempójukban, változatos és tetszőleges feldolgozásmóddal, és nem utolsó sorban közérthető, valósághű példákkal találkozva tudják elsajátítani a tárgyhoz szükséges ismereteket.

Ezt lehetővé tevő mesélős sztori készül a projekthez, ahol annak teljes ívében egymáshoz kapcsolódó, projekt szintű feladatokkal találkozhat mindenki.
Ezek az egészen egyszerű, a C++ nyelv újdonságait ismertető gyakorlófeladatoktól a komolyabb, objektum-orientált gondolkodásmód fejlesztéséül szolgáló tervezési lépéseken mind keresztülvezetnek.
Készül YouTube sorozat is, ahol a projekt egyes szakaszait először narrálva vezetjük fel, majd egy példamegoldást is közlünk - a teljes ahhoz szükséges gondolatmenet levezetésével együtt.

### Ami nem cél

A projektnek nem célja és érdeke az előadásokat és laborokat helyettesíteni. A tananyag alapos elsajátításához elengedhetetlen a tantárgyi órákon való részvétel és figyelem, valamint a szükséges önálló felkészülés.

## Hogyan navigálj?

A projekt teljes kódbázisa elérhető GitHub-on. Ezen belül az egyes szakaszok különböző brancheken helyezkednek el, így ezek között navigálva lehet az egyre komplexebb feladatokkal megismerkedni.

Amennyiben saját tempódban szeretnél haladni, és nem a mintamegoldást másolni, érdemes a repository másolása után a kiinduló branchet kiválasztani, és erről egy újat létrehozva azon dolgozni.
A kiinduló projekt olyan szerkezetű, hogy ahhoz érdemben új kódnak nem kell kerülnie, minden változtatást mi fogunk rajta végezni.

## Expozíció

Feltörekvő gyakornokként új helyen kezdesz, ahol a dolgod nem más, mint egy régi, elavult és lassan kezelhetetnel kódbázis megmentése. Szerencsére nem vagy egyedül a bajban, de hosszadalmas és fárasztó munka lesz az biztos.

Mivel a projektet korábban egyedül fejlesztő mérnök végre nyugdíjba vonult, a cég tűzoltás gyanánt sok újonccal próbálja menteni a helyzetet. Már csak azért sem lesz könnyű dolgotok, mivel egy régi C-s kódbázist kell felújítanotok. "Persze nem olyan nagy a váltás", gondolták a fejesek, akik azt hallották erről a menő C++ nyelvről, hogy nagyon hasonló szerkezetű, szóval számukra ez volt az egyértelmű választás.

Feladatod tehát egy, a cég által fejlesztett időjárás állomás kódbázisának felújítása lesz. Ennek jelenlegi alapfunkciója csak a hőmérséklet és páratartalom mérése valamint megjelenítése, de persze egy-két jobb üzletet nyélbe ütve beterveztek már egy rakat újítást a félévre.

### Történetünk szereplői

#### István 👨‍💼

Egy, az IT szektorba keveredett menedzser. Nem teljesen érti, hogy mit csináltok, de a pénzt ő mozgatja. Lehet, hogy irreális vagy értelmetlen a projekt feladata, de ekkor szinte biztosan őt lehet okolni miatta.

#### Géza 👴

Az előző fejlesztő, aki rátok hagyta a kódbázist. Annó még assembly-ben kezdte, neki a C pont olyan nagy váltás volt, mint neked most a C++.

#### Aladár 👨‍🏫

Egy igazi géniusz, de magának való. Cégek között ugrál, most éppen ide vetette a sors. Bár segít, és szívesen mesél egy-két dologról, a végén úgyis azt mondja, hogy olvass dokumentációt, neki van jobb dolga.

#### Kriszta 👩‍💻

A másik frissen felvett junior fejlesztő. Igyekszik, de inkább mennyiségre törekszik, mint minőségre. Ha munkát kap, előbb-utóbb megcsinálja, de szinte biztos, hogy valamit javítanunk kell benne.

#### Te 👤

Végső soron ez a Te történeted. Javaslom, vegyél is benne aktívan részt.

## Probléma esetén

Amennyiben bármilyen problémát találsz a projekttel, nyugodtan nyiss egy [issue](https://github.com/itsthatMatthew/prog2gyakkonzi/issues)-t.