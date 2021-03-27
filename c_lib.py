import ctypes , ctypes.util
import sys, platform

# libname = pathlib.Path().absolute() / "Position.dylib"
# libname = ctypes.util.find_library("./Position")
libname = ctypes.util.find_library("./Better_Pos")

if not libname:
	print("Unable to find the specified library.")
	sys.exit()

try:
	c_lib = ctypes.CDLL(libname)
except OSError:
	print("Unable to load the system C library")
	sys.exit()

# play = c_lib.play
# play.argtypes = [Position, ctypes.c_longlong]

# nbMove = c_lib.nbMoves
# nbMove.argtypes = [Position]
# nbMove.restype = ctypes.c_int

# getHistory = c_lib.getHistory
# getHistory.argtypes = [Position]
# getHistory.restype = ctypes.c_wchar_p

# undo = c_lib.undo
# undo.argtypes = [Position]

getBit = c_lib.getBit
getBit.argtypes = [ctypes.c_longlong, ctypes.c_int]
getBit.restype = ctypes.c_int

popcount = c_lib.popcount
popcount.argtypes = [ctypes.c_longlong]
popcount.restype = ctypes.c_uint

first = c_lib.first
first.argtypes = [ctypes.c_longlong]
first.restype = ctypes.c_longlong

digit = c_lib.digit
digit.argtypes = [ctypes.c_longlong]
digit.restype = ctypes.c_int

toNote = c_lib.toNote
toNote.argtypes = [ctypes.c_longlong,ctypes.c_wchar_p]
toNote.restype = ctypes.c_wchar_p

toPos = c_lib.toPos
toPos.argtypes = [ctypes.c_char, ctypes.c_char]
toPos.restype = ctypes.c_longlong

VtoPos = c_lib.vecToPos
VtoPos.argtypes = [ctypes.c_int, ctypes.c_int]
VtoPos.restype = ctypes.c_longlong

possible = c_lib.possible
possible.argtypes = [ctypes.c_longlong,ctypes.c_longlong]
possible.restype = ctypes.c_longlong

flips = c_lib.flips
flips.argtypes = [ctypes.c_longlong, ctypes.c_longlong, ctypes.c_longlong]
flips.restype = ctypes.c_longlong

printBin = c_lib.show
printBin.argtypes = [ctypes.c_longlong]

negaAB = c_lib.negaAB
negaAB.argtypes = [ctypes.c_longlong, ctypes.c_longlong, ctypes.c_int,ctypes.c_int,ctypes.c_int,ctypes.c_int]
negaAB.restype = ctypes.c_int

