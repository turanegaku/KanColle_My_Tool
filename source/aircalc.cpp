#include <bits/stdc++.h>
#include <picojson.h>

using namespace std;

#define LOG(...) fprintf(stderr, __VA_ARGS__)
//#define LOG(...)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define REP(i, n) for(int i = 0; i < (int)(n); ++i)
#define FORIT(it, c) for(auto it = (c).begin(); it != (c).end(); ++it)
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

struct P {
  int maxeq, idx;
  picojson::value *equip;
  bool operator <(const P& p) const {
    if (maxeq == p.maxeq)
      return idx > p.idx;
    return maxeq < p.maxeq;
  }
};

vector<pair<string, pair<string, int>>> state = {
  {"耐久", {"api_taik", 0}},
  {"装甲", {"api_souk", 1}},
  {"回避", {"", 0}},
  {"搭載", {"api_maxeq", -1}},
  {"火力", {"api_houg", 1}},
  {"雷装", {"api_raig", 1}},
  {"対空", {"api_tyku", 1}},
  {"対潜", {"", 0}},
  {"索敵", {"", 0}},
  {"運　", {"api_luck", -1}},
};

template <class T, typename F1, typename F2> void inputUntilCorrect(T &input, T end, F1 message, string error, F2 loop){
  T begin = input;
  do {
    if (input == end) {
      cout << "終了します．" << endl;
      exit(0);
    }
    if (input != begin) cout << input << error << endl;
    message();
    cin >> input;
  } while(loop(input));
}

int main() {
  // ===== load datas ===== //
  picojson::value v;
  ifstream fin("data/api_start2");
  while(fin >> v);
  fin.close();
  // === remap slotitem_equiptype {id : value} === //
  picojson::object api_mst_slotitem_equiptype;
  picojson::array api_mst_slotitem = v.get("api_mst_slotitem").get<picojson::array>();
  FORIT(equiptype, v.get("api_mst_slotitem_equiptype").get<picojson::array>()) {
    equiptype->get<picojson::object>().insert({"slotitems", picojson::value(picojson::array())});
    string id = to_string((int)equiptype->get("api_id").get<double>());
    api_mst_slotitem_equiptype.insert({id, *equiptype});
  }
  // === register slotitem to slotitem_equiptype === //
  FORIT(slotitem, api_mst_slotitem) {
    string type = to_string((int)slotitem->get("api_type").get<picojson::array>()[2].get<double>());
    api_mst_slotitem_equiptype[type].get("slotitems").get<picojson::array>().push_back(*slotitem);
  }
  // === from stype's equip_type delete unequipable === //
  picojson::array api_mst_stype = v.get("api_mst_stype").get<picojson::array>();
  FORIT(stype, api_mst_stype){
    picojson::array equipable;
    FORIT(it, stype->get("api_equip_type").get<picojson::object>()){
      if (it->second.get<double>()) {
        equipable.push_back(picojson::value(it->first));
      }
    }
    stype->get<picojson::object>().insert({"equip_type", picojson::value(equipable)});
  }
  picojson::object api_mst_ship;
  FORIT(s, v.get("api_mst_ship").get<picojson::array>()){
    string name = s->get("api_name").get<string>();
    api_mst_ship.insert({name, *s});
  }

  // ===== number of ships ===== //
  int n = 1;
  inputUntilCorrect(n, 0, [] {cout << "艦娘は何人出撃しますか？ [1-6] end 0: "; }, ":範囲外です．", [](int n) {
    return n < 1 || 6 < n;
  });
  // ===== who take with ===== //
  vector<picojson::value> member(n);
  REP(i, n){
    string name = "";
    inputUntilCorrect(name, string("#"), [i, n] {printf("艦娘の名前を入力して下さい(%d/%d)．ex.加賀 end #: ", i + 1, n); }, ":無効な名前です．", [api_mst_ship](string name){
      return !EXIST(api_mst_ship, name);
    });

    member[i] = api_mst_ship[name];
    auto stype = api_mst_stype[member[i].get("api_stype").get<double>() - 1];
    cout << stype.get("api_name").get<string>() << "　";
    FORIT(type, stype.get("equip_type").get<picojson::array>()){
      auto equiptype = api_mst_slotitem_equiptype[type->get<string>()];
      cout << equiptype.get("api_name").get<string>() << endl;
      FORIT(equip, equiptype.get("slotitems").get<picojson::array>()){
        cout << equip->get("api_name").get<string>() << ',';
      }
      cout << endl;
    }
    cout << name << endl;
    for(auto st : state) {
      cout << st.first << ':';
      if(member[i].contains(st.second.first)) {
        picojson::value arr = member[i].get(st.second.first);
        if (st.second.second != -1)
          cout << arr.get<picojson::array>()[st.second.second];
        else
          cout << arr;
      } else {
        cout << "\u2717";
      }
      cout << "　";
    }
    cout << endl;
  }

  // ===== select plan ===== //
  int plan = 1;
  inputUntilCorrect(plan, 0, [] {cout << "[1]: greedy\n[2]: 891 method\n方針を選択して下さい．[1,2] end 0: "; }, ":範囲外です．", [](int n) {
    return n < 1 || 2 < n;
  });

  vector<vector<pair<int, picojson::value>>> deck_equips(n, vector<pair<int, picojson::value>>(4));
  vector<P> p;
  REP(i, n){
    auto eq = member[i].get("api_maxeq").get<picojson::array>();
    cout << member[i].get("api_maxeq") << endl;
    REP(j, 4){
      deck_equips[i][j].first = eq[j].get<double>();
      p.push_back({deck_equips[i][j].first, j, &deck_equips[i][j].second});
    }
  }
  SORT(p);
  for(auto pp : p) {
    cout << pp.maxeq << " " << pp.idx << endl;
  }
}
