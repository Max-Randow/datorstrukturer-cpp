/**********************************************************************
 *  Mönsterigenkänning readme.txt
 **********************************************************************/

/**********************************************************************
 *  Empirisk    Fyll i tabellen nedan med riktiga körtider i millisekunder
 *  analys      när det känns vettigt att vänta på hela beräkningen.
 *              Ge uppskattningar av körtiden i övriga fall.
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
  12800       Mer än 3 timmar    16349


/**********************************************************************
 *  Teoretisk   Ge ordo-uttryck för värstafallstiden för programmen som
 *  analys      en funktion av N. Ge en kort motivering.
 *
 **********************************************************************/

Brute:

Genomsnitt N^3 men ibland N^4 då tre punkter ligger p samma linje.
Detta är fallet eftersom vi har 3 loopar nästlade i varandra som alla är linjära.
Även en 4:e loop ligger nästlad som är linjär, ligger dock i en if sats som kör ibland.

Värsta fallet sker då alla punkter ligger på en linje alltså alla loopar körs
hela tiden och vi får då O(N^4)

Sortering:
Looparna är linjär i N och den andra går från i till N vilket ger n(n+1)/2 eller O(N^2).
Varje iteration sker även en access och/eller emplace till unordered_map vilket båda
är i log(N). Detta ger O(N^2)*O(log(N)) = O(N^2*log(N)) i värsta fallet.
