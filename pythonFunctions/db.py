import sqlite3
from pathlib import Path


DB_PATH = Path(__file__).resolve().parent.parent / "library.db"


def connect():
    conn = sqlite3.connect(DB_PATH)
    conn.row_factory = sqlite3.Row
    conn.execute("PRAGMA foreign_keys = ON")
    return conn
