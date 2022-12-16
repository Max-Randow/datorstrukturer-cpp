/**********************************************************************
 *  M�nsterigenk�nning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga k�rtider i millisekunder
 *  analys      n�r det k�nns vettigt att v�nta p� hela ber�kningen.
 *              Ge uppskattningar av k�rtiden i �vriga fall.
 *
 **********************************************************************/

Compile in release mode.
	  N       brute              sortering
 -------------------------------------------
	150       100                1
	200       74                 33
	300       104                31
	400       139                41
	800       883                80
   1600       6943               238
   3200       55278              1691
   6400       441433             3493
  12800       Mer �n 3 timmar    16349


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck f�r v�rstafallstiden f�r programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:

Genomsnitt N^3 men ibland N^4 d� tre punkter ligger p samma linje.
Detta �r fallet eftersom vi har 3 loopar n�stlade i varandra som alla �r linj�ra.
�ven en 4:e loop ligger n�stlad som �r linj�r, ligger dock i en if sats som k�r ibland.

V�rsta fallet sker d� alla punkter ligger p� en linje allts� alla loopar k�rs
hela tiden och vi f�r d� O(N^4)

Sortering:
Looparna �r linj�r i N och den andra g�r fr�n i till N vilket ger n(n+1)/2 eller O(N^2).
Varje iteration sker �ven en access och/eller emplace till unordered_map vilket b�da
�r i log(N). Detta ger O(N^2)*O(log(N)) = O(N^2*log(N)) i v�rsta fallet.
