import sqlite3

from scripts.create_database import create_database


EXPECTED_TABLES = {
    "accepted_document_type",
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
        genre_count = conn.execute("SELECT COUNT(*) FROM book_genre").fetchone()[0]
        document_type_count = conn.execute(
            "SELECT COUNT(*) FROM accepted_document_type"
        ).fetchone()[0]

    assert EXPECTED_TABLES.issubset(tables)
    assert genre_count == 10
    assert document_type_count == 4
