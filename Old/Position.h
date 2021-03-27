#include <math.h>
#include <stdbool.h>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

unsigned int popcount(long long int m);

// struct uint128 {
//   long long int a;
//   long long int b;
//   uint128(long long int p1, long long int p2) {a = p1; b = p2;}
// };

// struct dbl {
//   long long int node;
//   long long int curr;
//   struct dbl(*or)(long long int*);
//   // uint128 key() {return uint128(node,curr);}
//   // uint128 key3() {
//   // 	return uint128(node,curr);
//   // }
//   int (*count)(int);
// };

// struct dbl dbl_or(long long int c) {
//   struct dbl a = {.node = node|c, .curr = curr|c}
//   return a;
// }

// int count(int x) {
//   switch(x) {
//     case 0:
//       return popcount(node); 
//     case 1:
//       return popcount(curr);
//     case 2:
//       return popcount(node^curr);
//   }
//   return 0;
// }

// struct dbl_int {
//   int a = -10000;
//   int b =  10000;
//   int c;
//   dbl_int(int c_=1) {c = c_;}
// };

// dbl mkdbl(long long int n, long long int c) {
//   dbl a = {.node = n, .curr = c};
//   return a;
// }

// struct dbl mkdbl_int(int n, int c) {return struct dbl_int(n,c);}

int max(int num1, int num2) {return (num1 > num2)? num1:num2;}

int min(int num1, int num2) {return (num2 > num1)? num1:num2;}

int getBit(long long int x, int digit);

long long int first(long long int m);

int digit(long long int m);

// double log2(long long int m);

char* toNote(long long int move, char note[]);

long long int toPos(char a, char b);

long long int vecToPos(int a, int b);

long long int possible(long long int mask, long long int current_position);

long long int flips(long long int mask, long long int current_position, long long int move);

void show(long long int object);

int negamax(long long int mask, long long int curr, int color, int end);

int alphabeta(long long int mask, long long int curr, int α, int β, bool maximising, int end);

int negaAB(long long int mask, long long int curr, int color, int α, int β, int end);

// bool checkReflectionalSymmetry(struct dbl board);

// bool checkRotationalSymmetry(struct dbl board);

#ifdef __cplusplus
}
#endif