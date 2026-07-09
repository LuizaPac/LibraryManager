from db import connect


class UserRepository:
    TABLE_NAME = "reader"

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

    def create(
        self,
        first_name,
        last_name,
        phone_number,
        birthday,
        document,
    ):
        with connect(self.db_path) as conn:
            cursor = conn.execute(
                f"""
                INSERT INTO {self.TABLE_NAME} (
                    first_name,
                    last_name,
                    phone_number,
                    birthday,
                    document,
                )
                VALUES (?, ?, ?, ?, ?)
                """,
                (
                    first_name,
                    last_name,
                    phone_number,
                    birthday,
                    document,
                ),
            )
            return cursor.lastrowid

    def get_all(self):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT
                    id,
                    first_name,
                    last_name,
                    phone_number,
                    birthday,
                    document
                FROM {self.TABLE_NAME}
                ORDER BY first_name, last_name
                """
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_by_id(self, user_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT
                    id,
                    first_name,
                    last_name,
                    phone_number,
                    birthday,
                    document
                FROM {self.TABLE_NAME}
                WHERE id = ?
                """,
                (user_id,),
            ).fetchone()
            return tuple(row) if row else None

    def get_by_document(self, document):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT
                    id,
                    first_name,
                    last_name,
                    phone_number,
                    birthday,
                    document,
                FROM {self.TABLE_NAME}
                WHERE document = ?
                """,
                (document,),
            ).fetchone()
            return tuple(row) if row else None

    def search_by_name(self, name):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT
                    id,
                    first_name,
                    last_name,
                    phone_number,
                    birthday,
                    document
                FROM {self.TABLE_NAME}
                WHERE first_name LIKE ?
                   OR last_name LIKE ?
                   OR TRIM(first_name || ' ' || last_name) LIKE ?
                ORDER BY first_name, last_name
                """,
                (f"%{name}%", f"%{name}%", f"%{name}%"),
            ).fetchall()
            return [tuple(row) for row in rows]
