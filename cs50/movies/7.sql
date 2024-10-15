SELECT title, rating
FROM movies, ratings
WHERE id = movie_id AND rating IS NOT NULL AND movie_id IN (
    SELECT id
    FROM movies
    WHERE year = 2010
)
ORDER BY rating DESC, title;
