# Name : exp_v1.rb
# Use  : ruby exp_v1.rb 
# 藤崎GA実行時のseed値を1 ~ 100まで自動実行するスクリプトです。

1.step(10,1){
  system("./fujisaki_ga.exe 10 1000 aiueo_F1.txt >> result.txt")
}
