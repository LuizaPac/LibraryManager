from db import connect


class BookGenreRepository:
    TABLE_NAME = "book_genre"

    def __init__(self, db_path=None):
        self.db_path = db_path
        self._check_table_exists()

    def _check_table_exists(self):
        with connect(self.db_path) as conn:
            row = conn.execute(
                """
                SELECT name
                FROM sqlite_master
                WHERE type = 'table'
                  AND name = ?
                """,
                (self.TABLE_NAME,),
            ).fetchone()

            if row is None:
                raise RuntimeError(
                    f"Table '{self.TABLE_NAME}' does not exist. "
                    "Run scripts/create_database.py first."
                )

    def get_all(self):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, genre
                FROM {self.TABLE_NAME}
                ORDER BY genre
                """
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_by_id(self, genre_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT id, genre
                FROM {self.TABLE_NAME}
                WHERE id = ?
                """,
                (genre_id,),
            ).fetchone()
            return tuple(row) if row else None

    def search_by_name(self, name):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, genre
                FROM {self.TABLE_NAME}
                WHERE genre LIKE ?
                ORDER BY genre
                """,
                (f"%{name}%",),
            ).fetchall()
            return [tuple(row) for row in rows]
