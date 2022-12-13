#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        
        // Initialization of w[]
        unsigned long long w[5];
        size_t size = k.size();
        unsigned long long h = 0;

        for (unsigned int i = 0; i < 5; i++)
        {
            w[4 - i] = 0; // Initializing w[i]

            // When no more letters left in k
            if (size == 0)
            {
                w[4 - i] = 0;
            }

            // When there are 6 letters in k
            else if (size / 6 != 0)
            {
                for (unsigned int j = 0; j < 6; j++)
                {
                    w[4 - i] += pow(36, j) * letterDigitToNumber(k[size - 1 - j]);
                }

                size -= 6; // Decreasing size
            }

            else // When there are less than 6 letters left in k
            {
                for (unsigned int j = 0; j < size; j++)
                {
                    w[4 - i] += (unsigned long long)pow(36, j) * letterDigitToNumber(k[size - 1 - j]);
                }

                size = 0; // Size will always be 0 after this case
            }
        }

        for (unsigned int i = 0; i < 5; i++)
        {
            h += rValues[i] * w[i];
            std::cout << w[i] << std::endl;
        }

        return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        // Case 1: Number 0-9
        if (letter > 47 && letter < 58)
        {
            return letter - 48 + 26;
        }

        // Case 2: Letters A-Z
        if (letter > 64 && letter < 91)
        {
            return letter - 65;
        }
        
        // Case 3: Letters a-z
        return letter - 97;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
