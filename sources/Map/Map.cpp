#include "Map.hh"
#include <iostream>
#include <cstdlib>
#include <ctime>

Map::Map(size_t x, size_t y)
{
  generate(x, y);
}

Map::Map(const Map &other)
{
  this->map = other.map;
}

Map &Map::operator=(const Map &other)
{
  this->map = other.map;
  return *this;
}

Map::~Map()
{

}

std::vector<std::vector<Case> > Map::quarter(size_t x, size_t y){
  std::srand(std::time(0));
  std::vector<std::vector<Case> > qMap(y);
  Case tmp_case;
  for (size_t i = 0 ; i < y ; i++){
    qMap[i].resize(x);
    for (size_t j = 0 ; j < x ; j++){
      if (((i % 2) == 1) && ((j % 2) == 1)){
        tmp_case.state = Case::UNBREAKABLE;
      }
      else{
        if ((std::rand() % 5) == 0 ) {
          tmp_case.state = Case::FREE;
        }
        else {
          tmp_case.state = Case::BREAKABLE;
        }
      }
      qMap[i][j] = tmp_case;
    }
  }
  qMap[0][0].state = Case::FREE;
  qMap[0][1].state = Case::FREE;
  qMap[1][0].state = Case::FREE;
  return qMap;
}

void Map::rotate(std::vector<std::vector<Case> > &qMap, size_t nb_rot){
  std::vector<std::vector<Case> > tmpMap = qMap;
  size_t y_len;
  size_t x_len;
  size_t tmp_x;

  y_len = qMap.size();
  x_len = qMap[y_len].size();
  for (size_t i = 0; i < nb_rot ;  i++){
    for (size_t y = 0; y < y_len; y++){
      x_len = qMap[y].size();
      for (size_t x = 0; x < x_len; x++){
        tmp_x = (y_len - 1) - x;
        tmpMap[y][x] = qMap[tmp_x][y];
      }
    }
    qMap = tmpMap;
  }
}

void Map::generate(size_t x, size_t y)
{
  std::vector<std::vector<Case> > qMap;
//  std::vector<std::vector<Case> > tmpMap(y, );
  std::vector<std::vector<Case> > tmpMap(y, std::vector<Case>(x));
  std::cout << "I will generate a map (" << x << ", " << y << ")" << std::endl;
  qMap = quarter((x / 2), (y / 2));
  size_t j_tmp;
  size_t i_tmp;
  j_tmp = 0;
  for (size_t i = 0; i < (y / 2) ; i++){
    i_tmp = 0;
    for (size_t j = 0 ; j < (x / 2); j++){
      tmpMap[i][j] = qMap[j_tmp][i_tmp];
      i_tmp++;
    }
    j_tmp++;
  }
  rotate(qMap, 1);
  j_tmp = 0;
  for (size_t i = 0; i < (y / 2) ; i++){
    i_tmp = 0;
    for (size_t j = (x / 2); j < x ; j++){
      tmpMap[i][j] = qMap[j_tmp][i_tmp];
      i_tmp++;
    }
    j_tmp++;
  }
  rotate(qMap, 1);
  j_tmp = 0;
  for (size_t i = (y / 2); i < y ; i++){
    i_tmp = 0;
    for (size_t j = (x / 2); j < x ; j++){
      tmpMap[i][j] = qMap[j_tmp][i_tmp];
      i_tmp++;
    }
    j_tmp++;
  }
  rotate(qMap, 1);
  j_tmp = 0;
  for (size_t i = (y / 2); i < y ; i++){
    i_tmp = 0;
    for (size_t j = 0; j < (x / 2); j++){
      tmpMap[i][j] = qMap[j_tmp][i_tmp];
      i_tmp++;
    }
    j_tmp++;
  }
  this->map = tmpMap;
  print();
  std::cout << std::endl;
}

void Map::print()
{
  std::vector<std::vector<Case> >::iterator it_y;
  std::vector<Case>::iterator it_x;
  for (it_y = map.begin(); it_y != map.end(); it_y++){
    for (it_x = (*it_y).begin(); it_x != (*it_y).end(); it_x++ ){
      std::cout << (*it_x).state << " ";
    }
    std::cout << std::endl;
  }
}
