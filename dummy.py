def countWords(txtfile):
  file = open(txtfile, "rt")
  data = file.read()
  words = data.split()
  print('Number of words in text file :', len(words))
