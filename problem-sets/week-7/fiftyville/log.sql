-- Keep a log of any SQL queries you execute as you solve the mystery.
-- List of suspects:

-- Thief:
-- name   | license_plate |  phone_number  | passport_number
-- Diana   | 322W7JE       | (770) 555-1861 | **
-- Bruce   | 94KL13X       | (367) 555-5533 | **

-- Accomplices:            | passport_number
-- Philip | (725) 555-3243 | 3391710505
-- Robin | (375) 555-8161 | ?

-- Get list of all tables in database
.tables

-- Look how crime_scene reports table was created
.schema crime_scene_reports

-- Get description of crimes on the street and day of crime
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND year = 2021 AND street = "Humphrey Street";

-- The description mentions three witnesses that were present and interviewed
-- all of them mentioned the Humphrey Street bakery, where it happened. Crime occurred at 10.15am

-- See how the table interviews was created
.schema interviews

-- Find mentions of the Humphrey Street bakery in interviews on the day of crime
SELECT transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2021
AND transcript LIKE "%bakery%";

-- First witness said he saw the thief get in a car in the bakery parking lot and drive within ten minutes of the theft,
-- check for security footage from the bakery parking lot in that time frame (10.15am to 10.25am)

-- Check how bakery_security_logs table was created and get that info from it
.schema bakery_security_logs
SELECT *
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND year = 2021
AND activity != "entrance"
AND hour = 10
AND minute >= 15
AND minute <= 25;

-- License plates of cars exiting within that time frame:
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- Search for owners of those cars
-- See how table people was created and get that info
.schema people
SELECT name, license_plate, phone_number
FROM people
WHERE
license_plate IN ("5P2BI95", "94KL13X", "6P58WS2", "4328GD8", "G412CB7", "L93JTIZ", "322W7JE", "0NTHK55");

-- Second witness recognised thief, saw him earlier on the day at an ATM on Legget Street withdrawing money.
-- Check table that might contain this info, get the names of people that made the transactions
.schema atm_transactions
.schema bank_accounts
SELECT people.name, people.phone_number, people.license_plate
FROM atm_transactions
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE
atm_location = "Leggett Street"
AND day = 28
AND month = 7
AND year = 2021
AND transaction_type = "withdraw";
-- The names Iman, Luca, Diana, Bruce, match both the list of people that left the car park and the list of people that withdrew money on that day

-- Third witness said thief called someone for less than a minute after leaving the bakery. They asked the accomplice to buy the earliest flight ticket out of Fiftyville
-- on the next day.

-- Search for that info
.schema phone_calls
SELECT people.name, caller, receiver, duration
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.receiver
WHERE
day = 28
AND month = 7
AND year = 2021
AND duration < 60;

-- Diana and Bruce's phone number matches those on the info
-- Get the info for those that received the call, Philip and Robin
-- Philip | (725) 555-3243
-- Robin | (375) 555-8161

SELECT name, passport_number, phone_number
FROM people
WHERE
phone_number IN ("(725) 555-3243", "(375) 555-8161");
-- Only found the passport_number info for Philip; 3391710505

-- Search for earliest flight leaving Fiftyville on 29.7.2021
.schema airports
.schema flights
SELECT
full_name, flights.id, flights.destination_airport_id, month, year, day, hour, minute
FROM airports
JOIN flights ON airports.id = flights.origin_airport_id
WHERE
day = 29
AND month = 7
AND year = 2021
AND city = "Fiftyville"
ORDER BY
hour, minute
LIMIT 1;

-- Found that the first flight is (ID: 36) going to the airport_id "4"
SELECT *
FROM airports
WHERE id = 4;
-- "LaGuardia Airport", "New York City" This is where they flew to.

-- Get passport_number of the remaining suspects
-- name   | license_plate |  phone_number  | passport_number
-- Diana   | 322W7JE       | (770) 555-1861 | 3592750733
-- Bruce   | 94KL13X       | (367) 555-5533 | 5773159633 ***
SELECT
name, passport_number
FROM people
WHERE phone_number IN ("(770) 555-1861", "(367) 555-5533");

-- Match info already stored for passport numbers of all suspects in flight 36
SELECT passport_number, seat
FROM passengers
JOIN flights ON passengers.flight_id = flights.id
WHERE
flights.id = 36
AND passport_number IN (3592750733, 5773159633, 3391710505);

-- Only Bruce was in that flight, passport: 5773159633, seat 4A.
-- Review information to whom Bruce called after the theft:
SELECT people.name
FROM phone_calls
JOIN people ON people.phone_number = phone_calls.receiver
WHERE
day = 28
AND month = 7
AND year = 2021
AND duration < 60
AND phone_calls.caller = "(367) 555-5533";

-- Robin was the accomplice
-- Bruce was the thief
-- Robin bought his ticket to New York City arriving at the LaGuardia Airport