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
        unsigned long long temp;

        //array holding w values
        unsigned long long w[] = {0,0,0,0,0};
        int counter = -1;
        size_t amtMult = 1;

        //creates the w values based on mod 6 of the counter to place in proper w
        for(int i = k.size() - 1; i >= 0; i--){
            //counter to determine which what value will be mod by 6
            counter++;
            if(k.length() > 0){
                temp = letterDigitToNumber(k[i]);
            }
            else{
                return 0;
            }
            if(counter < 6){
                int holder = counter % 6;
                switch (holder){
                    case 0:
                        w[4] = w[4] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 5:
                        w[4] = w[4] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 4:
                        w[4] = w[4] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 3:
                        w[4] = w[4] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 2:
                        w[4] = w[4] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 1:
                        w[4] = w[4] + temp * amtMult;
                        amtMult *= 36;
                        break;
                }
                if(counter == 5)
                    amtMult = 1;

            }
            else if(counter < 12){
                int holder = counter % 6;
                switch (holder){
                    case 0:
                        w[3] = w[3] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 5:
                        w[3] = w[3] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 4:
                        w[3] = w[3] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 3:
                        w[3] = w[3] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 2:
                        w[3] = w[3] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 1:
                        w[3] = w[3] + temp * amtMult;
                        amtMult *= 36;
                        break;
                }
                if(counter == 11)
                    amtMult = 1;

            }
            else if(counter < 18){
                int holder = counter % 6;
                switch (holder){
                    case 0:
                        w[2] = w[2] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 5:
                        w[2] = w[2] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 4:
                        w[2] = w[2] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 3:
                        w[2] = w[2] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 2:
                        w[2] = w[2] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 1:
                        w[2] = w[2] + temp * amtMult;
                        amtMult *= 36;
                        break;
                }
                if(counter == 17)
                    amtMult = 1;
            }
            else if(counter < 24){
                int holder = counter % 6;
                switch (holder){
                    case 0:
                        w[1] = w[1] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 5:
                        w[1] = w[1] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 4:
                        w[1] = w[1] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 3:
                        w[1] = w[1] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 2:
                        w[1] = w[1] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 1:
                        w[1] = w[1] + temp * amtMult;
                        amtMult *= 36;
                        break;
                }
                if(counter == 23)
                    amtMult = 1;
            }
            else{
                int holder = counter % 6;
                switch (holder){
                    case 0:
                        w[0] = w[0] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 5:
                        w[0] = w[0] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 4:
                        w[0] = w[0] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 3:
                        w[0] = w[0] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 2:
                        w[0] = w[0] + temp * amtMult;
                        amtMult *= 36;
                        break;
                    case 1:
                        w[0] = w[0] + temp * amtMult;
                        amtMult *= 36;
                        break;
                }
            }

        
        }

        //returns the sum of each w value multiplied by its corresponding r value
        return((rValues[0] * w[0]) + (rValues[1] * w[1]) + (rValues[2] * w[2]) + (rValues[3] * w[3]) + (rValues[4] * w[4]));

    }
    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        HASH_INDEX_T temp;
        // Add code here or delete this helper function if you do not want it
        //converts letter in char form to base 36
        if((HASH_INDEX_T)letter < 97){
            if((HASH_INDEX_T)letter < 58){
                return (HASH_INDEX_T)letter - 22;
            }
            else{
                temp = (HASH_INDEX_T)letter;
                temp = temp + 32;
                return temp - 97;
            }
        }
        else{
            return (HASH_INDEX_T)letter - 97;
        }
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
