# TODO
from cs50 import get_int


def main():
    # Prompt user for positive integer between 1 and 8
    while True:
        height = get_int("Height: ")

        if height > 0 and height < 9:
            break
    # Build pyramid
    build_pyramid(height)


# Build pyramid
def build_pyramid(n):
    # This loop prints the space for each row
    i = 1
    while (i <= n):

        # Print the opposite number of dots for each row (to reach 8 blocks per row)
        j = 0
        while (j < n - i):
            print(" ", end="")
            j += 1

        # This loop prints the blocks in each row
        k = i - i
        while (k < i):
            print("#", end="")
            k += 1

        print()
        i += 1


main()