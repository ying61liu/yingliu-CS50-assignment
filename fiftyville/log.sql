-- check the crime_scene_reports table for what happened
/*  Two crimes were reported on 07/28/2024 on Humphrey Street: 1) theft of the CS50 duck at 10:15am; 2) littering at 16:36.
    Three witnesses all mentioned the bakery. (next is to check the interviews and bakery tables) */
SELECT *
FROM crime_scene_reports
WHERE   year = 2024
    AND month = 07
    AND day = 28
    AND street = 'Humphrey Street';

-- check the interviews table for what the three witnesses said;
/*  Ruth saw the suspet driving off the bakery parking lot within 10 mins of the theft (bakery_security_logs: query cars left in that time frame)
    Eugene saw the thief withdrawing some money at an ATM on Leggett Street earlier that morning (see the ATM transactions and bank_accounts tables)
    Raymond saw the thief calling someone when they were leaving for less than 1 min;
    he heard they planned to take the earliest flight out of Fiftyville tomorrow (see the phone_calls, airports, flights, passengers tables) */
SELECT *
FROM interviews
WHERE   year = 2024
    AND month = 07
    AND day = 28;

-- find the cars that left the bakery's parking lot on the day within 10 mins after the theft happened
SELECT license_plate
FROM bakery_security_logs
WHERE   year = 2024
    AND month = 07
    AND day = 28
    AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit';

-- find the person_id of the people who withdrew money at Legget Street on that day
SELECT person_id
FROM bank_accounts
WHERE account_number IN (
    SELECT account_number
    FROM atm_transactions
    WHERE   year = 2024
        AND month = 07
        AND day = 28
        AND atm_location = 'Leggett Street'
        AND transaction_type = ‘withdraw');


-- find the caller of the phone call
SELECT caller
FROM phone_calls
WHERE   year = 2024
    AND month = 07
    AND day = 28
    AND duration < 60;

-- find the passport number of people who would board the earliest flight the next day
SELECT passport_number
FROM passengers
WHERE flight_id = (
    SELECT f.id
    FROM flights AS f
    INNER JOIN airports AS a
    ON origin_airport_id = a.id
    WHERE   year = 2024
        AND month = 07
        AND day = 29
    ORDER BY hour
    LIMIT 1);


-- Combine all previeous queries to narrow down the search who left the bakery parking lot, withdrew money at a bank, booked the earlist flight tomorrow from Fiftyville, and made a phone call for less than a min.
/* The query returns one result, and the person is Bruce. He is the theft. */

SELECT name
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE   year = 2024
        AND month = 07
        AND day = 28
        AND hour = 10
        AND minute BETWEEN 15 AND 25
        AND activity = 'exit')
AND id IN (
    SELECT person_id
    FROM bank_accounts
    WHERE account_number IN (
        SELECT account_number
        FROM atm_transactions
        WHERE   year = 2024
            AND month = 07
            AND day = 28
            AND atm_location = 'Leggett Street'
            AND transaction_type = 'withdraw'))
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE   year = 2024
        AND month = 07
        AND day = 28
        AND duration < 60)
AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
        SELECT f.id
        FROM flights AS f
        INNER JOIN airports AS a
        ON origin_airport_id = a.id
        WHERE   year = 2024
            AND month = 07
            AND day = 29
        ORDER BY hour
        LIMIT 1));


-- find the accomplice based on the phone call records
/* The query returns one result, Robin. However, Robin did not book the flight for the next day. */
SELECT name
FROM people
WHERE phone_number IN (
        SELECT receiver
        FROM phone_calls
        WHERE   year = 2024
            AND month = 07
            AND day = 28
            AND duration < 60
            AND caller = (
                SELECT phone_number
                FROM people
                WHERE name = 'Bruce'
            ));



-- find the city the thief escaped to
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE id = (
        SELECT flight_id
        FROM passengers
        WHERE passport_number = (
            SELECT passport_number
            FROM people
            WHERE name = 'Bruce')));

