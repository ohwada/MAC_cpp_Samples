// map.cpp
// https://cpprefjp.github.io/reference/map/map.html
#include <iostream>
#include <map>

int main()
{
  // charをキー、intを値として扱う連想配列
  std::map<char, int> m;

  // 挿入
  m.insert(std::make_pair('c', 30));
  m.insert(std::make_pair('a', 10));
  m.insert(std::make_pair('b', 20));

  // 検索 : キー(char)を指定し、値(int)を得る
  int value = m.at('a');
  std::cout << value << std::endl;
}
