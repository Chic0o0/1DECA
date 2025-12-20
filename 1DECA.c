#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 100
bool states[8]; // State array
bool currentLine[LINE_LENGTH]; // Current line holder

void changeState(int pos){
    states[pos] = 1;
}

int decToBinStates(int dec){
    for (int i = 0; i < 8; i++) {
        states[i]=dec%2;
        dec=dec/2;
    }
}

int binToDec(bool bin[3]){
    int dec = 0;
    for (int i = 0; i < 3; i++) {
        if(bin[i] == 1) {
            dec += (1 << (2 - i)); // Fixed: proper binary to decimal conversion
        }
    }
    return dec;
}

void getNextLine(bool nextLine[LINE_LENGTH], bool currentLine[LINE_LENGTH]){
    bool triplet[3];
    
    for (int i = 0; i < LINE_LENGTH; i++){
        triplet[1] = currentLine[i];
        if(i==0) triplet[0]=triplet[1];
        else triplet[0] = currentLine[i-1];
        if(i==LINE_LENGTH-1) triplet[2]=triplet[1];
        else triplet[2] = currentLine[i+1];      
        nextLine[i] = states[binToDec(triplet)];
    }
}

int main(int argc, char const *argv[]){
    int rule;
    printf("Enter a number between 0 and 255: ");
    scanf("%d", &rule); 
    if(rule<0 || rule>255) return -1;
    else decToBinStates(rule);
    
    // Initialize first line - single 1 in the middle
    for (int i = 0; i < LINE_LENGTH; i++) {
        currentLine[i] = 0;
    }
    currentLine[LINE_LENGTH / 2] = 1;

    for (int j = 0; j < LINE_LENGTH; j++) {
        // Print current line
        for (int i = 0; i < LINE_LENGTH; i++) {
            printf("%c", currentLine[i] ? '#':'.');
        }
        printf("\n");
        
        // Calculate next line
        bool nextLine[LINE_LENGTH];
        getNextLine(nextLine, currentLine);
        
        // Copy next line to current line for next iteration
        for (int i = 0; i < LINE_LENGTH; i++) {
            currentLine[i] = nextLine[i];
        }
    }
    
    return 0;
}