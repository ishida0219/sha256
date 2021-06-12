#include <iostream>
#include <time.h>
#include "SHA256.h"

int main()
{
	std::cout << "Hello World!\n";

	//	検証コマンド
	//	echo -n "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build." | openssl dgst -sha256


	const char* message = "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build.";

	std::cout << "message:" << message << std::endl << std::endl;

	//	結果格納配列を作成する
	unsigned int H[INIT_HASH_LENGTH];

	//	SHA256インスタンスを作成
	SHA256 sha256;


	bool blnFlag = true;
	int intCount = 0;
	int intTotal = 0;

//	for (int intI = 0; intI < 10; intI++) {

		//	スタート時間まで待つ
		clock_t start = clock();
		while (start % 1000 != 0) {
			start = clock();
		}

//		while (blnFlag == true) {
			//	パディング処理を実行
			unsigned char** result = sha256.padding((char*)message);

			//	ブロックを表示
			sha256.print_block(result);

			//	暗号化を行う
			sha256.compute(result, H);

			//	結果を出力する
			std::cout << "result:" << std::endl;
			sha256.print_hash(H);

			//	メモリ開放
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
