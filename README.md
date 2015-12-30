# KanColle_My_Tool
制空値を自動的に計算する

## plan
### greedy
貪欲  
スロットの大きい方から強い艦載機を積む

### 891 method
http://kancolle.doorblog.jp/archives/46338568.html
>
>891: 名無しさん＠おーぷん 2015/09/21(月)20:51:54 ID:Bp2  
>\>>732  
>1．その海域で連れていける最大数の正規空母  
>　　軽空母を合計搭載数の多いものから選びます  
>2．全てのスロットに艦攻を積みます  
>　　このあと、常に制空計算はし続けてください  
>3．各空母の最小スロットから艦戦に置き換えていきます  
　　制空が足りるまで繰り返しましょう  
>完成です
>
>冗談じゃなくて、マジでこれ。

## run
```
make origin.o
./origin.o
```
or
```
make run
```

if you run original(upstream) program,
```
make upstream.o
./upstream.o
```

## private
自分の持っている艦載機数で適用するためには，実行後に生成される`private.json`の中身をそれっぽく書きかえること．
