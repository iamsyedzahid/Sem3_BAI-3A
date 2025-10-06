def fix_file():
    try:
        f = open("replacement_needed.txt", "r")
        data = f.read()
        f.close()
        wrong = input("Enter wrong letter: ")
        right = input("Enter right letter: ")
        newdata = ""
        for ch in data:
            if ch == wrong:
                newdata += right
            else:
                newdata += ch
        f = open("replacement_needed.txt", "w")
        f.write(newdata)
        f.close()
        print("File fixed")
    except Exception as e:
        print("Error:", e)

fix_file()
