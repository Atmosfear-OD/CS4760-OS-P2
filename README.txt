P2 by Pascal Odijk Last Updated 9/27/2021
CMPSCI 4760 Prof. Bhatia

--------------------------------------------------------
To compile program:
make

To clean:
make clean
--------------------------------------------------------
Method of invocation:
	./runsim n < testing.data // Where n is an integer greater than or equal to 1. This will be used as the number of available licenses.
				  // Note: The parent process takes away 1 license, so if n = 1, only one license will be available and no children will be able to be 
				  // forked so program will wait for 20 seconds and then terminate without printing anything to logfile.data.  
--------------------------------------------------------
Problems I encountered:
1. I worked on this until the very limit of the due date ... so, my code may be a little janky. From what I can tell, everything works fine though.
2. I do not believe that I have the program temrination method (ctrl+d) working as the professor wants.
---------------------------------------------------------
Github version control web address:
https://github.com/Atmosfear-OD/CS4760-OS-P2
