#include <iostream>
#include <string>
#include <fstream>

class Fighter{
private:
	std::string name; //艦載機の名前
	bool kansen; //艦載機の種類
	int taiku; //艦載機の対空値
	int shojisu; //艦載機の残り所持数
	std::string kanji_name; //表示用の漢字の名前
public:
	void setting(std::string n, bool k, int t, int s, std::string kn); //初期化的な奴
	void showAll();//その艦載機の状態を見る
	bool get_kind() { return kansen; } //艦戦かをboolで返す
	std::string get_name() { return name; } //艦載機の名前を返す
	int get_taiku() { return taiku; } //対空値を返す
	int get_shojisu() { return shojisu; } //所持数を返す
	std::string show_name() { return kanji_name; } //表示用の名前を返す
	int equip(); //艦載機の装備、名前を返して所持数を減らす
	bool re_name(std::string na);
	void push_shojisu() { shojisu += 1; } //装備数を増やす
};

void Fighter::setting(std::string n, bool k, int t, int s, std::string kn){
	name = n;
	kansen = k;
	taiku = t;
	shojisu = s;
	kanji_name = kn;
}
void Fighter::showAll(){
	std::cout << "名前: " << kanji_name;
	std::cout << " (" << name << ")" << std::endl;
	if (kansen) std::cout << "艦戦";
	else std::cout << "艦攻/艦爆";
	std::cout << ", 対空: " << taiku;
	std::cout << ", 所持数: " << shojisu << std::endl;
}
int Fighter::equip(){
	if (shojisu >0)shojisu -= 1;
	else return 0;
	return taiku;
}
bool Fighter::re_name(std::string na){
	if (na == name) return true;
	else return false;
}
/* アウトプット用のソースコード */
/*
	ofstream ofs("Fighters.txt", std::ios::out);
	ofs << "Reppu601 1 11 1 烈風(601空)" << endl;
	ofs << "Reppu 1 10 7 烈風" << endl;
	ofs << "Shiden2 1 9 4 紫電改二" << endl;
	ofs << "Jukuren21 1 8 2 零式艦戦21型(熟練)" << endl;
	ofs << "Zerosen601 1 9 1 零戦52型丙(601空)" << endl;
	ofs << "Named 0 1 3 江草・友永・村田隊" << endl;
	ofs << "Zuiun 0 2 17 瑞雲" << endl;
	ofs << "Zuiun12 0 3 1 瑞雲12型" << endl;
*/
