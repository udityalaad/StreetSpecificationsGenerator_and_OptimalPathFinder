#!/usr/bin/env python3
# A simple unit test example. Replace by your own tests

import sys
import unittest
import importlib

# from ece650_a1 import *

class MyTest(unittest.TestCase):

    # New tests go here
	def test_lineParsing (self):
	
		line = 'add "Weber Street" (2,-1) (2,2) (5,5) (5,6) (3,8)'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'Weber Street')
		node1 = Node(2, -1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(5, 5, node2, None)
		node2.setNext(node3)
		node4 = Node(5, 6, node3, None)
		node3.setNext(node4)
		node5 = Node(3, 8, node4, None)
		node4.setNext(node5)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = 'add "King Street S" (4,2) (4,8)'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'King Street S')
		node1 = Node(4, 2, None, None)
		node2 = Node(4, 8, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = 'add "Davenport Road" (1,4) (5,8)'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'Davenport Road')
		node1 = Node(1, 4, None, None)
		node2 = Node(5, 8, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = 'mod "Weber Street" (2,1) (2,2)'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'mod')
		self.assertEqual(streetName, 'Weber Street')
		node1 = Node(2, 1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = 'rm "King Street S"'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'rm')
		self.assertEqual(streetName, 'King Street S')
		self.assertEqual(co_ord, None)
		
		line = 'gg'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'gg')
		self.assertEqual(streetName, None)
		self.assertEqual(co_ord, None)


		# ---------------------------------------------------
		# ----- Input with multiple spaces ---------- 
		line = '    add "Weber Street"    (2,-1)  (2,2)  (5,5) (5,6) (3,8)  '
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'Weber Street')
		node1 = Node(2, -1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(5, 5, node2, None)
		node2.setNext(node3)
		node4 = Node(5, 6, node3, None)
		node3.setNext(node4)
		node5 = Node(3, 8, node4, None)
		node4.setNext(node5)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = 'add   "King Street S" (4,2) (4,8)  '
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'King Street S')
		node1 = Node(4, 2, None, None)
		node2 = Node(4, 8, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = '   add   "Davenport Road"   (1,4)  (5,8)'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'Davenport Road')
		node1 = Node(1, 4, None, None)
		node2 = Node(5, 8, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		
		# ---------------------------------------------------
		# ----- Input with multiple spaces inside coordinate (Except after '-' sign) ---------- 
		line = '    add "Weber Street"    (2, -1 )  (2,  2)  ( 5,  5) (5, 6) (3, 8)  '
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'Weber Street')
		node1 = Node(2, -1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(5, 5, node2, None)
		node2.setNext(node3)
		node4 = Node(5, 6, node3, None)
		node3.setNext(node4)
		node5 = Node(3, 8, node4, None)
		node4.setNext(node5)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = 'add   "King Street S" (4  ,2) (   4, 8  )  '
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'King Street S')
		node1 = Node(4, 2, None, None)
		node2 = Node(4, 8, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		
		line = '   add   "Davenport Road"   (1,    4)  (5, 8)'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'add')
		self.assertEqual(streetName, 'Davenport Road')
		node1 = Node(1, 4, None, None)
		node2 = Node(5, 8, node1, None)
		node1.setNext(node2)
		self.assertEqual(co_ord.nodeEquals(co_ord, node1), True)
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		with self.assertRaises(Exception):
			line = ''
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "" (-1,3) (1,7)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'gg 23'
			cmd, streetName, co_ord = lineParsing(line)
			
			
		with self.assertRaises(Exception):
			line = 'rm'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'rm Weber'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'rm "King Street S" (2,1)'
			cmd, streetName, co_ord = lineParsing(line)
			
			
		with self.assertRaises(Exception):
			line = 'add'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport Road"'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add Davenport (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport" (1,4) "(5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "" (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport Road" (1,4 (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport Road" (1,a) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = '= a'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = '= abcd abcd'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'gg "adbs"'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport Road" (14) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport Road" (1,4,3) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Some Road" (1,7)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add  "Some Road"  (1,2)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = ' add  "Some other road"  (1,0)  '
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'mod "Davenport Road" (-1,4)' 
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Weber Street dqw" (2,-1) (2,- 2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street abcd" (2,-1) ((2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street wt" ((2,-1) (2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street dwq" (2,-1) (2,2) (5,5) (5,6) (3,8))'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Weber Street check" ( (2,-1) (2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street check" (2,-1) (2,2) ( (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street check" (2,-1) (2,2) (5,5) (5,6) (3,8) ('
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street check" (2,-1) (2,2) (5,5) (5,6) (3,8) (  '
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street check" (2,-1) (2,2) (5,5) (5,6) (3,8) )'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Extra street" (0,-1) (2,9) (5,5)) (5,2) (8,-1)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Extra street" (0,-1) (2,9) (5,5) (5,(2) (8,-1)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Check street a  name." (2,-1) (2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Check street name a @" (2,-1) (2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Weber Street a 24" (2,-1) (2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "King 2 Street a S" (4,2) (4,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "Davenport Road a 1" (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "" (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add " " (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "     " (1,4) (5,8)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Weber Street a" (2,-1) (2,2) (5,5) (5,6 1) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
		
		with self.assertRaises(Exception):
			line = 'add "Weber Street a" (2,-1 4) (2, 2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
		
		
		# From FAQs
		with self.assertRaises(Exception):
			line = 'add "A Weber Street" (2,-1) (+2,2) (5,5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "B Weber Street" (2,-1) (2,2) (5,-   5) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "C Weber Street" (2,-1) (2,2) (5,5  8) (5,6) (3,8)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "az weber" 1,2,3,4,5,6'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "bz weber" (1,2 (3,4) (5,6)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "cz weber" (1,2)(3,4) (5,6)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add"dz weber" (1,2) (3,4) (5,6)'
			cmd, streetName, co_ord = lineParsing(line)
			
		with self.assertRaises(Exception):
			line = 'add "ez weber"(1,2) (3,4) (5,6)'
			cmd, streetName, co_ord = lineParsing(line)
		
		
		
	def test_Controller_1_priority (self):
		# ---------------------------------------------------
		# ------------------- Example 1 ---------------------
		# ---------------------------------------------------
		c = Controller()
		self.assertEqual(c.getStreets(), [])
		
		line = 'add "Weber Street" (2,-1) (2,2) (5,5) (5,6) (3,8)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(2, -1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(5, 5, node2, None)
		node2.setNext(node3)
		node4 = Node(5, 6, node3, None)
		node3.setNext(node4)
		node5 = Node(3, 8, node4, None)
		node4.setNext(node5)
		c.addStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[0], testStreet))
		
		line = 'add "King Street S" (4,2) (4,8)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(4, 2, None, None)
		node2 = Node(4, 8, node1, None)
		node1.setNext(node2)
		c.addStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[1], testStreet))
		
		line = 'add "Davenport Road" (1,4) (5,8)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(1, 4, None, None)
		node2 = Node(5, 8, node1, None)
		node1.setNext(node2)
		c.addStreet(Street(streetName, co_ord))
		testStreet = Street('Davenport Road', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[2], testStreet))
		
		#'gg'
		expOut = "V 10\nE {<2,1>,<1,3>,<4,1>,<1,6>,<6,5>,<7,6>,<6,8>,<9,6>,<6,10>}"
		self.assertEqual(c.generateGraph(), expOut)
		
		line = 'mod "Weber Street" (2,1) (2,2)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(2, 1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		c.modifyStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[0], testStreet))
		
		#'gg'
		expOut = "V 5\nE {<2,1>,<1,3>,<4,1>,<1,5>}"
		self.assertEqual(c.generateGraph(), expOut)
		
		#'rm "King Street S"'
		c.removeStreet('King Street S')
		self.assertEqual(c.checkStreet('King Street S'), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c.generateGraph(), expOut)
		
		#'rm "King Street S"'
		with self.assertRaises(Exception):
			c.removeStreet('King Street S')
		
		#'rm "KING Street S"'
		with self.assertRaises(Exception):
			c.removeStreet('KING Street S')
		
		line = 'add "Weber Street" (2,-1) (2,2) (5,5) (5,6) (3,8)'
		with self.assertRaises(Exception):
			cmd, streetName, co_ord = lineParsing(line)
			node1 = Node(2, -1, None, None)
			node2 = Node(2, 2, node1, None)
			node1.setNext(node2)
			node3 = Node(5, 5, node2, None)
			node2.setNext(node3)
			node4 = Node(5, 6, node3, None)
			node3.setNext(node4)
			node5 = Node(3, 8, node4, None)
			node4.setNext(node5)
			c.addStreet(Street(streetName, co_ord))
		
		line = 'add "WEBER Street" (2,-1) (2,2) (5,5) (5,6) (3,8)'
		with self.assertRaises(Exception):
			cmd, streetName, co_ord = lineParsing(line)
			node1 = Node(2, -1, None, None)
			node2 = Node(2, 2, node1, None)
			node1.setNext(node2)
			node3 = Node(5, 5, node2, None)
			node2.setNext(node3)
			node4 = Node(5, 6, node3, None)
			node3.setNext(node4)
			node5 = Node(3, 8, node4, None)
			node4.setNext(node5)
			c.addStreet(Street(streetName, co_ord))
		
		#'rm "WEBER Street"'
		c.removeStreet('WEBER Street')
		self.assertEqual(c.checkStreet('WEBER Street'), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c.generateGraph(), expOut)
		
		#'mod "WEBER Street" (8,1) (2,3)'
		with self.assertRaises(Exception):
			node1 = Node(8, 1, None, None)
			node2 = Node(2, 3, node1, None)
			node1.setNext(node2)
			c.modifyStreet(Street('WEBER Street', node1))
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c.generateGraph(), expOut)
		
		#'rm "Street 12"'
		with self.assertRaises(Exception):
			c.removeStreet('Street 12')
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c.generateGraph(), expOut)
		
		#'mod "Abcd Street" (8,1) (2,3)'
		with self.assertRaises(Exception):
			node1 = Node(8, 1, None, None)
			node2 = Node(2, 3, node1, None)
			node1.setNext(node2)
			c.modifyStreet(Street('Abcd Street', node1))
		

		#with self.assertRaises(Exception):
		#	line = 'add "Davenport Road Duplicate" (1,4) (5,8)'
		#	cmd, streetName, co_ord = lineParsing(line)
		#	node1 = Node(1, 4, None, None)
		#	node2 = Node(5, 8, node1, None)
		#	node1.setNext(node2)
		#	c.addStreet(Street(streetName, co_ord))
		
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		
		
		
		# ---------------------------------------------------
		# ------------------- Example 2 ---------------------
		# ---------------------------------------------------
		c2 = Controller()
		self.assertEqual(c2.getStreets(), [])
		
		line = 'add "Weber Street" (-2,2) (1,0) (1,-3) (-3,-3)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(-2, 2, None, None)
		node2 = Node(1, 0, node1, None)
		node1.setNext(node2)
		node3 = Node(1, -3, node2, None)
		node2.setNext(node3)
		node4 = Node(-3, -3, node3, None)
		node3.setNext(node4)
		c2.addStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c2.getStreets()[0], testStreet))
		
		line = 'add "King Street S" (1,-1) (4,-1) (7,2) (7,5) (1,3)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(1, -1, None, None)
		node2 = Node(4, -1, node1, None)
		node1.setNext(node2)
		node3 = Node(7, 2, node2, None)
		node2.setNext(node3)
		node4 = Node(7, 5, node3, None)
		node3.setNext(node4)
		node5 = Node(1, 3, node4, None)
		node4.setNext(node5)
		c2.addStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c2.getStreets()[1], testStreet))
		
		line = 'add "Davenport Road" (7,2) (2,6) (5,0)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(7, 2, None, None)
		node2 = Node(2, 6, node1, None)
		node1.setNext(node2)
		node3 = Node(5, 0, node2, None)
		node2.setNext(node3)
		c2.addStreet(Street(streetName, co_ord))
		testStreet = Street('Davenport Road', node1)
		self.assertTrue(testStreet.streetEquals(c2.getStreets()[2], testStreet))
		
		line = 'add "Fourth Road" (1,-3) (6,-6) (6,-3) (4,-1)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(1, -3, None, None)
		node2 = Node(6, -6, node1, None)
		node1.setNext(node2)
		node3 = Node(6, -3, node2, None)
		node2.setNext(node3)
		node4 = Node(4, -1, node3, None)
		node3.setNext(node4)
		c2.addStreet(Street(streetName, co_ord))
		testStreet = Street('Fourth Road', node1)
		self.assertTrue(testStreet.streetEquals(c2.getStreets()[3], testStreet))
		
		
		#'gg'
		expOut = "V 14\nE {<2,1>,<1,3>,<1,4>,<3,5>,<3,6>,<7,4>,<4,10>,<10,8>,<8,12>,<12,9>,<9,14>,<14,10>,<8,11>,<11,12>,<12,14>,<14,13>}"
		self.assertEqual(c2.generateGraph(), expOut)
		
		line = 'mod "Weber Street" (-2,2) (1,0) (-3,-3)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(-2, 2, None, None)
		node2 = Node(1, 0, node1, None)
		node1.setNext(node2)
		node3 = Node(-3, -3, node2, None)
		node2.setNext(node3)
		c2.modifyStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c2.getStreets()[0], testStreet))
		
		#'gg'
		expOut = "V 10\nE {<2,1>,<3,1>,<1,6>,<6,4>,<4,8>,<8,5>,<5,10>,<10,6>,<4,7>,<7,8>,<8,10>,<10,9>}"
		self.assertEqual(c2.generateGraph(), expOut)
		
		#'rm "King Street S"'
		c2.removeStreet('King Street S')
		self.assertEqual(c2.checkStreet('King Street S'), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c2.generateGraph(), expOut)
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		
		
		# ---------------------------------------------------
		# ------------------- Example 3 ---------------------
		# ---------------------------------------------------
		c3 = Controller()
		self.assertEqual(c3.getStreets(), [])
		
		line = 'add "Weber Street" (0,0) (2,2) (6,-2) (8,0)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(0, 0, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(6, -2, node2, None)
		node2.setNext(node3)
		node4 = Node(8, 0, node3, None)
		node3.setNext(node4)
		c3.addStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c3.getStreets()[0], testStreet))
		
		line = 'add "King Street S" (0,0) (2,-2) (6,2) (8,0)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(0, 0, None, None)
		node2 = Node(2, -2, node1, None)
		node1.setNext(node2)
		node3 = Node(6, 2, node2, None)
		node2.setNext(node3)
		node4 = Node(8, 0, node3, None)
		node3.setNext(node4)
		c3.addStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c3.getStreets()[1], testStreet))
		
		
		#'gg'
		expOut = "V 7\nE {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>}"
		self.assertEqual(c3.generateGraph(), expOut)
		
		line = 'mod "Weber Street" (0,0) (2,2) (6,4) (8,0)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(0, 0, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(6, 4, node2, None)
		node2.setNext(node3)
		node4 = Node(8, 0, node3, None)
		node3.setNext(node4)
		c3.modifyStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c3.getStreets()[0], testStreet))
		
		#'gg'
		expOut = "V 6\nE {<1,2>,<1,3>,<5,4>,<6,4>}"
		self.assertEqual(c3.generateGraph(), expOut)
		
		#'rm "Weber Street"'
		c3.removeStreet('Weber Street')
		self.assertEqual(c3.checkStreet('Weber Street'), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c3.generateGraph(), expOut)
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		
		
		# ---------------------------------------------------
		# ------------------- Example 4 ---------------------
		# ---------------------------------------------------
		c4 = Controller()
		self.assertEqual(c4.getStreets(), [])
		
		line = 'add "Weber Street" (0,0) (9,0) (12,-2)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(0, 0, None, None)
		node2 = Node(9, 0, node1, None)
		node1.setNext(node2)
		node3 = Node(12, -2, node2, None)
		node2.setNext(node3)
		c4.addStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c4.getStreets()[0], testStreet))
		
		line = 'add "King Street S" (3,2) (6,-2) (9,2) (11,1) (11,-3) (3,-5) (3,1)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(3, 2, None, None)
		node2 = Node(6, -2, node1, None)
		node1.setNext(node2)
		node3 = Node(9, 2, node2, None)
		node2.setNext(node3)
		node4 = Node(11, 1, node3, None)
		node3.setNext(node4)
		node5 = Node(11, -3, node4, None)
		node4.setNext(node5)
		node6 = Node(3, -5, node5, None)
		node5.setNext(node6)
		node7 = Node(3, 1, node6, None)
		node6.setNext(node7)
		c4.addStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c4.getStreets()[1], testStreet))
		
		
		#'gg'
		expOut = "V 14\nE {<2,8>,<8,1>,<1,6>,<6,3>,<4,1>,<1,5>,<5,6>,<6,7>,<9,8>,<8,10>,<3,11>,<11,12>,<13,11>,<11,14>}"
		self.assertEqual(c4.generateGraph(), expOut)
		
		line = 'mod "Weber Street" (9,0) (12,-2)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(-2, 2, None, None)
		node2 = Node(1, 0, node1, None)
		node1.setNext(node2)
		node3 = Node(-3, -3, node2, None)
		node2.setNext(node3)
		c4.modifyStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c4.getStreets()[0], testStreet))
		
		#'gg'
		expOut = "V 5\nE {<2,1>,<1,3>,<4,1>,<1,5>}"
		self.assertEqual(c4.generateGraph(), expOut)
		
		#'rm "Weber Street"'
		c4.removeStreet('Weber Street')
		self.assertEqual(c4.checkStreet('Weber Street'), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c4.generateGraph(), expOut)
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		
		
		# ---------------------------------------------------
		# ------------------- Example 5 ---------------------
		# ---------------------------------------------------
		c5 = Controller()
		self.assertEqual(c5.getStreets(), [])
		
		line = 'add "Weber Street" (0,0) (3,3) (4,0) (4,-3)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(0, 0, None, None)
		node2 = Node(3, 3, node1, None)
		node1.setNext(node2)
		node3 = Node(4, 0, node2, None)
		node2.setNext(node3)
		node4 = Node(4, -3, node3, None)
		node3.setNext(node4)
		c5.addStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c5.getStreets()[0], testStreet))
		
		line = 'add "King Street S" (-7,3) (-7,0) (0,0) (2,-2) (6,4) (8,4)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(-7, 3, None, None)
		node2 = Node(-7, 0, node1, None)
		node1.setNext(node2)
		node3 = Node(0, 0, node2, None)
		node2.setNext(node3)
		node4 = Node(2, -2, node3, None)
		node3.setNext(node4)
		node5 = Node(6, 4, node4, None)
		node4.setNext(node5)
		node6 = Node(8, 4, node5, None)
		node5.setNext(node6)
		c5.addStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c5.getStreets()[1], testStreet))
		
		line = 'add "Davenport Road" (-4,0) (-4,6) (-2,6) (2,2)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(-4, 0, None, None)
		node2 = Node(-4, 6, node1, None)
		node1.setNext(node2)
		node3 = Node(-2, 6, node2, None)
		node2.setNext(node3)
		node4 = Node(2, 2, node3, None)
		node3.setNext(node4)
		c5.addStreet(Street(streetName, co_ord))
		testStreet = Street('Davenport Road', node1)
		self.assertTrue(testStreet.streetEquals(c5.getStreets()[2], testStreet))
		
		
		#'gg'
		expOut = "V 11\nE {<1,5>,<5,2>,<3,10>,<10,1>,<1,4>,<6,5>,<2,7>,<7,8>,<4,7>,<7,9>,<10,11>}"
		self.assertEqual(c5.generateGraph(), expOut)
		
		line = 'mod "King Street S" (-7,3) (-7,0)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(-7, 3, None, None)
		node2 = Node(-7, 0, node1, None)
		node1.setNext(node2)
		c5.modifyStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c5.getStreets()[1], testStreet))
		
		#'gg'
		expOut = "V 4\nE {<2,1>,<1,3>,<4,1>}"
		self.assertEqual(c5.generateGraph(), expOut)
		
		#'rm "Weber Street"'
		c5.removeStreet('Weber Street')
		self.assertEqual(c5.checkStreet('Weber Street'), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c5.generateGraph(), expOut)
		# ---------------------------------------------------
		# ---------------------------------------------------
		
		
		
		
	def test_Controller_2_spaces (self):
		c = Controller()
		self.assertEqual(c.getStreets(), [])
		
		
		line = '    add "Weber Street"    (2, -1 )  (2,  2)  ( 5,  5) (5, 6) (3, 8)  '
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(2, -1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		node3 = Node(5, 5, node2, None)
		node2.setNext(node3)
		node4 = Node(5, 6, node3, None)
		node3.setNext(node4)
		node5 = Node(3, 8, node4, None)
		node4.setNext(node5)
		c.addStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[0], testStreet))
		
		line = 'add   "King Street S" (4  ,2) (   4, 8  )  '
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(4, 2, None, None)
		node2 = Node(4, 8, node1, None)
		node1.setNext(node2)
		c.addStreet(Street(streetName, co_ord))
		testStreet = Street('King Street S', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[1], testStreet))
		
		line = '   add   "Davenport Road"   (1,    4)  (5, 8)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(1, 4, None, None)
		node2 = Node(5, 8, node1, None)
		node1.setNext(node2)
		c.addStreet(Street(streetName, co_ord))
		testStreet = Street('Davenport Road', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[2], testStreet))
		
		#'gg'
		expOut = "V 10\nE {<2,1>,<1,3>,<4,1>,<1,6>,<6,5>,<7,6>,<6,8>,<9,6>,<6,10>}"
		self.assertEqual(c.generateGraph(), expOut)
		
		
		line = '   mod "Weber Street" (2, 1) (2, 2)'
		cmd, streetName, co_ord = lineParsing(line)
		node1 = Node(2, 1, None, None)
		node2 = Node(2, 2, node1, None)
		node1.setNext(node2)
		c.modifyStreet(Street(streetName, co_ord))
		testStreet = Street('Weber Street', node1)
		self.assertTrue(testStreet.streetEquals(c.getStreets()[0], testStreet))
		
		
		#'gg'
		expOut = "V 5\nE {<2,1>,<1,3>,<4,1>,<1,5>}"
		self.assertEqual(c.generateGraph(), expOut)
		
		#'rm "King Street S"'
		line = 'rm "King Street S"'
		cmd, streetName, co_ord = lineParsing(line)
		self.assertEqual(cmd, 'rm')
		self.assertEqual(streetName, 'King Street S')
		c.removeStreet(streetName)
		self.assertEqual(c.checkStreet(streetName), None)
		
		#'gg'
		expOut = 'V 0\nE {}'
		self.assertEqual(c.generateGraph(), expOut)
		
	
if __name__ == '__main__':
	ece650_a1 = importlib.import_module("ece650-a1")
	globals().update(vars(ece650_a1))
	
	unittest.main()