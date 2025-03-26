#include <iostream>
#include <bitset>
#include <cmath>

class BitManipulationProblems {
public:
    // 1. Find the first bit set (rightmost bit set)
    static int firstBitSet(int n) {
        // If n is 0, no bit is set
        if (n == 0) return -1;
        
        // Use built-in function for modern compilers
        // __builtin_ffs returns 1-indexed position of first bit set
        return __builtin_ffs(n) - 1;
        
        // Alternative implementation without built-in function:
        // return log2(n & -n);
    }
    
    // 2. Count the number of bits set (population count)
    static int countSetBits(int n) {
        // Use built-in function for modern compilers
        return __builtin_popcount(n);
        
        // Alternative implementation:
        /*
        int count = 0;
        while (n) {
            count += n & 1;
            n >>= 1;
        }
        return count;
        */
    }
    
    // 3. Find the last bit set (leftmost bit set)
    static int lastBitSet(int n) {
        // If n is 0, no bit is set
        if (n == 0) return -1;
        
        // Use log2 to find position of most significant bit
        return static_cast<int>(log2(n));
    }
    
    // 4. Explanation of log(n & -n)
    static int lastSetBitPosition(int n) {
        // n & -n gives the rightmost set bit
        // log2 gives its position
        // n & -n isolates the least significant set bit.
        
        // Example:
        // n = 12 (1100 in binary)
        // -n = -12 (two's complement: 11110100 in binary)
        // n & -n = 0100 (4 in decimal)
        // log2(4) = 2 (position of rightmost set bit)
     
        // -n flipt all the digit except the first set digit.

        if (n == 0) return -1;
       
        return log2(n & -n);
      
    
    1  0 1 1 0 0 


    0  1 0 1 1 1
    -

    0  0 0 1 0 0  = 2 ^2 = 2


    -




        // n = 12
      1 1 0 0 = 12
     
      0 0 1 1 + 1 = -12

      0  1  0 0
            
      1 1 1 0 0 0
      
      0 0 0 1 1 1 + 1
      
      0  0   1   0   0   0

      - 3th bit 
      0 0 1 0 0 0 = 24 = 16

      -
      2^3 = 8
      log2 (8)  == 3
  
      log 2 2 ^3 = log 8

      3 log2 2 = log 8

      3  = log 8

    }
    
    // Bonus: Clear the rightmost set bit
    static int clearRightmostSetBit(int n) {
        return n & (n - 1);
    }

    1 1 0 0 - 1  =  
    
    1 0  1 1 + 1  

    -
    1 0 0 0
   -

    1 <- set bit

    1 0 0 
    0 1 1 
  --
    0 0 0 
  --  

  1 0 0 0 
  0 1 1 1
  -
  0 0 0 0 => this is power of 2


  -

  1 1 0 0 0 
  1 0 1 1 1 
  -
  1 0 0 0 0
  -
 
    So -1 flips all the bits till the first set bit.
    it make all zero to 1 and first one to zero from right.

    // Bonus: Check if number is power of 2
    static bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }


    static int singleNumber(int nums[], int numsSize) {
    int result = 0;
    for(int i = 0; i < numsSize; i++){
        result ^= nums[i];
    }
    return result;

  1, 1 , 2, 2, 3, 3, 5, 

  1, 2, 3, 1

  1 ^2^2 ^3 ^1

x ^x = 0
0 ^x = 1
1 ^ 1 = 0



swap (int &a , int&b) {
        a = a ^ b;
        b' =   a ^ b ^ b // swap = a
        a' =    a ^ b  ^ a 
        b = a ^ b;
        a = a ^ b;
    }
}
};
