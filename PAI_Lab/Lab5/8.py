try:
    a = int(input("Enter first number: "))
    b = int(input("Enter second number: "))
    print("Result:", a/b)
    except ZeroDivisionError:
        print("Cannot divide by zero")
    except ValueError:
        print("Invalid input")
    except Exception as e:
        print("Error:", e)
