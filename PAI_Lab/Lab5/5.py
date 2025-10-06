try:
    d = {'Ali': 23,'Saad':24,'Salman':15,'Shams':25,'Sadiq':46,'Hammad':23}
    f = open("data.json", "w")
    f.write(str(d))
    f.close()
    f = open("data.json", "r")
    text = f.read()
    f.close()
    text = text.strip("{}")
    pairs = text.split(",")
    d2 = {}
    for p in pairs:
        k,v = p.split(":")
        k = k.strip().strip("'")
        v = int(v)
        d2[k] = v
        max_age = 0
    for v in d2.values():
        if v > max_age:
            max_age = v
            print("Maximum Age:", max_age)
    for k,v in d2.items():
        if v == max_age:
            print("Name:", k)
except Exception as e:
    print("Error:", e)
