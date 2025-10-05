class Employee:
def init(self, name, salary):
self.name = name
self.salary = salary
def calculateBonus(self):
return 0

class Manager(Employee):
def calculateBonus(self):
return self.salary * 0.2
def hire(self):
print(self.name, "is hiring")

class Developer(Employee):
def calculateBonus(self):
return self.salary * 0.1
def writeCode(self):
print(self.name, "is writing code")

class SeniorManager(Manager):
def calculateBonus(self):
return self.salary * 0.3

m = Manager("Ali", 5000)
d = Developer("Sara", 4000)
sm = SeniorManager("Hassan", 8000)
print("Manager Bonus:", m.calculateBonus())
m.hire()
print("Developer Bonus:", d.calculateBonus())
d.writeCode()
print("Senior Manager Bonus:", sm.calculateBonus())
