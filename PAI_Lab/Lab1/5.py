name = input("Enter your name: ")
year = input("Enter your birth year: ")

part1 = name[:3]
part1 = part1[0].upper() + part1[1:].lower()
part2 = year[-2:]

symbols = "@#%&*"
first_letter_ascii = ord(name[0])
symbol = symbols[first_letter_ascii % len(symbols)]

password = part1 + part2 + symbol
print("Generated Password:", password)
