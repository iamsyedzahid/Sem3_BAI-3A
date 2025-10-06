try:
f = open("file1.txt", "r")
data = f.read()
f.close()
chars = len(data)
words = len(data.split())
print("Characters:", chars)
print("Words:", words)
except Exception as e:
print("Error:", e)
