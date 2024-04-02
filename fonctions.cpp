
#include "fonctions.h"
#include <array>
#include <iostream>
#include <math.h>
#include <complex>
void MicroPar (int m, int n, float er1, float er2, int d,int w, float tol, int* vp, float* Z0){
float liste[n+1][m+1];
double C, C0;
MDF(m,n,er1,er2,d,w,tol, (float*) liste);
// Imprimer le visuel pour l'utilisateur
std::cout << "Largeur: " << m+1 << " Hauteur: " << n+1 << " er1: " << er1<<
        " er2: "<< er2 << " Tolérance: "<< tol<< std::endl;
/*for(int i = 0; i<=n; i++){
      for(int j = 0; j<=m; j++){
          std::cout.width (10);
          std::cout<<liste[i][j]<< " ";
        }
      std::cout<< std::endl;
    }*/
IGauss((float*) liste,er1,er2,d,w,&C,&C0, m, n);
std::cout << std::endl << "C:"<< C << "      C0:" << C0<< std::endl;
//Calculs de vp et Z0
double erff = C/C0;
*vp = (300000000/(sqrt((erff))));
int vptemp = *vp;
*Z0 = 1/(C*vptemp);
std::cout << "Vp: " << *vp << " m/s _ Z0: "<< *Z0 << " ohms";
}

void MDF (int m,int n,float er1,float er2,int d,int w,float tol, float* liste){
  int stopper =1;
  //Initialiser le tableau de points avec les bonnes valeurs
  for(int i = 0; i<=n; i++){
      for(int j = 0; j<=m; j++){
          // Valeurs sur le contour
          if (i==0 or i == n or j==0 or j==m){
            *(liste+ i*(m+1)+j) = 0 ;
            }
          // 1V sur l'élément à 1V
          else if (i==(n-d) and (((m-w)/2)<= j and j <= (m+w)/2)){
            *(liste+i*(m+1)+j) = 1;
          }
          //Valeur pour le reste si nécessaire
          else{
            *(liste+i*(m+1)+j) = 0;
          }
        }
    }
    while (stopper == 1){
      stopper = 0;
      for(int i = 1; i<n; i++){
          for(int j = 1; j<m; j++){
              float temp = *(liste+ i*(m+1)+j);
              
              if (i==(n-d) and (((m-w)/2)<= j and j <= (m+w)/2)){
                }
              // Si on a 2 diélectriques
              else if(i==(n-d)){
                  //std::cout << "G:" << (*(liste+ (i-1)*(m+1)+j)) << "droite: " << (*(liste+ (i+1)*(m+1)+j)) << "decal" << (i+1)*(m+1)+j << "i:" << i << "j" << j;
                  *(liste+ i*(m+1)+j) = (((*(liste+ (i)*(m+1)+j+1))+ (*(liste+ (i)*(m+1)+j-1)))/4 + ((er1*(*(liste+ (i+1)*(m+1)+j)) + er2*(*(liste+ (i-1)*(m+1)+j)))/(2*(er1+er2))));
                  if (((*(liste+ i*(m+1)+j)-temp)) > tol or (temp-(*(liste+ i*(m+1)+j))) > tol){
                      stopper = 1;
                    }
                }
              //les autres points
              else{
                  *(liste+ i*(m+1)+j) = ((*(liste+ (i-1)*(m+1)+j))+ (*(liste+ (i+1)*(m+1)+j)) + (*(liste+ (i)*(m+1)+j+1)) + (*(liste+ (i)*(m+1)+j-1)))/4;
                  if (((*(liste+ i*(m+1)+j)-temp)) > tol or (temp-(*(liste+ i*(m+1)+j))) > tol){
                      stopper = 1;
                    }
                }
            }
        }
    }
}
  

void IGauss (float* liste,int er1,int er2,int d,int w,double* C, double* C0, int m,int n){
  double addtempC=0;
  double addtempC0=0;
  for(int i = 1; i<n; i++){
        for(int j = 1; j<m; j++){
            //coin haut gauche
             if (i==1 and j==(1)){
                 addtempC += er2 * (2*(*(liste+ i*(m+1)+j)));
                 addtempC0 += (2*(*(liste+ i*(m+1)+j)));
               } 
             //coin haut droit
             else if (i==1 and j==(m-1)){
                 addtempC += er2 * (2*(*(liste+ i*(m+1)+j)));
                 addtempC0 += (2*(*(liste+ i*(m+1)+j)));
               } 
             //coins bas
             else if (i==(n-1) and j==(1)){
                 addtempC += er1 * (2*(*(liste+ i*(m+1)+j)));
                 addtempC0 += (2*(*(liste+ i*(m+1)+j)));
               } 
             else if (i==(n-1) and j==((m-1))){
                 addtempC += er1 * (2*(*(liste+ i*(m+1)+j)));
                addtempC0 += (2*(*(liste+ i*(m+1)+j)));
               } 
             //Côté haut 
             else if(i==1 or (i<(n-d) and(j==1 or j==(m-1)))){
                 addtempC += er2*(*(liste+ i*(m+1)+j));
                 addtempC0 += *(liste+ i*(m+1)+j);
               }
             //côté bas 
             else if(i==(n-1) or (i>(n-d) and(j==1 or j==(m-1)))){
                 addtempC += er1*(*(liste+ i*(m+1)+j));
                 addtempC0 += *(liste+ i*(m+1)+j);
               }
             //Sur la jonction
             else if(i==(n-d) and(j==1 or j==(m-1))){
                 addtempC += ((er1+er2)/2)*(*(liste+ i*(m+1)+j));
                 addtempC0 += *(liste+ i*(m+1)+j);
               }
              
        }
    }
  addtempC = addtempC*(0.000000000008854)/1;
  addtempC0 = addtempC0*(0.000000000008854)/1;
  *C = addtempC;
  *C0 = addtempC0;
}


