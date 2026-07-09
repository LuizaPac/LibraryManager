PRAGMA foreign_keys = ON;

BEGIN TRANSACTION;

CREATE TABLE IF NOT EXISTS author (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(50) NOT NULL
);

CREATE TABLE IF NOT EXISTS book_genre (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    genre VARCHAR(20) NOT NULL
);

CREATE TABLE IF NOT EXISTS reader (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    first_name VARCHAR(50) NOT NULL,
    last_name VARCHAR(50) NOT NULL,
    email VARCHAR(100) UNIQUE,
    phone_number VARCHAR(20),
    birthday DATE NOT NULL,
    document VARCHAR(20)
);

CREATE TABLE IF NOT EXISTS book (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title VARCHAR(100) NOT NULL,
    release_date DATE NOT NULL,
    author_id INTEGER NOT NULL,
    genre_id INTEGER NOT NULL,
    FOREIGN KEY (author_id)
        REFERENCES author (id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,
    FOREIGN KEY (genre_id)
        REFERENCES book_genre (id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

CREATE TABLE IF NOT EXISTS lending (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    reader_id INTEGER NOT NULL,
    book_id INTEGER NOT NULL,
    lending_date DATE NOT NULL,
    expected_return_date DATE NOT NULL,
    return_date DATE,
    FOREIGN KEY (reader_id)
        REFERENCES reader (id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT,
    FOREIGN KEY (book_id)
        REFERENCES book (id)
        ON UPDATE CASCADE
        ON DELETE RESTRICT
);

CREATE INDEX IF NOT EXISTS idx_book_author_id ON book (author_id);
CREATE INDEX IF NOT EXISTS idx_book_genre_id ON book (genre_id);
CREATE INDEX IF NOT EXISTS idx_lending_reader_id ON lending (reader_id);
CREATE INDEX IF NOT EXISTS idx_lending_book_id ON lending (book_id);

COMMIT;
