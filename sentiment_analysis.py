#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Dec  9 22:36:03 2021

@authors: Anıl Alper, Haruko Okada, Leia Sohn
"""
import sys
import matplotlib.pyplot as plt


#import the module for emotion detection
import text2emotion as te

#reads the txt file as a string
def read_txt(file_directory):
    #open the text file
    text_file = open(file_directory, "r")
    
    #read it as a string
    data = text_file.read()
    
    #after reading it, close it
    text_file.close()
    
    #return that string
    return data



#main function that accepts the file directory as input
def main():
    # if the number of arguments is not 2 then the program will not work
    if len(sys.argv) != 2:
        # print the appropriate error message and exit the program
        sys.exit("Usage: python sentiment_analysis.py [txtfiledirectory]")
    
    # access the directory on the command line 
    directory = sys.argv[1]
    
    # represent the contents of this txt file as string
    txt_content = read_txt(directory)
    
    # get the emotions 
    emotion_dict = te.get_emotion(txt_content)

    # get rid of zeros
    for k in emotion_dict.copy():
        if emotion_dict[k] == 0:
            del emotion_dict[k]
    
    # access the labels
    emotions  = list(emotion_dict.keys())
    
    # access the proportions of sentiments
    proportions = list(emotion_dict.values())
    
    #plot the pie chart
    plt.pie(proportions, labels = emotions, autopct='%1.0f%%')

    #write a title for the pie chart
    plt.title(directory + " Emotion Pie Chart")
    
    #print emotion dictionary
    print(emotion_dict)

    #show the pie chart
    plt.show()
    
#call the main function
if __name__ == "__main__":
    main()
    
    
    