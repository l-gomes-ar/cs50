from cs50 import SQL
from flask import Flask, flash, redirect, request, render_template, session
from flask_session import Session
from functools import wraps
from html import escape
from random import randint, choice
from string import ascii_letters, digits, punctuation, ascii_lowercase, ascii_uppercase
from werkzeug.security import check_password_hash, generate_password_hash


app = Flask(__name__)

# Configure session to use filesystem
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///passwords.db")

# Configure database
db.execute(
    "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL, hash TEXT NOT NULL);"
)
db.execute(
    "CREATE UNIQUE INDEX IF NOT EXISTS username ON users (username);"
)
db.execute(
    "CREATE TABLE IF NOT EXISTS accounts (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, account TEXT);"
)
db.execute(
    "CREATE UNIQUE INDEX IF NOT EXISTS account ON accounts (account);"
)
db.execute(
    "CREATE TABLE IF NOT EXISTS passwords (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, user_id INTEGER NOT NULL, account_id INTEGER NOT NULL, password TEXT, email TEXT, FOREIGN KEY (user_id) REFERENCES users(id), FOREIGN KEY (account_id) REFERENCES accounts(id));"
)
db.execute(
    "CREATE UNIQUE INDEX IF NOT EXISTS password ON passwords (password);"
)


def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/2.3.x/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


# Show summary of all passwords saved
@app.route("/")
@login_required
def index():
    # Get info for all accounts and passwords saved for the current user
    info = db.execute(
        "SELECT passwords.id, account, email, password FROM accounts JOIN passwords ON account_id = accounts.id JOIN users ON user_id = users.id WHERE users.id = ?;",
        session["user_id"]
    )

    # Escape any special characters in the password
    for row in info:
        row["password"] = escape(row["password"])

    return render_template("index.html", info=info)


@app.route("/register", methods=["GET", "POST"])
def register():
    # If submitted via GET go to register page
    if request.method == "GET":
        return render_template("register.html")
    
    # If form submitted
    username = request.form.get("username")
    password = request.form.get("password")

    # Check if username and password both exist and password matches confirmation
    if username and password:
        # Ensure passwords is at least 15 characters long
        if len(password) < 15:
            flash("Password needs to be at least 15 characters long!")

            return redirect("/register")
        
        # Ensure password has both lower and upper case letters, digits, and punctuation 
        
        # Each of these is a generator which compares each character in password with each character in digits/punctuation/upper/lower, 
        # and returns a generator object of trues and falses whether the character is in digits/punctuation/upper/lower or not. 
        # any() checks if in a generator object we have at least one True bool.
        if any(char in password for char in digits) and any(char in password for char in punctuation) and any(char in password for char in ascii_lowercase) and any(char in password for char in ascii_uppercase):
            if password == request.form.get("confirmation"):
                # Check if username is unique
                usernames = db.execute(
                    "SELECT username FROM users;"
                )
                for i in range(len(usernames)):
                    if username in usernames[i].values():
                        flash("Username already exists!")

                        return redirect("/register")
                
                db.execute(
                    "INSERT INTO users (username, hash) VALUES (?, ?);",
                    username, generate_password_hash(password)
                )

                flash("Registered!")

                return redirect("/")
            else:

                flash("Input is blank or the passwords do not match!")

                return redirect("/register")
        
        else:
            flash("Password must contain lower and upper case letters, digits, and punctuation!")

            return redirect("/register")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            flash("Must provide username!")

            return render_template("login.html")

        # Ensure password was submitted
        elif not request.form.get("password"):
            flash("Must provide password!")

            return render_template("login.html")

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?",
            request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            flash("Invalid username and/or password!")

            return render_template("login.html")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash("Logged In!")

        # Redirect user to home page
        return redirect("/")
    
    return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/login")


@app.route("/generate", methods=["GET", "POST"])
@login_required
def add():
    """ Generates new password """
    if request.method == "GET":
        return render_template("generate.html")
    
    account = request.form.get("account")
    email = request.form.get("email")
    
    if account == "" or email == "":
        flash("Add an account name and email for the password!")

        return render_template("generate.html")
    
    possibilities = [ascii_letters, digits, punctuation]

    password = ""
    for i in range(0, 150):
        x = choice(possibilities)
        password = password + x[randint(0, len(x) - 1)]

    flash("Password Generated!")
    return render_template("generated.html", password=password, account=account, email=email)


@app.route("/save", methods=["POST"])
@login_required
def save():
    """ Saves new password """
    account = request.form.get("account").capitalize()
    password = request.form.get("password")
    email = request.form.get("email")

    # Insert the account into the accounts table if it is not already there
    db.execute(
        "INSERT INTO accounts (account) SELECT ? WHERE NOT EXISTS (SELECT account FROM accounts WHERE account = ?);",
        account, account
    )

    def escape_special(s):
        """
        Escape special characters in SQL.
        """
        for old, new in [(":", "\:")]:
            s = s.replace(old, new)

        return s

    # Insert into password tables the values for current user, the account id, and the password
    account_id = db.execute("SELECT id FROM accounts WHERE account = ?;", account)
    account_id = account_id[0]["id"]
    db.execute(
        "INSERT INTO passwords (user_id, account_id, email, password) VALUES (?, ?, ?, ?);",
        session["user_id"], account_id, email, escape_special(password)
    ) 

    return redirect("/")


@app.route("/delete", methods=["POST"])
@login_required
def delete():
    """ Deletes a password and account """
    id = request.form.get("id")

    db.execute(
        "DELETE FROM passwords WHERE id = ?",
        id
    )

    flash("Password deleted!")

    return redirect("/")


@app.route("/delete_all")
@login_required
def delete_all():
    """ Deletes all passwords """
    db.execute("DELETE FROM passwords WHERE user_id = ?", session["user_id"])

    flash("Passwords deleted!")

    return redirect("/")