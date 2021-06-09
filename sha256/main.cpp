#include <iostream>
#include "SHA256.h"

int main()
{
	std::cout << "Hello World!\n";


	const char* message = "Visual Studio drives me crazy and I am suspecting I am doing something wrong. This is what I do: I installed Visual Studio(Pro '08) a long time ago, I installed the Windows SDK (Win 7 x64), someone emails me a project, it fails to build.";

	std::cout << "message:" << message << std::endl << std::endl;

	//	SHA256インスタンスを作成
	SHA256 sha256;

	//	パディング処理を実行
	unsigned char** result = sha256.padding((char*)message);

	//	ブロックを表示
	sha256.print_block(result);

	//	結果格納配列を作成する
	unsigned int H[INIT_HASH_LENGTH];

	//	暗号化を行う
	sha256.compute(result, H);

	//	結果を出力する
	std::cout << "result:" << std::endl;
	sha256.print_hash(H);

	//	メモリ開放
	sha256.free_block(result);

	return 0;
}
