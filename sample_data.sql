PRAGMA foreign_keys = ON;

BEGIN TRANSACTION;

INSERT OR IGNORE INTO author (id, name) VALUES
    (1, 'Machado de Assis'),
    (2, 'Clarice Lispector'),
    (3, 'Jorge Amado');

INSERT OR IGNORE INTO book (id, title, release_date, author_id, genre_id) VALUES
    (1, 'Dom Casmurro', '1899/01/01', 1, 1),
    (2, 'Memorias Postumas de Bras Cubas', '1881/01/01', 1, 1),
    (3, 'A Hora da Estrela', '1977/01/01', 2, 1),
    (4, 'Capitaes da Areia', '1937/01/01', 3, 1);

INSERT OR IGNORE INTO reader (
    id,
    first_name,
    last_name,
    email,
    phone_number,
    birthday,
    document
) VALUES
    (1, 'Ana', 'Silva', 'ana.silva@example.com', '21999990001', '1995/03/12', '12345678901'),
    (2, 'Bruno', 'Costa', 'bruno.costa@example.com', '21999990002', '1992/07/25', '12345678902'),
    (3, 'Carla', 'Mendes', 'carla.mendes@example.com', '21999990003', '1988/11/05', '12345678903'),
    (4, 'Diego', 'Almeida', 'diego.almeida@example.com', '21999990004', '2000/01/18', '12345678904'),
    (5, 'Elisa', 'Pereira', 'elisa.pereira@example.com', '21999990005', '1998/09/30', '12345678905');

INSERT OR IGNORE INTO lending (
    id,
    reader_id,
    book_id,
    lending_date,
    expected_return_date,
    return_date
) VALUES
    (1, 1, 1, '2026/07/01', '2026/07/15', '2026/07/10'),
    (2, 2, 2, '2026/07/05', '2026/07/19', NULL),
    (3, 3, 3, '2026/07/08', '2026/07/22', NULL);

COMMIT;
