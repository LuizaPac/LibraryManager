import sqlite3

def loadUsers(dbPath):
    # Connect to the database
    conn = sqlite3.connect(dbPath)
    cursor = conn.cursor()

    # Execute the query and save all results
    cursor.execute("SELECT id, name, document, dateOfBirth FROM user")
    data = cursor.fetchall()

    # Close the connection
    conn.close()
    return data

def loadBooks(dbPath):
    # Connect to the database
    conn = sqlite3.connect(dbPath)
    cursor = conn.cursor()

    # Execute the query and save all results
    cursor.execute("SELECT id, title, releaseDate, author, genre FROM books")
    data = cursor.fetchall()

    # Close the connection
    conn.close()
    return data

def loadActiveLoans(dbPath):
    # Connect to the database
    conn = sqlite3.connect(dbPath)
    cursor = conn.cursor()

    # Execute the query and save all results
    cursor.execute("SELECT idUser, idBook FROM checkedOutBooks WHERE checkInDate IS NULL")
    data = cursor.fetchall()

    # Close the connection
    conn.close()
    return data

