import os
import re
import sys

def countWords(txtfile):
  file = open(txtfile, "rt")
  data = file.read()
  words = data.split()
  print('Number of words in text file :', len(words))

def main():
  if len(sys.argv) != 2:
    sys.exit("Usage: python dummy.py [txtfilename]")

  countWords(sys.argv[1])
