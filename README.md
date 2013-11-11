gearman_c_demo
==============

This is an example of building a Gearman Worker in C. There is a lack of documentation on the Gearman website for this. 

### Threaded Worker
Is on the TODO list. 

### Gearman Client 
There are 3 good examples of how to write a Gearman client at the Gearman documentation site. http://gearman.info/libgearman/examples.html. Use those. 
Compilation:gcc -I/usr/local -L/usr/local/libgearman/lib cworker.c -lgearman

