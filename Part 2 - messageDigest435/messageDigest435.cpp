/*
   COPYRIGHT (C) 2022 Jacen Conlan (jcc126) All rights reserved.

   Algorithms Project 1 - Part 2 - messageDigest435
   Author: Jacen Conlan (jcc126@uakron.edu)
   Version: 1.01 02.01.2022
   Purpose: This program contains the programmed solutions for Part 2 of Project 1
*/

// Preprocessor Directives || #includes
#include <string.h>
#include <iostream>
#include <fstream>
#include "sha256.h"
#include "BigIntegerLibrary.hh"

// Declarations to avoid the std:: prefix
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;

// Main function for the program
int main(int argc, char *argv[])
{
   // Checking to make sure arguments are correct || Code provided in assignment
   if ((argc != 3 || argv[1][0]!='s') && (argc !=4 || argv[1][0]!='v'))
   {
      cout << endl << "Wrong format! Should be \"./messageDigest435.exe s filename\" or \"./messageDigest435.exe v filename.signature\"";
      cout << endl << "Exiting program... please follow the correct format above." << endl << endl;
      return -1;
   } 
   
   // ******************** Variable Declarations ********************
   
   // String Variables
   string fileName;
   string fileHash;
   string fileLine;
   string fileData;
   string decrypt;
   string encrypt;
   string nValue;
   string signatureString;
   string signatureFileName;
   string verifySignatureString;
   string newFileData;
   string newFileHash;

   // BigUnsigned Variables
   BigUnsigned d = 0;
   BigUnsigned e = 0;
   BigUnsigned n = 0;
   BigUnsigned fileHashBase10 = 0;
   BigUnsigned signature = 0;
   BigUnsigned verifySignature = 0;
   BigUnsigned newFileHashBase10 = 0;
   BigUnsigned originalHash = 0;

   // File Stream Variables
   ofstream outFile;
   ifstream inFile;

   // ******************** General Preprogram Necessities ********************

   // Obtain the values for decrypt, encrypt, and nValue from text files
   inFile.open("d_n.txt");
   inFile >> decrypt;
   inFile >> nValue;
   inFile.close();
   inFile.open("e_n.txt");
   inFile >> encrypt;
   inFile.close();

   // Convert the data from the files from strings to BigUnsigned type
   d = stringToBigUnsigned(decrypt);
   e = stringToBigUnsigned(encrypt);
   n = stringToBigUnsigned(nValue);

   // ******************** File Signing Code ********************
   if (argv[1][0] == 's')
   {
      fileName = argv[2];

      // Reconstruct the data in the file to be signed as a string one line at a time
      inFile.open(fileName);

      if(!inFile)
      {
         cout << "Looks like there isn't a file with the name: " << fileName << " in the current directory. Exiting program..." << endl;
         return -1;
      }

      while (getline(inFile, fileLine))
      {
         fileData += fileLine + '\n';
      }

      inFile.close();

      // Hash the file to be signed using the sha256 method
      fileHash = sha256(fileData);

      // Convert the file hash from base 16 into base 10 using BigUnsignedInABase
      fileHashBase10 = BigUnsignedInABase(fileHash, 16);

      // Calculate signature of the base 10 hash using modexp and the private decrpyt key
      // Signature = (fileHashBase10 ^ d) % n
      signature = modexp(fileHashBase10, d, n);

      // Convert signature to a string
      signatureString = bigUnsignedToString(signature);

      // Save the signature string to the signature file
      signatureFileName = "file.txt.signature";
      outFile.open(signatureFileName);
      outFile << signatureString;
      outFile.close();

      cout << endl << "The signature file for the file: " << fileName << " has been generated" << endl << "You can now verify the file with file.txt.signature" << endl << endl;
   }
   
   // ******************** File Verification Code ********************
   else if (argv[1][0] == 'v')
   {
      fileName = argv[2];
      signatureFileName = argv[3];

      // Obtain the signature string from the signature file to verify
      inFile.open(signatureFileName);

      if(!inFile)
      {
         cout << "Looks like there isn't a file with the name: " << signatureFileName << " in the current directory. Exiting program..." << endl;
         return -1;
      }

      getline(inFile, verifySignatureString);
      inFile.close();

      // Reconstruct the data in the file to be verified as a string one line at a time
      inFile.open(fileName);

      if(!inFile)
      {
         cout << "Looks like there isn't a file with the name: " << fileName << " in the current directory. Exiting program..." << endl;
         return -1;
      }

      while (getline(inFile, fileLine))
      {
         newFileData += fileLine + '\n';
      }

      inFile.close();

      // Convert signature string into BigUnsigned type
      verifySignature = stringToBigUnsigned(verifySignatureString);

      // Hash the file to be verified using the sha256 method
      newFileHash = sha256(newFileData);

      // Convert the file hash from base 16 into base 10 using BigUnsignedInABase
      newFileHashBase10 = BigUnsignedInABase(newFileHash, 16);

      // Calculate the original base 10 hash using modexp and the public encrypt key
      // Signature = (fileHashBase10 ^ e) % n
      originalHash = modexp(verifySignature, e, n);

      // Verify if the hashes match and notify the user
      if (originalHash == newFileHashBase10)
      {
         cout << endl << "The hash values match! This file can be verified as authentic and has not been modified!" << endl << endl;
      }

      else
      {
         cout << endl << "The hash values do not match. This file cannot be verified as authentic and has been modified." << endl << endl;
      }
   }

    return 0;
}

// END OF FILE //