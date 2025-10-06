try:
    f = open("file2.txt", "r")
    data = f.read()
    f.close()
    old = input("Enter word to replace: ")
    new = input("Enter new word: ")
    data = data.replace(old, new)
    f = open("file2.txt", "w")
    f.write(data)
    f.close()
    print("Replacement Done")
except Exception as e:
    print("Error:", e)
