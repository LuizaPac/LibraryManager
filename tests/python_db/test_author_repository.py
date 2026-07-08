from scripts.create_database import create_database


def test_author_repository_create_get_and_search(tmp_path, monkeypatch):
    db_path = create_database(tmp_path / "library_test.db", reset=True)
    monkeypatch.setenv("LIBRARY_DB_PATH", str(db_path))

    from author_repository import AuthorRepository

    repository = AuthorRepository()
    author_id = repository.create("Machado de Assis")

    assert repository.get_by_id(author_id) == (author_id, "Machado de Assis")
    assert repository.search_by_name("Machado") == [(author_id, "Machado de Assis")]
