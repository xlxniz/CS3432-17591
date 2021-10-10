#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "tokenizer.h"
#include "memory.h"

int32_t* reg;
void init_regs();
bool interpret(char* instr);
//void write_read_demo();

//Initialize register array for usage.
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}

//Prints registers
void print_regs(){
	int col_size = 10;
	for(int i = 0; i < 8; i++){
		printf("X%02i:%.*lld", i, col_size, (long long int) reg[i]);
		printf(" X%02i:%.*lld", i+8, col_size, (long long int) reg[i+8]);
		printf(" X%02i:%.*lld", i+16, col_size, (long long int) reg[i+16]);
		printf(" X%02i:%.*lld\n", i+24, col_size, (long long int) reg[i+24]);
	}
}

//Checks if two strings are equal
bool compare_tokens(char* str1, char* str2){
	int i = 0;
	int j = 0;
	while(str1[i] != '\0' || str2[j] != '\0'){
		if(str1[i] != str2[j]) {
			return false;
		}
		if(str1[i] != '\0') {
		 ++i;
	 	}
		if(str2[j] != '\0') {
			++j;
		}
	}
	if(j == i) {
		 return true;
	}
	return false;
}
//find instruction type
int find_type(char* instruction){
	if(compare_tokens(instruction, "LW")) {
		return 0;
	}
	if(compare_tokens(instruction, "SW")) {
		return 1;
	}
	if(compare_tokens(instruction, "ADD")) {
		return 2;
	}
	if(compare_tokens(instruction, "ADDI")) {
		return 3;
	}
	if(compare_tokens(instruction, "AND")) {
		return 4;
	}
	if(compare_tokens(instruction, "OR")) {
		return 5;
	}
	if(compare_tokens(instruction, "XOR")) {
		return 6;
	}
	return -1;
}

//decimal to hex
int32_t to_hex(int decimal){
	char hexstring[32];
	printf("\n");
	return (int32_t)strtol(hexstring, NULL, 16);
}

 //Interprets user input to execute RV32 instructions

bool interpret(char* instr){
	int count = count_tokens(instr);
  char** token = tokenize(instr);
	int type = find_type(token[0]);

	//
	switch(type){
		//LW
		case 0: {
			token[1]++;
			token[3]++;
			int32_t mem_address = atoi(token[2]);
			//printf("Memory address: %d", mem_address);
			int32_t read_data = read_address(to_hex(mem_address), "mem.txt");
			reg[atoi(token[1])] = read_data;
			token[1]--;
			token[3]--;
			break;
		}
		//SW
		case 1: {
			token[1]++;
			token[3]++;
			int32_t mem_address = atoi(token[2]);
			write_address(reg[atoi(token[1])], to_hex(mem_address), "mem.txt");
			token[1]--;
			token[3]--;
			break;
		}
		//ADD
		case 2:
			token[1]++;
			token[2]++;
			token[3]++;
			reg[atoi(token[1])] = reg[atoi(token[2])] + reg[atoi(token[3])];
			token[1]--;
			token[2]--;
			token[3]--;
			break;
		//ADDI
		case 3:
			token[1]++;
			token[2]++;
			reg[atoi(token[1])] = reg[atoi(token[2])] + atoi(token[3]);
			token[1]--;
			token[2]--;
			break;
		//AND
		case 4:
			token[1]++;
			token[2]++;
			token[3]++;
			reg[atoi(token[1])] = reg[atoi(token[2])] + reg[atoi(token[3])];
			token[1]--;
			token[2]--;
			token[3]--;
			break;
		//OR
		case 5:
			token[1]++;
			token[2]++;
			token[3]++;
			reg[atoi(token[1])] = reg[atoi(token[2])] + reg[atoi(token[3])];
			token[1]--;
			token[2]--;
			token[3]--;
			break;
		//XOR
		case 6:
			token[1]++;
			token[2]++;
			token[3]++;
			reg[atoi(token[1])] = reg[atoi(token[2])] + reg[atoi(token[3])];
			token[1]--;
			token[2]--;
			token[3]--;
			break;
		//ERROR
		case -1:
			printf("Invalid instruction");
			break;
	}
	for(int i = 0; i < count; ++i){
		printf("Token[%d]: %s\n", i, token[i]);
	}
	return 0;
}
/*
void write_read_demo() {
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}
*/

int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE
	//write_read_demo();

	printf("\nRV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'Ctrl + c' character to end program\n");

	char* instruction = malloc(1000 * sizeof(char));
	bool is_null = false;
	// fgets() returns null if EOF is reached.
	is_null = fgets(instruction, 1000, stdin) == NULL;
	printf("\n");
	while(!is_null){
		interpret(instruction);
		printf("\n");
		print_regs();
		printf("\nEnter next or 'Ctrl + c' to end program\n");

		is_null = fgets(instruction, 1000, stdin) == NULL;
	}
	printf("ADIOS");
	return 0;
}
