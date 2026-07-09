from db import connect


class LendingRepository:
    TABLE_NAME = "lending"

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

    def create(self, reader_id, book_id, lending_date, expected_return_date):
        with connect(self.db_path) as conn:
            cursor = conn.execute(
                f"""
                INSERT INTO {self.TABLE_NAME} (
                    reader_id,
                    book_id,
                    lending_date,
                    expected_return_date
                )
                VALUES (?, ?, ?, ?)
                """,
                (reader_id, book_id, lending_date, expected_return_date),
            )
            return cursor.lastrowid

    def get_all(self):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT
                    id,
                    reader_id,
                    book_id,
                    lending_date,
                    expected_return_date,
                    return_date
                FROM {self.TABLE_NAME}
                ORDER BY id
                """
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_by_id(self, lending_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT
                    id,
                    reader_id,
                    book_id,
                    lending_date,
                    expected_return_date,
                    return_date
                FROM {self.TABLE_NAME}
                WHERE id = ?
                """,
                (lending_id,),
            ).fetchone()
            return tuple(row) if row else None

    def get_active(self):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT
                    id,
                    reader_id,
                    book_id,
                    lending_date,
                    expected_return_date,
                    return_date
                FROM {self.TABLE_NAME}
                WHERE return_date IS NULL
                ORDER BY id
                """
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_active_by_book_id(self, book_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT
                    id,
                    reader_id,
                    book_id,
                    lending_date,
                    expected_return_date,
                    return_date
                FROM {self.TABLE_NAME}
                WHERE book_id = ?
                  AND return_date IS NULL
                """,
                (book_id,),
            ).fetchone()
            return tuple(row) if row else None

    def check_in_book(self, book_id, return_date):
        with connect(self.db_path) as conn:
            cursor = conn.execute(
                f"""
                UPDATE {self.TABLE_NAME}
                SET return_date = ?
                WHERE book_id = ?
                  AND return_date IS NULL
                """,
                (return_date, book_id),
            )
            return cursor.rowcount > 0
