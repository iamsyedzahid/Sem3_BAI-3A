class Shape:
def area(self):
pass

class Rectangle(Shape):
def init(self, l, w):
self.l = l
self.w = w
def area(self):
return self.l * self.w

class Triangle(Shape):
def init(self, b, h):
self.b = b
self.h = h
def area(self):
return 0.5 * self.b * self.h

class Square(Shape):
def init(self, s):
self.s = s
def area(self):
return self.s * self.s

r = Rectangle(5, 3)
t = Triangle(4, 6)
s = Square(4)
print("Rectangle Area: ", r.area())
print("Triangle Area: ", t.area())
print("Square Area: ", s.area())
