
def is_palindrome(s):

    cleaned = s.lower()
    if cleaned == cleaned[::-1]:
        print("String is palindrome.")
    else:
        print("String is not a palindrome.")

is_palindrome("hell")