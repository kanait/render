////////////////////////////////////////////////////////////////////
//
// $Id: strutil.h 2021/06/01 01:32:43 kanai Exp $
//
// STL string utility
//
// Copyright (c) by Takashi Kanai. All rights reserved. 
//
////////////////////////////////////////////////////////////////////

#ifndef _STRUTIL_H
#define _STRUTIL_H 1

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class StrUtil {

public:

  // First whitespace-delimited token from str -> fw
  void first_word( std::string& str, std::string& fw ) {
    std::istringstream in(str); in >> fw;
  };

  // n-th whitespace-delimited token (reads n tokens, returns last)
  void nth_word( std::string& str, int n, std::string& fw ) {
    std::istringstream in(str);
    int i = 0;
    std::string t;
    while ( i < n ) { in >> t; ++i; }
    fw = t;
  };

  // Number of whitespace-delimited tokens
  int word_count( std::string& str ) {
    std::istringstream in(str);

    int count = 0; 
    std::string sstr;
    while ( in >> sstr ) ++count;

    return count;
  };

  // int to string
  std::string itos( int n ) {
    std::stringstream str_stream;
    str_stream << n;
    return str_stream.str();
  };

  // float to string
  std::string ftos( float n ) {
    std::stringstream str_stream;
    str_stream << n;
    return str_stream.str();
  };

  std::string GetExtension(const string &path) {
    std::string ext;
    size_t pos1 = path.rfind('.');
    if(pos1 != std::string::npos){
        ext = path.substr(pos1+1, path.size()-pos1);
        std::string::iterator itr = ext.begin();
        while(itr != ext.end()){
            *itr = tolower(*itr);
            itr++;
        }
        itr = ext.end()-1;
        while(itr != ext.begin()){    // trim trailing NUL or space from extension
            if(*itr == 0 || *itr == 32){
                ext.erase(itr--);
            }
            else{
                itr--;
            }
        }
    }

    return ext;
  };
};

#endif // _STRUTIL_H
