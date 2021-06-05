////////////////////////////////////////////////////////////////////
//
// $Id: IDInfo.hxx 2021/06/05 13:18:14 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef _IDINFO_HXX
#define _IDINFO_HXX 1

class IDInfo {

public:

  IDInfo( int id, float depth ) {
    setID(id);
    setDepth(depth);
  };
  ~IDInfo(){};

  void setID( int id ) { id_ = id; };
  int id () const { return id_; };
  void setDepth( float depth ) { depth_ = depth; };
  float depth() const { return depth_; };

  ////////////////////////////////////////////////////////////////////

  friend bool operator < ( const IDInfo& p, const IDInfo& q ) {
    return (p.depth_ < q.depth_);
  };

  friend bool operator > ( const IDInfo& p, const IDInfo& q ) {
    return (p.depth_ > q.depth_);
  };

  friend bool operator == ( const IDInfo& p, const IDInfo& q ) {
    return (p.depth_ == q.depth_);
  };

  friend bool operator != ( const IDInfo& p, const IDInfo& q ) {
    return (p.depth_ != q.depth_);
  };

private:

  int id_;
  float depth_;

};

#endif // _IDINFO_HXX
