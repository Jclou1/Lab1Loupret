/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   fonctions.h
 * Author: etudiant
 *
 * Created on 29 mars 2024, 21 h 54
 */

#include <array>

#ifndef FONCTIONS_H
#define FONCTIONS_H

void MicroPar (int m, int n, float er1, float er2, int d,int w, float tol, int* vp, float* Z0);
void MDF (int m,int n,float er1,float er2,int d,int w,float tol, float* liste);
void IGauss (float* liste,int er1,int er2,int d,int w, double* C,double* C0, int m , int n);

#endif /* FONCTIONS_H */