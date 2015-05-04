/* 
 * Euler Project Problem 72: Counting Fractions
 * Count the number of reduced proper fractions where denominator is 1,000,000 or less.
 * Employs Euler's phi function which says that the # of prime values less than n
 * can be found by its prime factorization. phi(n) = n * (1-(1/p)... and so on, where p is eah unique prime factor of n.
 * If n is prime, phi(n) is simply n-1.
 * 
 * File:   main.cpp
 * Author: elliot
 *
 * Created on May 3, 2015, 12:48 PM
 */

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <Windows.h>


using namespace std;

unsigned long long int rpfCounter = 0; //long long int to keep track of total # of reduced proper fractions found
int primeCounter; //int to count # of primes found by the sieve of eratosthenes
int *primes = new int[78500]; //array to store all primes under 1,000,000. The array size is set to 78500 because the actual number of prime values <1000000 is 78498.

/**
 * Credit: http://www.algolist.net/Algorithms/Number_theoretic/Sieve_of_Eratosthenes
 * This is an implementation of the Sieve of Eratosthenes. It checks all values <= the square root of the upperBound.
 * It starts with 2, marks it prime, and then marks all multiples of 2 so that they will not be checked.
 * It continues this way, checking every value available for checking, marking it as prime, and then marking out all of the multiples of that number.
 * @param upperBound: value under which all primes will be found
 */
void primeSieve(int upperBound) {
    
    int upperBoundSquareRoot = (int)sqrt((double)upperBound);
    bool *isComposite = new bool[upperBound + 1];
    primeCounter = 0;
    memset(isComposite, 0, sizeof(bool) * (upperBound + 1));
    
    //check all values up to the square root of the upperBound
    for (int m = 2; m <= upperBoundSquareRoot; m++) {
        if (!isComposite[m]) {
            primes[primeCounter] = m; //add to primes array
            primeCounter++;
            for (int k = m ; k <= upperBound; k += m){ //marks all multiples of that number so that they will not be checked as prime
                isComposite[k] = true;
            }
        }
    }

    //all of the values unmarked after checking up to the square root will be prime
    for (int m = upperBoundSquareRoot; m <= upperBound; m++){
        if (!isComposite[m]){
            primes[primeCounter] = m; // add to primes array
            primeCounter++;
        }
    }

    delete [] isComposite;

}

/**
 * 
 * @param number: number to find phi value for. 
 * @return: returns float phiValue for the number parameter
 */
float phi(int number){
    
    float phiValue = number; //
    int numberSR = (int)ceil(sqrt(number));

    //for loop is looking for prime factors. It checks all prime values in prime array less than number.
    //If number % any value from the array == 0, that value is incorporated into the phi equation.
    for(int i = 0; (i < primeCounter)&&(primes[i] <= number); i++){
        if(number % primes[i] == 0){
            phiValue = phiValue * (1-(1/(float)primes[i]));
        }
    }
    
    //this checks if the number made it all the way through the loop without finding a divisor.
    //if so, it is prime, and so phiValue is 1 less than number
    if(phiValue == number){
        phiValue--;
    }
    
    return phiValue;

}


int main(int argc, char** argv) {
    
    int upperLimit = 1000000; //the maximum denominator value. also will be the value under which to find all primes
    
    primeSieve(upperLimit); //find all primes < upperLimit. store those values in prime array
    
    //this for loop runs the phi function on each denominator value less
    for(int i = 2; i <= upperLimit; i++){
        rpfCounter += (int)phi(i);
    }
    
    cout << "Total # of reduced proper fractions with denominator <= " << upperLimit << ": " << rpfCounter;

    return 0;
}