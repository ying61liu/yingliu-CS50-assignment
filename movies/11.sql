SELECT title
FROM movies
JOIN stars s ON movies.id = s.movie_id
JOIN people p ON s.person_id = p.id
JOIN ratings r ON movies.id = r.movie_id
WHERE name = 'Chadwick Boseman'
ORDER BY rating DESC
LIMIT 5;
