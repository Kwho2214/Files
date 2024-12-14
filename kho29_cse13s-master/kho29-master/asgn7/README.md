In this assignment we go through and filter out certain words that are being used. We filter out the languages inorder to promote peace and virtue and to make sure children will not be corrupted by the use of bad languages. This assignment we use a Bloomfilter to quickly process and store words that comes in. We represent our BloomFilter using a bit vector. We use a HashTable to store translation from oldspeak to newspeak words, but inorder to avoid any hash collisions, where two oldspeak words have the same hash value, we use a binary search tree which are made up of nodes. 

To Build the program:
Download all files needed
On the linux terminal, type make, or make all

To Run the Program:
./banhammer -h[hash table size] -f[bloomfilter size] -s[statistics printing]
./banhammer < [file to feed in] [another file] [your phrase or words]
