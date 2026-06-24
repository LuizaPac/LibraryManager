import sqlite3

def createUser(dbName, name, document, dateBirth):
    # Connect to the database
    conn = sqlite3.connect(dbName)
    cursor = conn.cursor()

    # Create the user table if it doesnt exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS user (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            document TEXT NOT NULL,
            dateOfBirth TEXT NOT NULL
        )
    ''')

    # Put the new user into the database
    cursor.execute('''
        INSERT INTO user (name, document, dateOfBirth)
        values (?, ?, ?)
    ''', (name, document, dateBirth))

    # Get the new id (last one generated)
    userId = cursor.lastrowid

    # Save the changes and close the connection
    conn.commit()
    conn.close()

    return userId