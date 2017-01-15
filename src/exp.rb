# Name : exp.rb
# Use  : ruby exp.rb 
# 藤崎GAのseed値と世代数を変更しながら自動実行するスクリプトです。

10.step(100,10){|seed|
  print "seed : "
  puts seed
  0.step(10,1){|trial_time|
    print "gene : "
    puts trial_time
    system("./fujisaki_ga.exe #{seed} #{trial_time} #{ARGV[0]} > #{ARGV[0]}_#{seed}_#{trial_time}.txt")
  }
}