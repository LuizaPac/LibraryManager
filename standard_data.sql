PRAGMA foreign_keys = ON;

BEGIN TRANSACTION;

INSERT OR IGNORE INTO book_genre (id, genre) VALUES
    (1, 'Fiction'),
    (2, 'Non-fiction'),
    (3, 'Fantasy'),
    (4, 'Science Fiction'),
    (5, 'Biography'),
    (6, 'History'),
    (7, 'Romance'),
    (8, 'Mystery'),
    (9, 'Horror'),
    (10, 'Poetry');

COMMIT;
