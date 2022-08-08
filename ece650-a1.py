#!/usr/bin/env python3
import sys
import re

# YOUR CODE GOES HERE

# ------------------------------------------------------------
#   		Controller + Database
# ------------------------------------------------------------
class Controller (object):
	def __init__ (self):
		self.streets = []
		#self.allVertices = []
		
	def getStreets (self):
		return self.streets
		
	def setStreets (self, streets):
		self.streets = streets
	
	#def getAllVertices (self):
	#	return self.allVertices
	
	#def setAllVertices (self, allVertices):
	#	self.allVertices = allVertices
	
	
	def addStreet (self, street):
		if self.checkStreet(street.getName()) !=  None:
			raise Exception("Street with name '" + street.getName() + "' already exists")
			
		#for street2 in self.streets:
		#	if street.getCoordinates().nodeEquals(street.getCoordinates(), street2.getCoordinates()):
		#		raise Exception("A street with the same coordinates already exists (altough with a different name)")
			
		self.streets.append(street)
	
	def checkStreet (self, streetName):
		for street in self.streets:
			if street.getName().upper() == streetName.upper():
				return street
				
		return None
		
	def modifyStreet (self, newStreet):
		for i in range(len(self.streets)):
			if self.streets[i].getName().upper() == newStreet.getName().upper():
				self.streets[i] = newStreet
				return
				
		raise Exception("'mod' specified for a Street that does not exist")

	def removeStreet (self, delStreet):
		for i in range(len(self.streets)):
			if self.streets[i].getName().upper() == delStreet.upper():
				self.streets.pop(i)
				return
		
		raise Exception("'rm' specified for a Street that does not exist")

	def generateGraph (self):
		graph = generateVectorComplexGraph(self.streets)
		
		#self.allVertices = allVertices
		
		return str(graph)
	
	
	
# ------------------------------------------------------------
#   					Graph
# ------------------------------------------------------------
class Graph (object):
	def __init__ (self, vertices, edges):
		self.vertices = vertices
		self.edges = edges
	
	# ---------------------------------------------
	#              Graph Printer
	# ---------------------------------------------
	def __str__ (self):
		result = ''
		
		# Print Vertices
		result = result + "V " + str(len(self.vertices))
		
		# Print Edges
		result = result + "\nE {"
		for i in range(len(self.edges)):
			result = result + "<" + str(self.edges[i].getSrc()) + "," + str(self.edges[i].getDest()) + ">"
			
			if i != (len(self.edges) - 1):
				result = result + ","
			
		result = result + "}"
		
		return result
		
		
	def getVertices (self):
		return self.vertices
		
	def getEdges (self):
		return self.edges
	
	
	
class Street (object):
	def __init__ (self, name, co_ord):
		self.name = name
		self.co_ord = co_ord
		
	def __str__ (self):
		return self.name + " - " + str(self.co_ord)
	
	def streetEquals (self, street1, street2):
		if street1 == None  and  street2 == None:
			return True
		elif street1 == None  or  street2 == None:
			return False
		
		street1Co_ord = street1.getCoordinates()
		street2Co_ord = street1.getCoordinates()
		
		return (street1.getName().upper() == street2.getName().upper()   and   street1Co_ord.nodeEquals(street1Co_ord, street2Co_ord))
	
		
	def getName (self):
		return self.name
		
	def getCoordinates (self):
		return self.co_ord
	
	
	
class Node (object) :
	def __init__ (self, x, y, prev, next):
		self.x = x
		self.y = y
		self.prev = prev
		self.next = next
		
	def __str__ (self):
		result = ''
		node = self;
		
		while node != None:
			result = result + "(" + str(node.getX()) + "," + str(node.getY()) + ") "
			node = node.getNext()
			
		return result
		
	def nodeEquals (self, node1, node2):
		if node1 == None  and  node2 == None:
			return True
		elif node1 == None  or  node2 == None:
			return False
		
		return (node1.getX() == node2.getX()  and  node1.getY() == node2.getY()  and  self.nodeEquals(node1.getNext(), node2.getNext()))
		
	def getCoordinates (self):
		return self
		
	def getX (self):
		return self.x
		
	def getY (self):
		return self.y
		
	def setPrev (self, prev):
		self.prev = prev
	
	def getPrev (self):
		return self.prev
		
	def setNext (self, next):
		self.next = next
		
	def getNext (self):
		return self.next



class Vertex (object):
	def __init__ (self, name, x, y):
		self.name = name
		self.x = x
		self.y = y
		
	def getName (self):
		return self.name
	
	def getX (self):
		return self.x
		
	def getY (self):
		return self.y
		
	
	
class Edge (object) :
	def __init__ (self, src, dest):
		self.src = src
		self.dest = dest
		
	def getSrc (self):
		return self.src
		
	def getDest (self):
		return self.dest



# ---------------------------------------------
#              Graph Generator
# ---------------------------------------------
def generateVectorComplexGraph (latestStreets):
	latestVertices = []
	latestEdges = []
	
	intersections = []
	
	v_no = 0
	
	# Last vertex number used
	#if len(prevVertices) != 0:
	#	v_no = int(prevVertices[-1].getName())
	#else:
	#	v_no = 0
	
	# Finding Intersections and Vertices
	for street1 in latestStreets:
		node1 = street1.getCoordinates()
		
		while node1.getNext() != None  and  node1 != None:
			for street2 in latestStreets:
				if street1.streetEquals(street1, street2):
					continue
				
				node2 = street2.getCoordinates()
				
				while node2.getNext() != None  and  node2 != None:
					if node1.nodeEquals(node1, node2):
						node2 = node2.getNext()
						continue
					
					int_x, int_y = intersectionBetween (node1, node1.getNext(), node2, node2.getNext())
					
					if int_x == None or int_y == None:
						node2 = node2.getNext()
						continue
						
					
					intNode1 = Node(int_x, int_y, node1, node1.getNext())
					intNode2 = Node(int_x, int_y, node2, node2.getNext())
					
					flag = False
					if not(intersectionsContain(intNode1, intersections)):
						intersections.append(intNode1)
						flag = True
						
					if not(intersectionsContain(intNode2, intersections)):
						intersections.append(intNode2)
						flag = True
					
					if flag == False:
						node2 = node2.getNext()
						continue
					
					
					# Vertices with potential new names
					pVer = [intersections[-1], node1, node1.getNext(), node2, node2.getNext()]
					
					# Check if vertices already exist, so that same name can be used again
					#vCheck = [ findInVertices(int_x, int_y, prevVertices), 
					#			findInVertices(node1.getX(), node1.getY(), prevVertices),
					#			findInVertices(node1.getNext().getX(), node1.getNext().getY(), prevVertices),
					#			findInVertices(node2.getX(), node2.getY(), prevVertices),
					#			findInVertices(node2.getNext().getX(), node2.getNext().getY(), prevVertices) ]
					
					for i in range(len(pVer)):
						#if (vCheck[i] == None):
						#	v_no = v_no + 1
						#	tempVertex = Vertex(str(v_no), pVer[i].getX(), pVer[i].getY())
							
						#	latestVertices.append(tempVertex)
						#	prevVertices.append(tempVertex)
							
						#elif not(verticesContain(pVer[i].getX(), pVer[i].getY(), latestVertices)):
						#	latestVertices.append(vCheck[i])
						
						if not(verticesContain(pVer[i].getX(), pVer[i].getY(), latestVertices)):
							v_no = v_no + 1
							tempVertex = Vertex(str(v_no), pVer[i].getX(), pVer[i].getY())
							
							latestVertices.append(tempVertex)
						
						
					node2 = node2.getNext()
				
			node1 = node1.getNext()
	
	for it in intersections:
		v_no = v_no + 1
		temp = Vertex(str(v_no), it.getX(), it.getY())
	
	
	for intersection in intersections:
		newEdges = findEdges(intersection, intersections, latestEdges, latestVertices)
		if newEdges != None  and  len(latestEdges) == 0:
			latestEdges = newEdges
	
	return Graph(latestVertices, latestEdges)



def findInVertices (x, y, vertices):
	for v in vertices:
		if v.getX() == x  and  v.getY() == y:
			return v
	
	return None
	
	
	
def verticesContain (x, y, vertices):
	for v in vertices:
		if v.getX() == x  and  v.getY() == y:
			return True
	
	return False
	
	
	
def intersectionsContain (ipNode, intersections):
	for i in intersections:
		if i.getX() == ipNode.getX()  and  i.getY() == ipNode.getY():
			if (i.getPrev().getX() == ipNode.getPrev().getX()  and  i.getPrev().getY() == ipNode.getPrev().getY())   and   (i.getNext().getX() == ipNode.getNext().getX()  and  i.getNext().getY() == ipNode.getNext().getY()):
				return True
			
			elif (i.getPrev().getX() == ipNode.getNext().getX()  and  i.getPrev().getY() == ipNode.getNext().getY())   and   (i.getNext().getX() == ipNode.getPrev().getX()  and  i.getNext().getY() == ipNode.getPrev().getY()):
				return True
	
	return False
	
	
	
def findEdges (ipNode, intersections, latestEdges, latestVertices):
	options = [ipNode.getPrev(), ipNode.getNext()]
	
	i = 0
	for option in options:
		if latestEdges == None:
			latestEdges = []
		
		x1 = option.getX()
		y1 = option.getY()
		x2 = ipNode.getX()
		y2 = ipNode.getY()
		
		flagMoreEdges = False
		for intNode in intersections:
			# Checking if the intNode lies on the line (i.e. if cross == 0  and  it lies between the points)
			x = intNode.getX()
			y = intNode.getY()
			
			dxc = x - x1
			dyc = y - y1
			
			dxl = x2 - x
			dyl = y2 - y
			
			cross = (dxc * dyl) - (dyc * dxl)
			
			if (round(cross, 3) == 0)    and    ((x >= min(x1, x2) and x <= max(x1, x2))  and  (y >= min(y1, y2) and y <= max(y1, y2)))     and     not((x == x1 and y == y1)  or  (x == x2 and y == y2)):
				temp = None
				if i == 0:
					temp = Node(x, y, option, ipNode)
				else:
					temp = Node(x, y, ipNode, option)
				
				newEdges = findEdges(temp, intersections, latestEdges, latestVertices)
				if newEdges != None  and  len(latestEdges) == 0:
					latestEdges = newEdges
				
				flagMoreEdges = True
				break
		
		if flagMoreEdges == False:
			if i == 0:
				latestEdges = addEdge(option, ipNode, latestEdges, latestVertices)
			elif i == 1:
				latestEdges = addEdge(ipNode, option, latestEdges, latestVertices)
				
		i = i + 1
	
	return latestEdges



def addEdge (node1, node2, latestEdges, latestVertices):
	if latestEdges == None:
		latestEdges = []
	
	node1Vertex = findInVertices (node1.getX(), node1.getY(), latestVertices)
	node1Name = None
	if (node1Vertex != None):
		node1VertexName = node1Vertex.getName()
	
	node2Vertex = findInVertices (node2.getX(), node2.getY(), latestVertices)
	node2VertexName = None
	if (node2Vertex != None):
		node2VertexName = node2Vertex.getName()
	
	
	if node1VertexName == node2VertexName:
		return latestEdges
	
	flagExists = False
	if len(latestEdges) != 0:
		for edge in latestEdges:
			if ((edge.getSrc() == node1VertexName  and  edge.getDest() == node2VertexName)   or   (edge.getSrc() == node2VertexName  and  edge.getDest() == node1Vertex)):
				flagExists = True
				break
	
	if flagExists == False:
		latestEdges.append( Edge(node1VertexName, node2VertexName) )
	
	return latestEdges



# Code to find the point of intersection between 2 lines - using their co-ordinates
def intersectionBetween (node1a, node1b, node2a, node2b):
		x1, y1 = node1a.getX(), node1a.getY()
		x2, y2 = node1b.getX(), node1b.getY()
		x3, y3 = node2a.getX(), node2a.getY()
		x4, y4 = node2b.getX(), node2b.getY()
		
		xNum = ((x1*y2 - y1*x2) * (x3 - x4))  -  ((x1 - x2) * (x3*y4 - y3*x4))
		xDen = ((x1 - x2) * (y3 - y4))  -  ((y1 - y2) * (x3 - x4))
		
		if xDen == 0:
			return None, None
		
		yNum = ((x1*y2 - y1*x2) * (y3 - y4))  - ((y1 - y2) * (x3*y4 - y3*x4))
		# yDen is same as xDen
		yDen = ((x1 - x2) * (y3 - y4))  -  ((y1 - y2) * (x3 - x4))
		
		x = xNum / xDen
		y = yNum / yDen
		
		#*********************************
		# Do not consider the intersection, when intersection point is equal to one of the end points
		# Usefull when comparing lines on the same street
		#if not((x >= min(x1, x2) and x <= max(x1, x2))  and  (y >= min(y1, y2) and y <= max(y1, y2))  and  (x >= min(x3, x4) and x <= max(x3, x4))  and  (y >= min(y3, y4) and  y <= max(y3, y4)))      or    (((x == x1 and y == y1) and (x == x3 and y == y3))  or  ((x == x1 and y == y1)  and  (x == x4 and y == y4))  or  ((x == x2 and y == y2) and (x == x3 and y == y3))  or  ((x == x2 and y == y2)  and  (x == x4 and y == y4))):
		#	return None, None
		
		# Consider the intersection, when intersection point is equal to one of the end points
		# Usefull when not comparing lines on the same street
		if not((x >= min(x1, x2) and x <= max(x1, x2))  and  (y >= min(y1, y2) and y <= max(y1, y2))  and  (x >= min(x3, x4) and x <= max(x3, x4))  and  (y >= min(y3, y4) and  y <= max(y3, y4))):
			return None, None
		#*************************************
		
		
		#x = round(x, 2)
		#y = round(y, 2)
		
		if abs(x) == 0:
			x = 0
		
		if abs(y) == 0:
			y = 0
		
		return x, y


# ------------------------------------------------------------
#                   Command Parser
# ------------------------------------------------------------
def lineParsing (line):
	filteredLine = line.strip()
	tempList1 = filteredLine.split('"')
	
	if '"(' in filteredLine:
		raise Exception('Command must be followed by street name in double quotes, which must then be followed by the coordinates - (delimited by space)')
	
	ipList = []
	for i in range(len(tempList1)):
		if i == 0:
			comStr = tempList1[i]
			if len(tempList1[i]) > 1  and  len(tempList1) > 1:
				comStr = comStr[:-1]
			
			ipList.append(comStr)
			
		elif i == 1:
			regExprStreet = "^[a-zA-Z ]*$"
			if not(re.match(regExprStreet, tempList1[i])):
				raise Exception("Street name can contain only - alphabetical characters and spaces.")
			
			if len(tempList1[i].replace(" ", "")) == 0:
				raise Exception("No street name has been provided.");
			
			ipList.append(tempList1[i])
		elif i == 2:
			if "((" in tempList1[i].replace(" ", "")  or  tempList1[i].replace(" ", "")[-1:] == "(":
				raise Exception("There is a mistake in one of the Vertices. Please provide vertices in the format '(a,b)' - (Delimited by spaces) - a.")
			
			t = tempList1[i].split(' (')
			t.pop(0)
			ipList.extend(t)
	
	if len(ipList) == 0:
		raise Exception('The input contains no arguments')
	
	cmd = ipList[0]
	
	tempStr = cmd.replace(" ", "")
	if (tempStr == 'gg' or tempStr == 'rm' or tempStr == 'add' or tempStr == 'mod')  and  (cmd != tempStr):
		cmd = ipList[0].split(" ")[0]
	
	streetName = None
	co_ord = None
	
	if cmd == 'gg':
		if len(ipList) != 1:
			raise Exception(cmd + ' can contain only one argument')
			
	elif (cmd == 'rm'):
		if filteredLine.count('"') != 2:
			raise Exception(cmd + ' must be followed by only street name in double quotes')
		elif len(ipList) != 2:
			raise Exception(cmd + ' must be followed by only street name in double quotes')
		
		streetName = ipList[1].replace('"', '')
		
	elif (cmd == 'add'  or  cmd == 'mod'):
		if len(ipList) < 3:
			raise Exception(cmd + ' must be followed by street name in double quotes, which must then be followed by the coordinates - (delimited by space)')
		elif filteredLine.count('"') != 2:
			raise Exception(cmd + ' must be followed by street name in double quotes, which must then be followed by the coordinates - (delimited by space)')
			
			
		streetName = ipList[1].replace('"', '')
		if streetName == '' :
			raise Exception('No street name has been provided. --> ' + cmd + ' must be followed street name in double quotes, which must then be followed by the coordinates - (delimited by space)')
		
		nodeList = []
		for ip in ipList:
			if ip != ipList[0]  and  ip != ipList[1]:
				reCheckSpaceCoord = "[0-9]+[ ]+[0-9]+";
				if re.search(reCheckSpaceCoord, ip):
					raise Exception("There is a mistake in one of the Vertices. Please provide vertices in the format '(a,b)' - (Delimited by spaces) - 0")
				
				if "- " in ip:
					raise Exception("There should be no spaces after '-' sign in coordinates")
				
				nTemporary = ip.replace(" ", "")
				if nTemporary != "":
					nodeList.append(nTemporary)
		
		if len(nodeList) < 2:
			raise Exception("A street must have 2 or more points in the format '(x,y)' - delimted by spaces.")
		
		head = None
		for ip in nodeList:
			if len(str(ip)) < 4:
				raise Exception("There is a mistake in one of the Vertices. Please provide vertices in the format '(a,b)' - (Delimited by spaces) - b")
			elif (str(ip)[-1] != ')'):
				raise Exception("There is a mistake in one of the Vertices. Please provide vertices in the format '(a,b)' - (Delimited by spaces) - c")
			
			c = []
			c = str(ip).replace('(', '').replace(')','').split(',')
			
			if(len(c) != 2):
				raise Exception("There is a mistake in one of the Vertices. Please provide vertices in the format '(a,b)' - (Delimited by spaces)...")
			elif (not c[0].replace('-', '').isnumeric())  or  (not c[1].replace('-', '').isnumeric()):
				raise Exception("Non-integer coordinates provided")
			
			re1 = "^[-]?[0-9]+[,][-]?[0-9]+\)$"
			if not(re.match(re1, ip)):
				raise Exception("There is a mistake in one of the Vertices. Please provide vertices in the format '(a,b)' - (Delimited by spaces) - d")
			
			if co_ord == None:
				co_ord = Node(int(c[0]), int(c[1]), None, None)
				head = co_ord
			else:
				temp = Node(int(c[0]), int(c[1]), co_ord, None)
				co_ord.setNext(temp)
				co_ord = temp
					
		co_ord = head
				
	else:
		raise Exception(cmd + " is an invalid command")
		
		
	return cmd, streetName, co_ord



# ------------------------------------------------------------
#                     	 Main
# ------------------------------------------------------------
def main():
	# YOUR MAIN CODE GOES HERE
	controller = Controller()
	
	# sample code to read from stdin.
	# make sure to remove all spurious print statements as required
	# by the assignment
	while True:
		try:
			line = sys.stdin.readline()
			
			if line == '':
				break
			
			cmd, streetName, co_ord = lineParsing(line)
			
			if cmd == 'add':
				street = Street(streetName, co_ord)
				controller.addStreet(street)
				
			elif cmd == 'mod':
				street = Street(streetName, co_ord)
				controller.modifyStreet(street)
				
			elif cmd == 'rm':
				controller.removeStreet(streetName)
				
			elif cmd == 'gg':
				print(controller.generateGraph(), file = sys.stdout, flush = True)
				
		except Exception as e:
			print("Error: " + str(e), file = sys.stderr, flush = True)

		except KeyboardInterrupt:
			break
			
	# return exit code 0 on successful termination
	sys.exit(0)


if __name__ == "__main__":
	main()
	
	