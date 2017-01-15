
CXX = clang++
TARGET = fujisaki_ga.exe
# CXXFLAGS = -g -std=c++11 デバッグ用
CXXFLAGS = -std=c++11
SRCS = Fujisaki_GA.cpp Fuji_GA.cpp calc_fitness.cpp crossover.cpp mutation.cpp selection.cpp show.cpp sort_ga.cpp
#SRCSの各ファイルのsuffixを.cppから.oに変換
OBJS := $(SRCS:.cpp=.o) 

$(TARGET): $(OBJS)
				$(CXX) -o $@ $(OBJS)
clean:
				rm -rf $(TARGET) $(OBJS)
