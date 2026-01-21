#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool states[8]; // State array

int decToBinStates(int dec){
    for (int i = 0; i < sizeof(states); i++) {
        states[i]=dec%2;
        dec=dec/2;
    }
}

int binToDec(bool bin[3]){
    int dec = 0;
    for (int i = 0; i < 3; i++) {
        if(bin[i] == 1) {
            dec += (1 << (2 - i));
        }
    }
    return dec;
}

void getNextLine(bool *nextLine, bool *currentLine, int lenght){
    bool triplet[3];
    lenght=lenght*10; //Lazy and expensive but works
    
    //TODO: border problem, implement best solution for output to look clean
    for (int i = 0; i < lenght; i++){
        triplet[1] = currentLine[i];
        if(i==0) triplet[0]=triplet[1];
        else triplet[0] = currentLine[i-1];
        if(i==lenght-1) triplet[2]=triplet[1];
        else triplet[2] = currentLine[i+1];      
        nextLine[i] = states[binToDec(triplet)];
    }
}

int main(int argc, char const *argv[]){

    int lenght, height;
    printf("Enter lenght: ");
    scanf("%d", &lenght);
    printf("Enter height: ");
    scanf("%d", &height);

    int rule;
    printf("Enter a number between 0 and 255: ");
    scanf("%d", &rule); 
    if(rule<0 || rule>255) return -1;
    else decToBinStates(rule);

    bool *currentLine = malloc (lenght); // Current line holder
    bool *nextLine = malloc (lenght); // Next line holder
    
    // Initialize first line - single 1 in the middle
    for (int i = 0; i < lenght; i++) {
        currentLine[i] = 0;
    }
    currentLine[lenght / 2] = 1;

    for (int j = 0; j < height; j++) {
        // Print current line
        for (int i = 0; i < lenght; i++) {
            printf("%c", currentLine[i] ? '#':'.');
        }
        printf("\n");
        
        // Calculate next line
        getNextLine(nextLine, currentLine, lenght);
        
        // Copy next line to current line for next iteration
        for (int i = 0; i < lenght; i++) {
            currentLine[i] = nextLine[i];
        }
    }
    return 0;
}