#include "Map.hh"
#include <iostream>
#include <cstdlib>
#include <ctime>

Map::Map(size_t x, size_t y)
{
  this->_x = x;
  this->_y = y;
  generate();
}

Map::Map(const Map &other)
{
  this->_map = other._map;
}

Map &Map::operator=(const Map &other)
{
  this->_map = other._map;
  return *this;
}

Map::~Map()
{

}

std::vector<std::vector<Case> > Map::quarter(){
  std::srand(std::time(0));
  std::vector<std::vector<Case> > qMap((_y / 2));
  Case tmp_case;
  for (size_t i = 0 ; i < (_y / 2) ; i++){
    qMap[i].resize((_x / 2));
    for (size_t j = 0 ; j < (_x / 2); j++){
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
  x_len = qMap[y_len - 1].size();
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

void Map::fill_quarter(const std::vector<std::vector<Case> > &qMap,
  std::vector<std::vector<Case> > &tmpMap,
  const size_t &posb_x, const size_t &posb_y, const size_t &pose_x, const size_t &pose_y) {
  size_t i;
  size_t j;
  size_t j_tmp;
  size_t i_tmp;
  j_tmp = 0;
  for (i = posb_y ; i < pose_y; i++)
  {
    i_tmp = 0;
    for (j = posb_x; j < pose_x; j++){
      tmpMap[i][j] = qMap[j_tmp][i_tmp];
      i_tmp++;
    }
    j_tmp++;
  }
}

void Map::generate() {
  std::vector<std::vector<Case> > qMap;
  std::vector<std::vector<Case> > tmpMap(_y, std::vector<Case>(_x));
  std::cout << "I will generate a map (" << _x << ", " << _y << ")" << std::endl;
  qMap = quarter();

  fill_quarter(qMap, tmpMap, 0, 0, (_x / 2), (_y / 2));
  rotate(qMap, 1);
  fill_quarter(qMap, tmpMap, (_x / 2), 0, _x, (_y / 2));
  rotate(qMap, 2);
  fill_quarter(qMap, tmpMap, 0, (_y / 2), (_x / 2), _y);
  rotate(qMap, 3);
  fill_quarter(qMap, tmpMap, (_x / 2), (_y / 2), _x, _y);
  this->_map = tmpMap;
}

void Map::print()
{
  std::vector<std::vector<Case> >::iterator it_y;
  std::vector<Case>::iterator it_x;
  for (it_y = _map.begin(); it_y != _map.end(); it_y++){
    for (it_x = (*it_y).begin(); it_x != (*it_y).end(); it_x++ ){
      std::cout << (*it_x).state << " ";
    }
    std::cout << std::endl;
  }
}
