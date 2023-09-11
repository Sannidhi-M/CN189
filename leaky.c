client udp:
from socket import *


serverName = "127.0.0.1"
serverPort = 12000
clientSocket = socket(AF_INET, SOCK_DGRAM)


sentence = input("\nEnter file name:  ")


clientSocket.sendto(bytes(sentence,"utf-8"),(serverName, serverPort))


filecontents,serverAddress = clientSocket.recvfrom(2048)
print ('\nReply from Server:\n')
print (filecontents.decode("utf-8"))
# for i in filecontents:
    # print(str(i), end = '')
clientSocket.close()
clientSocket.close()


Server udp:
from socket import *


serverPort = 12000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(("127.0.0.1", serverPort))
print("The server is ready to receive")
while 1:
    sentence, clientAddress = serverSocket.recvfrom(2048)
    sentence = sentence.decode("utf-8")
    file = open(sentence, "r")
    con = file.read(2048)


    serverSocket.sendto(bytes(con, "utf-8"), clientAddress)


    print('\nSent contents of ', end=' ')
    print(sentence)
    #  for i in sentence:
    #  print (str(i), end = '')
    file.close()


Client tcp:
from socket import *
serverName = '127.0.0.1'
serverPort = 12000
while 1:
    clientSocket = socket(AF_INET, SOCK_STREAM)
    clientSocket.connect((serverName,serverPort))
    sentence = input("\nEnter file name: ")


    clientSocket.send(sentence.encode())
    filecontents = clientSocket.recv(1024).decode()
    print ('\nFrom Server:\n')
    print(filecontents)
    clientSocket.close()
Server:
from socket import *


serverName = "127.0.0.1"
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)
while 1:
    try:
        print("The server is ready to receive")
        connectionSocket, addr = serverSocket.accept()
        sentence = connectionSocket.recv(1024).decode()
        print(sentence)
        file = open(sentence, "r")
        l = file.read(1024)


        connectionSocket.send(l.encode())
        print('\nSent contents of ' + sentence)
        file.close()
        connectionSocket.close()
    except:
        print("No such file!")


Crc:
#include <stdio.h>
#include <string.h>


// CRC-CCITT polynomial: x^16 + x^12 + x^5 + 1 (0x1021)
//#define CRC_POLY 0x1021


// Function to perform bitwise XOR on binary strings
void binaryXOR(char *result, const char *a, const char *b) {
    for (int i = 0; i < 16; i++) {
        result[i] = (a[i] == b[i]) ? '0' : '1';
    }
    result[16] = '\0';
}


// Function to calculate CRC-CCITT checksum
void calculateCRC(const char *data, int length, char *checksum) {
    char crc[17];
    for (int i = 0; i < 16; i++) {
        crc[i] = '0';
    }
    crc[16] = '\0';


    for (int i = 0; i < length; i++) {
        for (int j = 0; j < 8; j++) {
            char msb = crc[0];
            for (int k = 0; k < 16; k++) {
                crc[k] = crc[k + 1];
            }
            crc[15] = '0';


            if (msb == '1') {
                char temp[17];
                binaryXOR(temp, crc, "10001000000100001"); // CRC_POLY in binary
                strcpy(crc, temp);
            }
        }
        crc[15] = (data[i] == '1') ? '1' : '0';
    }


    strcpy(checksum, crc);
}


void main() {
    char data[100]; // Replace with your actual data
    printf("Enter data in binary: ");
    scanf("%s", data);


    int dataLength = strlen(data);
    char checksum[17];
    calculateCRC(data, dataLength, checksum);


    printf("Calculated CRC: %s\n", checksum);


    // Concatenate the original data and the checksum
    char codeword[118]; // Assuming maximum length of data + CRC
    strcpy(codeword, data);
    strcat(codeword, checksum);


    // Display the complete codeword
    printf("Complete Codeword: %s\n", codeword);


    // Simulating error by changing a bit
    // data[2] ^= 0x01; // Uncomment this line to introduce an error


    // Verify the received data
    char receivedChecksum[17];
    printf("Enter received CRC: ");
    scanf("%s", receivedChecksum);


    if (strcmp(receivedChecksum, checksum) == 0)
        printf("Data is error-free.\n");
    else
        printf("Data contains errors.\n");
}


Leaky
#include <stdio.h>


int main() {
    int incoming, outgoing, bucket_size, n, store = 0;


    // Prompt the user to enter bucket size, outgoing rate, and the number of inputs
    printf("Enter bucket size, outgoing rate, and number of inputs: ");
    scanf("%d %d %d", &bucket_size, &outgoing, &n);


    // Loop to process incoming packets
    while (n != 0) {
        // Prompt the user to enter the size of the incoming packet
        printf("Enter the incoming packet size: ");
        scanf("%d", &incoming);


        printf("Incoming packet size: %d\n", incoming);


        if (incoming <= (bucket_size - store)) {
            // If the incoming packet can be accommodated in the bucket buffer
            store += incoming;
            printf("Bucket buffer size: %d out of %d\n", store, bucket_size);
        } else {
            // If the incoming packet would cause an overflow
            printf("Dropped %d packets\n", incoming - (bucket_size - store));
            printf("Bucket buffer size: %d out of %d\n", store, bucket_size);
            store = bucket_size;  // The buffer is considered full
        }


        // Remove outgoing packets from the buffer to simulate transmission
        store = store - outgoing;
        printf("After outgoing: %d packets left out of %d in buffer\n", store, bucket_size);


        // Decrement the loop counter
        n--;
    }


    return 0;
}