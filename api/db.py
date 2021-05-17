import sqlite3

DATABASE_NAME = "temperture.sqlite"

def get_db():
    conn = sqlite3.connect(DATABASE_NAME)
    return conn

def create_tables():
    sql_query = """ CREATE TABLE IF NOT EXISTS readings(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            location TEXT NOT NULL,
            reading REAL NOT NULL,
            isEmpty BOOL NOT NULL,
            timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
        """
    db = get_db()
    cursor = db.cursor()
    cursor.execute(sql_query)

def insert_device(location, reading, isEmpty):
    db = get_db()
    cursor = db.cursor()
    statement = "INSERT INTO readings(location, reading, isEmpty) VALUES (?, ?, ?)"
    cursor.execute(statement, [location, reading, isEmpty])
    db.commit()
    return True

def update_device(id, location, reading, isEmpty):
    db = get_db()
    cursor = db.cursor()
    statement = "UPDATE readings SET location = ?, reading = ?, isEmpty = ?, WHERE id = ?"
    cursor.execute(statement, [location, reading, isEmpty, id])
    db.commit()
    return True

def delete_device(id):
    db = get_db()
    cursor = db.cursor()
    statement = "DELETE FROM readings WHERE id = ?"
    cursor.execute(statement, [id])
    db.commit()
    return True

def get_by_id(id):
    db = get_db()
    cursor = db.cursor()
    statement = "SELECT id, location, reading, isEmpty, FROM readings WHERE id = ?"
    cursor.execute(statement, [id])
    return cursor.fetchone()

def get_devices():
    db = get_db()
    cursor = db.cursor()
    statement = "SELECT * FROM readings"
    cursor.execute(statement)
    return cursor.fetchall()
