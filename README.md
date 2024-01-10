# 1. szakasz

Alaptörténet, feladatok és megoldások

## Alaptörténet

Így, hogy Géza itt hagyta a céget, István elérkezettnek látta az időt, hogy a kódbázis teljes felújításon essen át.
Célja persze az is, hogy így új funkciókkal könnyebben lehessen majd bővíteni a piacra dobott terméket, viszont amíg nem lát eredményeket, se a befektetőknek, se nektek nem hajlandó semmit mondani.

Aladár a főprogram szerkezetét már újraírta, így a termék legalapvetőbb funkciói (a szenzor és a kijelző) hiba nélkül működnek. Istánnal egyeztetve elhatározták, hogy az állomásba egy olyan plusz funkciót vezetnek be, aminek a segítségével a felhasználó maga választhat, hogy Celsius vagy Fahrenheit értékben szeretné megjeleníteni a hőmérsékletet.

Így Krisztának feladatként azt osztotta ki, hogy készítsen el egy olyan függvényt, ami Celsius-Fahrenheit átváltást meg tud tenni.
Erre javasolta, hogy készítsen egy új header-forrásfile kettőst `idojaras_szamitasok` névvel, és ezekbe dolgozzon.

Kriszta ezt el is kezdte, de elakadt a munkában. Téged kért meg, hogy segíts neki befejezni határidőre, és mivel nem szeretnél konfliktust szítani, inkább bele is vágsz a munkába, hiszen tényleg vészesen közelít a határidő.

### Részfeladat
> Kriszta tehát arra kér, hogy az `idojaras_szamitasok.h` és `idojaras_szamitasok.cpp` fileokban elkezdett `int celsius_fahrenheit_atvalto(int);` prototípusú függvényt kidolgozd.

---

*Akkor érdemes továbbhaladnod, ha az eddigi résszel készen vagy.*

---

### Részmegoldás

Az első, aminek fel kellhet tűnnie, az az include guard hiánya, erről sajnos Kriszta megfeledkezett, de C++-ban sem hagyhatjuk el őket (hiszen a fordítási folyamat nagyrészt megegyezik a C-ben megismertekkel).

Így a projekt le sem fordulna, hiszen az `int celsius_fahrenheit_atvalto(int);` függvény többszörös definícióval rendelkezik (`main.cpp` és `idojaras_szamitasok.cpp`).
Ennek javításául írjuk ki valamilyen include guardot! Ez formailag az alábbi módon néz ki:

```cpp
// @file idojaras_szamitasok.h
#ifndef IDOJARAS_SZAMITASOK_INCLUDED
#define IDOJARAS_SZAMITASOK_INCLUDED

// érdemi kódrészlet, jelen esetben:
int celsius_fahrenheit_atvalto(int);

#endif
```

Ha ezt javítottuk, már csak Kriszta kétségbeesett kommentjével kell foglalkoznunk. Akár egy google kereséssel is gyorsan megtalálhatjuk a képletet: `F = (C × 9/5) + 32`. Ezt felhasználva tehát valami hasonló megoldásra kell jutnunk:

```cpp
// @file idojaras_szamitasok.cpp

int celsius_fahrenheit_atvalto(int celsius) { return (celsius*9)/5 + 32; }
```

Mivel `int` értékekkel dolgozunk, levágásra számíthatunk, de a szorzást előbb végezzük el, mint az osztást, így a visszatérési érték legalább egészrészében helyes lesz.