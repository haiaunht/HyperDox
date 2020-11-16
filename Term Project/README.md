A hyperlinked document system similar to web pages on the Internet.  Given a folder full of text files (Dox) the program will:

Import the contents of all .dox files in a given folder
Display the content of any given document
Calculate and display on request statistics about each document including:
The number of words
The average word length
The number of embedded links
Create an optimized search index for all the words in all the documents (ignore punctuation and case)
Provide a means to accept and execute user commands
Allow the user to search for and navigate to occurrences of specific words using the search index
Maintain a list of anchors (link endpoints) defined in each document
Resolve upon request any document links consisting of either:
A filename and an anchor, e.g. "|file.dox:my_anchor|" OR
A filename and a character index, e.g. "|file.dox:1032|" OR
A filename, e.g. "|file.dox:|"
Your submission will be graded based on:

Completeness
How well it satisfies the functional requirements above
Use of C++ techniques
Observation of style, convention and best practices
Sufficient use of comments to communicate intent
Efficiency of the logic and algorithms used
The set of dox which will be used for evaluation of your program is available in the course files.
