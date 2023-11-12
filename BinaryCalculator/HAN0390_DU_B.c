/**
 * @file HAN0390_DU_B.c
 * @author Hanke Matej (HAN0390)
 * @brief Binary Enumerator
 * @version 0.1
 * @date 2023-11-10
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int c;
    int v;
    int z;
    int n;
} SymptomRegister;

int printBin(int arr[]) {
    for (int i = 0; i < 8; i++) {
        printf("%d", arr[i]);
    }
}

void castToBin(int num, int arr[]) {
    int j = 0;
    int tmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    do {
        tmp[j] = num % 2;
        j++;
        num /= 2;
    } while (num != 0);

    for (int k = 0; k <= 7; k++) {
        arr[k] = tmp[7 - k];
    }
}

void addition(int fstNum, int sndNum) {
    printf("\nFirst number (bin):\t");
    int arr1[8] = {};
    castToBin(fstNum, arr1);
    printBin(arr1);

    printf("\nSecond number (bin):\t");
    int arr2[8] = {};
    castToBin(sndNum, arr2);
    printBin(arr2);

    SymptomRegister symptoms;
    symptoms.c = 0;
    int result[8] = {};
    for (int i = 7; i >= 0; --i) {
        result[i] = arr1[i] ^ arr2[i] ^ symptoms.c;
        symptoms.c = (arr1[i] & arr2[i]) | (arr1[i] & symptoms.c) | (arr2[i] & symptoms.c);

        if (result[i] == 0) {
            symptoms.z++;
        }

        if (i == 0) {
            symptoms.v = symptoms.c;
        }
    }
    symptoms.v = symptoms.v ^ symptoms.c;
    symptoms.z = (symptoms.z == 8) ? 1 : 0;
    symptoms.n = (result[0] == 1) ? 1 : 0;

    printf("\n\t\t\t========\nResult:\t\t\t");
    printBin(result);
    printf("\nC: %d\nV: %d\nZ: %d\nN: %d\n", symptoms.c, symptoms.v, symptoms.z, symptoms.n);
}

void plus1(int array[]) {
    int carry = 0;
    int tmp[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int one[] = {0, 0, 0, 0, 0, 0, 0, 1};
    for (int i = 7; i >= 0; --i) {
        tmp[i] = array[i] ^ one[i] ^ carry;
        carry = (array[i] & one[i]) | (array[i] & carry) | (one[i] & carry);
    }
    for (int i = 0; i < 8; i++) {
        array[i] = tmp[i];
    }
}

void negate(int array[]) {
    for (int i = 0; i < 8; ++i) {
        array[i] = (array[i] == 0) ? 1 : 0;
    }
}

void twosComplement(int array[]) {
    negate(array);
    plus1(array);
}

void subtraction(int fstNum, int sndNum) {
    printf("\nFirst number (bin):\t");
    int arr1[8] = {};
    castToBin(fstNum, arr1);
    printBin(arr1);

    printf("\nSecond number (bin):\t");
    int arr2[8] = {};
    castToBin(sndNum, arr2);
    printBin(arr2);
    twosComplement(arr2);
    
    SymptomRegister symptoms;
    symptoms.c = 0;
    int result[8] = {};
    for (int i = 7; i >= 0; --i) {
        result[i] = arr1[i] ^ arr2[i] ^ symptoms.c;
        symptoms.c = (arr1[i] & arr2[i]) | (arr1[i] & symptoms.c) | (arr2[i] & symptoms.c);

        if (result[i] == 0) {
            symptoms.z++;
        }

        if (i == 0) {
            symptoms.v = symptoms.c;
        }
    }
    symptoms.v = symptoms.v ^ symptoms.c;
    symptoms.z = (symptoms.z == 8) ? 1 : 0;
    symptoms.n = (result[0] == 1) ? 1 : 0;

    if (fstNum > sndNum) {
        printf("\n\t\t\t========\nResult:\t\t\t");
        printBin(result);
    } else {
        printf("\n\t\t\t========\n\t\t\t");
        printBin(result);
        printf("\n\t\t\t________\nResult (-):\t\t");
        twosComplement(result);
        printBin(result);
    }

    printf("\nC: %d\nV: %d\nZ: %d\nN: %d\n", symptoms.c, symptoms.v, symptoms.z, symptoms.n);
}

int main(int argc, char** argv) {
    int num1;
    printf("1. Number (0 - 127): ");
    scanf("%d", &num1);

    int num2;
    printf("2. Number (0 - 127): ");
    scanf("%d", &num2);

    printf("\n1 - Addition\n");
    printf("2 - Subtraction\n");
    printf("Select operation: ");
    int option = 0;
    scanf("%d", &option);

    switch (option) {
        case 1:
            addition(num1, num2);
            break;
        case 2:
            subtraction(num1, num2);
            break;
        default:
            printf("No such operation\n");
            break;
    }

    return 0;
}