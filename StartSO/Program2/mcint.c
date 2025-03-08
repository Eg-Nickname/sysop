// Standardowe pliki naglowkowe
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Wlasne pliki naglowkowe
#include "funkcja.h"
 
/* 
   Prosty program do wyznaczania liczby pi metoda Monte Carlo
   oraz wyliczania calki z funkcji dwoch zmiennych metoda podstawowa MC.
   ------------------------------------------------------------------------------
   Autor: Wieslaw Placzek,                                     Krakow, 21.02.2025
   ------------------------------------------------------------------------------
*/ 
int main(int argc,char *argv[])
{
  // Najpierw sprawdzamy, czy liczba argumentow wywolania programu jest poprawna!
  if (argc != 2) {
    puts(">>> Niepoprawna liczba argumentow programu!");
    printf(">>> Poprawne wywolanie programu: %s liczba_przypadkow\n",argv[0]);
    exit(1);
  }
  // Liczba przypadkow Monte Carlo do wygenerowania - pobrana z argumentu programu
  // i skonwertowana na liczbe typu double.
  double nn = atof(argv[1]);
  // Inne pomocnicze zmienne
  unsigned long i, ir1, ir2, np = 0;
  double rr1, rr2, dlogi, delta, rhit, pi_mc, sigpi;
  double fun, sum = 0.0, sum2 = 0.0, sigfun;

  printf("        -------------------\n");
  printf("        Metoda Monte Carlo:\n"); 
  printf("        -------------------\n");
  printf("1) Wyznaczanie wartosci liczby pi. \n");
  printf("2) Wyliczanie calki funkcji dwoch zmiennych.\n");                   
  printf("-> Generuje %g przypadkow ...\n",(double) nn);
  printf("=====================================================\n");
  // Inicjalizacja generatora liczb losowych
  srand(1371);
  // Generowanie liczb losowych i obliczanie pi metoda MC
  for (i = 1; i <= nn; ++i)
    {
      ir1 = rand();
      ir2 = rand();
      rr1 = ( (double) ir1 )/RAND_MAX;
      rr2 = ( (double) ir2 )/RAND_MAX;
      if (rr1*rr1 + rr2*rr2 <= 1.0)
	np++;
      // Wydruki kontrolne
      dlogi = log10(1.0*i);
      delta = dlogi - floor(dlogi);
      if (!delta && i > 1)
	{
	  rhit = 1.0*np/i;
	  pi_mc = 4.0*rhit;
	  sigpi = 4.0*sqrt( rhit*(1.0 - rhit)/(i - 1.0) ); 
	  printf("Metoda MC: pi = %7.5lf +- %7.5lf\t i = %8lu\n",pi_mc,sigpi,i);    
	}
      // Obliczanie calki metoda podstawowa MC
      fun = myFun(rr1,rr2);
      sum += fun;
      sum2 += fun*fun;
    }
  // Dokladna wartosc pi
  double pi_dokl = acos(-1.0);
  printf("Dokladnie: pi = %7.5lf\n",pi_dokl);
  sigfun = sqrt( (sum2 - sum*sum/nn)/nn/(nn - 1.0) ); 
  printf("=====================================================\n");
  printf("Calka funcji %g*[exp(x) - ln(y)] na [0,1]x[0,1]\n",WSP);
  printf("-> Metoda MC: %7.4lf +- %6.4lf\n",sum/nn,sigfun);
  printf("-> Dokladnie: %7.4lf\n",WSP*exp(1.0));
  printf("=====================================================\n");
}

