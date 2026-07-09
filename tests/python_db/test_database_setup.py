import sqlite3

import pytest

from scripts.create_database import create_database


EXPECTED_TABLES = {
    "author",
    "book",
    "book_genre",
    "lending",
    "reader",
}


def test_create_database_builds_schema_and_standard_data(tmp_path):
    db_path = create_database(tmp_path / "library_test.db", reset=True)

    with sqlite3.connect(db_path) as conn:
        tables = {
            row[0]
            for row in conn.execute(
                "SELECT name FROM sqlite_master WHERE type = 'table'"
            )
        }
        book_columns = {
            row[1]
            for row in conn.execute("PRAGMA table_info(book)")
        }
        genre_count = conn.execute("SELECT COUNT(*) FROM book_genre"
                                   ).fetchone()[0]
        
    assert EXPECTED_TABLES.issubset(tables)
    assert "release_date" in book_columns
    assert genre_count == 10


def test_connect_raises_when_database_file_does_not_exist(tmp_path,
                                                          monkeypatch):
    missing_db_path = tmp_path / "missing.db"
    monkeypatch.setenv("LIBRARY_DB_PATH", str(missing_db_path))

    from db import connect

    with pytest.raises(FileNotFoundError, match="Database not found"):
        connect()

    assert not missing_db_path.exists()
