# 1. szakasz - nem objektum-orientált újdonságok

Alaptörténet, feladatok és megoldások.

A szakasz érinti:
[névterek](#ismertető---névterek),
[I/O streamek](#ismertető---io-streamek),
[include guardok](#1-részfeladat---egyszerű-függvény-írása),
[`inline` kulcsszó](#2-részfeladat---függvénydefiníció-fejlécfileba-helyezése),
[referencia típus](#3-részfeladat---paraméterek-közvetlen-elérése),
[kivételek dobása és kezelése](#4-részfeladat---kivételek),
[függvénynév túlterhelése](#5-részfeladat---függvénynév-túlterhelése),
[alapértelmezett paraméterek](#6-részfeladat---alapértelmezett-paraméterek),
[függvénysablonok](#7-részfeladat---függvénysablonok).

Amennyiben egy-egy részfeladat után pihennél, vagy akár utánaolvasnál részletesebben valamelyik témának, nyugodtan. Magam sem ajánlom az egész szakasz egyben végigpörgetését - ez a törzsanyagban 2 hetet fed le!

## Alaptörténet

Így, hogy Géza itt hagyta a céget, István elérkezettnek látta az időt, hogy a kódbázis teljes felújításon essen át.
Célja persze az is, hogy így új funkciókkal könnyebben lehessen majd bővíteni a piacra dobott terméket, viszont amíg nem lát eredményeket, se a befektetőknek, se nektek nem hajlandó semmit mondani.

Aladár a főprogram szerkezetét már újraírta, így a termék legalapvetőbb funkciói (a szenzor és a kijelző) hiba nélkül működnek. Istvánnal egyeztetve elhatározták, hogy az állomásba egy olyan plusz funkciót vezetnek be, aminek a segítségével a felhasználó maga választhat, hogy Celsius vagy Fahrenheit értékben szeretné megjeleníteni a hőmérsékletet, hiszen ez nagyban megnövelheti a termék keresletét.

Így István Krisztának feladatként azt osztotta ki, hogy írjon olyan kódot, ami ezt a Celsius-Fahrenheit átváltást meg tudja tenni.
Aladár Erre javasolta, hogy készítsen egy új header-forrásfile kettőst `idojaras_szamitasok` névvel, és ezekbe dolgozzon.

Kriszta ugyan ezt el is kezdte, de elakadt a munkában. Kétségbeesésében téged kért meg, hogy segíts neki befejezni határidőre, és mivel nem szeretnél konfliktust szítani, inkább bele is vágsz a munkába, hiszen tényleg vészesen rövid időn belül el kéne készülni a kóddal.

## Ismertető - névterek

Pár apróság, mielőtt még belekezdünk. Vannak a C++ nyelvnek olyan újdonságai, amiknek C-ben szinte egyáltalán nincsenek is megfelelőik, így nem is igazán lehet átvezetni őket egyik példáról a másikra.

Ebből az okból kiindulva ezeket "fun-fact" jelleggel Aladár ledarálta neked, hogy biztosan ismerd a projekthezhez szükséges újdonságokat. Az első ilyen az úgynevezett névterek és felhasználásuk.

C-ben ha több függvény vagy struktúra összetartozását jelölni szerettük volna, nagyjából annyit tehettünk, hogy minden hozzá tartozó kifejezést egy adott prefixummal láttunk el. C++ már lehetőséget ad arra, hogy ilyen közös prefixumokat ne a kifejezésekhez kelljen hozzáírnunk, hanem az összetartozó kódot névterekbe helyezzük el, melyen belül minden közvetlenül látja egymást, azonban kívülről csak a névtér nevének felhasználásával érhetjük el a benne tartalmazott elemeket.

```cpp
// @file idojaras_szamitasok.h

namespace idojaras_allomas {
  int celsius_to_fahrenheit(int celsius);
}
```

Ha kiszerveztük a szükséges kódrészletet a megfelelő névtérbe, a `::` operátort felhasználva tudjuk azt a névteren belül elérni.

```cpp
idojaras_allomas::celsius_to_fahrenheit(20); // a névtérben található függvényt használjuk
```

A `using` kucslszó segítségével lehetőségünk van egyes elemeit a névtérnek közvetlenül elérhetővé tenni.

```cpp
using idojaras_allomas::celsius_to_fahrenheit;
celsius_to_fahrenheit(20); // csak ezt az egy függvényt érjük el közvetlenül
```

Valamint akár a teljes névteret is "kinyithatjuk", bár ezzel pont a konstrukció előnyeit veszítjük el.

```cpp
using idojaras_allomas;
celsius_to_fahrenheit(20); // bármit ami a névtérben található közvetlenül elérünk
```

Az utolsó kettő esetet érdemes csak függvényen belül felhasználni, hogy ne a terres forrásfilera legyenek érvényesek. Ennek megfelelően fejlécfileban névteret kinyitni az összes azt tartalmazó forrásfileban érvényesülni fog, így ez kifejezetten rosz öttlet.

> Egy névtérbe tetszőlegesen sok mindent elhelyezhetünk, valamint akár ágyazhatjuk is őket egymásba. Amennyiben valamit nem helyeztünk explicit névtérbe, tehát az úgynevezett "globális névtérben" található, akkor is a `::` operátort tudjuk felhasználni ennek egyértelműsítésére, csak ekkor nem kell semmit elé írnunk.

> C++-ban az alapvető (STL - Standard Template Library) headerekben található alapvető függvények és eszközök az úgynevezett `std` névtérben találhatóak.

## Ismertető - I/O streamek

Egy másik korábban még nem látott konstrukció az úgynevezett "stream"-ek. Működésüket most nem is fogjuk részletezni, a félév során szépen fel fog épülni akár a megírásukhoz is szükséges ismeretek, azonabn használatuk meglehetősen egyszerű.

Az alapvető konzolos kommunikációra felhasznált streamek az `iostream` fejlécfileban találhatóak, és lényegében a `scanf()` és `printf()` függvények elegánsabb kiváltását teszik lehetővé. Beolvasásra az `std::cin`, kiírásra az `std::cout` használható az "extraction" `>>` és "insertion" `<<` operátorokkal.

```cpp
#include <iostream>

int main() {
  int celsius = 0;
  std::cout << "Mennyi a homerseklet Celsiusban?" << std::endl;
  std::cin >> celsius;
  std::cout << "Homerseklet Fahrenheitben: " << celsius_to_fahrenheit(celsius) << "F";
}
```

> Az `std::endl` sortörésen kívül a teljes puffert üríti, így gyakori használata, például ciklusban egyszerűen `"\n"` használatával sokkal gyorsabbá tehető.

Mikrokontrolleres kis példáinkban kezdetben pont nem ezeket a streameket fogjuk felhasználni a kényes LCD kijelzőre írás végett, azonban konzolos PC-s környezetben nagyban megkönnyítik az életünket.

> Az ilyen I/O streamekhez rengeteg módosító elérhető, amik a formázást befolyásolják valamilyen módon, ezeknek érdemes utánanézni. Fontos még azt is megjegyezni, hogy az `<<` és `>>` operátorokat bitkezelésnél láttuk már, újrafelhasznásuk módjáról a szakasz vége felé fogunk találkozni.

## 1. Részfeladat - egyszerű függvény írása

Mindezek után Kriszta tehát arra kér, hogy az `idojaras_szamitasok.h` és `idojaras_szamitasok.cpp` fileokban elkezdett `int celsius_to_fahrenheit(int);` prototípusú függvényt kidolgozd.

Magát a projektet az `IdojarasAllomas` mappában találod. A projekt alapvető szerkezete olyan, hogy mikrokontrollerre lehessen fordítani, de te ettől ne ijedj meg, ilyen ismeretekhez a feladatok megoldásához nincsen szükséged.

A forráskód az `src` mappában található. Ebben kell dolgoznod. Reményeink szerint a projekt végső kiadása olyan lesz, hogy a feladat platformfüggetlenül tudjon fordulni és futni, ezzel megkönnyítve az otthoni példamegoldást és tesztelést.

> 🚦 *Akkor érdemes továbbhaladnod, ha az eddigi résszel már megpróbálkoztál.*

### Megoldás

Az első, aminek fel kellhet tűnnie, az az include guard hiánya, erről sajnos Kriszta megfeledkezett, de C++-ban sem hagyhatjuk el őket (hiszen a fordítási folyamat nagyrészt megegyezik a C-ben megismertekkel). Javítsuk ki a hibáját! Ez formailag például az alábbi módon nézhet ki:

```cpp
// @file idojaras_szamitasok.h
#ifndef IDOJARAS_SZAMITASOK_INCLUDED
#define IDOJARAS_SZAMITASOK_INCLUDED

namespace idojaras_allomas {
  // érdemi kódrészlet, jelen esetben:
  int celsius_to_fahrenheit(int);
}

#endif
```

> A legtöbb fordító ismeri az úgynevezett `#pragma` direktívákat. Fontos, hogy ezek egyáltalán nem képzik az ISO C++ standard részét, de bizonyos változatokat az összes "valamire való" támogat. Az egyik ilyen a `#pragma once` direktíva, aminek pontosan az a jelentése, hogy az adott header csak egyszer legyen feldolgozva, ezzel a klasszikus többszöri `#include` problémát feloldva (amire az include guardok jelentették eddig a megoldást).
```cpp
// @file idojaras_szamitasok.h
#pragma once

namespace idojaras_allomas {
  int celsius_to_fahrenheit(int);
}
```

Így, hogy ezt javítottuk, már csak Kriszta kétségbeesett kommentjével kell foglalkoznunk. Akár egy google kereséssel is gyorsan megtalálhatjuk a képletet: `F = (C × 9/5) + 32`. Ezt felhasználva tehát valami hasonló megoldásra kell jutnunk:

```cpp
// @file idojaras_szamitasok.cpp

namespace idojaras_allomas {
  int celsius_to_fahrenheit(int celsius) { return (celsius * 9) / 5 + 32; }
}
```

Mivel `int` értékekkel dolgozunk, levágásra számíthatunk, de a szorzást előbb végezzük el, mint az osztást, így a visszatérési érték legalább egészrészében helyes lesz.

## 2. Részfeladat - függvénydefiníció fejlécfileba helyezése

Megoldásunkat látva Kriszta nagyon megüröl, de egyből van egy kifogása: ha egyszer ilyen rövid a kód, minek szervezzük ki külön forrásfileba? Sokkal egyszerűbben kezelhető, ha egyből a fejlécfileban található, így nem kell két helyen kezelni ezt a kevés kis kódot.

Mivel nekünk is megtetszik az ötlet, úgy döntünk megtesszük. Ráadásul eszünkbe jut, amit Aladár mesélt egyszer: amennyiben a függvény definíciója egy adott forrásfileban található, azt a fordító külön fordítási egységként kezeli a többitől. Ez azt jelenti, hogy amennyiben egy rövid függvény deklarációja és definíciója szét van bontva, a fordító nem tud olyan alapvető optimalizációkat elvégezni, mint a függvényhívás helyett a törzset az adott kódrészletbe beilleszteni Pedig egy ilyen rövidke függvénynél ezzel igen is sokat nyernénk!

> Tegyünk tehát eleget Kriszta kérésének, és írjuk át az `int celsius_to_fahrenheit(int);` függvény definícióját egyenesen a headerbe!

Azonban amint ezzel megvagyunk, egy aprócska komplikáció fel is merül. Gézának a régi kódja Fahrenheit értékekkel tudott dolgozni, viszont ez a relikvia a mai napig sajnos a kódbázis részét képzi a `weathercalc.c` forrásfile formájában. Hogy Kriszta ezt egy kicsit megpatkolja, a `celsius_to_fahrenheit()` függvényt fel is használta benne.

Viszont így, hogy a függvény definícióját a fejlécfileba mozgattuk, a fordító több helyre is beilleszti (`main.cpp`, `weathercalc.c`), ezzel pedig többszörös definíció miatt hibaüzenetet kapunk, és nem fordul a programunk. Mégis hogyan tudnánk feloldani a problémát?

> 🚦 *Akkor érdemes továbbhaladnod, ha az eddigi résszel már megpróbálkoztál.*

### Megoldás

Mivel a kódoptimalizáció előnyét nem akarjuk elveszíteni, de a kódunk így hibás, valamit tennünk kell. Szerencsére a nyelv támogat egy olyan kulcsszót, ami pontosan az ilyen esetekre lett kitalálva. Ez az `inline`. Ha ezt a függvény elé kitesszük, a fordító már nem fog hibát jelezni:

```cpp
// @file idojaras_szamitasok.h

namespace idojaras_allomas {
  inline int celsius_to_fahrenheit(int celsius) { return (celsius * 9) / 5 + 32; }
}
```

Fontos a teljes kontextus, hogy megértsük, az `inline` mit is csinál pontosan: mint láttuk, ahhoz kell, hogy a fordító elfogadjon többszöri definíciót "egyként". Azt mondjuk vele, hogy ha ezzel a függvénynek a definíciójával a fordítás során többször is találkozol, igérjük, az ugyan az a függvénytörzs.

Mindezek után a fordító felelőssége lesz majd azt eldönteni, hogy a kódot az optimalizációs értelemben is "inlineolja"-e, az az a függvényhívást egszerűen a törzs behelyettesítésével pótólja. Viszont ennek megtörténéséhez elengedhetetlen, hogy a törzs mindig jelen legyen az adott fordítási egységben, mely alapból hibát okozna, viszont ezt íly módon fel tudjuk oldani.

> Minden fejlécfileban elhelyezett függvénydefiníciónak szükségszerűen `inline`-nak kell lennie!

## 3. Részfeladat - paraméterek közvetlen elérése

Krisztának azonban támadt még egy ötlete a függvényhez: amennyiben értelmetlen értéket kap paraméterül (ez a szenzor specifikációja alapján 0°C alatti és 50°C fölötti érték lehet), ezt hibaként jelezze!

Elsőre Aladár öttlete remekül hangzik. A hibajelzés egy nagyon hasznos és értékes eszköz lehet a programunkban, hogy bizonyos kondíciók esetén más működést váltsunk ki. Már csak az a kérdés, hogy hogyan tudjuk ezt elérni? Mivel a függvényünk visszatérési értékét másra használjuk, mint hibakezelés, más eszközhöz kell nyúlnunk. A probléma kezelésére C-s ismereteink alapján nagyjából három dolgot tudunk elképzelni:

- A visszatérési érték hibajelként való kezelése, de ezt már kilőttük,
- Globális változókban hibakódok tárolása (amik mikrokontrolleres kontextusban sokkal gyakrabban előfordulnak), de ezek használata továbbra is ellenjavallott,
- Plusz paraméter cím szerint átvéve, hogy közvetlenül módosíthassuk, és az esetleges hibakódot beleírhassuk.

Próbálkozzunk meg ezzel az utolsóval, hiszen még talán ez a legígéretesebb!

> 🚦 *Akkor érdemes továbbhaladnod, ha az eddigi résszel már megpróbálkoztál.*

### Megoldás

A fent ismertetett megközelítésre C-ben hagyományosan pointereket használnánk, hiszen így egy függvényen kívüli változó tartalmát meg tudjuk változtatni, ehhez csak egy plusz paraméterre van szükségünk:

```cpp
int celsius_to_fahrenheit(int celsius, bool *failure) {
  celsius < 0 || celsius > 50 ? *failure = true : *failure = false;
  return (celsius * 9) / 5 + 32;
}

bool failure;
celsius_to_fahrenheit(-10, &failure)
if (failure) { /*...*/ }
```

Azonban az már most szembetűnő, hogy ez egészen sok, számunkra igazából felesleges operátort igénybe vesz, ami kevésbé egyszerűen olvashatóvá teszi a kódot. A problémát már korábban felismerték, és ezen a téren el is kezdhetünk ismerkedni a C++ megannyi nyelvi újításával.

A pointerek kiváltására lehetőségünk van referenciákat használni, melyekre a legtágabb értelemben "alternatív névként", *alias*-ként tudunk gondolni. Ekkor lehetőségünk van a teljes pointerhasználatot referenciák mögé rejtenünk, hiszen ekkor a referenciára úgy tekinthetünk, mint magára az eredeti változóra:

```cpp
int celsius_to_fahrenheit(int celsius, bool &failure) {
  celsius < 0 || celsius > 50 ? failure = true : failure = false;
  return (celsius * 9) / 5 + 32;
}

bool failure;
celsius_to_fahrenheit(-10, failure)
if (failure) { /*...*/ }
```

Mint látjuk, referenciákat felhasználva egyáltalán nincsen szükség a pointerek használatakor előkerülő kellemetlenségekre, mint a címképzés vagy a dereferálás, csupán a változó deklarációjakor `*` helyett `&` jelet használunk. Azonban ez például a tömbök pointerként való viselkedésétől nem ment meg minket - szerencsére más majd igen... félig.

> Referenciákat nem csak paraméterlistán, hanem bárhol a kódban tudunk létrehozni. Fontos tulajdonságuk, hogy mindig inicializálni kell őket, és nem tudjuk őket átállítani más változóra. Hasznos eszköz még paraméterlistákban a `const` minősítővel használni őket, például olyankor, amikor nagyméretű adatstruktúrára pointert használnánk, hogy a másolást elkerüljük. `const &` létrehozása ugyanis a másolást elkerüli, azonban az adott struktúrához így csak olvasásra tudunk hozzáférni, annak adattagjait felülírni nem.

## 4. Részfeladat - kivételek

Aladár a hibajelzéses varázslásunkat azonban csak a következő képpen tudta értékelni: "ez mégis mi?"

Egyrészt szerinte a szenzor értelmezési tartományának megfelelés nem ennek a függvénynek a felelőssége, arról majd ő gondoskodik. Esetleg az abszolút nulla hőmérsékletet jelezhetjük hibával, az hasznos lenne, ha ilyen módon hiba csúszna a történetbe, valahogyan jelenzénk.

Valamint még nagyon nem értette, hogy minek vezetünk be egy új paramétert a függvényhez, egyébként is, C++-ban sokkal fejletteb hibajelzési lehetőségeink vannak! Hm, biztosan igaza van, valamiről valószínűleg megfeledkeztünk... Hagyjuk az úgynevezett "out parameter" megoldást egyelőre, és keressünk valami más megvalósítást a hibajelzésre!

> 🚦 *Akkor érdemes továbbhaladnod, ha az eddigi résszel már megpróbálkoztál.*

### Megoldás

A korábban felsorolt körülményes hibajelzések kiváltására a C++ nyelv egy olyan vezérlési szerkezetet vezet be, ami C-ből leginkább a `goto` kulcsszó működésére hasonlíthat, már annak, aki dolgozott ilyennel. A `goto` használata továbbra sem javasolt, hiszen nagyon körülményes, ellenben a kivételek "dobása" és "elkapása" egy nagyon hasznos nyelvi elem, és gyakran nagyban megkönnyíti a dolgunkat.

Kivételek felhasználásának segítségével a függvényt valami hasonló szerkezetre tudjuk átalakítani:

```cpp
#include <stdexcept>

int celsius_to_fahrenheit(int celsius) {
  if (celsius < -273)
    throw std::invalid_argument("Argument below absolute zero degree.");

  return (celsius * 9) / 5 + 32;
}

```

Ekkor amennyiben a paraméterül átadott `celsius` változó értéke `-273`-nál kevesebb, egy `std::invalid_argument` típusú kivétel dobódik, melyet a programnak lehetősége van elkapni, és a hibát megfelelően kezelni. Amennyiben semmi nem kapja el, az a program leállásához vezet.

> Az `stdexcept` header még több, az `std::invalid_argument`-hez hasonló beszédes kivételneveket tartalmaz.

Ahhoz, hogy a dobott kivételt elkapjuk, azaz a vezérlést átadjuk egy külső kódrészletnek, az úgynevezett `try`-`catch` blokkokat tudjuk felhasználni. A `try` blokkba kerül az a kód, aminek a kivételeit el akarjuk kapni, a `catch` részbe pedig paraméterszerűen a kivétel típusa, amit el szeretnénk kapni, a hozzá tartozó törzsbe pedig egy tényleges elkapás esetén futtatandó kódrészlet kerül.

```cpp
try {
  std::cout << "A homerseklet: " << celsius_to_fahrenheit(-300) << "F\n";
}
catch (const std::invalid_argument &exception) {
  std::cout << "Kivetel keletkezett:\n" << exception.what() << "\n";
}
```

> Lehetőségünk van több, különböző kivételtípust is felsorolni külön `catch` blokkoként, így az fogja a vezérlést átvenni, amelyiknek megfelelő típusú kivétel dobódott. Valamint akár egy `catch` blokk is dobhat kivételt, ami hasznos lehet, ha mondjuk egy függvényen belül le szeretnénk kezelni az elkapottat, azonban az azt hívó függvénynek is "továbbdobni".

## 5. Részfeladat - függvénynév túlterhelése

Miután Kriszta megmutatta Aladárnak az elkészült kódot, többségében elégedett volt vele. Megveregethetjük a saját vállunkat, ügyesek voltunk.
Azonban egy ötlete még támadt. Mivel a függvény egyszerűen csak számokkal dolgozik, hasznos lenne, ha nem csak `int` értékekre működne, hanem tudna kezelni `float`, `double`, vagy akár bármilyen más numerikus típust is.

\- "Ezt hívják generikusságnak", mondta Kriszta, de mivel neki *rengeteg sok más dolga van*, rádhagyta, hogy a feladattal megbírkózz. Tegyünk hát így! Vajon mit tudunk felhasználni ahhoz, hogy több különböző típust is fel tudjon dolgozni a függvény?

> 🚦 *Akkor érdemes továbbhaladnod, ha az eddigi résszel már megpróbálkoztál.*

### Megoldás

Na ez egy tipikusan olyan probléma, amivel C-ben teljesen meg lettünk volna lőve. Az előző problémákat még mind meg lehetett volna ott is oldani (még ha kicsit másként is), de itt már muszáj olyanhoz nyulnunk, ami ott nem élvez natív nyelvi támogatást.

Persze nagyon nyers módon elkezdhettük folna prefixekkel jelölni a különböző függvényváltozatokat, de ez nem a kívánt célt érné el:

```cpp
int    int_celsius_to_fahrenheit   (int);
float  float_celsius_to_fahrenheit (float);
double double_celsius_to_fahrenheit(double);
```

Célunk pont azt, hogy ezt a különbséget elrejtsük a többi programozó, vagy akár saját magunk elől. Viszont ahogyan korábban felvezettük, van egy olyan nyelvi eszköz, ami többek között erre a problémára is felhasználható (bár talán itt a legerőltetettebb a példa).

Ez pedig a függvénynevek túlterhelése. Ez azt tudja, hogy azonos függvénynévvel több paraméterlistát is deklarálhatunk. Na hogy erre példát is lássunk, íme az átváltó függvényeink prototípusai:

```cpp
int    celsius_to_fahrenheit(int);
float  celsius_to_fahrenheit(float);
double celsius_to_fahrenheit(double);
```

Ez C++-ban teljesen legális, és egy egészen hasznos kis eszköz tud lenni.

Egy másik példával élve, mondjuk vegyük Krisztának az `its_too_cold()` függvényét: elvárt működésnek megfelelően teljesen más paraméterlistákat tudunk írni hozzá, amik esetén más és más tényleges függvénytörzs fog lefutni:

```cpp
// Teljesen szubjektív érték alapján beállított függvény:
bool its_too_cold(float celsius);

// Itt is szubjektív, de a relatív páratartalommal számolva már a hőindexet veszi alapul:
bool its_too_cold(float celsius, float relative_humidity);

// Itt már a "túl hidegnek" számító hőmérsékleti érték is személyre szabható:
bool its_too_cold(float celsius, float relative_humidity, float reference_temp);
```

> Az ökölszabály az, hogy függvénynevek túlterhelése esetén legalább a paraméterlistáknak különbözniük kell. Lehet akár azonos, akár különböző az egyes változatok között a visszatérési érték típusa, azonban ha csak ez jelentené a különbséget, a fordítónak szinte semmi esélye nem lenne eldönteni, hogy melyiket használja. Természetesen teljesen azonos szignatúrák esetén a többszöri definíció problémája továbbra is fennáll.

> C++-ban az operátorok is függvényként vannak megvalósítva, így a legtöbbet akár nekünk is lehetőségünk van túlterhelni az `operator` kulcsszó felhasználásával, erre konkrét példát is fogunk majd látni. Az I/O streamek is ezt használják ki.

A mi esetünkben (`celsius_to_fahrenheit()`) a módszer hátránya persze az, hogy lényegében ugyan azt a függvénytörzset 3 különböző helyen írjuk meg ugyan úgy. Nem baj, igazából nekünk már ez is előrelépés, így nyugodt szívvel adhatjuk át Krisztának az elkészült kódot.

Üzenetben válaszolt, csak ennyit írt: "luke alika nem csipte, szerinte van sokkal jobb megoldas is 🤷‍♀️"

Hogy mégis mi a jelen esetben sokkal jobb megoldás, Aladár a nagy siettségében már nem volt hajlandó megosztani. Annyival lerázott minket, hogy "majd ha lesz időm, elmagyarázom, de ez érezhetően túl sok lenne most nektek".

## 6. Részfeladat - alapértelmezett paraméterek

Azonban Kriszta még valamiben a segítségünket kérné: Aladár nem csak a mi megoldásunkra szólt be, de az övéére is: szerinte az `its_too_cold()` függvényt "így semmi értelme szétbontani, az egyparaméterű felesleges, a `reference_temp` meg egybe belefér".

Hogy mégis mi? Az egyparaméteres feleslegessége még kézenfekvő, azt a változatot hagyjuk el, mert egyszerűen van nála jobb is. Azonban a két- és háromparaméterű függvényekre vonatkozó megjegyzésén érdemes eltöprengenünk. Aladár lényegében azt mondja, hogy mivel a függvény valamihez mindenképpen hasonlítja a számolt hőindexet (ez az abszolút hőmérséklettel és relatív páratartalommal az "érzett" hőmérsékletet adja meg), elég neki egy olyan paraméterlista, ami a Kriszta által szubjektíven beállított alapértéket (20°C) is tartalmazza. Próbáljuk tehát ezt megvalósítani!

> 🚦 *Akkor érdemes továbbhaladnod, ha az eddigi résszel már megpróbálkoztál.*

### Megoldás

A megoldást számunkra egy másik C++-os nyelvi elem, az alapértelmezett paraméterek adják. Ez annyit tesz, hogy egy függvényünk paramétereinek tudunk olyan alapértelmezett értéket beállítani, amit ha amúgy híváskor nem kapna mást, a fordító behelyettesít, és ezzel hívódik meg a függvényünk.

A saját példánknál maradva, ha tehát Kriszta esetében a `reference_temp` mindkét függvényben megjelenik, csak az egyikben belekódolva a törzsbe, a másikban pedig paraméterlistán, akkor elég egy olyan függvényt írnunk, melynek ezen paramétere ezt az alapértéket veszi fel:

```cpp
// A személyre szabható érték alapból 20-at vesz fel, így nem kötelező hívásnál megadnunk:
bool its_too_cold(float celsius, float relative_humidity, float reference_temp = 20.0f);
```

Így jelen esetben elég ezt az egy függvényt megírnunk, hogy egyből az eddigi kettő funkcionalitását kiváltsuk. Fontos szabály azonban, hogy az alapértékeket csak jobbról balra tudjuk megadni, tehát amennyiben a fenti példában mondjuk a `relative_humidity` paraméternek szeretnénk alapértelmezett értéket beállítani, a tőle jobbra található (most csak egyetlen) `reference_temp`-nek is kötelező megadni! Másküldönben egyszerűen fordítási hibát fogunk kapni.

Ez a mechanizmus azt a problémát hivatott kivédeni, hogy ha mondjuk a függvényünk első és harmadik paraméterének adnánk alapértéket, a másodiknak pedig nem, akkor két paraméterrel hívás esetén mégis melyik kettőt szeretnénk kitölteni?

Érdemes vigyáznunk! Kísérteties az átfedés a túlterhelés adta lehetőségek és az alapértelmezett paraméterek adta lehetőségek között. Az alábbi példában mindkét függvény hívható ugyan azzal a paraméterlistával:

```cpp
bool its_too_cold(float celsius, float relative_humidity);                               // 1)
bool its_too_cold(float celsius, float relative_humidity, float reference_temp = 20.0f); // 2)

bool is_it_cold = its_too_cold(23.0f, 71.0f);
                                        // ^~~ Itt mire gondoltunk?
                                        // Az 1) függvényt hívjuk?
                                        // Vagy a 2)-t 20-as alapértelmezett paraméterrel?
```

Ekkor persze a névütközést a fordító is jelzi számunkra, de érdemes tisztában lenni, vele, hogy mi is okozza a hibát.

> Aladár tippje: amennyiben az alapértelmezett érték felismerésére elágazást használsz, érdemes lehet az egyszerű függvénytúlterhelést választanod alapértékek helyett, hiszen ezek szerint más paraméterlistákhoz más funkcionalitást is vársz.

## 7. Részfeladat - függvénysablonok



## 8. Részfeladat - dinamikus memóriakezelés



## Összegzés

