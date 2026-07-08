#!/usr/bin/env python3
import argparse
import sqlite3
from pathlib import Path


PROJECT_ROOT = Path(__file__).resolve().parent.parent
DEFAULT_DB_PATH = PROJECT_ROOT / "library.db"
SCHEMA_PATH = PROJECT_ROOT / "schema.sql"
STANDARD_DATA_PATH = PROJECT_ROOT / "standard_data.sql"


def parse_args():
    parser = argparse.ArgumentParser(
        description="Create the LibraryManager SQLite database."
    )
    parser.add_argument(
        "db_path",
        nargs="?",
        default=DEFAULT_DB_PATH,
        type=Path,
        help="Database file to create. Defaults to project-root library.db.",
    )
    parser.add_argument(
        "--reset",
        action="store_true",
        help="Delete the target database before creating it.",
    )
    return parser.parse_args()


def execute_sql_file(conn, sql_path):
    conn.executescript(sql_path.read_text(encoding="utf-8"))


def create_database(db_path, reset=False):
    db_path = db_path.expanduser().resolve()

    if reset and db_path.exists():
        db_path.unlink()

    db_path.parent.mkdir(parents=True, exist_ok=True)

    with sqlite3.connect(db_path) as conn:
        conn.execute("PRAGMA foreign_keys = ON")
        execute_sql_file(conn, SCHEMA_PATH)
        execute_sql_file(conn, STANDARD_DATA_PATH)

    return db_path


def main():
    args = parse_args()
    db_path = create_database(args.db_path, reset=args.reset)
    print(f"Database ready: {db_path}")


if __name__ == "__main__":
    main()
