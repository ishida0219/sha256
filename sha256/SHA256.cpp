/**
 * @file      SHA256.cpp
 * @brief     SHA256�Í����N���X
 * @note      SHA256�A���S���Y���ňÍ������s���܂��B
 * @author    Yoshiteru Ishida
 * @copyright Copyright 2021 Yoshiteru Ishida
 */

#include <iostream>
#include <iomanip> 
#include "SHA256.h"


#define MESSAGE_BLOCK_SIZE 64

/**
	�p�f�B���O����

	�������e�F���̓f�[�^��64�o�C�g���Ƃɕ������A�Ō�̃u���b�N�Ƀr�b�g����ǉ����܂��B
	�u���b�N�͓��I�Ƀ��������m�ۂ��܂��B�u���b�N���g�p���I������烁�������J������K�v������܂��B

	�����F���̓f�[�^
	�߂�l�F�u���b�N�z��
*/
unsigned char** SHA256::padding(char* input) {

	//	���̓f�[�^�̒������擾����
	int intLength = strlen(input);

	//	�U�蕪����u���b�N�̌����v�Z����
	//	(MESSAGE_BLOCK_SIZE-1)�͐؂�グ�̂��߂ɕK�v
	int intBlock = (intLength + 9 + (MESSAGE_BLOCK_SIZE - 1)) / MESSAGE_BLOCK_SIZE;
	std::cout << "block:" << intBlock << std::endl;

	//	�u���b�N�����̃|�C���^���m�ۂ���
	unsigned char** output = (unsigned char**)malloc(sizeof(char*) * (intBlock + 1));

	int intP = 0;
	for (int intI = 0; intI < intBlock; intI++) {

		//	�u���b�N�����̃��������m�ۂ���
		output[intI] = (unsigned char*)malloc(sizeof(char) * MESSAGE_BLOCK_SIZE);

		//	�R�s�[���钷�����v�Z����
		int intCopyLength = intLength - intP;

		//	�R�s�[���钷�����u���b�N���𒴂���ꍇ�̓u���b�N����ݒ肷��
		if (intCopyLength > MESSAGE_BLOCK_SIZE) {
			intCopyLength = MESSAGE_BLOCK_SIZE;
		}
		else {
			//	�R�s�[���钷�����}�C�i�X�̏ꍇ��0�Ƃ���
			if (intCopyLength < 0) {
				intCopyLength = 0;
			}
		}

		//	�R�s�[���钷�����u���b�N���Z���ꍇ
		if (intCopyLength < MESSAGE_BLOCK_SIZE) {
			//	�u���b�N���N���A����
			memset(output[intI], NULL, sizeof(char) * MESSAGE_BLOCK_SIZE);
		}

		//	���̓f�[�^���R�s�[����ꍇ
		if (intCopyLength > 0) {
			//	���ۂɃf�[�^���R�s�[����
			memcpy(output[intI], &input[intP], sizeof(char) * intCopyLength);

			//	�R�s�[�������������b�Z�[�W�u���b�N��菬�����ꍇ�̓R�s�[����������̏I�[��0x80������
			if (intCopyLength < MESSAGE_BLOCK_SIZE) {
				output[intI][intCopyLength] = 0x80;
			}
		}

		//	���̓f�[�^���R�s�[���Ȃ��ꍇ
		else {
			//	���̓f�[�^�̒�����MESSAGE_BLOCK_SIZE�Ŋ���؂��ꍇ��0x80��ǉ��ł��Ă��Ȃ����ߍŌ�̃u���b�N�̐擪�ɒǉ�����
			if (intLength % MESSAGE_BLOCK_SIZE == 0) {
				output[intI][0] = 0x80;
			}
		}

		//	�Ō�̃u���b�N�̏ꍇ
		if (intI == intBlock - 1) {
			//	�Ō�̂S�o�C�g�ɕ����񒷁i�r�b�g�j������
			int intBitLength = intLength * 8;

			std::cout << "bit:" << intBitLength << std::endl;
			output[intI][MESSAGE_BLOCK_SIZE - 4] = (unsigned char)(intBitLength >> 24 & (unsigned char)0xff);
			output[intI][MESSAGE_BLOCK_SIZE - 3] = (unsigned char)(intBitLength >> 16 & (unsigned char)0xff);
			output[intI][MESSAGE_BLOCK_SIZE - 2] = (unsigned char)(intBitLength >> 8 & (unsigned char)0xff);
			output[intI][MESSAGE_BLOCK_SIZE - 1] = (unsigned char)(intBitLength & (unsigned char)0xff);
		}

		intP = intP + MESSAGE_BLOCK_SIZE;
	}

	//	�u���b�N�z��̍Ō��NULL������
	output[intBlock] = NULL;

	std::cout << std::endl;

	return output;
}

void SHA256::print_block_one(unsigned char* block) {
	for (int intJ = 0; intJ < MESSAGE_BLOCK_SIZE; intJ++) {
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned short int)(block[intJ]);

		if (intJ % 4 == 3) {
			std::cout << " ";
		}
		if (intJ % 32 == 31) {
			std::cout << std::endl;
		}
	}
	std::cout << std::dec;
}

void SHA256::print_block(unsigned char** block) {
	int intI = 0;
	while (block[intI] != NULL) {
		std::cout << intI << ":" << std::endl;

		print_block_one(block[intI]);

		for (int intJ = 0; intJ < MESSAGE_BLOCK_SIZE; intJ++) {
			if (block[intI][intJ] >= 0x20 && block[intI][intJ] < 0x80) {
				std::cout << (block[intI][intJ]) << " ";
			}
			else {
				std::cout << ". ";
			}

			if (intJ % 4 == 3) {
				std::cout << " ";
			}
			if (intJ % 32 == 31) {
				std::cout << std::endl;
			}
		}

		std::cout << std::endl;
		std::cout << std::endl;

		intI++;
	}
}

void SHA256::free_block(unsigned char** block) {
	int intI = 0;
	while (block[intI] != NULL) {
		free(block[intI]);
		intI++;
	}
	free(block);
}

void SHA256::print_hex(unsigned int i) {
	unsigned int h;

	h = (i & 0xff000000) >> 24;
	std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned short int)(h);

	h = (i & 0x00ff0000) >> 16;
	std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned short int)(h);

	h = (i & 0x0000ff00) >> 8;
	std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned short int)(h);

	h = (i & 0x000000ff);
	std::cout << std::hex << std::setw(2) << std::setfill('0') << (unsigned short int)(h);
}

void SHA256::print_bin(unsigned int i) {
	unsigned int h;

	h = i;
	for (int intI = 0; intI < 32; intI++) {
		if ((h & 0x80000000) == 0x00000000UL) {
			std::cout << "0";
		}
		else {
			std::cout << "1";
		}
		h = h << 1;
	}
}

void SHA256::print_hash(unsigned int* H) {

	for (int intI = 0; intI < INIT_HASH_LENGTH; intI++) {
		print_hex(H[intI]);
		std::cout << " ";
	}

	std::cout << std::endl;
}

void SHA256::compute(unsigned char** block, unsigned int* H) {

	std::cout << "sha256_cpu" << std::endl;

	//	���b�Z�[�W�̌����J�E���g����
	int N = 0;
	while (block[N] != NULL) {
		N++;
	}

	unsigned int W[MESSAGE_BLOCK_SIZE];

	//	H������������
	memcpy(H, H0, sizeof(int) * INIT_HASH_LENGTH);

	//	���b�Z�[�W�������[�v����
	for (int i = 0; i < N; i++) {
		//	�ϐ���`
		unsigned int a, b, c, d, e, f, g, h, s0, s1, T1, T2;

		std::cout << std::dec << i << std::endl;

		//	1. Prepare the message schedule, { Wt }:
		char* msg = (char*)block[i];
		print_block_one(block[i]);

		for (int t = 0; t < MESSAGE_BLOCK_SIZE; t++) {
			if (t < 16) {
				int p = t * 4;
				std::cout << std::dec << "+++" << p << std::endl;
				print_bin(msg[p] << 24);
				std::cout << std::endl;
				print_bin(msg[p + 1] << 16);
				std::cout << std::endl;
				print_bin(msg[p + 2] << 8);
				std::cout << std::endl;
				print_bin(msg[p + 3]);
				std::cout << std::endl;

				W[t] = (unsigned int)((msg[p] & 0xff) << 24) | (unsigned int)((msg[p + 1] & 0xff) << 16) | (unsigned int)((msg[p + 2] & 0xff) << 8) | (unsigned int)(msg[p + 3] & 0xff);
				print_bin(W[t]);
				std::cout << std::endl;
			}
			else {

				std::cout << std::dec << "---" << t << std::endl;

				print_bin(W[(t - 2)]);
				std::cout << std::endl;

				print_bin(ROTR(W[(t - 2)], 17));
				std::cout << std::endl;

				print_bin(ROTR(W[(t - 2)], 19));
				std::cout << std::endl;

				print_bin(SHR(W[(t - 2)], 10));
				std::cout << std::endl;

				W[t] = sigma1(W[(t - 2)]) + W[(t - 7)] + sigma0(W[(t - 15)]) + W[(t - 16)];

				print_bin(W[t]);
				std::cout << std::endl;

			}
		}

		std::cout << "W:" << std::endl;
		for (int t = 0; t < MESSAGE_BLOCK_SIZE; t++) {
			std::cout << std::setw(2) << std::setfill('0') << std::dec << t << ":";
			print_bin(W[t]);
			std::cout << std::endl;
		}
		std::cout << std::endl;

		//	2. Initialize the eight working variables, a, b, c, d, e, f, g, and h, with the (i-1)st hash value:
		a = H[0];
		b = H[1];
		c = H[2];
		d = H[3];
		e = H[4];
		f = H[5];
		g = H[6];
		h = H[7];

		//	3. For t=0 to 63:
		for (int t = 0; t < MESSAGE_BLOCK_SIZE; t++) {


			T1 = h + SIGMA1(e) + Ch(e, f, g) + K[t] + W[t];
			T2 = SIGMA0(a) + Maj(a, b, c);

			h = g;
			g = f;
			f = e;
			e = d + T1;
			d = c;
			c = b;
			b = a;
			a = T1 + T2;
		}

		//	4. Compute the ith intermediate hash value H(i):
		H[0] = (a + H[0]) & 0xffffffff;
		H[1] = (b + H[1]) & 0xffffffff;
		H[2] = (c + H[2]) & 0xffffffff;
		H[3] = (d + H[3]) & 0xffffffff;
		H[4] = (e + H[4]) & 0xffffffff;
		H[5] = (f + H[5]) & 0xffffffff;
		H[6] = (g + H[6]) & 0xffffffff;
		H[7] = (h + H[7]) & 0xffffffff;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
