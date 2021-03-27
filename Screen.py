from Othello import *
# from pynput import mouse, keyboard as K
from tkinter import *

## SETUP

START = vec2d(40,40)
WIDTH = 700
HEIGHT = 700

def _circle(self,x,y,r, **kwargs):
	return self.create_oval(x,y,x+2*r,y+2*r, **kwargs)
Canvas.circle = _circle

def draw():
	global current_player, canvas
	canvas.create_rectangle(START.x,START.y,680,680,fill="#2DC630")
	for y in range(8):
		# for x in range(8):
		for x in range(7):
			c = (x+1)*80+40
			# x line
			canvas.create_line(40,c,680,c)
			# y line
			canvas.create_line(c,40,c,680)
	opp = board.opponent()
	copy = board.mask
	for x in range(popcount(copy)):
		power = digit(copy)
		y = 560-80*(int(power/8));#80*(7-y)
		x = 560-80*(power%8);#80*(7-x)
		if getBit(board.current_position, power) == 1:
			canvas.circle(x+40+5, y+40+5, 35, fill="white" if current_player == 0 else "black")
		else:## getBit(opp, power) == 1:
			canvas.circle(x+40+5, y+40+5, 35, fill="black" if current_player == 0 else "white")
		copy ^= (1 << power)
	copy = board.possible()
	for x in range(popcount(copy)):
		power = digit(copy)
		y = 640-80*(int(power/8));
		x = 640-80*(power%8);
		canvas.create_line(x+35, y+35, x-35, y-35, fill="red");
		canvas.create_line(x+35, y-35, x-35, y+35, fill="red");
		copy ^= (1 << power)
## END draw

def OutofRange(mouse):
	x = mouse.x
	y = mouse.y
	if x > WIDTH | x < 0:
		return 1;
	if y > HEIGHT | y < 0:
		return 1;
	return 0

def inRange(x,y):
	if x.x > 80*y.x-40 and x.x < 80*y.x+40 and x.y > 80*y.y-40 and x.y < 80*y.y+40:
		return 1;
	return 0

def checkClick(mouse):
	x = mouse.x;
	y = mouse.y;
	global current_player;
	if OutofRange(mouse):
		return;
	poss = board.possible()
	for x_ in range(popcount(poss)):
		pos = to2d(digit(poss))
		if inRange(vec2d(x,y),pos) == 1:
			board.play(VtoPos(pos.x,pos.y));
			current_player = not current_player;
			draw();
			return;
		poss ^= (1 << digit(poss));

def on_press(key):
	global current_player
	if key.char == 'p':
		print("Current Player: ")
		printBin(board.current_position);
		print()
		print("Possible: ")
		printBin(board.possible());
		print("History: ")
		print(board.move_history);
	if key.char == 'u':
		board.undo()
		current_player = not current_player;
		draw()
		return
	if key.char == 'a':
		board.AImove(60)
		current_player = not current_player
		draw()

board = Position()
current_player = 1

window = Tk()
window.title("Reversi")
canvas = Canvas(window, width=WIDTH,height=HEIGHT)
canvas.pack()

## RUN

# Draw board
for y in range(8):
	canvas.create_text(15, y*80+80, anchor=W, font="Arial",text=chr(y+65))
for x in range(8):
	canvas.create_text(x*80+78, 15, anchor=W, font="Arial",text=x+1)
canvas.create_rectangle(30,30,690,690,fill="#000")
canvas.create_rectangle(START.x,START.y,680,680,fill="#2DC630")
for x in range(7):
	c = (x+1)*80+40
	# x line
	canvas.create_line(40,c,680,c)
	# y line
	canvas.create_line(c,40,c,680)
draw()

window.bind("<Key>", on_press)
window.bind("<Button-1>",checkClick)
window.mainloop()
