
// ----- How the password generator is suppose to work: -----
// 1. Generate MD5 hash from "abc0"
// 2. If the hash starts with 5 zeroes, save the 6th character 
//    as next character in password
// 3. Start over at step 1 and increase the number at the end of "abc"
//    so you generate MD5 hash for "abc1"
// 4. Keep going this way until you have gotten 8 characters in your password
//    In other words, you have ran in 8 MD5 hashes that starts with 5 zeroes.

// TODO:
// 1. Import a MD5 library and solve it just so that it works, without
//    optimizaion, verify that it works correctly with "abc" as example Door ID.
//    the password should be 18f47a30 according to advent of code assignent 
//    description.
// 2. Write the MD5 library myself, just so that it works
// 3. See if there is things that I can optimize about the MD5 hash generator
//    or just something else.
//    - Based on the face that we are only interested in generating MD5 hashes
//      that starts with 5 zeroes, can I make any assumptions about jumping
//      steps in incrementing the index/number at the end of Door ID?
//      so I save time by not having to generate MD5 hash with every single
//      number?

#include <stdio.h>
#include <openssl/md5.h>
#include <string.h>
#include <limits.h>

#define DOOR_ID "abc"

// MD5 hash (128-bit e.g. 16-bytes long) converted to string of hexadecimals
void md5ToHexStr(unsigned char* str, char* hexStr);

int main(int argc, char* argv[])
{
    char passwd[9] = {0}; // Initialize so all elements are nullbytes
    int pwix = 0;// pw = password, ix = index
    passwd[0] = '\0';
    long long unsigned i = 0;
    unsigned char md5Input[10000];
    unsigned char md5Hash[10000];
    char md5HashStr[10000];
    int j = 0;

    while (strlen(passwd) < 8 && i < ULLONG_MAX)
    {
        md5Input[0] = '\0';
        md5HashStr[0] = '\0';
        sprintf((char*) md5Input, "%s%llu", DOOR_ID, i++);
        //md5Hash[0] = '\0'; 
        unsigned long len = strlen((char*)md5Input);
        MD5(md5Input, len, md5Hash);
        md5ToHexStr(md5Hash, md5HashStr);
        if ((i % 500000) == 0)
            printf("j=%d i = %3llu | len = %2lu | md5Input = %10s | md5Hash = %15s\n", j, i, len, (char*)md5Input, (char*)md5HashStr);

        //if (strcmp("00000", md5HashStr) == 0)
        if (strncmp("00000", md5HashStr, 5) == 0)
        {
            printf("Found match! j = %d\n", j);
            passwd[pwix] = md5HashStr[5];
            printf("passwd = %s\n", passwd);
            pwix++;
            j++;
        }

        if (i > 99999999999999 || j == 9)//(3231928+5))
        {
            printf("passwd = %s\n", passwd);
            break;
        }
    }

    return 0;
}

void md5ToHexStr(unsigned char* str, char* hexStr)
{
    long i = 0;

    // A MD5 hash is always 128-bit long, which is 16-bytes
    for (i = 0; i < 16; ++i)
    {
        char nextHex[10];
        nextHex[0] = '\0';

        sprintf(nextHex, "%02x", str[i]);
        //printf("c* = %d, nexthex = %s\n", *c, nextHex);
        strcat(hexStr, nextHex);
    }
}
