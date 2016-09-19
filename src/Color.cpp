//
// Created by consta_n on 19/05/16.
//

#include "Color.hpp"

Color::Color(const std::string &str) {

   set(str);
}

void Color::set(std::string const &str) {
   int i = 0;
   std::string delimiter = ",";
   size_t pos = 0;
   std::string token;
   std::string s = str;

   while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      switch (i)
      {
         case 0:
            r = std::stof(token);
            break;
         case 1:
            g = std::stof(token);
            break;
         case 2:
            b = std::stof(token);
            break;
         case 3:
            a = std::stof(token);
            break;
         default:
            break;
      }
      ++i;
      s.erase(0, pos + delimiter.length());
   }
}



