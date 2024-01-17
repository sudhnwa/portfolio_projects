<h2>huffman_code</h2>

demonstration of data compression algorithm in C

Huffman Coding is a lossless data compression technique. We generate prefix codes for every character encountered while reading the input file or text. To generate these prefix codes, we use the tree traversing method, which follows a greedy algorithm. The tree is generated using the frequencies of the characters.

First, calculate the frequency of every character and generate the linked list, each node of the linked list will contain data as a character and its frequency. Sort the linked list in ascending order so that nodes with characters having less frequency will be at the start of the linked list.

Tree Generation: The tree is generated from leaf nodes to the root node. For Tree generation, we have to maintain two queues. Our first queue will be our generated linked list and the second queue will hold the addition of two nodes, this will be our internal node with the first dequeued node as the left child and the second dequeued node as the right child

Dequeue two nodes from the first queue, create an internal node with a frequency equal to the sum of two nodes' frequencies, and add that internal node to the second queue.

Now dequeue two nodes with the minimum frequency by examining the front of both queues. Repeat the following steps two times 1. If the second queue is empty, dequeue from the first queue. 2. If the first queue is empty, dequeue from the second queue. 3. Else, compare the front of two queues and dequeue the minimum.
Repeat step two until only one node is present in any of the queues, that will be our root node.

while executing the code it takes the three command line arguments:

1. The name of the file, in which data is to be compressed is present

2. The name of the file, in which codes are to be stored

3. The name of the file, in which decoded data is to be stored

Note: create all three text files beforehand executing the program, even though codes and decoded text will be generated afterward, the program will still require the name of these destination files, so create empty files.

Snapshot of execution: huffman_execution

![huffman](https://github.com/sudhnwa/projects/assets/110271704/2474be84-1e14-4cf4-98f2-0242fd218bce)

You can write your text in an input text file or try this code with any text file, even for files containing thousands of lines of text ;)
