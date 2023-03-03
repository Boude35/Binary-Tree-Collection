#include "MovieCollection.hpp"

#include <iostream>

using namespace std;

//return the number of nodes in the tree
int traverse(MovieNode *subtree)
{
	if (!subtree)//if the subtree is null
		return 0;
	else return(traverse(subtree->left())+1+traverse(subtree->right()));	
	
}

//returns the size of the tree by calling the previous function
int
MovieCollection::size() const
{
	
	MovieNode *curr=_root; //new node equals head
	return traverse(curr); //return the result of the previous function
	
}

//remove a given node
void
MovieCollection::erase(Movie m)
{
	MovieNode *toDel = find(m);
	if (!toDel) //(toDel==NULL)
	{
		cerr << "Attempt to delete value not in tree: " << m << endl;
		return;
	}

	// case of deleting a leaf node 
	if (toDel->isLeaf())
	{
		if (toDel == _root)
		{
			_root = NULL;
		}
		else // we are not the root
		{
			MovieNode *parent = toDel->parent();
			if (parent->left() == toDel)
				parent->left() = NULL;
			else // must be right child
				parent->right() = NULL;
		}

		// we should "clean up" toDel
		toDel->parent() = NULL;
		delete toDel;  // return the storage holding the node we erased back to C++
	}
	// we have 1 child
	else if ( 
                  ( toDel->right()!=NULL && toDel->left()==NULL) || // we have only a right child
                  ( toDel->left()!=NULL && toDel->right()==NULL)    // we have only a left child
                )
	{
		if (toDel == _root)
		{
			if (toDel->right() !=NULL)
			{
				_root = toDel->right();
				_root->parent() = NULL;
			}
			else //(toDel->left() != NULL)
			{
				_root = toDel->left();
				_root->parent() = NULL;
			}

			// clean up deleted node
			toDel->left() = toDel->right() = toDel->parent() = NULL;
			
			delete toDel;
			return;
		}
		// if we got here, toDel is not the root, but has 1 child. 
		MovieNode *subTree;
		if (toDel->left() != NULL)
			subTree = toDel->left();
		else // the child must be the right child
			subTree = toDel->right();

		MovieNode *parent = toDel->parent();
		if (parent->right()==toDel)
			parent->right() = subTree;
		else if (parent->left()==toDel)
			parent->left() = subTree;

		subTree->parent() = parent;

		toDel -> left() = toDel -> right() = toDel -> parent() = NULL;

		delete toDel;
	}
	else // we have two children
	{
		MovieNode *curr = toDel->right(); // goal: curr will hold the smallest node bigger than toDel
		while (curr->left()!=NULL)
			curr = curr->left();

		Movie smallestInRightSubTree = *curr->value();
		erase(*curr->value());
		*toDel->value() = smallestInRightSubTree;
	}	
}


//find a given movie
MovieNode*
MovieCollection::find(Movie m)const
{
	MovieNode *curr=_root; //new movie nood equals the root of the tree
	
	while(curr!=NULL)//while the node is not null
	{
		if (*curr->value() == m) //if it is equal
			return curr; //retunr the node
		else if ( m < *curr->value() ) //if the movie is less than the actual node
			curr = curr->left(); //go to the left
		else // (m > curr->value()
			curr = curr->right(); //go to the right
	}
	
	return NULL; //else return NULL
}

//retunr the rating of a given film
double
MovieCollection::getRating(string film, int year)
{
	MovieNode *curr=_root;//new node equals head
	Movie *m = new Movie(film, year, 0);//create a new pointer with the parameters
	
	if(curr!=NULL)//while the node is not null
	{
		while(curr!=NULL)
		{
			if (*curr->value() == *m)//if it is equal
				return curr->value()->rating();//retunr the rating of that film
			else if ( *m < *curr->value() )//if the movie is less than the actual node
				curr = curr->left();//go to the left
			else // (m> curr->value()
				curr = curr->right();//go to the right
		}
	}
	return -1;
}

//function that find the maximum search lenght
int maximum(MovieNode *curr)
{
	if(curr!=NULL) //while the node is not null
	{
		if (maximum(curr->left())>maximum(curr->right())) //if the left search lenght is bigger 
			return 1 + maximum(curr->left()); //print the lenght (recursive call)
		else //else maximum(curr->left())<maximum(curr->right())
			return 1 + maximum(curr->right()); //print the lenght (recursive call)
	}
	return 0;
}

//method that retunr the maximum search lenght
int
MovieCollection::maxSearchLenght()
{
	MovieNode *curr= _root; //new node equals the roort
	return maximum(curr); //use the function above to find it
}

//insert a new node to the tree
void
MovieCollection::insert(Movie m)
{
	//if can find the movie
	if (find(m) != NULL)
	{
		cout << m << " already in tree!. Insert ignored. " << endl;
		return;
	}



	
	MovieNode *newNode = new MovieNode(m); //new node with the movie in it
	//if the root is not NULL
	if (_root==NULL)
	{
		_root = newNode; //the root equal the new node
		return;
	}
	
	
	MovieNode *curr=_root; //current node equal the root
	MovieNode *prev=NULL; // _root has no previous. 
	
	while(curr!=NULL)
	{
		prev = curr;
		
		// update curr to get closer to bottom of tree. 
		if (m < *curr->value())
			curr = curr->left();
		else // value > curr->value()
			curr = curr->right();
	}
	
	newNode->parent() = prev;
	
	// fix prev's left or right child to point to the new node. 
	if (m < *prev->value())
		prev->left()=newNode;
	else // value > prev->value()
		prev->right()=newNode;	
}

//constructor from an input
MovieCollection::MovieCollection(ifstream &ifile)
{
	//inizializate the variables
	_root= NULL;
	
	//new movie
	Movie m;
	//pass the movie from the file to the new just created
	ifile >> m;
	//while the document has text
	while(ifile)
	{
		insert(m);//add it to the tree
		ifile >> m;//add the next values
	}
}

//copy constructor
MovieCollection::MovieCollection(const MovieCollection &other)
{
	//inizializate the variable
	_root = NULL;
	//use the method below
	copiador(this->_root, other._root);
}

//copy a choosen binary tree
void
MovieCollection::copiador(MovieNode* &to, const MovieNode* from) const
{
	if(from == NULL) //if the other binary is null
	{ 
		to = NULL; //new equaks null too
	}
	else{ //if it is not NULL
		to = new MovieNode(*from->value()); //copy all the variables of the node
		copiador(to->left(), from->left());
		copiador(to->right(), from->right());
		
	}
		
}
//print the values of the list
void infixPrint(std::ostream &os, MovieNode *subtree)
{
	if (!subtree)
		return;
	//recursive call to go over all the nodes of the left subtree
	infixPrint(os, subtree->left());
	
	os << *subtree->value() << endl;
	//recursive call to go over all the nodes of the right subtree
	infixPrint(os, subtree->right());
}

//print method. Print the tree
std::ostream&
MovieCollection::print(std::ostream &os) const
{
	infixPrint(os, _root); //call the function above
	return os;
}


//<< operator overloading
ostream& operator<<(ostream &os, const MovieCollection &tree)
{
	return tree.print(os); //call the method print
}

//insert the values without repeating them
void traverseinsert(MovieNode *curr, MovieCollection *answer)
{

	if(curr!=NULL) //if the node is not NULL
	{	
			traverseinsert(curr->left(),answer);//recursive call to go over all the nodes of the left subtree
			if(!answer->find(*curr->value()))//if the values is not in the tree
				answer->insert(*curr->value()); //insert it to the tree
			traverseinsert(curr->right(), answer);//recursive call to go over all the nodes of the right subtree
		
		
	}
	
}
//plus operator overloading
const MovieCollection& 
MovieCollection::operator+(const MovieCollection &other) const
{
	MovieCollection *answer = new MovieCollection(); //new moviecollection
	
	MovieNode *curr=_root;//new node equals the head
	//add all the values from LHS to teh new collection
	if(curr!=NULL)
	{
		traverseinsert(curr, answer);
	}	
	
	
	MovieNode *curr2=other._root;//new node equals the head of the RHS
	
	//add all the values of the RHS that are not already in the new collection
	if(curr2!=NULL)
	{	
		
		traverseinsert(curr2, answer);
		
	}
	return *answer; //return the new collection
}

//Insert the values that are common to both trees
void traverseinsert2(MovieNode *subtree, MovieCollection *answer, const MovieCollection *LHS)
{

	if(subtree!=NULL) //if the node is not NULL
	{	
			traverseinsert2(subtree->left(),answer,LHS);//recursive call to go over all the nodes of the left subtree
			if(LHS->find(*subtree->value()))//if the RHS value can be find in the LHS
				answer->insert(*subtree->value()); //add it to the tree
			traverseinsert2(subtree->right(), answer,LHS);//recursive call to go over all the nodes of the right subtree
		
		
	}
	
}
// /operator oveloading
const MovieCollection& 
MovieCollection::operator/(const MovieCollection &other) const
{
	MovieCollection *answer = new MovieCollection(); //new collection
	MovieNode *curr= other._root;//new node equals head
	
	//add all the values that are in bot RHS and LHS
	if(curr!=NULL)
	{
			traverseinsert2(curr, answer, this);
	}
	
	
	return *answer;
}

// plus equal operator overloading
const MovieCollection& 
MovieCollection::operator+=(const Movie &movieToAdd)
{	
        //add the movie to this only if it is not already in it
	if(!find(movieToAdd))
	{
		insert(movieToAdd);
	}

	MovieCollection *answer = new MovieCollection(*this);
	return *answer;
}

// plus equal operator overloading with other collection
const MovieCollection& 
MovieCollection::operator+=(const MovieCollection &other)
{

	MovieNode *curr=other._root;//new node equals head
	//add the values that arent already in the collection by usinf the previous += operator
	if(curr!=NULL)
	{
		traverseinsert(curr, this);

	}
	
	MovieCollection *answer = new MovieCollection(*this);
	return *answer;
}

//erase the value that are in the RHS
void traverseinsert3(MovieNode *subtree, MovieCollection *answer, MovieCollection *LHS)
{

	if(subtree!=NULL) //if the node is not NULL
	{	
			traverseinsert3(subtree->left(),answer, LHS);//recursive call to go over all the nodes of the left subtree
			if(LHS->find(*subtree->value()))//if the values can be find in the LHS
				LHS->erase(*subtree->value()); //erase it from it
			traverseinsert3(subtree->right(), answer, LHS);//recursive call to go over all the nodes of the right subtree
		
		
	}
	
}
//minus equal operator overloading. Remove the specified value
const MovieCollection& 
MovieCollection::operator-=(const Movie &movieToDel)
{
	if(find(movieToDel))
	{
		erase(movieToDel);//use erase function
	}

	MovieCollection *answer = new MovieCollection(*this);
	return *answer;
}

//Remove in the LHS the values in the RHS
const MovieCollection& 
MovieCollection::operator-=(const MovieCollection &other)
{
	
	MovieCollection *answer = new MovieCollection();//new Moviecollection
	MovieNode *curr=other._root;//new node equals head
	if(curr!=NULL)
	{
		//remove the ones in common with the function traverseinsert3
		traverseinsert3(curr, answer, this);
	}
	
	//use assigment operator overloaded
	*answer = *this;
	return *answer;
}

//assgiment operator overloading
const MovieCollection& 
MovieCollection::operator=(const MovieCollection &other)
{
	MovieNode *curr=other._root;//new node equals head
	if(curr!=NULL)
	{
		//copy every value with the traverse function
		traverseinsert(curr, this);
	}
	return *this;
}

//clear the list
void
MovieCollection::clear()
{
	//if head is null the rest is not printed
	_root = NULL;
}


