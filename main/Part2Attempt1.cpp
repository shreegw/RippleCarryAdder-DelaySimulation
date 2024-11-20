#include <iostream>
#include <cstdlib>  // For srand and rand
#include <ctime>    // For time
#include <array>
#include <cmath>    // For pow
using namespace std;

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
    unsigned long int Carin = 0;  // Initial Carry in of 0

    for (int i = 31; i >= 0; i--)
    {
        Summ[i] = A[i] ^ B[i] ^ Carin;
        Summstore[i] = A[i] ^ B[i];

        Lcout = (A[i] & B[i]) | (B[i] & Carin) | (Carin & A[i]);

        if (Lcout != 0)
        {
            delayCount += 2;
        }

        if (A[i] == B[i] && A[i] == 1)  // if A=1, B=1 Carry is 1
        {
            Carstore[i] = 1;
        }
        else
        {
            Carstore[i] = 0;
        }

        Carin = Lcout;  // Lcout is the carryout which will be set to carry in for next iteration
    }

    // the value of Carin will be used for the final carry-out
    Lcout = Carin;
}

int main() {
    const int size = 40;  // size of the array for random numbers
    const int totalCases = 1600;  // Total pairs of inputs (1600)
    unsigned int randomNumbersA[size];  // Array to store the pseudorandom numbers A
    unsigned int randomNumbersB[size];  // Array to store the pseudorandom numbers B
    array<unsigned long int, 32> A, B, Summ;  // 32 bit arrays to store A, B and Final Sum
    array<unsigned long int, 32> Carstore, Summstore;  // 32 Bit arrays to store values of Carry and Sum for each pair of A and B
    unsigned long int Lcout = 0;
    float Avg_Delay = 0.0f;  // Variable to store the average delay
    int delayCount = 0;
    int D_array[totalCases];  // Array to store delay values for 1600 cases

    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(0)));

    // Generate and store 1600 pseudorandom unsigned int numbers
    for (int caseIndex = 0; caseIndex < totalCases; ++caseIndex) {
        // Generate two pseudorandom numbers
        unsigned int randomA = rand() % 4294967295;
        unsigned int randomB = rand() % 4294967295;

        // Convert to 32-bit binary arrays (BCD format)
        A = bcdConv(randomA);
        B = bcdConv(randomB);

        // Reset delay counter
        delayCount = 0;

        // Apply inputs to the full adder (RCA)
        fullAdder(A, B, Summ, Summstore, Carstore, Lcout, delayCount);

        // Store the delay for this pair in D_array
        D_array[caseIndex] = delayCount;
    }

    // Calculate the average delay by summing all delays and dividing by 1600
    int totalDelay = 0;
    for (int i = 0; i < totalCases; i++) {
        totalDelay += D_array[i];
    }
    Avg_Delay = static_cast<float>(totalDelay) / totalCases;

    // Display the average delay
    cout << "Average Delay (Avg_Delay): " << Avg_Delay << endl;

    return 0;
}
