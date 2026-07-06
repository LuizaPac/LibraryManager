import sqlite3

def createBook(dbName, title, releaseDate, author, gender):
    # Connect to the database
    conn = sqlite3.connect(dbName)
    cursor = conn.cursor()

    # Create the book table if it doesnt exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            releaseDate TEXT NOT NULL,
            author TEXT NOT NULL,
            genre TEXT NOT NULL 
        )
    ''')

    # Put the new book into the database
    cursor.execute('''
        INSERT INTO books (title, releaseDate, author, genre)
        values (?, ?, ?, ?)
    ''', (title, releaseDate, author, gender))

    # Get the new id (last one generated)
    bookId = cursor.lastrowid

    # Save the changes and close the connection
    conn.commit()
    conn.close()

    return bookId
