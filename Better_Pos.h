#include <stdbool.h>

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned long u64;
typedef unsigned int u32;

int max(int num1, int num2) {return (num1 > num2)? num1:num2;}

int min(int num1, int num2) {return (num2 > num1)? num1:num2;}

int getBit( u64 x, int digit );

u32 popcount( u64 m );

u64 first( u64 m );

int digit( u64 m );

char* toNote( u64 move, char note[] );

u64 toPos(char a, char b);
u64 vecToPos(int a, int b);

bool checkEdge(int power, int dir);

u64 possible( u64 mask, u64 current_pos );

u64 flips( u64 mask, u64 current_pos, u64 move );

void show(u64 object);

int negamax( u64 mask, u64 curr, int color, int end);

int alphabeta( u64 mask, u64 curr, int α, int β, bool maximising, int end);

int negaAB( u64 mask, u64 curr, int color, int α, int β, int end);

#ifdef __cplusplus	
}
#endif