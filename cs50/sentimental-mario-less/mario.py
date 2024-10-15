from cs50 import get_int


def main():
    # Prompt the user for the pyramid's height
    while True:
        n = get_int("Height: ")
        if n >= 1 and n <= 8:
            break

    # Print a pyramid of that height
    for i in range(n):
        # Print row of bricks
        print_row(n - i, i + 1)


def print_row(space, bricks):
    for i in range(space - 1, 0, -1):
        print(" ", end="")

    for i in range(bricks):
        print("#", end="")

    print("")


main()
