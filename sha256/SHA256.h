/**
 * @file      SHA256.h
 * @brief     SHA256�Í����N���X
 * @note      SHA256�A���S���Y���ňÍ������s���܂��B
 * @author    Yoshiteru Ishida
 * @copyright Copyright 2021 Yoshiteru Ishida
 */

#define MESSAGE_BLOCK_SIZE 64


class SHA256
{
public:
	unsigned char** padding(char* input);
	void print_block_one(unsigned char* block);
	void print_block(unsigned char** block);
	void free_block(unsigned char** block);

private:

};

