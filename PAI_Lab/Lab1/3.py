num = input("Enter a 4-digit number: ")
swapped = num[3] + num[2] + num[1] + num[0]

encrypted = ""
for digit in swapped:
    new_digit = (int(digit) + 7) % 10
    encrypted += str(new_digit)

print("Encrypted Number:", encrypted)
