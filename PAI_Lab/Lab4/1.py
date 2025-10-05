class Vehicle:
def init(self, capacity):
self.capacity = capacity
def fare(self):
return self.capacity * 100

class Bus(Vehicle):
def fare(self):
total = super().fare()
return total + (0.1 * total)

b = Bus(50)
print("Bus Fare:", b.fare())
