from cs50 import get_int 

num = -1
while num < 1 or num > 8:
    num = get_int("Height: ")

for i in range(num):
    for j in range(num):
        if j+1 >= (num-i):
            print("#", end="")
        else:
            print(" ", end="")
    print("  ", end="")
    for j2 in range(num):
        if j2+1 <= i+1:
            print("#", end="")
    print("")