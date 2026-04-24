SELECT DISTINCT name
FROM people p
JOIN stars s on p.id = s.person_id
JOIN movies m on s.movie_id = m.id
WHERE year = 2004
ORDER BY birth;


