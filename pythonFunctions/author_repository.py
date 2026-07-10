from db import connect


class AuthorRepository:
    TABLE_NAME = "author"

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

    def create(self, name):
        with connect(self.db_path) as conn:
            cursor = conn.execute(
                f"INSERT INTO {self.TABLE_NAME} (name) VALUES (?)",
                (name,),
            )
            conn.commit()
            return cursor.lastrowid

    def get_by_id(self, author_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"SELECT id, name FROM {self.TABLE_NAME} WHERE id = ?",
                (author_id,),
            ).fetchone()
            return tuple(row) if row else None

    def find_by_name(self, name):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"SELECT id, name FROM {self.TABLE_NAME} WHERE name = ?",
                (name,),
            ).fetchone()
            return tuple(row) if row else None

    def get_or_create(self, name):
        author = self.find_by_name(name)
        if author is not None:
            return author

        author_id = self.create(name)
        return author_id, name

    def search_by_name(self, name):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, name
                FROM {self.TABLE_NAME}
                WHERE name LIKE ?
                ORDER BY name
                """,
                (f"%{name}%",),
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_all(self):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, name
                FROM {self.TABLE_NAME}
                ORDER BY name
                """,
            ).fetchall()
            return [tuple(row) for row in rows]
