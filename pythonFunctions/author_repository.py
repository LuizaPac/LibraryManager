from db import connect


class AuthorRepository:
    def __init__(self):
        pass

    def create(self, name):
        with connect() as conn:
            cursor = conn.execute(
                "INSERT INTO author (name) VALUES (?)",
                (name,),
            )
            return cursor.lastrowid

    def get_by_id(self, author_id):
        with connect() as conn:
            row = conn.execute(
                "SELECT id, name FROM author WHERE id = ?",
                (author_id,),
            ).fetchone()
            return tuple(row) if row else None

    def search_by_name(self, name):
        with connect() as conn:
            rows = conn.execute(
                """
                SELECT id, name
                FROM author
                WHERE name LIKE ?
                ORDER BY name
                """,
                (f"%{name}%",),
            ).fetchall()
            return [tuple(row) for row in rows]
