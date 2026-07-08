import sqlite3

def loadUsers(dbPath):
    # Connect to the database
    conn = sqlite3.connect(dbPath)
    cursor = conn.cursor()

    # Execute the query and save all results
    try:
        cursor.execute("SELECT id, name, document, dateOfBirth, telephone FROM user")
        data = cursor.fetchall()
    except sqlite3.OperationalError:
        # Se a tabela não existir, avisa no console e devolve uma lista vazia
        print("[Python] WARNING: Empty DB.")
        data = []

    # Close the connection
    conn.close()
    return data

def loadBooks(dbPath):
    # Connect to the database
    conn = sqlite3.connect(dbPath)
    cursor = conn.cursor()

    # Execute the query and save all results
    try:
        cursor.execute("SELECT id, title, releaseDate, author, genre FROM books")
        data = cursor.fetchall()
    except sqlite3.OperationalError:
        # Se a tabela não existir, avisa no console e devolve uma lista vazia
        print("[Python] WARNING: Empty DB.")
        data = []

    # Close the connection
    conn.close()
    return data

def loadActiveLoans(dbPath):
    # Connect to the database
    conn = sqlite3.connect(dbPath)
    cursor = conn.cursor()

    # Execute the query and save all results
    try:
        cursor.execute("SELECT id, idUser, idBook, checkOutDate FROM checkedOutBooks WHERE checkInDate IS NULL")
        data = cursor.fetchall()
    except sqlite3.OperationalError:
        # Se a tabela não existir, avisa no console e devolve uma lista vazia
        print("[Python] WARNING: Empty DB.")
        data = []

    # Close the connection
    conn.close()
    return data

