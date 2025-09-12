def make_dictionary(list1, list2): 
    if not list1 or not list2: 
        print("List is empty.") 
        return {}
    else: 
        new_dict = {}
        for key, value in list(zip(list1, list2)):
            new_dict[key] = value
        return new_dict
 
 
list1 = [1, 2, 3] 
list2 = ["a", "b", "c"] 
result = make_dictionary(list1, list2)

with open("output.txt", "w") as file:
    file.write(str(result))

print(result)