from cs50 import get_string
import re


def main():
    number = get_string("Number: ")

    # check length
    length = len(number)
    if length not in [13, 15, 16]:
        print("INVALID")

    else:
        # Luhn's algorithm
        if length % 2 == 1:
            # (for an odd number of digits)
            sum = 0
            idx = length - 1
            while idx > 0:
                product = int(number[idx - 1]) * 2
                product_d = str(product)
                for i in range(len(product_d)):
                    sum += int(product_d[i])
                idx -= 2
            i = 0
            while i < length:
                sum += int(number[i])
                i += 2
            last_d = str(sum)[-1]
            if last_d == "0":
                check_brand(number)
            else:
                print("INVALID")

        else:
            # (for an even number of digits)
            sum = 0
            idx = length - 1
            while idx >= 0:
                product = int(number[idx - 1]) * 2
                product_d = str(product)
                for i in range(len(product_d)):
                    sum += int(product_d[i])
                idx -= 2
            i = 1
            while i < length:
                sum += int(number[i])
                i += 2
            last_d = str(sum)[-1]
            if last_d == "0":
                check_brand(number)
            else:
                print("INVALID")

# check brand


def check_brand(number):
    length = len(number)

    # Check for American Express
    if (length == 15) and (re.search("^34", number) or re.search("^37", number)):
        print("AMEX")

    # Check for MasterCard
    elif (length == 16) and (re.search("^51", number) or re.search("^52", number)
                             or re.search("^53", number) or re.search("^54", number)
                             or re.search("^55", number)):
        print("MASTERCARD")

    # Check for Visa
    elif (length == 13 or 16) and (re.search("^4", number)):
        print("VISA")

    else:
        print("INVALID")


if __name__ == "__main__":
    main()
