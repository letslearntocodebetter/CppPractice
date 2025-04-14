// Algorithm Design
// Use two pointers:
// readIndex: Scans through the original array
// writeIndex: Marks the position where we write the compressed result
// For each unique character:
// Count consecutive occurrences
// Write the character at writeIndex and increment it
// If count > 1, convert it to string and write each digit at subsequent positions
// The final value of writeIndex will be the new length of the compressed array

int compress(vector<char>& chars) {
        // Edge case: empty array
        if (chars.empty()) return 0;
        
        int writeIndex = 0;  // Position where we write compressed characters
        int readIndex = 0;   // Position where we read from original array
        
        while (readIndex < chars.size()) {
            char currentChar = chars[readIndex];
            int count = 0;
            
            // Count consecutive occurrences of the current character
            while (readIndex < chars.size() && chars[readIndex] == currentChar) {
                readIndex++;
                count++;
            }
            
            // Write the character
            chars[writeIndex++] = currentChar;
            
            // If count > 1, write the count digits
            if (count > 1) {
                // Convert count to string and write each digit
                string countStr = to_string(count);
                for (char digit : countStr) {
                    chars[writeIndex++] = digit;
                }
            }
        }
        
        // Return the new length of the compressed array
        return writeIndex;
    }
