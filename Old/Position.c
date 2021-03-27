#include "Position.h"
#include <stdio.h>

//97 98 99 100 101 102 103 104
//a  b  c   d   e   f   g   h

//49 50 51 52 53 54 55 56
//1  2  3  4  5  6  7  8

// 100 = 2^3 3/8 = 0 so h 104 - 1 then 3 = 6 = 57 - 3
// 0010011
// 0000000 = 2^13 = 1 so g 104-1 then 13 % 8 = 5 = 57 - 5 + 2^10 + 2^9 

int getBit(long long int x, int digit) {
  return (x & (1ULL << digit)) >> digit;
}

unsigned int popcount(long long int m) {
  unsigned int c = 0;
  for(c = 0; m; c++) m &= m - 1;
  return c;
}

long long int first(long long int m) {
  int count = popcount(m);
  if(count == 1)return m;
  for(int x = 0; x < count-1; x++) m &= m - 1;
  return m;
}

int digit(long long int m) {
  if(m > 0) {
    return (int)log2(m);
  }else {
    for(int x = 63; x >= 0; x--) {
      if(getBit(m, x) != 0) return x;
    }
  }
  return -1;
}

enum eDirection {
	TOP_LEFT, UP, TOP_RIGHT, 
	LEFT, RIGHT, 
	BOTTOM_LEFT, DOWN, BOTTOM_RIGHT, 
	LAST
};

int Dir_Conjugate[] = {8+1, 8, 8-1, -1, 1, -8+1, -8, -8-1};

// double log2(long long int m) {
//   return log2(m);
// }

char* toNote(long long int move, char note[]) {
	move = (int)(log(move)/log(2));
  // printf("%s",(104-(int)(move/8))+'0');
  note += (104-(int)(move/8))+'0';
  note += (57 - (move % 8))+'0';
  return note;
}

long long int toPos(char a, char b) {
  int y = 104-(int)a;
  int x = (57-(int)b);
  return (1ULL << (8*y+x));
}

long long int vecToPos(int a, int b) {
  return (1ULL << (8*(8-b)+8-a));
}

long long int possible(long long int mask, long long int current_position) {
  long long int possible_moves = 0;
  long long int spaces = ~mask;
  long long int opp = mask^current_position;
  int power;
  if(popcount(current_position) < popcount(spaces)) {
    long long int copy = current_position;

    for(int x = 0; x < popcount(current_position); x++) {
      // power = (int)(log2(copy));
      power = digit(copy);

      for(int index = TOP_LEFT; index != LAST; index++) {

        int dir = Dir_Conjugate[index];
        int digit = power+dir;
        int bit = getBit(opp,digit);

        while(bit != 0 && digit < 64 && digit > 0) {
          bit = getBit(opp,digit);
          if(bit == 0 && getBit(current_position,digit) == 0) {
            possible_moves |= (1ULL << digit);
            break;
          }
          if((64-power) % 8 != 0) {

          }else if((64-power) % 8 != 1) {
            
          }
          if( ((64-digit) % 8 == 0 && (64-power) % 8 != 0) || ((64-digit) % 8 == 1 && (64-power) % 8 != 1)) {
            break;
          }
          digit += dir;
         
        }
      }
      copy ^= (1ULL << power);
    }

  }else {
    long long int copy = spaces;

    for(int x = 0; x < popcount(spaces); x++) {
      // power = (int)(log(copy)/log(2));
      power = digit(copy);

      for(int index = TOP_LEFT; index != LAST; index++) {

        int dir = Dir_Conjugate[index];
        int digit = power+dir;
        int bit = getBit(opp,digit);
        int self = getBit(current_position, digit);
        while(bit != 0 && self == 0) {
          bit = getBit(opp,digit);
          if(bit == 0 && getBit(current_position,digit) == 0) {
            possible_moves |= (1ULL << power);
            break;
          }
          if((64-power) % 8 != 0) {
            if((64-power) % 8 != 1) {
              if((64-digit) % 8 == 0 || (64-digit) % 8 == 1) {
                break;
              }
            }
            if((64-digit) % 8 == 0) {
              break;
            }
          }else if((64-power) % 8 != 1) {
            break;
          }
          // if((64-digit) % 8 == 0 || (64-digit) % 8 == 1) {
          //   break;
          // }
          digit += dir;
        }
        copy ^= (1ULL << power);
      }
    }
  }
  return possible_moves;
}

long long int flips(long long int mask, long long int current_position, long long int move) {
  long long int flips = 0;
  long long int opp = mask^current_position;
  // int power = (int)(log2(move));
  int power = digit(move);

  for(int index = TOP_LEFT; index != LAST; index++) {
    long long int temp = 0;
    int dir = Dir_Conjugate[index];
    int digit = power+dir;
    int bit = getBit(opp,digit);
    while(bit != 0) {
      temp |= (1ULL << digit);
      bit = getBit(opp,digit);
      if(getBit(current_position,digit) == 1) {
        flips |= temp;
        break;
      }
      if((64-digit) % 8 == 0 || (64-digit) % 8 == 1) {
        temp = 0;
        break;
      }
      digit += dir;
    }
  }
  return flips;
}

void show(long long int object) {
  for(int x = 63; x >= 0; x--) {
    printf("%d", (int)((object >> x)&1));
    if((64-x) % 8 == 0) {
      printf("\n");
    }
  }
}

int negamax(long long int mask, long long int curr, int color=1, int end=60) {
  if(end == 0) {
    return color * popcount(curr);
  }
  int value = -10000;
  long long int children = possible(mask,curr);
  for(int x = 0; x < popcount(children); x++) {
    // long long int child = (1ULL << (int)(log2(children)));
    long long int child = first(children);
    value = max(value,-negamax(mask|child, curr|child, -color,end-1));
    children ^= child;
  }
  return value;
}

int alphabeta(long long int mask, long long int curr, int α=-10000, int β=10000, bool maximising=true, int end=60) {
  if(end == 0) {
    return popcount(curr);
  }
  int value;
  long long int children = possible(mask,curr);
  if(maximising) {
    value = -10000;
    for(int x = 0; x < popcount(children); x++) {
      // long long int child = (1ULL << (int)(log2(children)));
      long long int child = first(children);
      value = max(value, alphabeta(mask|child, curr|child,α,β,false,end-1));
      α = max(α,value);
      if(α >= β) {
        break;
      }
      children ^= child;
    }
  }else {
    value = 10000;
    for(int x = 0; x < popcount(children); x++) {
      // long long int child = (1ULL << (int)(log2(children)));
      long long int child = first(children);
      value = min(value, alphabeta(mask|child, curr|child,α,β,true,end-1));
      β = min(β,value);
      if(β <= α) {
        break;
      }
      children ^= child;
    }
  }
  return value;
}

int negaAB(long long int mask, long long int curr, int α, int β, int color, int end=60) {
  if(end == 0 || popcount(~mask) == 0 || popcount(possible(mask,curr)) == 0) {
    return color * popcount(curr);
  }
  int value = -10000;
  long long int children = possible(mask, curr);
  for(int x = 0; x < popcount(children); x++) {
    // long long int child = (1ULL << (int)(log2(children)));
    long long int child = first(children);
    value = max(value,-negaAB(mask|child, curr|child, -β, -α, -color,end-1));
    α = max(α,value);
    if(α >= β) {
      break;
    }
    children ^= child;
  }
  return value;
}

// bool checkReflectionalSymmetry(dbl board) {
//   bool s;
//   long long int smaller = board.count(1) < board.count(2)? board.curr:board.node^board.curr;
//   long long int copy = smaller;
//   // First check horizontal symmetry i.e. flip about y-axis
//   for(int temp = 0; temp < popcount(smaller); temp++) {
//   	int power = (int)log2(copy);
//   	int x = power%8;
//   	if(x < 4) {
//   	  getBit(smaller, power-2(x-4));
//   	}else {
//   	  getBit(smaller, power+2(x-4));
//   	}
//   }
//   return s;
// }

// bool check

// int main() {
//   long long int mask = 0;
//   long long int current_position = 0;
//   mask |= (3ULL << (8*4+3));
//   mask |= (3ULL << (8*3+3));
//   current_position |= (1ULL << (8*4+4));
//   current_position |= (1ULL << (8*3+3));
//   show(possible(mask,current_position));
//   // show(mask^current_position);
//   // printf("%d",(int)(log(current_position)/log(2)));
//   // for(int x = UP)
//   return 0;
// }