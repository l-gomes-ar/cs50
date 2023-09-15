import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    people = []
    # TODO: Read database file into a variable
    with open(sys.argv[1]) as f:
        reader = csv.DictReader(f)
        keys = csv.reader(f)

        # Get keys
        for row in keys:
            keys = []
            keys = row
            break

        # Reset file reader to first position
        f.seek(0)
        for row in reader:
            person = {}

            # Each key gets its value from file for each row
            for i in range(len(keys)):
                person[keys[i]] = row[keys[i]]

            # Add person dict to list of people
            people.append(person)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as f:
        reader = csv.reader(f)
        for row in reader:
            sequence = row[0]
            break

    # TODO: Find longest match of each STR in DNA sequence
    longest_matches = {}
    for i in range(1, len(keys)):
        longest_matches[keys[i]] = longest_match(sequence, keys[i])

    # TODO: Check database for matching profiles
    counter = 0
    matches = 0
    i = 1

    # Check for each key, update number of matches if True
    while counter < len(people) and i < len(keys):
        if int(people[counter][keys[i]]) == longest_matches[keys[i]]:
            matches += 1
            i += 1
        else:
            i = 1
            matches = 0
            counter += 1

    # If number of matches equals number of keys, print name
    if matches == (len(keys) - 1):
        print(people[counter]["name"])
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
