#include <iostream>
#include <time.h>
#include "SHA256.h"

int main()
{
	std::cout << "Hello World!\n";

	//	���؃R�}���h
	//	echo -n "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build." | openssl dgst -sha256


	const char* message = "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build.";

	std::cout << "message:" << message << std::endl << std::endl;

	//	���ʊi�[�z����쐬����
	unsigned int H[INIT_HASH_LENGTH];

	//	SHA256�C���X�^���X���쐬
	SHA256 sha256;


	bool blnFlag = true;
	int intCount = 0;
	int intTotal = 0;

//	for (int intI = 0; intI < 10; intI++) {

		//	�X�^�[�g���Ԃ܂ő҂�
		clock_t start = clock();
		while (start % 1000 != 0) {
			start = clock();
		}

//		while (blnFlag == true) {
			//	�p�f�B���O���������s
			unsigned char** result = sha256.padding((char*)message);

			//	�u���b�N��\��
			sha256.print_block(result);

			//	�Í������s��
			sha256.compute(result, H);

			//	���ʂ��o�͂���
			std::cout << "result:" << std::endl;
			sha256.print_hash(H);

			//	�������J��
			sha256.free_block(result);

			clock_t end = clock();
			if (end - start >= 1000) {
				blnFlag = false;
			}

			intCount++;
//		}
		intTotal += intCount;

//		std::cout << "Hashrate:" << intCount << "H/s" << std::endl;
//	}

//	std::cout << "Average Hashrate:" << intTotal/10 << "H/s" << std::endl;

	return 0;
}
