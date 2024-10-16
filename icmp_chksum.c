// this following code calculates the checksums used by icmp packets to maintian integrity of icmp payload maaximum bytes for icmp cheksums are 2bytes allocated and the icmp payload is 33 bytes

// default payload used by icmp is { !"#$%&'()*+,-./012345678 }  which is 32 bytes

#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert ASCII value to 8-bit binary
long long to_binary(int ascii_value) {
    long long binary = 0;
    int factor = 1;

    for (int i = 0; i < 8; i++) {
        binary += ((ascii_value >> i) & 1) * factor;
        factor *= 10;
    }
    return binary;
}

// Function to add two binary numbers and return the result
long long add_binary(long long bit1, long long bit2) {
    int carry = 0;
    long long result = 0, factor = 1;

    while (bit1 != 0 || bit2 != 0 || carry != 0) {
        int sum = (bit1 % 10) + (bit2 % 10) + carry;
        carry = sum / 2;
        result += (sum % 2) * factor;
        factor *= 10;
        bit1 /= 10;
        bit2 /= 10;
    }
	
   return result;
	
}

// Function to perform 1's complement on the binary number
long long ones_complement(long long binary) {
    long long complement = 0, factor = 1;

    while (binary != 0) {
        int bit = binary % 10;
        complement += (bit == 0 ? 1 : 0) * factor;
        factor *= 10;
        binary /= 10;
    }
  

    return complement;
}

// Main checksum function: processes input data
void calculate_checksum(char data[]) {
    long long checksum = 0;

    for (int i = 0; data[i] != '\0' && data[i] != '\n'; i++) {
        int ascii_value = (int)data[i];
        long long binary_value = to_binary(ascii_value);

        printf("Character: %c, ASCII: %d, Binary: %08lld\n", data[i], ascii_value, binary_value);

        // Add the binary value to the checksum
        checksum = add_binary(checksum, binary_value);
    }

    printf("Sum of all binaries: %lld\n", checksum);

    // Perform 1's complement on the checksum
    long long complement = ones_complement(checksum);

    // Print the final result in binary
    printf("1's Complement (Checksum): %lld\n",complement); 
    printf("Checksum in HEX: 0x%llx\n",complement);

}

int main() {
    char data[35];

    printf("Enter the text: ");
    fgets(data, sizeof(data), stdin);

    calculate_checksum(data);

    return 0;
}
