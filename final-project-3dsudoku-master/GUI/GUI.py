from cs1lib import *
import sys
import random

fp = open("logfile16.txt", "r")

first_line = fp.readline()[0:6]
print(first_line)
size = int(fp.readline()[0:2])
print(size)

if first_line[0:6] != "create":
    sys.exit("file must have been created by ./sudoku create")

# Creates a list containing size lists, each of size items, all set to 0
sudoku = [[0 for x in range(size)] for y in range(size)]

frame = 1  # initialize start variable

bg = True
wasSolve = False
pressed_S = False
solvePassed = False

r = random.uniform(0, 1)
g = random.uniform(0, 1)
b = random.uniform(0, 1)

if (r+g+b/3 < 0.7):
    r,g,b = 1,1,0.5

def keypress(key):
    global pressed_S
    if key == "s":
        pressed_S = True

def keyrelease(key):
    global pressed_S
    if key == "s":
        pressed_S = False

def draw_numbers():
    global frame, wasSolve, pressed_S, solvePassed

    if frame % 50 == 0 and not wasSolve:
        draw_numbers_helper()

    if wasSolve and pressed_S:
        draw_numbers_helper()
        wasSolve = False
        solvePassed = True

    if solvePassed:
        draw_numbers_helper()

    frame += 1

def draw_numbers_helper():
    global wasSolve, pressed_S, r, g, b

    line = fp.readline()

    if line and line[0:5] == "solve":
        wasSolve = True

    if line and (line[0:5] != "solve"):
        row = int(line[3:5])
        col = int(line[6:8])
        num = int(line[0:2])

        sudoku[row][col] = num

        if sudoku[row][col] != 0:
            strnum = str(sudoku[row][col])
            draw_text(strnum, (row + 6.7 + (30 * row)), (col + 18 + (30 * col)))
        else:
            set_fill_color(r, g, b)
            disable_stroke()
            draw_rectangle(row + 5.5 + (30 * row), col + 5.5 + (30 * col), 15, 15)
            enable_stroke()

def draw_grid():
    global r,g,b
    x_var = 5
    y_var = 5

    set_fill_color(r,g,b)

    for row in range(0, size):
        for col in range(0, size):
            draw_rectangle(x_var, y_var, 30, 30)
            y_var = y_var + 30
        x_var = x_var + 30
        y_var = 5

def main():
    global bg
    if bg:
        draw_grid()
        bg = False
    draw_numbers()

if size == 4 or size ==6:
    start_graphics(main, 2400, None, 500,"cs1", 290, 290, key_press=keypress, key_release= keyrelease)
elif size == 9 or size == 16:
    start_graphics(main, 2400, None, 1000, "cs1", 500, 500, key_press=keypress, key_release= keyrelease)
fp.close()

