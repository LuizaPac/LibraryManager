from scripts.create_database import create_database


def test_user_repository_create_get_and_search(tmp_path, monkeypatch):
    db_path = create_database(tmp_path / "library_test.db", reset=True)
    monkeypatch.setenv("LIBRARY_DB_PATH", str(db_path))

    from user_repository import UserRepository

    repository = UserRepository()
    user_id = repository.create(
        "Maria",
        "Silva",
        "21999999999",
        "1990-05-20",
        1,
        "12345678900",
    )

    expected = (
        user_id,
        "Maria",
        "Silva",
        "21999999999",
        "1990-05-20",
        1,
        "12345678900",
    )
    assert repository.get_by_id(user_id) == expected
    assert repository.get_by_document("12345678900") == expected
    assert repository.search_by_name("Maria") == [expected]
    assert repository.search_by_name("Maria Silva") == [expected]
    assert repository.get_all() == [expected]
