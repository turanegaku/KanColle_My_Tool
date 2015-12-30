#include <bits/stdc++.h>
#include <picojson.h>

using namespace std;

#define LOG(...) fprintf(stderr, __VA_ARGS__)
//#define LOG(...)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define REP(i, n) for(int i = 0; i < (int)(n); ++i)
#define ALL(a) (a).begin(), (a).end()
#define RALL(a) (a).rbegin(), (a).rend()
#define EXIST(s, e) ((s).find(e) != (s).end())
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define SQ(n) (n) * (n)

typedef long long ll;
typedef unsigned long long ull;
typedef vector<bool> vb;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vb> vvb;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

vector<pair<string, pair<string, int>>> state = {
  {"耐久", {"api_taik", 0}},
  {"装甲", {"api_souk", 1}},
  {"回避", {"", 0}},
  {"搭載", {"api_maxeq", -1}},
  {"火力", {"api_houg", 1}},
  {"雷装", {"api_raig", 1}},
  {"対空", {"api_tyku", 1}},
  {"対潜", {"", 0}},
  {"索敵", {"api_taik", 1}},/**/
  {"運　", {"api_luck", -1}},
};

int main() {
  picojson::value v;
  ifstream fin("data/api_start2");
  while(fin >> v);
  fin.close();
  picojson::value api_mst_ship = picojson::value(picojson::object());
  for (picojson::value s : v.get("api_mst_ship").get<picojson::array>()) {
    string name = s.get("api_name").get<string>();
    api_mst_ship.get<picojson::object>().insert({name, s});
  }


  int n = 1;
  do {
    if (n == 0) {
      cout << "終了します．" << endl;
      return 0;
    }
    if (n != 1) printf("%d:範囲外です．\n", n);
    cout << "艦娘は何人出撃しますか？ [1-6] end 0: ";
    cin >> n;
  } while(n < 1 || 6 < n);
  vector<string> member(n, "");
  REP(i, n){
    do {
      if (member[i] == "#") {
        cout << "終了します．" << endl;
        return 0;
      }
      if (member[i] != "") printf("%s:無効な名前です．\n", member[i].c_str());
      printf("艦娘の名前を入力して下さい(%d/%d)．ex.加賀 end #: ", i + 1, n);
      cin >> member[i];
    } while(!api_mst_ship.contains(member[i]));

    cout << member[i] << endl;
    picojson::value s = api_mst_ship.get(member[i]);
    for(auto st : state) {
      cout << st.first << ':';
      if(!s.contains(st.second.first)) {
        cout << endl;
        continue;
      }
      picojson::value arr = s.get(st.second.first);
      if (st.second.second != -1)
        cout << arr.get<picojson::array>()[st.second.second] << endl;
      else
        cout << arr << endl;
    }
  }
}
