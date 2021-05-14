import sqlite3

DATABASE_NAME = "temperture.sqlite"

def get_db():
    conn = sqlite3.connect(DATABASE_NAME)
    return conn

def create_tables():
    sql_query = """ CREATE TABLE IF NOT EXISTS readings(
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            reading REAL NOT NULL
        )
        """
    db = get_db()
    cursor = db.cursor()
    cursor.execute(sql_query)

def insert_device(name, reading):
    db = get_db()
    cursor = db.cursor()
    statement = "INSERT INTO readings(name, reading) VALUES (?, ?)"
    cursor.execute(statement, [name, reading])
    db.commit()
    return True

def update_device(id, name, reading):
    db = get_db()
    cursor = db.cursor()
    statement = "UPDATE readings SET name = ?, reading = ? WHERE id = ?"
    cursor.execute(statement, [name, reading, id])
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
    statement = "SELECT id, name, reading FROM readings WHERE id = ?"
    cursor.execute(statement, [id])
    return cursor.fetchone()

def get_devices():
    db = get_db()
    cursor = db.cursor()
    statement = "SELECT * FROM readings"
    cursor.execute(statement)
    return cursor.fetchall()
