#include <stdio.h>
#include <string.h>

int main() {
    int no_of_queries = 4; // Total number of times bucket content is checked
    int storage = 0; // Initial packets in the bucket
    int bucket_size = 10; // Total number of packets that can be accommodated in the bucket
    int input_pkt_size = 4; // Number of packets that enter the bucket at a time
    int output_pkt_size = 1; // Number of packets that exit the bucket at a time
    int size_left; // Space left in the bucket

    for (int i = 0; i < no_of_queries; i++) {
        size_left = bucket_size - storage;

        if (input_pkt_size <= size_left) {
            // Update storage
            storage += input_pkt_size;
            printf("Buffer size = %d out of bucket size = %d\n", storage, bucket_size);
        } else {
            printf("Packet loss = %d\n", input_pkt_size - size_left);
            // Full size
            storage = bucket_size;
            printf("Buffer size = %d out of bucket size = %d\n", storage, bucket_size);
        }

        // Remove packets from the bucket
        storage -= output_pkt_size;
    }

    return 0;
}