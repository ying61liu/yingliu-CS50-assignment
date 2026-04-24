from cs50 import get_float


def main():
    while True:
        paid = int(get_float("Change: ") * 100)
        if paid > 0:
            break

    quarters = calculate_quarters(paid)
    paid = paid - quarters * 25
    dimes = calculate_dimes(paid)
    paid = paid - dimes * 10
    nickels = calculate_nickels(paid)
    paid = paid - nickels * 5
    pennies = calculate_pennies(paid)
    print(quarters + dimes + nickels + pennies)


def calculate_quarters(paid):
    quarters = 0
    while paid >= 25:
        quarters += 1
        paid = paid - 25
    return quarters


def calculate_dimes(paid):
    dimes = 0
    while paid >= 10:
        dimes += 1
        paid = paid - 10
    return dimes


def calculate_nickels(paid):
    nickels = 0
    while paid >= 5:
        nickels += 1
        paid = paid - 5
    return nickels


def calculate_pennies(paid):
    pennies = 0
    while paid >= 1:
        pennies += 1
        paid = paid - 1
    return pennies


if __name__ == "__main__":
    main()
