def check_vowels():
    word = input("Enter a : ")
    if word[-1] in "aeiouAEIOU":
        print("Last letter is a vowel.")
    else:
        print("Last letter is a consonant.")


check_vowels()