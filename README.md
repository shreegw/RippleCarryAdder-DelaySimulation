# Ripple Carry Adder
![image](https://github.com/user-attachments/assets/ecde3f20-f7cc-4f75-924f-40d6660c8490)

 A Ripple Carry Adder is made of Full Adder Circuits connected in series where the subsequent adder is connected to the previous full adder and the carryout of the previous adder becomes the carryin of the next full adder. The Schematic of a 32-Bit Ripple Carry Adder is shown in figure 1. The worst-case delay of a Ripple Carry Adder circuit is n*2D where n is the number of bits and D is the delay of one logic gate level. In Fig. 2 we can observe the first logic gate delay occurs at Sum = A ^ B ^ Cin and (A & B), (B & Cin), (Cin & A). The Second Logic Gate delay occurs at Cout = (A & B) | (B & Cin) | (Cin & A), Hence the Full adder has a delay of 2D.
 
![image](https://github.com/user-attachments/assets/44786436-5a62-4e5f-aafb-a8ec4dcddfd3)

For this assignment, the Ripple Carry Adder is coded using C++. There are 3 functions used for the program. 

```
array <unsigned long int,32> bcdConv (unsigned long int A)
```
This function converts decimal number to binary number. The datatype used here is unsigned long int which has a range of 0 to 4294967295, therefore converting the decimal number to binary equivalent. It returns an array of size 32 with the binary equivalent. The program utilizes this function twice to convert Number A and Number B to 32-bit binary equivalent by padding zeros in front of it if required.

```
void  fullAdder(array<unsigned  long  int, 32>&  A, array<unsigned  long  int, 32>&  B,array<unsigned  long  int, 32>&  Summ, array<unsigned  long  int, 32>&  Summstore,array<unsigned  long  int, 32>&  Carstore, unsigned  long  int&  Lcout, int&  delayCount)
```
This function is a Full Adder that performs addition on two 32-bit arrays by taking one pair of binary numbers at a time and storing the sum bits of each pair in Summstore and carry bits in Carstore array. Along with that it also counts delay for each iteration

```
int main()
```
This function contains code to display the outputs and is also used in Part 2 to generate 1600 pairs of random numbers.

