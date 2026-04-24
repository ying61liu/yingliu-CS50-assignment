SELECT AVG(rating)
FROM movies
INNER JOIN ratings
ON movies.id = movie_id
WHERE year = 2012;

