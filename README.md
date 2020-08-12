## Yutong Xie, Ruikang Mao, ruyx
## Contributions
- Yutong focused more on free.c, print_heap.c, Makefile, bench.c and the skeleton of c files.
- Ruikang focused more on getmen.c, get_men_status.c, men.h, men_impl.h, men_untils.c.
- We worked together on testing and debugging.
## Discription
Our free list stores blocks that are ready to be allocated. The free list is organized in an order of strictly increasing memory addresses. Block sizes are positive numbers and no smaller than whatever minimum size. Also, they do not overlap and are not touching.
During the running process, when *getmem()* is called, it extracts a block with a proper size from our free list and returns it. Then this block is a candidate to be free. When *freemem()* is called, it returns the block of storage at the given location p to our free list and combines the block with other adjacent 
## Results
CPU TIME is generally around .02 seconds when running 10000 trials. The total storage acquired from the underlying system is generally around 200032 bytes for every run.
## Resources
The homework spec is useful to some extent. Also, we tried to learn about how malloc() is implemented internally from stack overflow resources: <a href="https://stackoverflow.com/questions/3479330/how-is-malloc-implemented-internally" target="_blank"></a>
