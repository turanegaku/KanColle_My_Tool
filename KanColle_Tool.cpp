#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <functional>
#include "Kanmusu_List.h"
#include "Fighter.h"
#define GET_ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
using namespace std;

int wepons[6][4] = {}; //所持する装備
string weponsName[6][4] = {}; //所持する装備の名前
string names[6] = {}; //出撃する艦娘のリスト
int sally; //出撃する艦娘の数(sally...出撃の意)
int mode = 0; //モード選択の変数
int seiku = 0; //目標制空値の変数
bool loop = true; //ループ制御の変数
int aircommand = 0; //計算中の制空値
int inwepon = 0; //武器の装備数
Fighter fi[8] = {}; //艦載機のクラス
ifstream ifs("Fighters.txt", ios::in);
int fsize = GET_ARRAY_SIZE(fi); //艦載機の種類数

void ga(string*, int); //プロトタイプ宣言(がっつり計算)
void hu(string*, int); //プロトタイプ宣言(2,3スロットに入れる計算)
void my(string*, int); //プロトタイプ宣言(手動計算)
void sh();			   //プロトタイプ宣言(表示)
void Fsetting(){ //艦載機のセット
	string name, kanji;
	int taiku, shoji, i = 0;
	bool kansen;
	while (ifs >> name){
		ifs >> kansen >> taiku >> shoji >> kanji;
		fi[i].setting(name, kansen, taiku, shoji, kanji);
		i++;
	}
}

int main(){
	KMS();
	Fsetting();
	bool endCheck = true;
	/* 登録のHAJIMARI */
	cout << "空母の艦娘は何人出撃しますか？ ";
	cin >> sally;
	if (sally < 1 || 6 < sally) return 0;
	for (int i = 0; i < sally; i++){
		cout << "名前の登録をします。名前を入力してください。" << endl;
		cin >> names[i];
		if (kms.find(names[i]) == kms.end()){
			cout << "不正な入力です。入力しなおしてください。" << endl;
			i -= 1;
		}
	}
	/* 登録のOWARI */
MODE:
	/* モードと目標制空値のNYURYOKU */
	cout << "使用したいモードを選択してください" << endl;
	cout << "1: 自動装備(がっつり), 2: 自動装備(攻撃向け), 3: 手動装備: ";
	cin >> mode;

	/* モード選択のHAJIMARI */
	switch (mode){
	case 1:
		ga(names, sally); //がっつり計算
		sh();
		break;
	case 2:
		hu(names, sally);
		sh();
		break;
	case 3:
		my(names, sally); //手動計算
		break;
	default:
		cout << "不正な入力です。" << endl;
		goto MODE;
		break;
	}
	loop = true; //修正の時にちゃんと使えるように
	/* モード選択のOWARI */

	/* 手動修正モードのSENTAKU */
	string fix;
	cout << "修正しますか?(yes/no): ";
	cin >> fix;
	if (fix == "yes") my(names, sally);
	/* 手動修正モードのOWARI */

	/* 終了の確認 */
	while (endCheck){
		cout << "OK?" << endl;
		string ok;
		cin >> ok;
		if (ok == "ok") endCheck = false;
	}
} //mainのOWARI

void ga(string* n, int sa){
	KMS();
	Fsetting();
	string na[6]; //名前格納用
	for (int i = 0; i < sa; i++){
		na[i] = *n;
		++n;
	}
	cout << "目標の制空値を入力して頂戴: ";
	cin >> seiku;
	while (loop){
		int i = 0, j = 0;
		int max = 0;
		int mi = 0, mj = 0;
		aircommand = 0;
		/* 搭載してない最大スロットの検索 */
		for (i = 0; i < sa; i++){
			for (j = 0; j < 4; j++){
				if (kms[na[i]][j] > max && wepons[i][j] == 0){
					max = kms[na[i]][j];
					mi = i; //装備してない最大スロット(艦娘の位置)
					mj = j; //装備してない最大スロット(スロットの位置)
				}
			}
		}
		/* スロットの装備 */
		for (i = 0; i < fsize; i++){
			if (fi[i].get_shojisu() > 0){
				wepons[mi][mj] = fi[i].equip();
				weponsName[mi][mj] = fi[i].show_name();
				inwepon += 1;
				break;
			}
		}
		/* 計算する */
		for (i = 0; i < sa; i++){
			for (j = 0; j < 4; j++){
				aircommand += int(wepons[i][j] * sqrt(kms[na[i]][j]));
			}
		}
		/* 制空値との比較 */
		if (seiku < aircommand) loop = false;
		else if (inwepon == sa * 4) loop = false; //全積みだったら抜ける
	}
}

void hu(string* n, int sa){
	KMS();
	Fsetting();
	string na[6]; //名前格納
	vector<pair<int, pair<int, int>>> Daughters(sa * 2); //艦娘の名前とスロット数を覚える
	vector<pair<int, int>> temp(4); //firstには搭載数 secondには場所を覚える

	for (int i = 0; i < sa; i++){
		na[i] = *n;
		++n;
	}
//	cout << "目標の制空値を入力してね: ";
//	cin >> seiku;
	for (int i = 0; i < sa; i++) {
		for (int j = 0; j < 4; j++){
			temp[j].first = kms[na[i]][j];
			temp[j].second = j;
		}
		sort(temp.begin(), temp.end(), greater<pair<int, int> >());
		/* 2番目のスロットを登録 */
		Daughters[i * 2].first = temp[1].first; //スロット数
		Daughters[i * 2].second.first = i; //名前(何番目に登録されている艦娘か)
		Daughters[i * 2].second.second = temp[1].second; //装備の場所
		/* 3番目のスロットを登録 */
		Daughters[i * 2 + 1].first = temp[2].first; //スロット数
		Daughters[i * 2 + 1].second.first = i; //名前(何番目に登録されている艦娘か)
		Daughters[i * 2 + 1].second.second = temp[2].second; //装備の場所
	}
	/* スロットの大きい順にソート */
	sort(Daughters.begin(), Daughters.end(), greater<pair<int, pair<int, int>> >());

	for (int i = 0; i < sa*2; i++) { //武器の装備
		for (int j = 0; j < fsize; j++) {
			if (fi[j].get_shojisu() > 0){
				wepons[Daughters[i].second.first][Daughters[i].second.second] = fi[j].equip();
				weponsName[Daughters[i].second.first][Daughters[i].second.second] = fi[j].show_name();
				break;
			}
		}
	}

	for (int i = 0; i < sa; i++){ //制空値の計算
		for (int j = 0; j < 4; j++){
			aircommand += int(wepons[i][j] * sqrt(kms[na[i]][j]));
		}
	}
}

void my(string* n, int sa){
	KMS();
	sh();
	Fsetting();
	string na[6]; //名前格納
	string inName; //入力された艦娘、艦載機の名前
	int inslot; //入力されたスロット
	for (int i = 0; i < sa; i++){
		na[i] = *n;
		++n;
	}
	while (loop){
		int kanmusui; //入力された艦娘が何番目にいるかを保有
		int kansaikii; //入力された艦載機が何番目にあるかを保有
		int sloti; //入力されたスロットの場所を保有
		aircommand = 0;
		/* 名前入力 */
	NAMING:
		cout << "誰の装備を編集する?" << endl;
		cin >> inName; //艦娘の名前入力
		for (int i = 0; i < sa; i++){
			if (inName == na[i]){
				kanmusui = i;
				break;
			}
			else kanmusui = 99;
		}
		if (kanmusui == 99){
			cout << "不正な入力です。" << endl;
			goto NAMING;
		}

		/* 艦載機入力 */
		while (loop){
			cout << "どの艦載機を装備する?" << endl;
			cin >> inName; //艦載機の名前入力
			for (int i = 0; i < fsize; i++){
				if (inName == fi[i].get_name()){
					kansaikii = i;
					loop = false;
					break;
				}
				else kansaikii = 99;
			}
			if (inName == "out") {
				loop = false;
				kansaikii = 90;
			}
			if (kansaikii == 99 || fi[kansaikii].get_shojisu() <= 0){
				cout << "不正な入力です。" << endl;
			}
		}
		loop = true;

		/* スロット入力 */
		while (loop){
			cout << "どのスロットに装備する?" << endl;
			if (cin >> inslot)
				if (1 <= inslot && inslot <= 4){
					loop = false; //スロットの入力
				}
				else cout << "不正な入力です" << endl;
			else {
				cin.clear();
				cin.ignore();
				cout << "不正な入力です" << endl;
			}

			sloti = inslot - 1;
			for (int i = 0; i < fsize; i++) {
				if (fi[i].re_name(inName))
					weponsName[kanmusui][sloti] = fi[i].show_name();
			}
		}
		loop = true;
		/* スロット入力終わり */

		/* 装備をしているかどうかのチェック */
		if (inName == "out"){ //装備外し
			for (int i = 0; i < fsize; i++){
				if (wepons[kanmusui][sloti] == fi[i].get_taiku()){
					fi[i].push_shojisu();
					wepons[kanmusui][sloti] = 0;
				}
			}
			goto CALC;
		}
		if (wepons[kanmusui][sloti] == 0){
			wepons[kanmusui][sloti] = fi[kansaikii].equip();
		}
		else{
			for (int i = 0; i < fsize; i++){
				if (wepons[kanmusui][sloti] == fi[i].get_taiku()){
					fi[i].push_shojisu();
					wepons[kanmusui][sloti] = fi[kansaikii].equip();
				}
			}
		}

		/* 計算のHAJIMARI */
	CALC:
		for (int i = 0; i < sa; i++){
			for (int j = 0; j < 4; j++){
				aircommand += int(wepons[i][j] * sqrt(kms[na[i]][j]));
			}
		}
		/* 計算のOWARI */
		/* 出力のHAJIMARI */
		sh();
		/* 出力のOWARI */
		/* 終了処理 */
		cout << "満足?(yes/no)" << endl;
		string ok;
		cin >> ok;
		if (ok == "yes") loop = false;
	}
}

void sh(){
	Fsetting();
	/* 出力のHAJIMARI */
	for (int i = 0; i < sally; i++){
		cout << names[i] << " の装備" << endl;
		for (int j = 0; j < 4; j++){
			cout << kms[names[i]][j] << ": ";
			if (weponsName[i][j] == "" || wepons[i][j] == 0)weponsName[i][j] = "なし";
			cout << weponsName[i][j] << endl;
		}
	}
	if (inwepon == sally * 4 && aircommand < seiku) cout << "この編成では無理です" << endl;
	cout << "制空値は " << aircommand << " です。" << endl;
	cout << "残りの艦載機は" << endl;
	for (int i = 0; i < fsize; i++) fi[i].showAll();
	int bonus_check = 0;
	for (int i = 0; i < sally; i++){
		for (int j = 0; j < 4; j++){
			if (wepons[i][j] == 0) bonus_check += 1;
		}
	}
	if (bonus_check != sally * 4){
		cout << "熟練度ボーナスを含める？(yes/no) ";
		string bonus;
		cin >> bonus;
		if (bonus == "yes"){
			for (int i = 0; i < sally; i++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < fsize; k++){
						if (weponsName[i][j] == fi[k].show_name() && fi[k].get_kind())
							aircommand += 25;
					}
				}
			}
			cout << "ボーナスを含めた制空値は " << aircommand << " です。" << endl;
		}
	}
	/* 出力のOWARI */
}
