class VehicleRental:
def init(self, make, model, price):
self.make = make
self.model = model
self.__price = price
self.available = True
def checkAvailability(self):
return self.available
def rent(self):
self.available = False
def ret(self):
self.available = True
def cost(self, days):
return self.__price * days
def details(self):
print("Q5", self.make, self.model, "Price:", self.__price, "Available:", self.available)

class Car(VehicleRental):
pass

class SUV(VehicleRental):
pass

class Truck(VehicleRental):
pass

class Customer:
def init(self, name, contact):
self.name = name
self.__contact = contact
self.history = []
def addHistory(self, rental):
self.history.append(rental)
def showHistory(self):
print("Customer:", self.name)
for h in self.history:
h.details()

class RentalReservation:
def init(self, customer, vehicle, start, end):
self.customer = customer
self.vehicle = vehicle
self.start = start
self.end = end
vehicle.rent()
customer.addHistory(self)
def details(self):
print("Reservation:", self.customer.name, self.vehicle.make, self.vehicle.model, self.start, self.end)

c1 = Car("Toyota", "Corolla", 100)
cust = Customer("Ahmed", "12345")
res = RentalReservation(cust, c1, "1-Oct", "5-Oct")
res.details()
cust.showHistory()
