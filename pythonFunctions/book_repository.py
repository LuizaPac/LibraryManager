from db import connect


class BookRepository:
    TABLE_NAME = "book"

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

    def create(self, title, release_date, author_id, genre_id):
        with connect(self.db_path) as conn:
            cursor = conn.execute(
                f"""
                INSERT INTO {self.TABLE_NAME} (title, release_date, author_id, genre_id)
                VALUES (?, ?, ?, ?)
                """,
                (title, release_date, author_id, genre_id),
            )
            conn.commit()
            return cursor.lastrowid

    def get_all(self):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, title, release_date, author_id, genre_id
                FROM {self.TABLE_NAME}
                ORDER BY title
                """
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_by_id(self, book_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT id, title, release_date, author_id, genre_id
                FROM {self.TABLE_NAME}
                WHERE id = ?
                """,
                (book_id,),
            ).fetchone()
            return tuple(row) if row else None

    def search_by_title(self, title):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, title, release_date, author_id, genre_id
                FROM {self.TABLE_NAME}
                WHERE title LIKE ?
                ORDER BY title
                """,
                (f"%{title}%",),
            ).fetchall()
            return [tuple(row) for row in rows]
