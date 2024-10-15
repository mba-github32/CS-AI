-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find crime scene description
SELECT description
FROM crime_scene_reports
WHERE street = 'Humphrey Street' AND year = 2023 AND month = 7 AND day = 28;

-- Find interviews transcript
SELECT transcript
FROM interviews
WHERE year = 2023 AND month = 7 AND day = 28;


--Find thief => Bruce
SELECT id, name
FROM people
WHERE phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    )
)
AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE activity = 'exit' AND year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25
)
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
    )
)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN (
        SELECT id
        FROM flights
        WHERE year = 2023 AND month = 7 AND day = 29 AND hour <=12
    )
);

-- FIND destination (knowing that Bruce(id:686048) was the theif from previous query)=> New York City
SELECT city
FROM airports
WHERE id IN (
    SELECT destination_airport_id
FROM flights
WHERE id IN (
    SELECT flight_id
    FROM passengers
    WHERE passport_number IN (
        SELECT passport_number
        FROM people
        WHERE id = 686048
    )
)
);

-- Find accomplice based on the calls with the theif
SELECT id, name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE year = 2023 AND month = 7 AND day = 28 AND duration <= 60
    AND caller IN (SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
);



