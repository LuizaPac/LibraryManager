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

INSERT OR IGNORE INTO accepted_document_type (id, document_type_name) VALUES
    (1, 'CPF'),
    (2, 'RG'),
    (3, 'Passport'),
    (4, 'Driver License');

COMMIT;
