try:
    list1 = input("Enter first list (comma separated): ").split(",")
    list2 = input("Enter second list (comma separated): ").split(",")
    if len(list1) != len(list2):
        print("Lists must have same length")
    else:
        d = {}
    for i in range(len(list1)):
        d[list1[i]] = list2[i]
        f = open("dictfile.txt", "w")
        f.write(str(d))
    f.close()
    print("Dictionary saved")
except Exception as e:
print("Error:", e)
