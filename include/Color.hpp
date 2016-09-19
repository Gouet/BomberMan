//
// Created by consta_n on 19/05/16.
//

#ifndef CPP_INDIE_STUDIO_COLOR_HPP
#define CPP_INDIE_STUDIO_COLOR_HPP

#include <string>

class Color {
public:
  float r;
  float g;
  float b;
  float a;

public:
  Color(std::string const &str);
  void set(std::string const &str);
};


#endif //CPP_INDIE_STUDIO_COLOR_HPP
