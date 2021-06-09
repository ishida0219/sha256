#include <iostream>
#include "SHA256.h"

int main()
{
	std::cout << "Hello World!\n";


	const char* message = "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build.";

	std::cout << "message:" << message << std::endl << std::endl;

	//	SHA256�C���X�^���X���쐬
	SHA256 sha256;

	//	�p�f�B���O���������s
	unsigned char** result = sha256.padding((char*)message);

	//	�u���b�N��\��
	sha256.print_block(result);

	//	���ʊi�[�z����쐬����
	unsigned int H[INIT_HASH_LENGTH];

	//	�Í������s��
	sha256.compute(result, H);

	//	���ʂ��o�͂���
	std::cout << "result:" << std::endl;
	sha256.print_hash(H);

	//	�������J��
	sha256.free_block(result);

	return 0;
}
