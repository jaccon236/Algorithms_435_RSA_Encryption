/*
   COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

   Algorithms Project 1 - Part 1 - rsa435
   Author: Jacen Conlan (jcc126@uakron.edu)
   Version: 1.01 02.01.2022
   Purpose: This program contains the programmed solutions for Part 2 of Project 1
*/

// Preprocessor Directives || #includes
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <chrono>
#include <cmath>

// Declarations to avoid the std:: prefix
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;

// 'BigIntegerLibrary.hh' includes all of the library headers.
#include "BigIntegerLibrary.hh"

// Call to determine if a number of the BigUnsigned type is prime
bool fermat(BigUnsigned checkValue)
{
   BigInteger randomBase = rand();
   BigUnsigned modx = modexp(randomBase, checkValue - 1, checkValue);
   
   // Running fermat 20 times minimizes possible error when checking primality
   for (BigInteger i = 0; i < 20; i++)
   {
      // If the number is not prime then modexp will return a value greater than 1
      if (modx > 1)
      {
         return false;
      }

      // If modexp did not return 1, pick a new random base and try again (just in case)
      randomBase = rand();
      modx = modexp(randomBase, checkValue - 1, checkValue);
   }

   // If the code reaches this point, the number in checkValue is prime
   return true;
}

// Call to determine the number of digits in a number of the BigUnsigned type
int totalDigits(BigUnsigned value)
{
   int count = 0;

   while (value != 0)
   {
      value /= 10;
      count++;
   }
   
   return count;
}

// Main function for the program
int main()
{
	/* The library throws 'const char *' error messages when things go
	 * wrong.  It's a good idea to catch them using a 'try' block like this
	 * one.  Your C++ compiler might need a command-line option to compile
	 * code that uses exceptions. */

   // Use time to seed the random number generator so that the values are different each time the program runs
   srand(time(NULL));

	try 
   {
      cout << "Running rsa435.exe" << endl << "Generating Random Primes p and q. This may take a moment..." << endl;
      
      BigUnsigned p;
      BigUnsigned q;

      // Start p at 1, increase it to a number of at least 155 digits, and check if that number is prime
      // If p is not prime, do it again until it is
      do
      {
         p = BigUnsigned(1);

         for (int i = 0; i < 154; i++)
         {
            p = (p * 10) + rand();
         }
      } while (!fermat(p));
      
      cout << "p generated!" << endl;

      // Start q at 1, increase it to a number of at least 155 digits, and check if that number is prime
      // If q is not prime, do it again until it is
      do
      {
         q = BigUnsigned(1);

         for (int i = 0; i < 154; i++)
         {
            q = (q * 10) + rand();
         }
      } while (!fermat(q));

      cout << "q generated!" << endl << "Calculating n, phi, e, and d..." << endl;
      
      // Multiply p and q together to get n
      BigUnsigned n = p * q;
      cout << "n calculated!" << endl;

      // Multiply p-1 and q-1 together to get phi
      BigUnsigned phi = (p - 1) * (q - 1);
      cout << "phi calculated!" << endl;

      // Generate a random 10-15 digit number to be used to find the final value of e
      // BigUnsigned e = BigUnsigned((rand() + 1) * (rand() + 1) + 1000000000);

      BigUnsigned e = BigUnsigned(1);

      for (int i = 0; i < 10; i++)
      {
         e = (e * 10) + rand();
      }
      
      // Find an odd integer that is relatively prime to phi
      while (gcd(phi, e) != 1)
      {
         e++;
      }
      
      cout << "e calculated!" << endl;

      // Use modinv to find the multiplicitive inverse of e modulo(phi)
      BigUnsigned d = modinv(e, phi);
      cout << "d calculated!" << endl;   

      // Create a output file type variable
      ofstream outFile;

      // Create or open a file named "p_q.txt" and store p and q each on their own line
      outFile.open("p_q.txt");
      outFile << p << endl << q;
      outFile.close();

      // Create or open a file named "e_n.txt" and store e and n each on their own line
      outFile.open("e_n.txt");
      outFile << e << endl << n;
      outFile.close();

      // Create or open a file named "d_n.txt" and store d and n each on their own line
      outFile.open("d_n.txt");
      outFile << d << endl << n;
      outFile.close();

      // Checking the total number of digits for each value generated to make sure they are big enough
      // cout << "Total digits of p: " << totalDigits(p) << endl;
      // cout << "Total digits of q: " << totalDigits(q) << endl;
      // cout << "Total digits of n: " << totalDigits(n) << endl;
      // cout << "Total digits of d: " << totalDigits(d) << endl;
      // cout << "Total digits of e: " << totalDigits(e) << endl;
   
	} catch(char const* err) {
		std::cout << "The library threw an exception:\n"
			<< err << std::endl; 
	}

   cout << endl << "Finished!" << endl;
   
	return 0;
}

// END OF FILE //