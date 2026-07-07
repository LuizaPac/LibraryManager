import sqlite3
from datetime import date

def newLoan(dbName, idUser, idBook):
    # Connect to the database
    conn = sqlite3.connect(dbName)
    cursor = conn.cursor()

    # Create the user table if it doesnt exist
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS checkedOutBooks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            idUser INTEGER NOT NULL,
            idBook INTEGER NOT NULL,
            checkOutDate TEXT NOT NULL,
            checkInDate TEXT
        )
    ''')

    # Get today's date
    today = date.today().isoformat()

    # Put the new loan into the database
    cursor.execute('''
        INSERT INTO checkedOutBooks (idUser, idBook, checkOutDate)
        values (?, ?)
    ''', (idUser, idBook, today))

    # Get the new id (last one generated)
    loanId = cursor.lastrowid

    # Save the changes and close the connection
    conn.commit()
    conn.close()

    return loanId

def checkInBook(dbName, idBook):
    # Connect to the database
    conn = sqlite3.connect(dbName)
    cursor = conn.cursor()

    # Get today's date
    today = date.today().isoformat()

    # Update the loan register with the checkin datte
    cursor.execute('''
        UPDATE checkedOutBooks 
            SET checkInDate = ? 
            WHERE idBook = ? AND checkInDate IS NULL
    ''', (today, idBook))

    success = cursor.rowcount > 0

    conn.commit()
    conn.close()

    return success
