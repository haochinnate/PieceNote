# coding style: PEP 8

# class naming should use CamelCase
class Point:
	pass
	
p1 = Point()
p2 = Point()
print(p1)
print(p2)

p1.x = 5.2
p1.y = 3
p1.z = 4

p2.x = 1
p2.y = 3
print(p1.x, p1.y, p1.z)
print(p2.x, p2.y, p2.z)

# class className:
class Point2:
	# def methodName(self):
	def reset(self): 
		self.x = 0
		self.y = 0
		
p = Point2()
p.reset
print(p.x, p.y)		


	
