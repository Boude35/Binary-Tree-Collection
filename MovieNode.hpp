#ifndef _MOVIE_NODE_HPP_
#define _MOVIE_NODE_HPP_

#include<iostream>

#include "Movie.hpp"


class MovieNode
{
 private:
 
 	//Information in the node
 	Movie* _film;
 	
 	//Node representing the left child
 	MovieNode* _left;
 	
 	//Node representing the right child
 	MovieNode* _right;
 	
 	//Node representing the parent node
 	MovieNode* _parent;
 
 public:
 	
 	//constructor. insert the film as parameter in the node
 	MovieNode(Movie peli): _left(NULL), _right(NULL), _parent(NULL) {_film = new Movie(); *_film = peli;}
 	
 	//accesor to the fil in the node
 	Movie* value() const {return _film;}
 	
 	//accesor and modifier of the left child
 	MovieNode* left() const {return _left;}
 	MovieNode* &left() {return _left;}
 	
 	//accesor and modifier of the right child
 	MovieNode* right() const {return _right;}
 	MovieNode* &right() {return _right;}
 	
 	//accesor and modifier of the parent node
 	MovieNode* parent() const {return _parent;}
 	MovieNode* &parent() {return _parent;}
 	
 	//has the node any child
 	bool isLeaf() const;

 	//overloading of << operator
 	friend std::ostream& operator<<(std::ostream &os, const MovieNode&in);
};








#endif
