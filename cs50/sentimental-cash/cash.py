from cs50 import get_float


def main():
    # Prompt the user for change owed, in cents
    while True:
        dollars = get_float("Change: ")
        if dollars >= 0:
            break

    cents = dollars * 100
    # Calculate how many quarters you should give customer
    quarters = calculate_quarters(cents)

    # Subtract the value of those quarters from cents
    cents = cents - (quarters * 25)

    # Calculate how many dimes you should give customer
    dimes = calculate_dimes(cents)

    # Subtract the value of those dimes from remaining cents
    cents = cents - (dimes * 10)

    # Calculate how many nickels you should give customer
    nickels = calculate_nickels(cents)

    # Subtract the value of those nickels from remaining cents
    cents = cents - (nickels * 5)

    # The remaining cents should be equal to pennies
    pennies = cents

    # Sum the number of quarters, dimes, nickels, and pennies used
    sum = quarters + dimes + nickels + pennies

    # Print that sum
    print(f"{int(sum)}")


def calculate_quarters(cents):
    # Calculate how many quarters you should give customer
    quarters = 0
    while (cents >= 25):
        quarters += 1
        cents = cents - 25

    return quarters


def calculate_dimes(cents):
    # Calculate how many dimes you should give customer
    dimes = 0
    while (cents >= 10):
        dimes += 1
        cents = cents - 10

    return dimes


def calculate_nickels(cents):
    # Calculate how many nickels you should give customer
    nickels = 0
    while (cents >= 5):
        nickels += 1
        cents = cents - 5

    return nickels


main()
