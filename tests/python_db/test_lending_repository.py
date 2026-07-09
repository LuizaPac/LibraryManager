from scripts.create_database import create_database


def _create_reader_and_book(db_path):
    from author_repository import AuthorRepository
    from book_repository import BookRepository
    from user_repository import UserRepository

    user_repository = UserRepository(str(db_path))
    reader_id = user_repository.create(
        "Maria",
        "Silva",
        "21999999999",
        "1990-05-20",
        1,
        "12345678900",
    )

    author_repository = AuthorRepository(str(db_path))
    author_id = author_repository.create("Machado de Assis")

    book_repository = BookRepository(str(db_path))
    book_id = book_repository.create("Dom Casmurro", "1899-01-01", author_id, 1)

    return reader_id, book_id


def test_lending_repository_create_get_active_and_check_in(tmp_path, monkeypatch):
    db_path = create_database(tmp_path / "library_test.db", reset=True)
    monkeypatch.setenv("LIBRARY_DB_PATH", str(db_path))

    from lending_repository import LendingRepository

    reader_id, book_id = _create_reader_and_book(db_path)
    repository = LendingRepository()

    lending_id = repository.create(
        reader_id,
        book_id,
        "2026-07-09",
        "2026-07-23",
    )

    active_expected = (
        lending_id,
        reader_id,
        book_id,
        "2026-07-09",
        "2026-07-23",
        None,
    )
    assert repository.get_by_id(lending_id) == active_expected
    assert repository.get_active() == [active_expected]
    assert repository.get_active_by_book_id(book_id) == active_expected

    assert repository.check_in_book(book_id, "2026-07-10") is True
    assert repository.get_active() == []
    assert repository.get_by_id(lending_id) == (
        lending_id,
        reader_id,
        book_id,
        "2026-07-09",
        "2026-07-23",
        "2026-07-10",
    )
    assert repository.check_in_book(book_id, "2026-07-11") is False


def test_loan_functions_use_lending_repository(tmp_path):
    db_path = create_database(tmp_path / "library_test.db", reset=True)

    from lending_repository import LendingRepository
    from loanFunctions import checkInBook, newLoan

    reader_id, book_id = _create_reader_and_book(db_path)
    lending_id = newLoan(str(db_path), reader_id, book_id)

    repository = LendingRepository(str(db_path))
    lending = repository.get_by_id(lending_id)

    assert lending[1] == reader_id
    assert lending[2] == book_id
    assert lending[5] is None

    from loadData import loadActiveLoans

    assert loadActiveLoans(str(db_path)) == [
        (lending_id, reader_id, book_id, lending[3])
    ]

    assert checkInBook(str(db_path), book_id) is True
    assert repository.get_by_id(lending_id)[5] is not None
