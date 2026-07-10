# Library Management System

## Project purpose

This project develops a library collection management system focused on managing users, books, loans, and returns. The system supports creating user accounts, listing user information, adding books to the collection, listing book information, lending books, returning books, and checking whether a book is available or currently borrowed.

The C++ frontend handles user interaction and calls into Python functions. The Python backend interfaces with the SQLite database and updates persisted library data.

## Authors

- Rafael Gabriel
- Luiza Pacheco

## Database instructions

Create Database with standard values:

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

