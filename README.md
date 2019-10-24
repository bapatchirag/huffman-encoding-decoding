# huffman-encoding-decoding
Data encoding and decoding using the Huffman code

# INTRODUCTION

Digital data communication is always subject to losses due to channel materials, noise in the connection, etc. To reduce these losses, a data encoding scheme known as the Huffman scheme is implemented.

The Huffman scheme involves constructing a max heap (called the Huffman tree) from all the characters in the text to be sent, on the basis of the frequency of occurrence of each character in the message. This max heap is traversed and bit values of either 0 or 1 are assigned if the character required is in the left or right subtree respectively, of the current root node.

This piece of code allows us to define an arbitrary character set, and construct a Huffman tree from this character set. Then any message with characters from that character set can be encoded using this scheme. Similarly, decoding of any encoded message can be performed using this code.


# HUFFMAN ENCODING AND DECODING PROCEDURE:
	
To encode any given character, traverse the Huffman tree to that character. The sequence of 0’s and 1’s encountered on the way will be the encoded value of the character.
	
Similarly, to decode any sequence of 0’s and 1’s into the required character, traverse to the left subtree if 0 is encountered and to the right subtree is 1 is encountered. The leaf node ended up at would be the required character.


# MAKE OPTIONS
1. To make both encoder and decoder, execute
```bash
make all
```
2. To make only decoder, execute
```bash
make decode
```
3. To make only encoder, execute
```bash
make encode
```
4. To remove executables, execute
```bash
make clean
```

# UPDATES
Huffman encoder and decoder files soon to be added
