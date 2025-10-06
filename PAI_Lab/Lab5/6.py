def write_question():
    try:
        s = input("Enter a sentence: ")
        if s.endswith("?"):
        f = open("questions.txt", "w")
        f.write(s)
        f.close()
        print("Question saved")
    except Exception as e:
        print("Error:", e)

write_question()
