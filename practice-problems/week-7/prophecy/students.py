import csv
from cs50 import SQL


def main():
    db = SQL("sqlite:///new_roster.db")

    # Create Tables
    db.execute(
        "CREATE TABLE students (id INTEGER NOT NULL, student_name TEXT, PRIMARY KEY(id))"
    )
    db.execute(
        "CREATE TABLE houses (id INTEGER NOT NULL, house TEXT NOT NULL, head TEXT NOT NULL, PRIMARY KEY(id))"
    )
    db.execute(
        "CREATE TABLE assignments (id INTEGER, student_id INTEGER, house_id INTEGER, FOREIGN KEY (student_id) REFERENCES students(id), FOREIGN KEY (house_id) REFERENCES houses(id), PRIMARY KEY(id))"
    )

    # Add values into houses
    db.execute(
        "INSERT INTO houses (house, head) VALUES ('Gryffindor', 'Minerva McGonagall')"
    )
    db.execute(
        "INSERT INTO houses (house, head) VALUES ('Slytherin', 'Severus Snape')"
    )
    db.execute(
        "INSERT INTO houses (house, head) VALUES ('Hufflepuff', 'Pomona Sprout')"
    )
    db.execute(
        "INSERT INTO houses (house, head) VALUES ('Ravenclaw', 'Filius Flitwick')"
    )

    # Get houses_id
    slytherin_id = db.execute(
        "SELECT id FROM houses WHERE house = 'Slytherin'"
    )
    hufflepuff_id = db.execute(
        "SELECT id FROM houses WHERE house = 'Hufflepuff'"
    )
    ravenclaw_id = db.execute(
        "SELECT id FROM houses WHERE house = 'Ravenclaw'"
    )
    gryffindor_id = db.execute(
        "SELECT id FROM houses WHERE house = 'Gryffindor'"
    )
    
    with open("students.csv", "r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            db.execute(
                "INSERT INTO students (student_name) VALUES (?)", row["student_name"]
            )

            if row["house"] == "Slytherin":
                db.execute(
                    "INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", row["id"], slytherin_id[0]["id"]
                )
            elif row["house"] == "Gryffindor":
                db.execute(
                    "INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", row["id"], gryffindor_id[0]["id"]
                )
            elif row["house"] == "Hufflepuff":
                db.execute(
                    "INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", row["id"], hufflepuff_id[0]["id"]
                )
            else:
                db.execute(
                    "INSERT INTO assignments (student_id, house_id) VALUES (?, ?)", row["id"], ravenclaw_id[0]["id"]
                )
    return


main()
