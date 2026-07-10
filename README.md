# Library Management System

## Project purpose

This project develops a library collection management system focused on managing users, books, loans, and returns. The system supports creating user accounts, listing user information, adding books to the collection, listing book information, lending books, returning books, and checking whether a book is available or currently borrowed.

The C++ frontend handles user interaction and calls into Python functions. The Python backend interfaces with the SQLite database and updates persisted library data.

## Authors

- Rafael Gabriel
- Luiza Pacheco

## How to Run

### 1. Setup
On Ubuntu/Debian, run this once:

```bash
make system-deps
```

This installs the C++ compiler, SQLite CLI, Python venv support, and Python development headers required by pybind11.

If you are not on Ubuntu/Debian, install equivalent packages manually:

- `g++`
- `sqlite3`
- Python 3.12 development headers
- Python 3.12 venv support

```bash
make setup
```

This creates `.venv/` and installs `requirements.txt`, including `pytest` and `pybind11`.

### 2. Create the database

```bash
make data
```

To create the database with sample authors, books, readers, and lendings:

```bash
make sampledata
```

To delete the local database and SQLite sidecar files:

```bash
make rmdata
```

### 3. Run program

Build and run main program
```bash
make
make run
```

Run python (database connection) tests, cpp specific tests or all tests
```bash
make pytest
make ctest (not yet avaliable)
make tests
```


If you need to rebuild from scratch:
```bash
make clean
make
```

## Database Instructions

Create database with the project helper:

```bash
make data
```

Or create database manually with standard values:

```bash
sqlite3 library.db < schema.sql
sqlite3 library.db < standard_data.sql
sqlite3 library.db < sample_data.sql
```

Recreate a clean database with sample rows:

```bash
make rmdata
make sampledata
```

Edit database:

```bash
sqlite3 library.db
```

Exit database edit mode:
=======
```sql
sqlite3 library.db < schema.sql
sqlite3 library.db < standard_data.sql
```

Edit Database:

```sql
sqlite3 library.db
```

Exit Database edit mode:

```sql
.quit
```

