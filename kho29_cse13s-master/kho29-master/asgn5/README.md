These are huffman encoding and decoding programs. Encoding compresses the data of the input fil. Decode decompresses the compressed input file and puts out the original file that was compressed. Encode uses a priority queue made of Nodes to make a tree that keeps what the input file has and them makes a code table of it, saying how many characters there are and their frequency. Decode takes that code from the encoded file and remakes the tree. It the traverses the tree to reassemble what was in the file. 

How to use program:
Download all needed file for encode and decode to run.

Run Program:
Make all to create excutable.
type ./encode -h to see program details
type ./decode -h to see program details 

SYNOPSIS
  A Huffman encoder.
  Compresses a file using the Huffman coding algorithm.

USAGE
  ./encode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print compression statistics.
  -i infile      Input file to compress.
  -o outfile     Output of compressed data.

