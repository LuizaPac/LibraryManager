from scripts.create_database import create_database


def test_book_genre_repository_reads_standard_data(tmp_path, monkeypatch):
    db_path = create_database(tmp_path / "library_test.db", reset=True)
    monkeypatch.setenv("LIBRARY_DB_PATH", str(db_path))

    from book_genre_repository import BookGenreRepository

    repository = BookGenreRepository()

    assert repository.get_by_id(1) == (1, "Fiction")
    assert repository.search_by_name("Science") == [(4, "Science Fiction")]
    assert len(repository.get_all()) == 10