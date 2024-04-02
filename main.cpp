
/* 
 * File:   main.cpp
 * Author: etudiant
 *
 * Created on 29 mars 2024, 21 h 08
 */

#include <cstdlib>
#include "fonctions.h"
#include <iostream>

using namespace std;

/*
 * 
 */
int
main ()
{
  int m = 120;
  int n = 80;
  float er1 = 16;
  float er2 = 1;
  int d = 40;
  int w = 10;
  float tol = 0.00001;
  int vp;
  float Z0;
  
 /* cout << "Paramètre m :";
  cin >> m;
  cout << "Paramètre n :";
  cin >> n;
  cout << "Paramètre er1 :";
  cin >> er1;
  cout << "Paramètre er2 :";
  cin >> er2;
  cout << "Paramètre d :";
  cin >> d;
  cout << "Paramètre w :";
  cin >> w;
  cout << "Paramètre tol :";
  cin >> tol;
 */ 
  MicroPar (m, n, er1, er2, d,w, tol, &vp, &Z0);

  return 0;
}

