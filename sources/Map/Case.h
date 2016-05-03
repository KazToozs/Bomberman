/*
** Case.h for  in /home/msa_m/Epitech/tek2/C++/cpp_indie_studio/sources/core
**
** Made by Matheo MSA
** Login   <msa_m@epitech.net>
**
** Started on  Wed Apr 27 17:32:54 2016 Matheo MSA
** Last update Fri Apr 29 10:25:08 2016 Matheo MSA
*/

#ifndef CASE_H_
#define CASE_H_


struct Case {

enum State{
  FREE,
  UNBREAKABLE,
  BREAKABLE,
  TAKEN,
  EXPLODING
};

  State  state;
};

#endif
