#ifndef _MOVIE_COLLECTION_HPP
#define _MOVIE_COLLECTION_HPP

#include<iostream>
#include<fstream>

#include "Movie.hpp"
#include "MovieNode.hpp"


class MovieCollection
{
private:
	MovieNode *_root;//pointer to the head node

public:
	//return the number of nodes of the binary tree
	int size() const;
	
	//return the rating of the wanted movie
	double getRating(std::string film, int year);
	
	//add a node to the end of the list
	void insert(Movie m);
	
	//find the largest number of nodes searched when looking up a movie
	int maxSearchLenght();
	
	//method to copy a binary tree
	void copiador(MovieNode* &to, const MovieNode* from) const;
	
	//add the node to the list
	void erase(Movie m);
	
	
	//Deault constructor
	MovieCollection(): _root(NULL) {};
	//constructor from an input
	MovieCollection(std::ifstream &ifile);
	//copy constructor
	MovieCollection(const MovieCollection & other);
	
	//accesor of the root
	MovieNode* root() const {return _root;}
	
	
	//find the movie given as a parameter
	MovieNode* find(Movie m) const;

	
	//overloading of plus operator
	const MovieCollection& operator+(const MovieCollection &other) const;
	//overloading of division operator
	const MovieCollection& operator/(const MovieCollection &other) const;
	
	//overloading of assigment operator
	const MovieCollection& operator=(const MovieCollection &other);
	
	//overloading of plus equal operator for a movie
	const MovieCollection& operator+=(const Movie &movieToAdd);
	//overloading of plus equal operator for a moviecollection
	const MovieCollection& operator+=(const MovieCollection &other);
	
	//overloading of minus equal operator for a movie
	const MovieCollection& operator-=(const Movie &movieToDel);
	//overloading of minus equal operator for a moviecollection
	const MovieCollection& operator-=(const MovieCollection &other);
	
	//clear the list
	void clear();
	//print the list
	std::ostream& print(std::ostream &os) const;
	//overloading of << operator
	friend std::ostream& operator<<(std::ostream &os, const MovieCollection &node);
};
#endif

