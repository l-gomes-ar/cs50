# Password Manager Web Application
#### Video Demo:  https://youtu.be/NAeSedR7c9M
#### Description:
This is a web application built using Flask that serves as a password manager. It allows users to register, log in, generate secure passwords, save passwords for different accounts, and manage their password data.

#### Features
- Allows registering a new account or logging in with existing credentials.
- Generates secure passwords using the provided password generator.
- Saves generated passwords along with the associated account name and email.
- View a summary of all saved passwords in a table.
- Allows copying password to clipboard by clicking on 'Copy Password' in the table.
- Lets user delete passwords individually or delete all passwords at once.

## app.py
This is the Flask-based web application serving the password manager. It uses Flask for routing and rendering templates, as well as SQLite via the cs50 library for managing user and password data in a database.
First, it configures session to use filesystem, configures the cs50 library to use SQLite database, then it configures the database, creating tables for storing the information required for the password manager to work properly. More on that on "password.db".

Below is an example of how the different routes and functionalities work:

### login_required Decorator
This custom decorator (login_required) ensures that certain routes are only accessible to logged-in users. If a user is not logged in, they are redirected to the login page.

### Index Route ("/") - Home Page
When a user logs in, they are redirected to the home page. The home page displays a summary of all the saved passwords associated with the user's account.

### Register Route ("/register")
Users can register by providing a username and password. The password must be at least 15 characters long and include a mix of lowercase letters, uppercase letters, digits, and special characters.

### Login Route ("/login")
Registered users can log in using their credentials. The application checks the entered username and password against the stored hash to verify the user's identity.

### Logout Route ("/logout")
Users can log out of their accounts, clearing their session data.

### Generate Password Route ("/generate")
Users can generate a random, secure password. They need to provide an account name and an associated email address for which they want to generate a password.

### Save Password Route ("/save")
After generating a password, users can save it along with the associated account name and email. The password is also associated with the user's account.

### Delete Password Route ("/delete")
Users can delete a saved password and its associated account. This route is typically accessed from the home page.

### Delete All Passwords Route ("/delete_all")
Users can delete all saved passwords associated with their account.

## passwords.db
This is the SQL database created using SQLite3. It stores three tables, being:

### users
Contains the id for a user, their username and the hash for their password (generated with generate_password_hash() from the werkzeug.security module)

### accounts
This table contains the accounts the user generated a password for, it has the id for the account and the its name

### passwords
It contains the id for the password, the user's id, the id for the account, and the password generated

## requirements.txt
This file lists the external Python packages my project depends on. Each line corresponds to a package required for my project.

### Dependencies
    cs50
    flask
    flask-session
    functools
    html
    random
    string
    werkzeug

## templates/layout.html
This is the HTML template for my web application's layout. It includes Bootstrap CSS and JavaScript libraries, an icon, a navigation bar, and placeholders for dynamic content using Jinja syntax.

The components in this template are:

### Bootstrap Libraries
Includes links to Bootstrap CSS and JavaScript libraries from the official CDN. These libraries help in styling and adding interactive elements to the web application.

### Favicon
The favicon (website icon) is linked using the <link> tag. It's displayed in the browser's tab and bookmark bar.

### JavaScript Function
There's one JavaScript function named copyPassword(s) that allows users to copy the password (or username) to the clipboard when clicking on the "Copy" button.

### Navigation Bar
A Bootstrap navigation bar is included. It has the links to various parts of the app such as generating passwords, registering, logging in, and logging out. 
These navigation links depend on whether the user is logged in or not.

### Flashed Messages
If there are any flashed messages (error or success messages), they are displayed in a Bootstrap alert at the top of the web page.

### Dynamic Content
The {% block title %}{% endblock %} and {% block main %}{% endblock %} tags provide placeholders for dynamic content to be filled in by the specific pages that extend this template. This is where the actual content of each page will be placed.

## templates/register.html
This template provides the structure and components for the registration page. When a user accesses this page, they will see the registration form with the specified fields and validation rules. The layout, navigation bar, and other elements are extended from the layout.html template using Jinja templating.

## templates/login.html
Similar to the register template, the user will see the login form with the specified fields for username and password, which will be checked in "app.py" using the check_password_hash() function from the werkzeug.security module. The layout, navigation bar, and other elements are also extended from the layout.html template using Jinja templating.

## templates/generate.html
This template has the structure for the generate password page of my web application. When the user access this page, they will see the form with input fields for specifying the account and email associated with the password they want to generate. The layout navigation bar, and other elements are also extended from the layout.html template using Jinja templating.

## templates/generated.html
After the user submits the form in "generate.html" they will be redirected to this page, which contains the generated password displayed and have the option to save it in the table or cancel.

## templates/index.html
This is the home page for my web application. It displays a summary of all saved passwords, so that the users can view and manage them. As with all other templates, it extends "layout.html" using Jinja templating, and shows the saved passwords displayed in a table with columns for the account name, associated email or username and password (email/username and password are hidden in a modal), and delete options.

Each username or password is displayed in a modal when the "View" button is clicked. Users can copy the username or password to the clipboard using the "Copy Password" button within the modal.

For each password, a "Delete" button is provided to delete the password and associated account.

At the bottom of the table, there's an option to delete all passwords associated with the user's account.

## static/icon.png
This is the favicon displayed in the browser's tab and bookmark bar.

## Usage Instructions
If you want to set up and run this application you can dowload (or clone) this repository. Install the dependencies listed in "requirements.txt". 
Run it by going into the directory and using the following command to start the Flask development server:

    flask run

To access the application go to your browser and type http://127.0.0.1:5000/

Then you can register and log in, generate new passwords, save and manage them.