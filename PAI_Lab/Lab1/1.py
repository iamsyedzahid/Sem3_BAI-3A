num = int(input("Enter a number: "))
num_float = float(num)
num_str = str(num)
num_complex = complex(num)

print(f"Float: {num_float}, Type: {type(num_float)}")
print(f"String: {num_str}, Type: {type(num_str)}")
print(f"Complex: {num_complex}, Type: {type(num_complex)}")

if (num // 2) * 2 == num:
    print(f"{num} is divisible by 2")
else:
    print(f"{num} is NOT divisible by 2")
