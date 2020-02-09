## GitInt.cpp Tests
The testcases.cpp tests each individual function from the GitInt class. It's intended to be used to make sure your functions are working properly and catch any edge cases before you write process command or gitint-shell.cpp. This should test all of the functions we had to implement (other than process_command)--I'll probably add a separate test file for that later since that deals more with catching user errors than logic errors. 

## To run the testcases:
1. Make sure testcases.cpp is in the same directory as your gitint.cpp. You can also just copy and 
paste the code into your gitint-shell main() if that's easier, just remember to #include <stdexcept>
if you haven't already. 
2. Compile using:
	g++ -g -Wall -std=c++11 gitint.cpp testcases.cpp -o testcases 
3. Run using: 
	./testcases
4. Compare your output to the included test.check file. Let me know if you think there's any 		mistakes in the expected output. 

## Note:
These tests assume that you already have exception handling implemented in your functions--if you don't yet, comment out all of the try-catch blocks in testcases.cpp-- *all* of them will trigger an exception!
