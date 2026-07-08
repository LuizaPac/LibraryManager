# Tests

## Overview

The project starts CI with Python-to-database tests. These tests validate direct
Python database calls first, because the C++ layer will later call these Python
functions.

Future C++ method tests should reuse the same database setup strategy: create a
temporary database, point the code to it, run the method, and assert the database
or returned values.

## File Organization

- `.github/workflows/ci.yml`: GitHub Actions workflow. It runs on pushes and
  pull requests to `main`, across Ubuntu runners and Python versions.
- `requirements.txt`: Python dependencies needed to run the tests.
- `tests/`: pytest test suite.
- `tests/test_database_setup.py`: verifies that a database can be created from
  `schema.sql` and `standard_data.sql`.
- `tests/test_author_repository.py`: verifies direct Python database calls in
  `AuthorRepository`.
- `scripts/create_database.py`: helper used by tests and CI to create isolated
  SQLite databases.

## Current CI Matrix

The workflow tests on:

- `ubuntu-latest`
- `ubuntu-22.04`
- Python `3.11`, `3.12`, `3.13`, `3.14`, `3.15`, and `3.16-dev`

`3.16-dev` is used for the development version. If it becomes a stable release,
the workflow can be changed to `3.16`.

## Running Tests Locally

Install dependencies:

```bash
python -m pip install -r requirements.txt
```

Run syntax checks:

```bash
python -m py_compile pythonFunctions/*.py scripts/*.py
```

Run tests:

```bash
PYTHONPATH=pythonFunctions:. pytest
```

## Good Practices

- Keep tests isolated from `library.db`; use temporary databases.
- Use `LIBRARY_DB_PATH` when testing code that calls `pythonFunctions/db.py`.
- Test behavior, not implementation details.
- Add a test for each new repository method before connecting it to C++.
- Keep CI fast; split slow C++ or integration tests into separate jobs later.
- Do not commit generated files such as `library.db`, `__pycache__`, or build
  directories.
