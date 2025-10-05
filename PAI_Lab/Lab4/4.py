class Student:
def init(self, sid, name):
self.sid = sid
self.name = name
def display(self):
print("ID: ", self.sid, "Name:", self.name)

class Marks(Student):
def init(self, sid, name, algo, ds, calc):
super().init(sid, name)
self.algo = algo
self.ds = ds
self.calc = calc
def displayMarks(self):
print("Algo: ", self.algo, "DS:", self.ds, "Calc:", self.calc)

class Result(Marks):
def init(self, sid, name, algo, ds, calc):
super().init(sid, name, algo, ds, calc)
def showResult(self):
total = self.algo + self.ds + self.calc
avg = total / 3
print("Total: ", total, "Average:", avg)

r = Result(1, "Ali", 80, 90, 85)
r.display()
r.displayMarks()
r.showResult()
