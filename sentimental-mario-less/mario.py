from cs50 import get_int

while True:
    rows = int(get_int("Height: "))
    if rows >= 1 and rows <= 8:
        break

for row in range(rows):
    print(" " * (rows - 1 - row) + "#" * (1 + row))
