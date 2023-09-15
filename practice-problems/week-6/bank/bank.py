# If greeting starts with 'h' give $20, if not "hello", or starting with "h", $0, and if it is 'hello',$100

from cs50 import get_string

greeting = get_string("Greeting? ").lower().strip()

if "h" in greeting[0] and "hello" not in greeting:
    print("$20")
elif "hello" in greeting:
    print("$0")
else:
    print("$100")