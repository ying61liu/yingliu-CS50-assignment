from cs50 import get_float


while True:
    paid = int(get_float("Change: ") * 100)
    if paid > 0:
        break

quarters = paid // 25
paid = paid - quarters * 25
dimes = paid // 10
paid = paid - dimes * 10
nickels = paid // 5
paid = paid - nickels * 5
pennies = paid // 1

count = (quarters + dimes + nickels + pennies)

print(count)
