//Author: Shree Ganesh Wooradi

//Copyright (c) 2024 Shree Ganesh Wooradi

//Project: Ripple Carry Adder Delay Simulation

#include <iostream>
#include <array>
#include <math.h>
using namespace std;

// This Function Converts Decimal to Binary Equivalent Number
array<unsigned long int, 32> bcdConv(unsigned long int A)
{
    array<unsigned long int, 32> bcd;
    unsigned long int temp;
    for (int i = 31; i >= 0; i--)
    {
        temp = A % 2;
        A = A / 2;
        bcd[i] = temp;
    }
    return bcd;
}

// This Function is a full adder which stores the value of each step for sum and carry
void fullAdder(array<unsigned long int, 32>& A, array<unsigned long int, 32>& B,
               array<unsigned long int, 32>& Summ, array<unsigned long int, 32>& Summstore,
               array<unsigned long int, 32>& Carstore, unsigned long int& Lcout, int& delayCount)
{
    unsigned long int Carin = 0;  //Initial Carry in of 0

    for (int i = 31; i >= 0; i--)
    {
        Summ[i] = A[i] ^ B[i] ^ Carin;
        Summstore[i] = A[i] ^ B[i];
     
        Lcout = (A[i] & B[i]) | (B[i] & Carin) | (Carin & A[i]);

        if(Lcout!=0)
        {
            delayCount += 2;
        }

        if(A[i]==B[i] && A[i]==1) //if A=1, B=1 Carry is 1
        {
            Carstore[i]=1;
        }
        else
        {
            Carstore[i]=0;
        }
  
        Carin = Lcout;  //Lcout is the carryout which will be set to carry in for next iteration
    }

    //the value of Carin will be used for the final carry-out
    Lcout = Carin;
}

int main() {
    array<unsigned long int, 32> A, B, Summ; // 32 bit arrays to store A, B and Final Sum
    array<unsigned long int, 32> Carstore, Summstore; // 32 Bit arrays to store values of Carry and Sum for each pair of A and B
    unsigned long int Lcout = 0;
    int delayCount = 0;
    
    unsigned long int a, b;

    // Input A and B in Decimal
    cout << "Enter number A (Range 0 to 4294967295): ";
    cin >> a;
    cout << "Enter number B (Range 0 to 4294967295): ";
    cin >> b;

    cout << endl;

    // Convert Decimal to Binary for A
    cout << "32 Bit Binary of A: ";
    A = bcdConv(a);
    for (int i = 0; i < 32; i++)
    {
        cout << " "<<A[i];
    }
    cout << endl;
   
    // Convert Decimal to Binary for B
    cout << "32 Bit Binary of B: ";
    B = bcdConv(b);
    for (int i = 0; i < 32; i++)
    {
        cout << " " << B[i];
    }
    cout << endl;

    // Sending the Arrays to the full adder after converting to Binary
    fullAdder(A, B, Summ, Summstore, Carstore, Lcout, delayCount);

    // Output of the sum and carry bits from first iteration
    cout << "Sum Bits            ";
    for (int i = 0; i < 32; i++) {  // Printing from MSB to LSB
        cout << " " <<Summstore[i];
    }
    cout << endl;
 
    cout << "Carry Bits          ";
    for (int i = 0; i < 32; i++) {  // Printing from MSB to LSB
        cout << " "<< Carstore[i];  
    }
    cout << endl;
    cout << endl;
   
    // Output the result (Sum and Carry-out)
    cout << "Overall Sum:        ";
    for (int i = 0; i < 32; i++) {  // Printing from MSB to LSB
        cout <<" " <<Summ[i];
    }
    cout << endl;

    cout << "Overall Sum in  Decimal: ";
    unsigned long int decimalSum = 0;
    for (int i = 0; i < 32; i++)
    {
        decimalSum += Summ[i] * static_cast<unsigned long int>(pow(2, 31 - i));  // Converting binary addition value to decimal
    }
    cout << decimalSum;

    cout << endl;

    cout << "Final Carry-out: " << Lcout << endl;  // Last Carry Out to display any overflow
    
    cout<<endl;
    cout << "total delay: " << delayCount; // Displays overall Delay of the adder
    return 0;
}

