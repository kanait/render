////////////////////////////////////////////////////////////////////
//
// $Id: SelList.hxx 2021/06/05 13:15:27 kanai Exp $
//
// Copyright (c) 2021 Takashi Kanai
// Released under the MIT license
//
////////////////////////////////////////////////////////////////////

#ifndef _SELLIST_HXX
#define _SELLIST_HXX

#include <list>
using namespace std;

#define SEL_NONE   0
#define SEL_VERTEX 1
#define SEL_EDGE   2
#define SEL_FACE   3
#define SEL_LOOP   4

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


class SelNode {

  int     id_;
  //    int     type_;

public:

  SelNode() { SelNode( -1 ); };
  SelNode( int i ) { id_ = i; };
  //    SelNode( int i, int type ) { id_ = i; type_ = type; };

  ~SelNode(){};

  void setID( int key ) { id_ = key; };
  int id() const { return id_; };

  //    void setType( int type ) { type_ = type; };
  //    int& type() { return type_; };

};

class SelList {

  int type_;
  std::list<SelNode*> nodes_;

public:

  SelList() { init(); };
  ~SelList() { clear(); };

  void init() { nodes_.clear(); };

  void setType( int type ) { type_ = type; };
  int& type() { return type_; };

  std::list<SelNode*>& nodes() { return nodes_; };
  unsigned int size() const { return nodes_.size(); };

  void clear() {
    foreach ( std::list<SelNode*>, nodes_, I )
      delete *I;
    nodes_.clear();
  };

  void erase( int id ) {
    foreach( std::list<SelNode*>, nodes_, n )
      {
        if ( (*n)->id() == id )
          {
            SelNode* tn = *n; delete tn;
            nodes_.erase( n );
            return;
          }
      }
  };

  void add( int id ) {
    SelNode* node = new SelNode( id );
    nodes_.push_back( node );
    //add( id , SEL_NONE );
  };
  //    void add( int id, int type ) {
  //      SelNode* node = new SelNode( id, type );
  //      nodes_.push_back( node );
  //    };

};

#endif // _SELLIST_H

