#pragma once

#ifndef RSAHEADER_H
#define RSAHEADER_H

#define ALPHABET_INDEX_RU_LEN      32
#define ALPHABET_INDEX_EN_LEN      26
#define ALPHABET_INDEX_SYMBOL_LEN      3
#define MAX_MSG_LEN 100


int* replace_char(char* msg, int msgSize)
{
	int* temp = new int[msgSize];
	for (int i = 0; i < msgSize; i++)
	{
		if (msg[i] == 'à' || msg[i] == 'À') { temp[i] = 10; }
		else if (msg[i] == 'á' || msg[i] == 'Á') { temp[i] = 11; }
		else if (msg[i] == 'â' || msg[i] == 'Â') { temp[i] = 12; }
		else if (msg[i] == 'ã' || msg[i] == 'Ã') { temp[i] = 13; }
		else if (msg[i] == 'ä' || msg[i] == 'Ä') { temp[i] = 14; }
		else if (msg[i] == 'å' || msg[i] == 'Å') { temp[i] = 15; }
		else if (msg[i] == 'æ' || msg[i] == 'Æ') { temp[i] = 16; }
		else if (msg[i] == 'ç' || msg[i] == 'Ç') { temp[i] = 17; }
		else if (msg[i] == 'è' || msg[i] == 'È') { temp[i] = 18; }
		else if (msg[i] == 'é' || msg[i] == 'É') { temp[i] = 19; }
		else if (msg[i] == 'ê' || msg[i] == 'Ê') { temp[i] = 20; }
		else if (msg[i] == 'ë' || msg[i] == 'Ë') { temp[i] = 21; }
		else if (msg[i] == 'ì' || msg[i] == 'Ì') { temp[i] = 22; }
		else if (msg[i] == 'í' || msg[i] == 'Í') { temp[i] = 23; }
		else if (msg[i] == 'î' || msg[i] == 'Î') { temp[i] = 24; }
		else if (msg[i] == 'ï' || msg[i] == 'Ï') { temp[i] = 25; }
		else if (msg[i] == 'ð' || msg[i] == 'Ð') { temp[i] = 26; }
		else if (msg[i] == 'ñ' || msg[i] == 'Ñ') { temp[i] = 27; }
		else if (msg[i] == 'ò' || msg[i] == 'Ò') { temp[i] = 28; }
		else if (msg[i] == 'ó' || msg[i] == 'Ó') { temp[i] = 29; }
		else if (msg[i] == 'ô' || msg[i] == 'Ô') { temp[i] = 30; }
		else if (msg[i] == 'õ' || msg[i] == 'Õ') { temp[i] = 31; }
		else if (msg[i] == 'ö' || msg[i] == 'Ö') { temp[i] = 32; }
		else if (msg[i] == '÷' || msg[i] == '×') { temp[i] = 33; }
		else if (msg[i] == 'ø' || msg[i] == 'Ø') { temp[i] = 34; }
		else if (msg[i] == 'ù' || msg[i] == 'Ù') { temp[i] = 35; }
		else if (msg[i] == 'ú' || msg[i] == 'Ú') { temp[i] = 36; }
		else if (msg[i] == 'û' || msg[i] == 'Û') { temp[i] = 37; }
		else if (msg[i] == 'ü' || msg[i] == 'Ü') { temp[i] = 38; }
		else if (msg[i] == 'ý' || msg[i] == 'Ý') { temp[i] = 39; }
		else if (msg[i] == 'þ' || msg[i] == 'Þ') { temp[i] = 40; }
		else if (msg[i] == 'ÿ' || msg[i] == 'ß') { temp[i] = 41; }
		else if (msg[i] == 'a' || msg[i] == 'A') { temp[i] = 42; }
		else if (msg[i] == 'b' || msg[i] == 'B') { temp[i] = 43; }
		else if (msg[i] == 'c' || msg[i] == 'C') { temp[i] = 44; }
		else if (msg[i] == 'd' || msg[i] == 'D') { temp[i] = 45; }
		else if (msg[i] == 'e' || msg[i] == 'E') { temp[i] = 46; }
		else if (msg[i] == 'f' || msg[i] == 'F') { temp[i] = 47; }
		else if (msg[i] == 'g' || msg[i] == 'G') { temp[i] = 48; }
		else if (msg[i] == 'h' || msg[i] == 'H') { temp[i] = 49; }
		else if (msg[i] == 'i' || msg[i] == 'I') { temp[i] = 50; }
		else if (msg[i] == 'j' || msg[i] == 'J') { temp[i] = 51; }
		else if (msg[i] == 'k' || msg[i] == 'K') { temp[i] = 52; }
		else if (msg[i] == 'l' || msg[i] == 'L') { temp[i] = 53; }
		else if (msg[i] == 'm' || msg[i] == 'M') { temp[i] = 54; }
		else if (msg[i] == 'n' || msg[i] == 'N') { temp[i] = 55; }
		else if (msg[i] == 'o' || msg[i] == 'O') { temp[i] = 56; }
		else if (msg[i] == 'p' || msg[i] == 'P') { temp[i] = 57; }
		else if (msg[i] == 'q' || msg[i] == 'Q') { temp[i] = 58; }
		else if (msg[i] == 'r' || msg[i] == 'R') { temp[i] = 59; }
		else if (msg[i] == 's' || msg[i] == 'S') { temp[i] = 60; }
		else if (msg[i] == 't' || msg[i] == 'T') { temp[i] = 61; }
		else if (msg[i] == 'u' || msg[i] == 'U') { temp[i] = 62; }
		else if (msg[i] == 'v' || msg[i] == 'V') { temp[i] = 63; }
		else if (msg[i] == 'w' || msg[i] == 'W') { temp[i] = 64; }
		else if (msg[i] == 'x' || msg[i] == 'X') { temp[i] = 65; }
		else if (msg[i] == 'y' || msg[i] == 'Y') { temp[i] = 66; }
		else if (msg[i] == 'z' || msg[i] == 'Z') { temp[i] = 67; }
		else if (msg[i] == ' ') { temp[i] = 68; }
		else if (msg[i] == ',') { temp[i] = 69; }
		else if (msg[i] == '.') { temp[i] = 70; }

	}
	return temp;
}

char* inv_replace_char(int* arrayOfNumber, int msgSize)
{
	char* ReverseConversion = new char[msgSize];
	//memset(&ReverseConversion[0], 0, sizeof(ReverseConversion));
	for (int i = 0; i < msgSize; i++)
	{
		if (arrayOfNumber[i] == 10) { ReverseConversion[i] = 'À'; }
		else if (arrayOfNumber[i] == 11) { ReverseConversion[i] = 'Á'; }
		else if (arrayOfNumber[i] == 12) { ReverseConversion[i] = 'Â'; }
		else if (arrayOfNumber[i] == 13) { ReverseConversion[i] = 'Ã'; }
		else if (arrayOfNumber[i] == 14) { ReverseConversion[i] = 'Ä'; }
		else if (arrayOfNumber[i] == 15) { ReverseConversion[i] = 'Å'; }
		else if (arrayOfNumber[i] == 16) { ReverseConversion[i] = 'Æ'; }
		else if (arrayOfNumber[i] == 17) { ReverseConversion[i] = 'Ç'; }
		else if (arrayOfNumber[i] == 18) { ReverseConversion[i] = 'È'; }
		else if (arrayOfNumber[i] == 19) { ReverseConversion[i] = 'É'; }
		else if (arrayOfNumber[i] == 20) { ReverseConversion[i] = 'Ê'; }
		else if (arrayOfNumber[i] == 21) { ReverseConversion[i] = 'Ë'; }
		else if (arrayOfNumber[i] == 22) { ReverseConversion[i] = 'Ì'; }
		else if (arrayOfNumber[i] == 23) { ReverseConversion[i] = 'Í'; }
		else if (arrayOfNumber[i] == 24) { ReverseConversion[i] = 'Î'; }
		else if (arrayOfNumber[i] == 25) { ReverseConversion[i] = 'Ï'; }
		else if (arrayOfNumber[i] == 26) { ReverseConversion[i] = 'Ð'; }
		else if (arrayOfNumber[i] == 27) { ReverseConversion[i] = 'Ñ'; }
		else if (arrayOfNumber[i] == 28) { ReverseConversion[i] = 'Ò'; }
		else if (arrayOfNumber[i] == 29) { ReverseConversion[i] = 'Ó'; }
		else if (arrayOfNumber[i] == 30) { ReverseConversion[i] = 'Ô'; }
		else if (arrayOfNumber[i] == 31) { ReverseConversion[i] = 'Õ'; }
		else if (arrayOfNumber[i] == 32) { ReverseConversion[i] = 'Ö'; }
		else if (arrayOfNumber[i] == 33) { ReverseConversion[i] = '×'; }
		else if (arrayOfNumber[i] == 34) { ReverseConversion[i] = 'Ø'; }
		else if (arrayOfNumber[i] == 35) { ReverseConversion[i] = 'Ù'; }
		else if (arrayOfNumber[i] == 36) { ReverseConversion[i] = 'Ú'; }
		else if (arrayOfNumber[i] == 37) { ReverseConversion[i] = 'Û'; }
		else if (arrayOfNumber[i] == 38) { ReverseConversion[i] = 'Ü'; }
		else if (arrayOfNumber[i] == 39) { ReverseConversion[i] = 'Ý'; }
		else if (arrayOfNumber[i] == 40) { ReverseConversion[i] = 'Þ'; }
		else if (arrayOfNumber[i] == 41) { ReverseConversion[i] = 'ß'; }
		else if (arrayOfNumber[i] == 42) { ReverseConversion[i] = 'A'; }
		else if (arrayOfNumber[i] == 43) { ReverseConversion[i] = 'B'; }
		else if (arrayOfNumber[i] == 44) { ReverseConversion[i] = 'C'; }
		else if (arrayOfNumber[i] == 45) { ReverseConversion[i] = 'D'; }
		else if (arrayOfNumber[i] == 46) { ReverseConversion[i] = 'E'; }
		else if (arrayOfNumber[i] == 47) { ReverseConversion[i] = 'F'; }
		else if (arrayOfNumber[i] == 48) { ReverseConversion[i] = 'G'; }
		else if (arrayOfNumber[i] == 49) { ReverseConversion[i] = 'H'; }
		else if (arrayOfNumber[i] == 50) { ReverseConversion[i] = 'I'; }
		else if (arrayOfNumber[i] == 51) { ReverseConversion[i] = 'J'; }
		else if (arrayOfNumber[i] == 52) { ReverseConversion[i] = 'K'; }
		else if (arrayOfNumber[i] == 53) { ReverseConversion[i] = 'L'; }
		else if (arrayOfNumber[i] == 54) { ReverseConversion[i] = 'M'; }
		else if (arrayOfNumber[i] == 55) { ReverseConversion[i] = 'N'; }
		else if (arrayOfNumber[i] == 56) { ReverseConversion[i] = 'O'; }
		else if (arrayOfNumber[i] == 57) { ReverseConversion[i] = 'P'; }
		else if (arrayOfNumber[i] == 58) { ReverseConversion[i] = 'Q'; }
		else if (arrayOfNumber[i] == 59) { ReverseConversion[i] = 'R'; }
		else if (arrayOfNumber[i] == 60) { ReverseConversion[i] = 'S'; }
		else if (arrayOfNumber[i] == 61) { ReverseConversion[i] = 'T'; }
		else if (arrayOfNumber[i] == 62) { ReverseConversion[i] = 'U'; }
		else if (arrayOfNumber[i] == 63) { ReverseConversion[i] = 'V'; }
		else if (arrayOfNumber[i] == 64) { ReverseConversion[i] = 'W'; }
		else if (arrayOfNumber[i] == 65) { ReverseConversion[i] = 'X'; }
		else if (arrayOfNumber[i] == 66) { ReverseConversion[i] = 'Y'; }
		else if (arrayOfNumber[i] == 67) { ReverseConversion[i] = 'Z'; }
		else if (arrayOfNumber[i] == 68) { ReverseConversion[i] = ' '; }
		else if (arrayOfNumber[i] == 69) { ReverseConversion[i] = ','; }
		else if (arrayOfNumber[i] == 70) { ReverseConversion[i] = '.'; }
	}
	return ReverseConversion;
}
#endif