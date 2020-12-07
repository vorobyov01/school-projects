import sqlite3

conn = sqlite3.connect('db.sqlite3')

cursor = conn.cursor()

cursor.execute("INSERT INTO comp VALUES (1, 'team1', 123)")
cursor.execute("INSERT INTO comp VALUES (2, 'team3', 123)")
conn.commit()
cursor.execute("SELECT * FROM comp")

result = cursor.fetchall()

print(result)

conn.close()