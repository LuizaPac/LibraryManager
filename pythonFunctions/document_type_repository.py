from db import connect


class DocumentTypeRepository:
    TABLE_NAME = "accepted_document_type"

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
                SELECT id, document_type_name
                FROM {self.TABLE_NAME}
                ORDER BY document_type_name
                """
            ).fetchall()
            return [tuple(row) for row in rows]

    def get_by_id(self, document_type_id):
        with connect(self.db_path) as conn:
            row = conn.execute(
                f"""
                SELECT id, document_type_name
                FROM {self.TABLE_NAME}
                WHERE id = ?
                """,
                (document_type_id,),
            ).fetchone()
            return tuple(row) if row else None

    def search_by_name(self, name):
        with connect(self.db_path) as conn:
            rows = conn.execute(
                f"""
                SELECT id, document_type_name
                FROM {self.TABLE_NAME}
                WHERE document_type_name LIKE ?
                ORDER BY document_type_name
                """,
                (f"%{name}%",),
            ).fetchall()
            return [tuple(row) for row in rows]
