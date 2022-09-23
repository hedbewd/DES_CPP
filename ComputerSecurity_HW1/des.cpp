// This code is my own code.
// But I refered a site that has description and algorithm of DES.
// Honestly, I followed an algorithm of the site as it is.
// https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
// This code is made by only C language.
// I think C++ language is more and more comfortable to make DES(String library or Vector library... etc.)
// , but I want to use only array to make this algorithm.
// So, maybe my code is rough and sorry for that. Let's get started.
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY 1	// available: 1 ~ 16

// Change function hexadecimal to binary system
char* text_hex_to_bin(char* hex_text, char* bin_text)
{
	char text_temp[4] = { 0 };
	for (int i = 0; i < strlen(hex_text); i++) {
		if (hex_text[i] == '0') {
			text_temp[0] = '0';
			text_temp[1] = '0';
			text_temp[2] = '0';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == '1') {
			text_temp[0] = '0';
			text_temp[1] = '0';
			text_temp[2] = '0';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == '2') {
			text_temp[0] = '0';
			text_temp[1] = '0';
			text_temp[2] = '1';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == '3') {
			text_temp[0] = '0';
			text_temp[1] = '0';
			text_temp[2] = '1';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == '4') {
			text_temp[0] = '0';
			text_temp[1] = '1';
			text_temp[2] = '0';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == '5') {
			text_temp[0] = '0';
			text_temp[1] = '1';
			text_temp[2] = '0';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == '6') {
			text_temp[0] = '0';
			text_temp[1] = '1';
			text_temp[2] = '1';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == '7') {
			text_temp[0] = '0';
			text_temp[1] = '1';
			text_temp[2] = '1';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == '8') {
			text_temp[0] = '1';
			text_temp[1] = '0';
			text_temp[2] = '0';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == '9') {
			text_temp[0] = '1';
			text_temp[1] = '0';
			text_temp[2] = '0';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == 'A') {
			text_temp[0] = '1';
			text_temp[1] = '0';
			text_temp[2] = '1';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == 'B') {
			text_temp[0] = '1';
			text_temp[1] = '0';
			text_temp[2] = '1';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == 'C') {
			text_temp[0] = '1';
			text_temp[1] = '1';
			text_temp[2] = '0';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == 'D') {
			text_temp[0] = '1';
			text_temp[1] = '1';
			text_temp[2] = '0';
			text_temp[3] = '1';
		}
		else if (hex_text[i] == 'E') {
			text_temp[0] = '1';
			text_temp[1] = '1';
			text_temp[2] = '1';
			text_temp[3] = '0';
		}
		else if (hex_text[i] == 'F') {
			text_temp[0] = '1';
			text_temp[1] = '1';
			text_temp[2] = '1';
			text_temp[3] = '1';
		}

		bin_text[i * 4] = text_temp[0];
		bin_text[i * 4 + 1] = text_temp[1];
		bin_text[i * 4 + 2] = text_temp[2];
		bin_text[i * 4 + 3] = text_temp[3];
	}

	return bin_text;
}

// Round function
char* des_function_C(char* C, int round, char* C_out)
{
	if (round == 1 || round == 2 || round == 9 || round == 16) {
		for (int i = 1; i < 28; i++) {
			C_out[i - 1] = C[i];
		}
		C_out[27] = C[0];
	}
	else {
		for (int i = 2; i < 28; i++) {
			C_out[i - 2] = C[i];
		}
		C_out[26] = C[0];
		C_out[27] = C[1];
	}

	return C_out;
}

// We can make total 16 keys. You can choice that through total_cat[0~15].
char* key_generation(char* cat, char* key)
{
	char compression_table[48] = { 14,17,11,24,1,5,3,28,15,6,21,10,23,19,12,4,26,8,16,7,27,20,13,2,41,52,31,37,47,55,30,40,51,45,
		33,48,44,49,39,56,34,53,46,42,50,36,29,32 };

	for (int i = 0; i < 48; i++) {
		key[i] = cat[compression_table[i] - 1];
	}

	return key;
}

char* init_permutation(char* plain_message, char* IP)
{
	char initial_permutation[64] = { 58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
		57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7 };

	for (int i = 0; i < 64; i++) {
		IP[i] = plain_message[initial_permutation[i] - 1];
	}

	return IP;
}

int main()
{
	// Plain text M
	char plain_text_hex[1000] = { 0 };
	printf("Enter a plain text message: ");
	scanf("%s", plain_text_hex);
	
	// Plain text hex to bin
	char plain_text_bin[10000] = { 0 };
	char* plain_text_bin2;
	
	plain_text_bin2 = text_hex_to_bin(plain_text_hex, plain_text_bin);

	printf("\nPlain text hexadecimal: ");
	printf("%s\n", plain_text_hex);
	printf("Plain text binary: ");
	printf("%s\n", plain_text_bin2);

	// Hexadecimal key K = '133457799BBCDFF1'
	char key_hex[17] = { 0 };
	key_hex[0] = '1'; key_hex[1] = '3'; key_hex[2] = '3'; key_hex[3] = '4'; key_hex[4] = '5'; key_hex[5] = '7'; key_hex[6] = '7'; key_hex[7] = '9';
	key_hex[8] = '9'; key_hex[9] = 'B'; key_hex[10] = 'B'; key_hex[11] = 'C'; key_hex[12] = 'D'; key_hex[13] = 'F'; key_hex[14] = 'F'; key_hex[15] = '1';
	
	// key K hex to bin
	char key_bin[10000] = { 0 };
	char* key_bin2;

	key_bin2 = text_hex_to_bin(key_hex, key_bin);

	printf("Hexadecimal key K hex: ");
	printf("%s\n", key_hex);
	printf("Hexadecimal key K bin: ");
	printf("%s\n", key_bin2);

	// PC-1(parity drop)
	int parity_drop[56] = { 57,49,41,33,25,17,9,1,58,50,42,34,26,18,10,2,59,51,43,35,27,19,11,3,60,52,44,36,63,55,47,39,31,23,15,7,62,54,
		46,38,30,22,14,6,61,53,45,37,29,21,13,5,28,20,12,4 };
	char key_plus[1000] = { 0 };

	for (int i = 0; i < 56; i++) {
		key_plus[i] = key_bin2[parity_drop[i]-1];
	}
	printf("\n");
	printf("Do parity drop: ");
	printf("%s\n\n", key_plus);	// 56-bit permutation
	
	// Split key_plus to C0 and D0
	char C_0[29] = { 0 };
	char D_0[29] = { 0 };
	for (int i = 0; i < 56; i++) {
		if (i < 28)
			C_0[i] = key_plus[i];
		else
			D_0[i-28] = key_plus[i];
	}
	printf("Do round\n");
	printf("C0: %s\n", C_0);
	printf("D0: %s\n\n", D_0);

	// 16 Round
	char C_output[29] = { 0 };
	char D_output[29] = { 0 };
	char* C_output2;
	char* D_output2;
	char C_output3[29] = { 0 };
	char D_output3[29] = { 0 };
	char cat_cout_dout[57] = { 0 };
	char total_cat[17][57] = { 0 };
	for (int round = 1; round < 17; round++) {
		if (round == 1) {
			C_output2 = des_function_C(C_0, round, C_output);
			D_output2 = des_function_C(D_0, round, D_output);
			printf("C%d: %s\n", round, C_output2);
			printf("D%d: %s\n", round, D_output2);
		}
		else {
			C_output2 = des_function_C(C_output3, round, C_output);
			D_output2 = des_function_C(D_output3, round, D_output);
			printf("C%d: %s\n", round, C_output2);
			printf("D%d: %s\n", round, D_output2);
		}
		for (int i = 0; i < 28; i++) {
			C_output3[i] = C_output2[i];
			D_output3[i] = D_output2[i];
		}
		for (int i = 0; i < 56; i++) {
			if (i < 28)
				cat_cout_dout[i] = C_output3[i];
			else
				cat_cout_dout[i] = D_output3[i - 28];
		}
		for (int i = 0; i < 56; i++) {
			total_cat[round - 1][i] = cat_cout_dout[i];
		}
		
		printf("\n");
	}

	// PC-2, compute Kn
	char key[100] = { 0 };
	char* key2;
	char key_final[17][100] = { 0 };

	for (int i = 0; i < 16; i++) {
		printf("C%dD%d: %s\n", i+1, i+1, total_cat[i]);	// C1D1 ~ C16D16
	}

	printf("\nKey 1 ~ 16\n");
	for (int i = 0; i < 16; i++) {
		key2 = key_generation(total_cat[i], key);
		for (int j = 0; j < 48; j++) {
			key_final[i][j] = key2[j];
		}
		printf("Key %d: %s\n", i+1, key_final[i]);
	}
	
	printf("\n");

	// Encode each 64-bit block of data
	// Init permutation
	char IP[100] = { 0 };
	char* IP2;

	IP2 = init_permutation(plain_text_bin2, IP);
	printf("IP: %s\n", IP2);
	
	// Split L0, R0
	char L0[65] = { 0 };
	char R0[65] = { 0 };

	for (int i = 0; i < 64; i++) {
		if (i < 32)
			L0[i] = IP2[i];
		else
			R0[i - 32] = IP2[i];
	}
	printf("L0: %s\n", L0);
	printf("R0: %s", R0);

	// Compute Ln, Rn round


	return 0;
}