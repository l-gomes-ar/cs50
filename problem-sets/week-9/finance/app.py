import os

from cs50 import SQL
from datetime import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Select symbol and shares
    rows = db.execute(
        "SELECT symbol, shares FROM users JOIN shares ON shares.user_id = users.id JOIN stocks ON shares.stock_id = stocks.id WHERE users.id == ?;", session["user_id"])

    # Select current user's cash
    f = db.execute("SELECT cash FROM users WHERE id == ?;", session["user_id"])
    print(f)
    print(session["user_id"])
    cash = f[0]["cash"]

    # Get the SUM of all symbol values
    total = 0
    for row in rows:
        total += (lookup(row["symbol"])["price"] * row["shares"])

    return render_template("index.html", rows=rows, lookup=lookup, usd=usd, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    
    # Store info submitted
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")

    try:
        shares = int(shares)
    except ValueError:
        return apology("Must buy at least one share!")
    
    purchase_time = datetime.now()

    # If symbol not valid
    quote = lookup(symbol)
    if quote == None:
        return apology("Symbol not valid!")
    
    # If shares less than 1
    if shares < 1:
        return apology("Must buy at least one share!")
    
    # Check for users cash, add apology if user cannot add purchase
    cash = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])
    price = quote["price"]

    if cash[0]["cash"] - (shares * price) <= 0:
        return apology("Not enough cash to buy these shares")
    
    # If purchase successful create tables for storing both the stock symbol and 
    db.execute("CREATE TABLE IF NOT EXISTS stocks (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, symbol TEXT);")
    db.execute("CREATE UNIQUE INDEX IF NOT EXISTS symbol ON stocks (symbol);")
    db.execute("CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, stock_id INTEGER NOT NULL, user_id INTEGER NOT NULL, time TEXT NOT NULL, n_shares INTEGER, price TEXT, FOREIGN KEY(user_id) REFERENCES users(id), FOREIGN KEY(stock_id) REFERENCES stocks(id));")
    db.execute("CREATE INDEX IF NOT EXISTS time ON transactions (time);")
    db.execute("CREATE INDEX IF NOT EXISTS n_shares ON transactions (n_shares);")
    db.execute("CREATE INDEX IF NOT EXISTS price ON transactions (price);")
    db.execute("CREATE TABLE IF NOT EXISTS shares (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, stock_id INTEGER, user_id INTEGER, shares INTEGER NOT NULL DEFAULT 0, FOREIGN KEY(user_id) REFERENCES users(id), FOREIGN KEY(stock_id) REFERENCES stocks(id));")

    # Add a stock to the stocks table
    db.execute("INSERT or IGNORE INTO stocks (symbol) VALUES (?);", symbol)
    
    # Get stock_id and current user_id then add them to transactions
    stock_id = db.execute("SELECT id FROM stocks WHERE symbol == ?", symbol)
    db.execute("INSERT INTO transactions (stock_id, user_id, time, n_shares, price) VALUES (?, ?, ?, ?, ?);",
               stock_id[0]["id"], session["user_id"], purchase_time, shares, usd(price))

    # Add number of shares into shares table
    try:
        current_n_shares = db.execute("SELECT shares FROM shares WHERE stock_id == ? AND user_id == ?;",
                                      stock_id[0]["id"], session["user_id"])
        if len(current_n_shares) == 0:
            raise ValueError
    except ValueError:
        # If no shares, add them
        db.execute("INSERT INTO shares (stock_id, user_id, shares) VALUES (?, ?, ?);",
                   stock_id[0]["id"], session["user_id"], shares)
        db.execute("UPDATE users SET cash = (cash - ?) WHERE id == ?", (price * shares), session["user_id"])

        flash("Bought!")

        return redirect("/")

    # Update number of shares user holds and their cash
    db.execute("UPDATE shares SET shares = (shares + ?) WHERE stock_id == ? AND user_id == ?;",
               shares, stock_id[0]["id"], session["user_id"])
    db.execute("UPDATE users SET cash = (cash - ?) WHERE id == ?;", (price * shares), session["user_id"])

    flash("Bought!")

    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute(
        "SELECT symbol, n_shares, price, time FROM transactions JOIN stocks ON stock_id = stocks.id WHERE user_id == ? ORDER BY time DESC", session["user_id"])

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        flash("Logged In!")
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    
    # When form is submitted
    quote = lookup(request.form.get("symbol"))
    if quote == None:
        return apology("Symbol not valid!")
    
    return render_template("quoted.html", quote=quote, usd=usd)


@app.route("/register", methods=["GET", "POST"])
def register():
    # If submitted via GET go to register page
    if request.method == "GET":
        return render_template("register.html")
    
    # If form submitted
    # Check if username and password both exist and password matches confirmation
    if request.form.get("username") and request.form.get("password"):
        if request.form.get("password") == request.form.get("confirmation"):
            # Check if username is unique
            usernames = db.execute("SELECT username FROM users;")
            for i in range(len(usernames)):
                if request.form.get("username") in usernames[i].values():
                    return apology("Username already exists!")
            
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", request.form.get(
                "username"), generate_password_hash(request.form.get("password")))

            flash("Registered!")

            return redirect("/")

    return apology("Input is blank or the passwords do not match!")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    symbols = db.execute("SELECT symbol FROM stocks JOIN shares ON stock_id = stocks.id WHERE user_id == ?;", session["user_id"])

    if request.method == "GET":
        return render_template("sell.html", symbols=symbols)
    
    symbol = request.form.get("symbol")
    shares = int(request.form.get("shares"))
    
    # If user does not select a stock
    if symbol == None or request.form.get("shares") == "":
        return apology("No stock or number of shares selected!")
    
    # If user does not own any shares of that stock
    n_shares = db.execute("SELECT shares FROM shares JOIN stocks ON stock_id = stocks.id WHERE symbol == ?;", symbol)
    if len(n_shares) < 1:
        return apology("You do not own any shares of this stock!")
    
    if int(n_shares[0]["shares"]) < shares:
        return apology("Not enough shares!")
    
    # Get time and details for the selling
    sell_time = datetime.now()
    stock_id = db.execute("SELECT id FROM stocks WHERE symbol == ?", symbol)
    price = (lookup(symbol))["price"]

    # Add to the transactions table
    db.execute("INSERT INTO transactions (stock_id, user_id, time, n_shares, price) VALUES (?, ?, ?, ?, ?);",
               stock_id[0]["id"], session["user_id"], sell_time, (-1 * shares), usd(price))

    # Update number of shares for that stock
    db.execute("UPDATE shares SET shares = (shares - ?) WHERE user_id == ? AND stock_id == ?;",
               shares, session["user_id"], stock_id[0]["id"])

    # If stock 0, delete that share for this user
    n = db.execute("SELECT shares FROM shares WHERE user_id == ? AND stock_id == ?;", session["user_id"], stock_id[0]["id"])
    if n[0]["shares"] == 0:
        db.execute("DELETE FROM shares WHERE user_id == ? AND stock_id == ?;", session["user_id"], stock_id[0]["id"])

    # Update user's cash
    db.execute("UPDATE users SET cash = (cash + ?) WHERE id == ?;", (price * shares), session["user_id"])

    flash("Sold!")

    return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    if request.method == "GET":
        return render_template("add.html")
    
    cash = request.form.get("cash")

    if cash == "":
        return apology("Type in how much you want to add!")
    
    try:
        cash = int(cash)
    except ValueError:
        return apology("Type in how much you want to add!")
    
    if cash == 0:
        return apology("Type in at least $0.01!")
    
    db.execute("UPDATE users SET cash = (cash + ?) WHERE id == ?;", cash, session["user_id"])

    flash("Cash Added!")

    return redirect("/")