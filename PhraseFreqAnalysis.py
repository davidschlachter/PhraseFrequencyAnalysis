#!/usr/bin/env python3

import os, sys, re

"""
The following method was written by Scott Triglia,
posted on Jan 20th, 2013
from http://locallyoptimal.com/blog/2013/01/20/elegant-n-gram-generation-in-python/
Function will compile a list into a sequence of tuples comprised of
 the n consecutive elements in the list
"""
def find_ngrams(input_list, n):
  return list(zip(*[input_list[i:] for i in range(n)]))


"""
 build a dictionary of the n-tuples formed by consecutive words and the
 number of times each appears where the tuple of words is the key and
 the number of occurences is the value
"""
def make_frequency_dict(input_list):
    my_dict = {}
    for item in input_list:
        if item not in my_dict:
            my_dict[item] = 1
        elif item in my_dict:
            my_dict[item] += 1
    return my_dict

# Runtime error checking on the commmand line for parameter completeness
# DEVNOTE: may consider more intelligent argument parsing, ie. int vs text
#          or bad ordered args, ie. prgmname int filename == BAD!!!!
#                       instead of  prmgname filename int == GOOD!!!
if len(sys.argv)<= 2:
    print("Error: usage\n>>python prog_name.py source_txt.txt words_per_phrase")
    exit(1)

###
#Comments between the "###" lines are for program usage reference
# sys.argv[0] is program running
sourcefilename = sys.argv[1]  # sys.argv[1] is source text file
len_of_phrase = sys.argv[2]   # sys.argv[2] number of words per phrase
###

# opens and reads a text file and extract all "words"
## a "word" is defined here as any consecutive sequence of letters (including
##     contractions) delimited by non-alpha characters (excluding
##     apostrophe/single quotation marks, ex. "'")
pattern = re.compile(r'[\w]+\'?[\w]+', re.UNICODE)
with open(sourcefilename, "r") as source_file:
    line_read = source_file.read()
    low = re.findall(pattern, line_read)
print("Number of words counted: "+str(len(low)))

zipped_list = find_ngrams(low, int(len_of_phrase))
dictionary = make_frequency_dict(zipped_list)

# sort the keys of the dictionary based on their values
sorted_keys = sorted(list(dictionary.keys()), key=lambda k: dictionary[k], reverse=True)

# loop through the keys and store phrases and their frequencies in list
sorted_list = []
for k in sorted_keys:
    sorted_list.append( (k, dictionary[k]) )

# Printing the shortlist of common phrases from 'dictionary' that are
#      (runtime parameter #2) words long
shortlist_len = 10  # arbitrary length of shortlist (later versions may   \
                    #   make this a runtime parameter)
print("Printing shortlist of top "+str(shortlist_len)+" most common phrases "\
      "in text file:\n---"+str(sourcefilename)+"-"*3)
print("\nFREQ. | PHRASE")
for i in range(0,shortlist_len):
    print(sorted_list[i][1]," "*4, end=' ')
    for x in range(0,int(len_of_phrase)):
        print(sorted_list[i][0][x], end=' ')
    print()
