#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define LINE_LENGTH 100
bool states[8]; // State array
bool currentLine[LINE_LENGTH]; // Current line holder

void changeState(int pos){
    states[pos] = 1;
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
        // Handle boundaries (wrap-around or fixed boundaries)
        if(i == 0) {
            triplet[0] = 0; // Fixed: left boundary as 0
        } else {
            triplet[0] = currentLine[i-1];
        }
        
        triplet[1] = currentLine[i];
        
        if(i == 19) {
            triplet[2] = 0; // Fixed: right boundary as 0
        } else {
            triplet[2] = currentLine[i+1];
        }
        
        nextLine[i] = states[binToDec(triplet)];
    }
}

int main(int argc, char const *argv[]){
    // Initialize states - rule 100 (1D elementary cellular automaton)
    states[0] = 0; // 000
    states[1] = 1; // 001
    states[2] = 1; // 010
    states[3] = 1; // 011
    states[4] = 0; // 100
    states[5] = 1; // 101
    states[6] = 1; // 110
    states[7] = 0; // 111
    
    // Initialize first line - single 1 in the middle
    for (int i = 0; i < LINE_LENGTH; i++) {
        currentLine[i] = 0;
    }
    currentLine[LINE_LENGTH / 2] = 1; // Center position
    
    for (int j = 0; j < LINE_LENGTH; j++) {
        // Print current line
        for (int i = 0; i < LINE_LENGTH; i++) {
            printf("%c", currentLine[i] ? '#' : ' ');
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