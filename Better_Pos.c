#include "Better_Pos.h"
#include <math.h>
#include <stdio.h>

#define B(x) S_to_binary_(#x)

static inline u64 S_to_binary_(const char *s)
{
        u64 i = 0;
        while (*s) {
                i <<= 1;
                i += *s++ - '0';
        }
        return i;
}

int getBit( u64 x, int digit ) {return (x >> (digit))&1;}

u32 popcount( u64 m ) {
	u32 c = 0;
	for(c = 0; m; c++) m &=m -1;
	return c;
}

// Gets the number with only the largest bit remaining only //
// e.g. 10,110,110  - >  10,000,000
u64 first( u64 m ) {
	int count = popcount(m);
	if(count == 1) return m;
	for(int x = 0; x < count-2; x++) m &= m - 1;
	return m;
}

int digit( u64 m ) {return (int)log2(m);}

enum eDirection {
	TOP_LEFT, UP, TOP_RIGHT,
	LEFT,		  RIGHT,
	BOTTOM_LEFT, DOWN, BOTTOM_RIGHT,
	LAST
};

int Dir_Conjugate[] = { 8+1, 8, 8-1,
						  1,     -1,
					   -8+1,-8,-8-1 };

char* toNote(u64 move, char note[]) {
	move = (int)(log(move)/log(2));
	note += (104-(int)(move/8))+'0';
	note += (57 - (move % 8)) + '0';
	return note;
}

u64 toPos(char a, char b) {
	int y = 104-(int)a;
	int x = (57-(int)b);
	return (1ULL << (8*y+x));
}

u64 vecToPos(int a, int b) {
	return (1ULL << ( 8*(8-b) + 8-a) );
}

bool Edge(int power, int dir) {
	bool r = power < 8 && dir > 4;
	r |= power > 55 && dir < 3;
	r |= (power % 8 == 7) && (dir == 0)|(dir==3)|dir==5;
	r |= (power % 8 == 0) && (dir == 2)|(dir==4)|dir==7;
	return r;
}

u64 possible( u64 mask, u64 current_pos ) {
	u64 possible_moves = 0; // var to store possible moves
	u64 spaces = ~mask; // var to store all current spaces
	u64 opp = mask^current_pos; // get opponent's possition through xor
	int power; // just a temp var
	if(popcount(current_pos) < popcount(spaces)) {
		// search the smallest amount of spots
		u64 copy = current_pos;

		for(int x = 0; x < popcount(current_pos); x++) {
			power = (int)log2(copy);

			for(int index = TOP_LEFT; index != LAST; index++) {
				// loop through all directions
				int dir = Dir_Conjugate[index];// the direction we will check
				int digit = power + dir;// the digit we are checking
				int bit = getBit(opp, digit);// the data of the digit we are checking

				if(Edge(power,index)) continue;
				// Only check if we are not out of the board,
				// i.e. digit < 64 && digit > 0;
				// And while we are still on our player's tile
				// bit == 1 or just bit for short 
				for(digit = power + dir; bit; digit += dir) {
					bit = getBit(opp, digit);
					if(!bit && !getBit(current_pos, digit)) {
						// add to possible moves
						possible_moves |= (1ULL << digit);
						break;
						// exit while loop
					}
					// After checking if current pos is a move,
					// Check if current pos is an edge case
					if(Edge(digit,index)) break;
					// digit += dir;
				}
				// }
			}
			copy ^= (1ULL << power);
			// Remove the bit that was used to check
		}
	}else {
		u64 copy = spaces;
		for(int x = 0; x < popcount(spaces); x++) {
			power = (int)log2(copy);
			for(int index = TOP_LEFT; index !=LAST; index++) {
				int dir = Dir_Conjugate[index];
				int digit = power + dir;
				int bit = getBit(opp, digit);
				int self = getBit(current_pos, digit);

				if(Edge(power,index)) continue;

				for(digit = power + dir; bit && !self; digit += dir) {
					bit = getBit(opp,digit);
					self = getBit(current_pos,digit);
					if(!bit && self) {
						possible_moves |= (1ULL << power);
						break;
					}
					if(Edge(digit,index)) break;
					// digit += dir;
				}
			}
			copy ^= (1ULL << power);
		}
	}
	return possible_moves;
}

u64 flips( u64 mask, u64 current_pos, u64 move ) {
	u64 flips = 0;
	u64 opp = mask^current_pos;
	int power = (int)log2(move);

	for(int index = TOP_LEFT; index != LAST; index++) {
		// u64 temp = 0;
		int dir = Dir_Conjugate[index];
		int digit = power + dir;
		int bit = getBit(opp, digit);

		if(Edge(power,index)) continue;

		for(digit = power + dir; bit; digit += dir) {
			bit = getBit(opp, digit);
			// temp |= (1ULL << digit);
			if(getBit(current_pos,digit)) {
				// flips |= temp;
				for(int x = 1; x < (digit-power)/dir; x++) flips |= (1ULL << power+dir*x);
				// temp = 0;
				break;
			}
			if(Edge(digit,index)) break;
			// digit += dir;
		}
	}
	return flips;
}

u64 flips_1( u64 mask, u64 current_pos, u64 move ) {
	u64 flips = 0;
	u64 opp = mask^current_pos;
	int power = (int)log2(move);

	for(int index = TOP_LEFT; index != LAST; index++) {
		u64 temp = 0;
		int dir = Dir_Conjugate[index];
		int digit = power + dir;
		int bit = getBit(opp, digit);

		if(Edge(power,index)) continue;

		for(digit = power + dir; bit; digit += dir) {
			bit = getBit(opp, digit);
			temp |= (1ULL << digit);
			if(getBit(current_pos,digit)) {
				flips |= temp;
				temp = 0;
				break;
			}
			if(Edge(digit,index)) {
				temp = 0;
				break;
			}
		}
	}
	return flips;
}

void show(u64 object) {
  for(int x = 63; x >= 0; x--) {
    printf("%d", (int)((object >> x)&1));
    if((64-x) % 8 == 0) {
      printf("\n");
    }
  }
}

int negamax( u64 mask, u64 curr, int color, int end) {//color = 1 end = 60
  if(end == 0) {
    return color * popcount(curr);
  }
  int value = -10000;
  u64 children = possible(mask,curr);
  for(int x = 0; x < popcount(children); x++) {
    // u64 child = (1ULL << (int)(log2(children)));
    u64 child = first(children);
    value = max(value,-negamax(mask|child, curr|child, -color,end-1));
    children ^= child;
  }
  return value;
}

int alphabeta( u64 mask, u64 curr, int α, int β, bool maximising, int end) {//int α=-10000, int β=10000, bool maximising=true, int end=60
  if(end == 0) {
    return popcount(curr);
  }
  int value;
  u64 children = possible(mask,curr);
  if(maximising) {
    value = -10000;
    for(int x = 0; x < popcount(children); x++) {
      // u64 child = (1ULL << (int)(log2(children)));
      u64 child = first(children);
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
      // u64 child = (1ULL << (int)(log2(children)));
      u64 child = first(children);
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

int negaAB( u64 mask, u64 curr, int color, int α, int β, int end) {//end = 60
  if(end == 0 || popcount(~mask) == 0 || popcount(possible(mask,curr)) == 0) {
    return color * popcount(curr);
  }
  int value = -10000;
  u64 children = possible(mask, curr);
  for(int x = 0; x < popcount(children); x++) {
    // u64 child = (1ULL << (int)(log2(children)));
    u64 child = first(children);
    value = max(value,-negaAB(mask|child, curr|child, -β, -α, -color,end-1));
    α = max(α,value);
    if(α >= β) {
      break;
    }
    children ^= child;
  }
  return value;
}

int main() {
	u64 mask = 		  B(1111111111111110111111111111111111111111111111110001111000011101);
	u64 current_pos = B(0000111100000110001011111111011111111011111101110001011000010101);
	printf("Mask: %lu\n", mask);
	show(mask);
	printf("\n");
	show(current_pos);
	printf("\n");
	show(possible(mask,current_pos));
	return 0;
}
