import sys
import random
from cs50 import get_string
from pyfiglet import Figlet

figlet = Figlet()
fonts = figlet.getFonts()

# Expect zero or two command-line arguments
if len(sys.argv) == 1:
    # Prompt user for str of text
    input = get_string("Input: ")

    # Set random font
    figlet.setFont(font=random.choice(fonts))

    # Output rendered text
    print(figlet.renderText(input))

    sys.exit(0)

elif len(sys.argv) == 3:
    # Ensure command-line arguments were handled correctly
    if sys.argv[1] not in ["-f", "--font"] or sys.argv[2] not in fonts:
        print("Invalid usage")
        sys.exit(1)

    # Prompt user for str of text
    input = get_string("Input: ")

    # Set argv[2] as the font
    figlet.setFont(font=sys.argv[2])

    # Output rendered text
    print(figlet.renderText(input))

    sys.exit(0)

else:
    print("Invalid usage")
    sys.exit(1)