# Makefile for Vigenere encryption and decryption

# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# 目录
BINDIR = bin
OBJDIR = obj

# 目标
all: $(BINDIR)/encrypt $(BINDIR)/decrypt

# 确保bin和obj目录存在
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# 编译加密程序
$(BINDIR)/encrypt: $(OBJDIR)/encrypt.o | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/encrypt $(OBJDIR)/encrypt.o

# 编译解密程序
$(BINDIR)/decrypt: $(OBJDIR)/decrypt.o | $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/decrypt $(OBJDIR)/decrypt.o

# 生成加密程序的对象文件
$(OBJDIR)/encrypt.o: encrypt.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c encrypt.cc -o $(OBJDIR)/encrypt.o

# 生成解密程序的对象文件
$(OBJDIR)/decrypt.o: decrypt.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c decrypt.cc -o $(OBJDIR)/decrypt.o

# 清理
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/encrypt $(BINDIR)/decrypt

