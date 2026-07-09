import os
import sqlite3
from pathlib import Path


DEFAULT_DB_PATH = Path(__file__).resolve().parent.parent / "library.db"


def get_db_path():
    return Path(os.environ.get("LIBRARY_DB_PATH", DEFAULT_DB_PATH))


def connect(db_path=None):
    db_path = Path(db_path) if db_path is not None else get_db_path()

    if not db_path.exists():
        raise FileNotFoundError(
            f"Database not found at {db_path}. Run scripts/create_database.py first."
        )

    conn = sqlite3.connect(db_path)
    conn.row_factory = sqlite3.Row
    conn.execute("PRAGMA foreign_keys = ON")
    return conn
