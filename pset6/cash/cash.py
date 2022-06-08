from cs50 import get_float
import math

change = -0.5
coins = 0

while change < 0:
    change = get_float("Change owed: ")
    
change = int(round(change * 100))
    
while change >= 25:
    change = change - 25
    coins += 1
while change >= 10:
    change = change - 10
    coins += 1
while change >= 5:
    change = change - 5
    coins += 1
while change >= 1:
    change = change - 1
    coins += 1
    
print(coins)