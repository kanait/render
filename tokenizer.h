////////////////////////////////////////////////////////////////////
//
// $Id: tokenizer.h 2021/06/05 13:10:28 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef TOKENIZER_H
#define TOKENIZER_H 1

#include <algorithm>
#include <string>
using namespace std;

typedef std::string String;

class tokenizer {
 private:
  String::size_type cur_;
  String str_;
  String del_;
  bool   ret_;
//   void skip();
  void skip() {
    if ( cur_ == str_.length() )
      cur_ = String::npos;
    if ( !ret_ && cur_ != String::npos ) {
      String::size_type tmp = str_.find_first_not_of(del_, cur_);
      if ( tmp != String::npos )
	cur_ = tmp;
    };
}
 public:
  typedef std::pair<String::size_type,String::size_type> range_type;
  tokenizer(const String& str, const String& del, bool ret=false) 
    : cur_(0), str_(str), del_(del), ret_(ret) {};
    
//   bool empty();
  bool empty() {
    skip();
    return cur_ == String::npos;
  };
//   String next();
  String next() {
    range_type range = next_range();
    return str_.substr(range.first, range.second);
  };
  String str() { return str_; };
//   tokenizer::range_type tokenizer::next_range() {
  range_type next_range() {
    skip();
    String::size_type start = cur_;
    //String::size_type tmp = cur_;
    if ( cur_ != String::npos ) cur_ = str_.find_first_of(del_,cur_);
    if ( cur_ == String::npos ) return range_type(start,str_.length()-start);
    if ( ret_ && start == cur_ && del_.find(str_[cur_]) != String::npos ) ++cur_;
    return range_type(start,cur_-start);
  };

//   void set_str(const String& str);
  void set_str(const String& str) {
    str_ = str;
    cur_ = 0;
  };

//   void set_delimiter(const String& del, bool ret=false);
  void set_delimiter(const String& delim, bool ret) {
    del_ = delim;
    ret_ = ret;
  };

//   size_t count() const;
  size_t count() const {
    size_t count = 0;
    String::size_type currpos = cur_;
    while ( currpos != String::npos ) {
      if ( !ret_ ) {
	currpos = str_.find_first_not_of(del_,currpos);
	if ( currpos == String::npos ) { ++count; break; }
      } else if ( currpos == str_.length() ) {
	break;
      }
      String::size_type start = currpos;
      if ( currpos != String::npos ) currpos = str_.find_first_of(del_,currpos);
      if ( currpos == String::npos ) { ++count; break; }
      if ( ret_ && start == currpos && del_.find(str_[currpos]) != String::npos ) ++currpos;
      ++count;
    }
    return count;
  };

};

// Notes (ASCII only for MSVC /utf-8):
// tokenizer(str, del, ret):
//   str  - string to scan
//   del  - delimiter character set
//   ret  - if false, skip runs of delimiters; if true, a delimiter at the
//          current position is returned as its own token.
// empty() - true when no more tokens remain (after skip).
// next() / next_range() - next token substring; range is (start index, length).
// set_str / set_delimiter - change input string or delimiter set; set_str resets cur_.
// count() - number of tokens from current position to end of str.
// Example: tokenizer("a,b,c", ",") yields "a", "b", "c".
// Example: tokenizer("a__b", "_", true) yields "a", "_", "_", "b".

#endif // TOKENIZER_H
