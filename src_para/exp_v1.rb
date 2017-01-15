# Name : exp_v1.rb
# Use  : ruby exp_v1.rb 
# 藤崎GA実行時のseed値を1 ~ 100まで自動実行するスクリプトです。

1.step(100,1){|seed|
  trial_time = 10
  print "seed : "
  puts seed
  system("./fujisaki_ga.exe #{seed} #{trial_time} t_aiueo_F1.txt > result1_#{seed}_#{trial_time}.txt")
}
