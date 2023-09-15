# TODO
from cs50 import get_float


def main():
    # Ask how many cents the customer is owed
    dollars = get_dollars()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(dollars)
    dollars = round((dollars - quarters * 0.25), 2)

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(dollars)
    dollars = round((dollars - dimes * 0.1), 2)

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(dollars)
    dollars = round((dollars - nickels * 0.05), 2)

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(dollars)
    dollars = round((dollars - pennies * 0.01), 2)

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give
    print(f"{coins:.0f}")


def get_dollars():
    while True:
        cents = get_float("Change owed: ")

        if cents >= 0:
            return cents


def calculate_quarters(dollars):
    return int(dollars / 0.25)


def calculate_dimes(dollars):
    return int(dollars / 0.10)


def calculate_nickels(dollars):
    return int(dollars / 0.05)


def calculate_pennies(dollars):
    return int(dollars / 0.01)


main()