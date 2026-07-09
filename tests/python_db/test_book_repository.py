from scripts.create_database import create_database


def test_book_repository_create_get_and_search(tmp_path, monkeypatch):
    db_path = create_database(tmp_path / "library_test.db", reset=True)
    monkeypatch.setenv("LIBRARY_DB_PATH", str(db_path))

    from author_repository import AuthorRepository
    from book_repository import BookRepository

    author_repository = AuthorRepository()
    author_id = author_repository.create("Machado de Assis")

    repository = BookRepository()
    book_id = repository.create("Dom Casmurro", "1899-01-01", author_id, 1)

    expected = (book_id, "Dom Casmurro", "1899-01-01", author_id, 1)
    assert repository.get_by_id(book_id) == expected
    assert repository.search_by_title("Casmurro") == [expected]
    assert repository.get_all() == [expected]

