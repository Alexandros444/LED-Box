#ifndef LED_MATRIX_DATA_H
#define LED_MATRIX_DATA_H
#include <Arduino.h>

inline byte A[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 0, 0, 
0, 1, 0, 0, 1, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t A_size = sizeof(A) / sizeof(A[0]);

inline byte acid[256] = {
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 0, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 0, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, };

inline size_t acid_size = sizeof(acid) / sizeof(acid[0]);

inline byte B[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 0, 1, 1, 0, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t B_size = sizeof(B) / sizeof(B[0]);

inline byte black[256] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t black_size = sizeof(black) / sizeof(black[0]);

inline byte C[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t C_size = sizeof(C) / sizeof(C[0]);

inline byte D[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 0, 1, 1, 1, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t D_size = sizeof(D) / sizeof(D[0]);

inline byte dot[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t dot_size = sizeof(dot) / sizeof(dot[0]);

inline byte E[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t E_size = sizeof(E) / sizeof(E[0]);

inline byte ex_mark[40] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t ex_mark_size = sizeof(ex_mark) / sizeof(ex_mark[0]);

inline byte F[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t F_size = sizeof(F) / sizeof(F[0]);

inline byte frame_red_yellow[256] = {
0, 1, 0, 1, 0, 1, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 0, 0, 0, 0, 0, 0, 1, 
0, 1, 0, 1, 0, 1, 0, 1, };

inline size_t frame_red_yellow_size = sizeof(frame_red_yellow) / sizeof(frame_red_yellow[0]);

inline byte frame_red_yellow2[256] = {
1, 0, 1, 0, 1, 0, 1, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 1, 0, 1, 0, 1, 0, };

inline size_t frame_red_yellow2_size = sizeof(frame_red_yellow2) / sizeof(frame_red_yellow2[0]);

inline byte G[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 0, 0, 0, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t G_size = sizeof(G) / sizeof(G[0]);

inline byte H[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 1, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t H_size = sizeof(H) / sizeof(H[0]);

inline byte heart[64] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 1, 1, 0, 0, 
0, 1, 0, 0, 0, 1, 0, 0, 
0, 1, 0, 0, 0, 1, 0, 0, 
0, 0, 1, 0, 0, 0, 1, 0, 
0, 0, 1, 0, 0, 0, 1, 0, 
0, 0, 1, 1, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t heart_size = sizeof(heart) / sizeof(heart[0]);

inline byte I[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t I_size = sizeof(I) / sizeof(I[0]);

inline byte J[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 1, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t J_size = sizeof(J) / sizeof(J[0]);

inline byte K[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 1, 1, 0, 0, 0, 
0, 0, 1, 0, 0, 1, 0, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t K_size = sizeof(K) / sizeof(K[0]);

inline byte L[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t L_size = sizeof(L) / sizeof(L[0]);

inline byte M[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t M_size = sizeof(M) / sizeof(M[0]);

inline byte N[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 1, 1, 0, 0, 0, 0, 
0, 0, 1, 1, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t N_size = sizeof(N) / sizeof(N[0]);

inline byte neo[256] = {
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, };

inline size_t neo_size = sizeof(neo) / sizeof(neo[0]);

inline byte num0[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num0_size = sizeof(num0) / sizeof(num0[0]);

inline byte num1[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num1_size = sizeof(num1) / sizeof(num1[0]);

inline byte num2[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 0, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 1, 0, 0, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num2_size = sizeof(num2) / sizeof(num2[0]);

inline byte num3[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num3_size = sizeof(num3) / sizeof(num3[0]);

inline byte num4[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 1, 1, 1, 0, 
0, 0, 0, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num4_size = sizeof(num4) / sizeof(num4[0]);

inline byte num5[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 1, 1, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num5_size = sizeof(num5) / sizeof(num5[0]);

inline byte num6[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 1, 1, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num6_size = sizeof(num6) / sizeof(num6[0]);

inline byte num7[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 
0, 1, 0, 0, 1, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num7_size = sizeof(num7) / sizeof(num7[0]);

inline byte num8[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num8_size = sizeof(num8) / sizeof(num8[0]);

inline byte num9[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 0, 1, 1, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t num9_size = sizeof(num9) / sizeof(num9[0]);

inline byte O[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 1, 0, 0, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t O_size = sizeof(O) / sizeof(O[0]);

inline byte P[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 1, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t P_size = sizeof(P) / sizeof(P[0]);

inline byte Q[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 
0, 1, 0, 1, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t Q_size = sizeof(Q) / sizeof(Q[0]);

inline byte R[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 1, 0, 0, 0, 
0, 0, 1, 1, 0, 0, 1, 0, 
0, 0, 1, 1, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t R_size = sizeof(R) / sizeof(R[0]);

inline byte S[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 0, 1, 1, 1, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 0, 1, 0, 0, 1, 0, 
0, 1, 0, 0, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t S_size = sizeof(S) / sizeof(S[0]);

inline byte space[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t space_size = sizeof(space) / sizeof(space[0]);

inline byte T[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t T_size = sizeof(T) / sizeof(T[0]);

inline byte test[256] = {
1, 0, 1, 0, 1, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
1, 0, 1, 0, 1, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t test_size = sizeof(test) / sizeof(test[0]);

inline byte U[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 1, 0, 
0, 1, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t U_size = sizeof(U) / sizeof(U[0]);

inline byte V[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 1, 1, 1, 0, 
0, 1, 1, 1, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t V_size = sizeof(V) / sizeof(V[0]);

inline byte W[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 1, 0, 0, 
0, 0, 1, 0, 0, 0, 0, 0, 
0, 1, 1, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t W_size = sizeof(W) / sizeof(W[0]);

inline byte white[256] = {
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, 
1, 1, 1, 1, 1, 1, 1, 1, };

inline size_t white_size = sizeof(white) / sizeof(white[0]);

inline byte X[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 0, 0, 1, 1, 0, 
0, 0, 0, 1, 1, 0, 0, 0, 
0, 0, 0, 1, 1, 0, 0, 0, 
0, 1, 1, 0, 0, 1, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t X_size = sizeof(X) / sizeof(X[0]);

inline byte Y[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 1, 1, 0, 
0, 0, 0, 1, 1, 1, 1, 0, 
0, 0, 0, 0, 1, 0, 0, 0, 
0, 1, 1, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t Y_size = sizeof(Y) / sizeof(Y[0]);

inline byte Z[48] = {
0, 0, 0, 0, 0, 0, 0, 0, 
0, 1, 1, 0, 0, 0, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 0, 0, 1, 0, 1, 0, 
0, 1, 1, 0, 0, 0, 1, 0, 
0, 0, 0, 0, 0, 0, 0, 0, };

inline size_t Z_size = sizeof(Z) / sizeof(Z[0]);

#endif