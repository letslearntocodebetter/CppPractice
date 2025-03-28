#include <iostream>
#include <bitset>
#include <cstdint>
using namespace std;

class Solution {
public:
    // 1. NAIVE APPROACH - BIT BY BIT REVERSAL
    // Time: O(1), Space: O(1)
    uint32_t reverseBits_naive(uint32_t n) {
        uint32_t result = 0;
        
        // Iterate through all 32 bits
        for (int i = 0; i < 32; i++) {
            // Left shift result to make space for new bit
            result <<= 1;
            
            // Add least significant bit of n
            result |= (n & 1);
            
            // Move to next bit in n
            n >>= 1;
        }
        
        return result;
    }
    
    // 2. DIVIDE AND CONQUER APPROACH
    // Time: O(1), Space: O(1)
    uint32_t reverseBits_divide_and_conquer(uint32_t n) {
        // Swap adjacent bits
        n = ((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1);
        
        // Swap bit pairs
        n = ((n & 0xcccccccc) >> 2) | ((n & 0x33333333) << 2);
        
        // Swap nibbles (4-bit groups)
        n = ((n & 0xf0f0f0f0) >> 4) | ((n & 0x0f0f0f0f) << 4);
        
        // Swap bytes
        n = ((n & 0xff00ff00) >> 8) | ((n & 0x00ff00ff) << 8);
        
        // Swap 16-bit halves
        n = (n >> 16) | (n << 16);
        
        return n;
    }
    
    // 3. LOOKUP TABLE APPROACH
    // Time: O(1), Space: O(1)
    uint32_t reverseBits_lookup_table(uint32_t n) {
        // Precomputed reverse for 8-bit numbers
        uint8_t lookup[256] = {0};
        
        // Populate lookup table once
        for (int i = 0; i < 256; i++) {
            lookup[i] = (i & 0x1) << 7 | (i & 0x2) << 5 |
                        (i & 0x4) << 3 | (i & 0x8) << 1 |
                        (i & 0x10) >> 1 | (i & 0x20) >> 3 |
                        (i & 0x40) >> 5 | (i & 0x80) >> 7;
        }
        
        // Reverse each byte and combine
        return  (lookup[n & 0xff] << 24) | 
                (lookup[(n >> 8) & 0xff] << 16) | 
                (lookup[(n >> 16) & 0xff] << 8) | 
                (lookup[(n >> 24) & 0xff]);
    }
    
    // 4. STANDARD LIBRARY APPROACH
    // Time: O(1), Space: O(1)
    uint32_t reverseBits_standard(uint32_t n) {
        // C++20 standard library bit manipulation
        return __builtin_bswap32(n);
    }
    
    // 5. DETAILED BINARY REPRESENTATION APPROACH
    void printBinaryRepresentation(uint32_t n) {
        bitset<32> bits(n);
        cout << "Original:  " << bits.to_string() << endl;
        
        uint32_t reversed = reverseBits_naive(n);
        bitset<32> reversedBits(reversed);
        cout << "Reversed:  " << reversedBits.to_string() << endl;
    }
};

int main() {
    Solution sol;
    
    // Example input
    uint32_t n = 43261596;  // Input in decimal
    
    // Print binary representation
    sol.printBinaryRepresentation(n);
    
    cout << "\nReverse Bits Results:" << endl;
    
    // Test different approaches
    cout << "Naive Approach:           " 
         << sol.reverseBits_naive(n) << endl;
    
    cout << "Divide and Conquer:       " 
         << sol.reverseBits_divide_and_conquer(n) << endl;
    
    cout << "Lookup Table Approach:    " 
         << sol.reverseBits_lookup_table(n) << endl;
    
    cout << "Standard Library Approach:" 
         << sol.reverseBits_standard(n) << endl;
    
    return 0;
}