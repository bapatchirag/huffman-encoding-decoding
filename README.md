# huffman-encoding-decoding
Data encoding and decoding using the Huffman code

# INTRODUCTION

Digital data communication is always subject to losses due to channel materials, noise in the connection, etc. To reduce these losses, a data encoding scheme known as the Huffman scheme is implemented.

The Huffman scheme involves constructing a max heap (called the Huffman tree) from all the characters in the text to be sent, on the basis of the frequency of occurrence of each character in the message. This max heap is traversed and bit values of either 0 or 1 are assigned if the character required is in the left or right subtree respectively, of the current root node.

This piece of code allows us to define an arbitrary character set, and construct a Huffman tree from this character set. Then any message with characters from that character set can be encoded using this scheme. Similarly, decoding of any encoded message can be performed using this code.

# HUFFMAN TREE CONSTRUCTION
First, a frequency list of all characters in the charset is constructed, which is then sorted by frequency, ascending. 

Then a binary max heap is generated from this list, with every element of the list becoming a leaf node. For this, intermediate nodes are created for every consecutive pair of nodes in the list, with the frequency of the intermediate node being the sum of frequencies of its 2 children. These intermediate nodes are also added in sorted manner to this list, and this process is continued until all nodes in the sorted list are exhausted.

# HUFFMAN ENCODING AND DECODING PROCEDURE:
To encode any given character, traverse the Huffman tree to that character. The sequence of 0’s and 1’s encountered on the way will be the encoded value of the character.
	
Similarly, to decode any sequence of 0’s and 1’s into the required character, traverse to the left subtree if 0 is encountered and to the right subtree is 1 is encountered. The leaf node ended up at would be the required character.


# FILE DETAILS
1. helper.h: Node functions.
2. huffman-init.h: Contains code which returns root of created Huffman Tree.
3. etext: Contains either encoded string, or string to be decoded.
4. ptext: Contains either decoded string, or string to be decoded.
5. charset: Contains all characters from which Huffman Tree is to be created; frequency list is created from these characters.
6. decode.c: Code to decode a string taken from etext and print to ptext.
7. encode.c: Code to encode a string taken from ptext and print to etext.

# MAKE OPTIONS
To make both encoder and decoder, execute
```bash
make all
```

To make only decoder, execute
```bash
make decode
```

To make only encoder, execute
```bash
make encode
```

To remove executables, execute
```bash
make clean
```
To clear all text files, execute
```bash
make clean-texts
```

## USE INSTRUCTIONS
To decode any string composed of 0's and 1's, execute
```bash
./decode
```

To encode any string composed of the characters from the charset, execute
```bash
./encode
```

### NOTES
- Currently, *etext* contains sample encoded string, and *ptext* contains the corresponding decoded output. These can be changed as required.
- Currently, *charset* contains an example set of characters. This too, can be altered as required.
- Every encoded letter in the encoded text must be followed by a '.', even if that letter is the last in a word
