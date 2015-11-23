#include <string>
#include <map>
#include <vector>
std::map<std::string, std::vector<int>> kms;

void KMS(){
	/* 正規空母 */
	kms["Akagi"] = { 20, 20, 32, 10 };
	kms["Kaga"] = { 20, 20, 46, 12 };
	kms["Soryu"] = { 18, 27, 18, 10 };
	kms["Soryu2"] = { 18, 35, 20, 6 };
	kms["Hiryu"] = { 18, 27, 18, 10 };
	kms["Hiryu2"] = { 18, 36, 22, 3 };
	kms["Shokaku"] = { 24, 24, 24, 12 };
	kms["Shokaku2"] = { 27, 27, 27, 12 };
	kms["Zuikaku"] = { 24, 24, 24, 12 };
	kms["Zuikaku2"] = { 28, 26, 26, 13 };
	kms["Unryu"] = { 18, 21, 27, 3 };
	kms["Amagi"] = { 18, 21, 27, 3 };
	kms["Katsuragi"] = { 18, 21, 27, 3 };
	kms["katuragi"] = { 18, 24, 3, 6 };
	/* 装甲空母 */
	kms["Taiho"] = { 30, 24, 24, 8 };
	kms["Shokaku2kou"] = { 34, 21, 12, 9 };
	kms["Zuikaku2kou"] = { 34, 24, 12, 6 };
	/* 軽空母 */
	kms["Hosho"] = { 14, 16, 12, 0 };
	kms["Ryujo"] = { 9, 24, 5, 5 };
	kms["Ryujo2"] = { 18, 28, 6, 3 };
	kms["Ryuho"] = { 21, 9, 9, 6 };
	kms["Shoho"] = { 18, 12, 12, 6 };
	kms["Zuiho"] = { 18, 12, 12, 6 };
	kms["Hiyou"] = { 18, 18, 18, 12 };
	kms["Junyou"] = { 18, 18, 18, 12 };
	kms["Junyou2"] = { 24, 18, 20, 4 };
	kms["Chitose"] = { 21, 9, 6, 0 };
	kms["Chitose2"] = { 24, 16, 11, 8 };
	kms["Chiyoda"] = { 21, 9, 6, 0 };
	kms["Chiyoda2"] = { 24, 16, 11, 8 };
	/* 航空戦艦 */
	kms["Fuso"] = { 10, 10, 10, 10 };
	kms["Fuso2"] = { 4, 4, 9, 23 };
	kms["Yamashiro"] = { 10, 10, 10, 10 };
	kms["Yamashiro2"] = { 4, 4, 9, 23 };
	kms["Ise"] = { 11, 11, 11, 14 };
	kms["Hyuga"] = { 11, 11, 11, 14 };
	/* 航空巡洋艦 */
	kms["Mogami"] = { 5, 6, 5, 3 };
	kms["Mikuma"] = { 5, 6, 5, 3 };
	kms["Suzuya"] = { 5, 6, 5, 3 };
	kms["Kumano"] = { 5, 6, 5, 3 };
	kms["Tone"] = { 2, 2, 9, 5 };
	kms["Chikuma"] = { 2, 2, 9, 5 };
	/* その他 */
	kms["Akitsumaru"] = { 8, 8, 8, 0 };
}