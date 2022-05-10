## ŠACHY
Autor: Pham Tien Dat

## Téma z Progtestu
Klasická hra Šachy (příp. libovolná varianta - asijské šachy, ...)

Implementujte následující varianty:

    1. pro 2 hráče na jednom počítači
    2. pro hru proti počítači

Hra musí splňovat následující funkcionality:

    - Dodržování všech pravidel dané varianty (u klasické varianty tedy i rošáda, braní mimochodem, proměna pěšce).
    - Ukládání (resp. načítání) rozehrané hry do (resp. ze) souboru (vytvořte vhodný formát a uživatelské rozhraní)
    - Oznamovat stav a konec hry (šach, mat, pat) a její výsledek.
    - Umělá inteligence (škálovatelná nebo alespoň 3 různé druhy, jeden druh můžou být náhodné tahy, ale nestačí implementovat pouze náhodné tahy)

Kde lze využít polymorfismus? (doporučené)

    Ovládání hráčů: lokální hráč, umělá inteligence (různé druhy), síťový hráč
    Pohyby figurek: král, dáma, věž, jezdec,...
    Uživatelské rozhraní: konzolové, ncurses, SDL, OpenGL (různé druhy),...
    Pravidla různých variant: klasické šachy, žravé šachy, asijské šachy
    Jednotlivá pravidla: tahy, rošáda, braní mimochodem, proměna (jejich výběr pak může být konfigurovatelný)


## Zadání šachy 

Hra bude čistě konzolová, a bude se ovládat z terminálu, na začátek bude usermenu 
- `1v1` hra pro dva hráče 
- `1vPC` hra proti počítači 
- `load [filename]` načte hru ze souboru
- `save [filename]` uloží hru do souboru


- `status` zobrazí aktuální stav hry
- `move [r][c] [r][c]  na řádek a sloupec  (`r`, `c`) pohne figurkou 
- `help` zobrazí nápovědu
- `quit` ukončí program




```     
      A    B    C    D    E    F    G    H    I
        
  10  X----C----T----P~~~~K~~~~P----T----C----X
      |    |    |    |    |    |    |    |    |
  9   +----F----+----+~~~~+~~~~+----+----F----|
      |    |    |    #    |    #    |    |    |
  8   +----+----+----+~~~~+~~~~+----+----+----|
      |    |    |    #    |    #    |    |    |
  7   E----+----E----+----E----+----E----+----E
      |    |    |    |    |    |    |    |    |
  6   +----+----+----+----+----+----+----+----+
      |    |    |    |    |    |    |    |    |
  5   +----+----+----+----+----+----+----+----+
      |    |    |    |    |    |    |    |    |
  4   E----+----E----+----E----+----E----+----E
      |    |    |    |    |    |    |    |    |
  3   +----F----+----+~~~~+~~~~+----+----F----|
      |    |    |    #    |    #    |    |    |
  2   +----+----+----+~~~~+~~~~+----+----+----|
      |    |    |    #    |    #    |    |    |
  1   X----C----T----P~~~~K~~~~P----T----C----X 
``

### Kde mám polymorfismus?

Polymorfismus budu využívat u třídy `CTroops`, abstraktni metody `ValidateMove`. Implementace ruzné druhy figurek ( CKnight... ), 


Polymorfismus využívám u třídy `CMapBuilder`, ta má dvě abstraktní metody `Configure` a `Generate`. Dvě implementace `CMapBuilderRandom` a `CMapBuilderFile` přetěžují tyto metody. Náhodná varianta se dotáže na 3 čísla (šířku, výšku a počet min), souborová se zeptá na jméno souboru. Následně v metodě `Generate` každý vygeneruje mapu, náhodná vygeneruje prázdnou mapu a do ní umístí náhodně miny, souborová naopak načte mapu ze souboru (a případně dogeneruje náhodně miny). Souborová mapa může obsahovat navíc zdi. (Jsou rovnou vidět, ale nevíme kolik je kolem nich min.)

Polymorfní volání je v třídě `CCommandNew`, která při kompilaci dostane specifikovány všechny `CMapBuilder` třídy (kdybychom chtěli přidat dynamický). Následně od uživatel dostane řetězec, který spáruje a na správný `CMapBuilder` zavolá `Configure` a `Generate`.

> Vedlejší polymorfismus budeme mít nad samotnými `CCommand` objekty, bohužel takový polymorfismus je příliš obyčejný a šel by nahradit vhodným voláním lambda funkcí. To možná provedu, abych snížil počet tříd.

> Nejsem "no lifer", takže na polymorfismus na uživatelském rozhraní kašlu. Navíc máme problém, že naše uživatelské rozhraní bude využívat šablony. Šablony neumožňují použití virtuálních funkcí, a brání polymorfismu.
