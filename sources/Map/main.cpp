//
// main.cpp for  in /home/msa_m/Epitech/tek2/C++/cpp_indie_studio/sources/core
//
// Made by Matheo MSA
// Login   <msa_m@epitech.net>
//
// Started on  Wed Apr 27 16:36:46 2016 Matheo MSA
// Last update Wed May  4 15:34:11 2016 Jules Palluau
//

#include "Map.hh"
#include <iostream>
#include "../Player/include/Game.hh"

int	main()
{
  Game  *m;
  //Map map10 (10, 10);
//  Map map15 (15, 15);
//  Map	map20 (20, 20);
m = new Game(0, 4, 20);
m->init();
// map10.print();
//  map15.print();
//  std::cout << std::endl;
 //map20.print();
// std::cout << std::endl;
  return 0;
}
