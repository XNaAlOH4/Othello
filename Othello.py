import c_lib as cpp
from math import *

getBit = cpp.getBit
popcount = cpp.popcount
first = cpp.first
digit = cpp.digit
# toNote = cpp.toNote
# toPos = cpp.toPos
VtoPos = cpp.VtoPos
printBin = cpp.printBin

# eDirection = {'TOP_LEFT':8+1,'UP':8,'TOP_RIGHT':8-1,
# 'LEFT':1,'RIGHT':-1,
# 'BOTTOM_LEFT':-8+1,'DOWN':-8,'BOTTOM_RIGHT':-8-1}

def toNote(move):
	note = ""
	move = digit(move)
	note += chr(104-int(move/8))
	note += chr(56 - (move%8))
	return note

def toPos(move):
	y = 104 - ord(move[0])
	x = (56-ord(move[1]))
	return (1 << (8*y+x))
class vec2d:
	def __init__(self,x,y):
		self.x = x;
		self.y = y;

def to2d(x):
	return vec2d(8-(x%8),8-int(x/8))

class Position:
	WIDTH = 8
	HEIGHT = 8
	MIN_SCORE =  -(WIDTH*HEIGHT) / 2 + 3
	MAX_SCORE = (WIDTH*HEIGHT+1) / 2 - 3
	def __init__(self):
		self.move_history = ""
		self.restart()
	def restart(self):
		self.mask = (3 << 8*4+3) | (3 << 8*3+3)
		self.current_position = (1 << 8*4+3) | (1 << 8*3+4)
		self.moves = 0
	def play(self, move, undo=False):
		self.flips(move)
		self.mask |= move
		self.current_position |= move
		self.current_position ^= self.mask
		self.moves += 1
		if self.moves == 60:
			if popcount(self.current_position) > popcount(self.opponent()):
				print("White Wins" if moves%2 else "Black Wins");
		if not undo:
			self.record(move)
	def flips(self,move):
		flip = cpp.flips(self.mask, self.current_position, move);
		# printBin(flip);
		for x in range(popcount(flip)):
			thing = first(flip);
			self.current_position ^= thing;
			flip ^= thing; 
	def record(self,move):
		# print("Binary move:",move)
		# print("Move:",toNote(move))
		self.move_history += toNote(move) + " "
	def loadPosition(self):
		moves = self.moves;
		self.restart();
		for move in range(moves):
			# print("Partial:",self.move_history[move*3:move*3+2])
			# print("Test:",toNote(toPos(self.move_history[move*3:move*3+2])))
			self.play(toPos(self.move_history[move*3:move*3+2]),True);
	def undo(self):
		if self.moves > 0:
			self.move_history = self.move_history[:(self.moves-1)*3];
			self.moves -= 1;
			self.loadPosition();
	def possible(self):
		return cpp.possible(self.mask, self.current_position);
	def opponent(self):
		return self.current_position ^ self.mask;
	def AImove(self,depth):
		bestMove = 0;
		bestScore = -1;
		possible = self.possible()
		if(popcount(possible) == 0):
			print("No more possible moves!")
			return
		# print(possible)
		# print()
		for move_ in range(popcount(possible)):
			move = first(possible)
			self.play(move)
			score = cpp.negaAB(self.mask,self.current_position,-10000,10000,1,depth)
			self.undo()
			if(score > bestScore):
				bestScore = score
				bestMove = move
		if bestScore > -1:
			self.play(bestMove)
		else:
			self.play(first(possible))




		


