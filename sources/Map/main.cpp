//
// main.cpp for  in /home/msa_m/Epitech/tek2/C++/cpp_indie_studio/sources/core
//
// Made by Matheo MSA
// Login   <msa_m@epitech.net>
//
// Started on  Wed Apr 27 16:36:46 2016 Matheo MSA
// Last update Tue May  3 18:07:26 2016 Matheo MSA
//

#include "Map.hh"
#include <iostream>

int	main()
{
  Map map10 (10, 10);
//  Map map15 (15, 15);
  Map	map20 (20, 20);

 map10.print();
 std::cout << std::endl;
//  map15.print();
//  std::cout << std::endl;
 map20.print();
 std::cout << std::endl;
  return 0;
}
