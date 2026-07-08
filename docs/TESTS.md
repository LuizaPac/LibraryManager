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
- `scripts/create_database.py`: helper used by tests and CI to create isolated
  SQLite databases.
- `tests/python_db/`: pytest tests for direct Python-to-SQLite behavior. These
  tests cover database creation and repository classes such as
  `AuthorRepository`.
- `tests/cpp/`: future pure C++ unit tests. Use this for C++ classes and methods
  that do not need Python or SQLite.
- `tests/integration/`: future cross-boundary tests. Use this when C++ calls
  Python and Python talks to SQLite.

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

Run the current Python database tests:

```bash
PYTHONPATH=pythonFunctions:. pytest tests/python_db
```

## Future Test Jobs

The current CI job only runs `tests/python_db`. When C++ tests are added, split
CI into separate jobs:

- `python-db-tests`: direct Python repository/database tests.
- `cpp-unit-tests`: pure C++ unit tests.
- `integration-tests`: C++ to Python to SQLite tests.

Keeping these jobs separate makes failures easier to diagnose and avoids making
fast database tests wait for slower integration checks.

## Good Practices

- Keep tests isolated from `library.db`; use temporary databases.
- Use `LIBRARY_DB_PATH` when testing code that calls `pythonFunctions/db.py`.
- Test behavior, not implementation details.
- Add a test for each new repository method before connecting it to C++.
- Put pure C++ tests in `tests/cpp/` and cross-language tests in
  `tests/integration/`.
- Keep CI fast; split slow C++ or integration tests into separate jobs later.
- Do not commit generated files such as `library.db`, `__pycache__`, or build
  directories.
