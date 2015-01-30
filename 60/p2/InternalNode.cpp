//Programmed by Edward Guo and Andy Pham
#include <iostream>
#include <climits>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
			   InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [ISize];
} // InternalNode::InternalNode()


BTreeNode* InternalNode::addPtr(BTreeNode *ptr, int pos)
{ // called when original was full, pos is where the node belongs.
  if(pos == internalSize)
    return ptr;

  BTreeNode *last = children[count - 1];

  for(int i = count - 2; i >= pos; i--)
    {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
    } // shift things to right to make room for ptr, i can be -1!

  children[pos] = ptr;  // i will end up being the position that it is inserted
  keys[pos] = ptr->getMinimum();
  ptr->setParent(this);
  return last;
} // InternalNode:: addPtr()


void InternalNode::addToLeft(BTreeNode *last)
{
  ((InternalNode*)leftSibling)->insert(children[0]);

  for(int i = 0; i < count - 1; i++)
    {
      children[i] = children[i + 1];
      keys[i] = keys[i + 1];
    }

  children[count - 1] = last;
  keys[count - 1] = last->getMinimum();
  last->setParent(this);
  if(parent)
    parent->resetMinimum(this);
} // InternalNode::ToLeft()


void InternalNode::addToRight(BTreeNode *ptr, BTreeNode *last)
{
  ((InternalNode*) rightSibling)->insert(last);
  if(ptr == children[0] && parent)
    parent->resetMinimum(this);
} // InternalNode::addToRight()



void InternalNode::addToThis(BTreeNode *ptr, int pos)
{  // pos is where the ptr should go, guaranteed count < internalSize at start
  int i;

  for(i = count - 1; i >= pos; i--)
    {
      children[i + 1] = children[i];
      keys[i + 1] = keys[i];
    } // shift to the right to make room at pos

  children[pos] = ptr;
  keys[pos] = ptr->getMinimum();
  count++;
  ptr->setParent(this);

  if(pos == 0 && parent)
    parent->resetMinimum(this);
} // InternalNode::addToThis()



int InternalNode::getMaximum() const
{
  if(count > 0) // should always be the case
    return children[count - 1]->getMaximum();
  else
    return INT_MAX;
}  // getMaximum();


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{  // count must always be >= 2 for an internal node
  int pos; // will be where value belongs

  for(pos = count - 1; pos > 0 && keys[pos] > value; pos--);

  BTreeNode *last, *ptr = children[pos]->insert(value);
  if(!ptr)  // child had room.
    return NULL;

  if(count < internalSize)
    {
      addToThis(ptr, pos + 1);
      return NULL;
    } // if room for value

  last = addPtr(ptr, pos + 1);

  if(leftSibling && leftSibling->getCount() < internalSize)
    {
      addToLeft(last);
      return NULL;
    }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < internalSize)
      {
	addToRight(ptr, last);
	return NULL;
      }
    else // both siblings full or non-existent
      return split(last);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *oldRoot, BTreeNode *node2)
{ // Node must be the root, and node1
  children[0] = oldRoot;
  children[1] = node2;
  keys[0] = oldRoot->getMinimum();
  keys[1] = node2->getMinimum();
  count = 2;
  children[0]->setLeftSibling(NULL);
  children[0]->setRightSibling(children[1]);
  children[1]->setLeftSibling(children[0]);
  children[1]->setRightSibling(NULL);
  oldRoot->setParent(this);
  node2->setParent(this);
} // InternalNode::insert()


void InternalNode::insert(BTreeNode *newNode)
{ // called by sibling so either at beginning or end
  int pos;

  if(newNode->getMinimum() <= keys[0]) // from left sibling
    pos = 0;
  else // from right sibling
    pos = count;

  addToThis(newNode, pos);
} // InternalNode::insert(BTreeNode *newNode)


void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


BTreeNode* InternalNode::remove(int value)
{  // to be written by students
  BTreeNode *ptr;

  for (int i = 0; i < count; i++){
    if (i == 0 && keys[i] >=value ){
      ptr = children [i] -> remove(value);
      //cout << "1" << endl;
      if(count == 1){
	return children[0];
      }else{
	resetMinimum(children[i]);
	resetMinimum(children[i+1]);
	break;
      }
    }else if (keys[i] > value){
      //cout << "2" << endl;
      ptr = children [i-1] -> remove (value);
      resetMinimum(children[i]);
      break;
    }else if(keys [i] == value){
      //cout << "3" << endl;
      ptr = children [i] -> remove(value);
      resetMinimum(children[i]);
      break;
    }else if (i == count - 1 && value >= keys[i]){
      //cout << "4" << endl;
      ptr = children [i] -> remove(value);
      resetMinimum(children[i]);
      break;
    }//end else if
  }//end for
  if(ptr == NULL){
    //cout << " here?" << endl;
    // cout << "NULL"<<endl;
    return NULL;
  }
  else{
    //Removes the internal node value===============================
    for (int i = 0; i < count; i++){
      if (ptr == children [i]){
	if(i == count - 1){
	  count --;
	  // cout << "decremented count " << count << endl;
	}else{
	  for (int j = i; j < count; j++){
	    keys [j] = keys[j+1];
	    children [j] = children [j+1];
	  }//end for
	  // cout << "decremented count " << count << endl;
	  count --;
	}//end else
      }//end if
    }//end for
    //=======================================================
    if (getLeftSibling() == NULL && getRightSibling() == NULL){
      cout << "returning children [0] " << endl;
      return children[0];
    }//end if(getLeftSibling())
    if (count >= (internalSize + 1)/2){
      // cout << "No need to borrow/merge" << endl;
      //cout << " here?1" << endl;
      return NULL;
    }else if (count < (internalSize + 1)/2){
      //looks left
      if(leftSibling){
	if(leftSibling -> getCount() > (internalSize + 1)/2){
	  this -> insert (((InternalNode*)leftSibling) -> deleteChild(0));
	  //cout << " here?3" << endl;
	  return NULL;
	}//end if(leftSibling -> getCount())
	 //MERGE 
	 else if(leftSibling -> getCount() <= (internalSize + 1)/2){
	   for (int i = 0; i < count; ++i)
	     {
	       ((InternalNode*)leftSibling)->insert(this->children[i]); 
	     }
	   //cout << " here?154" << endl;
	   return this;
	 }//end else if(leftSibling -> getCount())
       }//end if(leftSibling)
       else if (rightSibling){
	 if(rightSibling -> getCount() > (internalSize + 1)/2){
	   this -> insert (((InternalNode*)rightSibling) -> deleteChild(0));
	   //cout << " here?4" << endl;
	   return NULL;
	 }//end if(leftSibling -> getCount())
	 //MERGE 
	 else if(rightSibling -> getCount() <= (internalSize + 1)/2){
	   for (int i = 0; i < count; ++i)
	     {
	       ((InternalNode*)rightSibling)->insert(this->children[i]); 
	     }
	   //cout << " here?54" << endl;
	   return this;
	 }//end else if(rightSibling -> getCount())
       }//end else if (rightSibling)
    }//end else if(count < )
    return NULL; // filler for stub
  }//end else
}// InternalNode::remove(int value)

BTreeNode* InternalNode::deleteChild(int pos){
  BTreeNode* ptr = children[pos];
  count--;
  for (int i = 0; i < count; ++i)
    {
      children[i] = children[i+1];
      keys[i] = children[i]->getMinimum();
    }
  return ptr;
}//end deadChildren


void InternalNode::resetMinimum(const BTreeNode* child)
{
  for(int i = 0; i < count; i++)
    if(children[i] == child)
      {
	keys[i] = children[i]->getMinimum();
	if(i == 0 && parent)
	  parent->resetMinimum(this);
	break;
      }
} // InternalNode::resetMinimum()


InternalNode* InternalNode::split(BTreeNode *last)
{
  InternalNode *newptr = new InternalNode(internalSize, leafSize,
					  parent, this, rightSibling);


  if(rightSibling)
    rightSibling->setLeftSibling(newptr);

  rightSibling = newptr;

  for(int i = (internalSize + 1) / 2; i < internalSize; i++)
    {
      newptr->children[newptr->count] = children[i];
      newptr->keys[newptr->count++] = keys[i];
      children[i]->setParent(newptr);
    }

  newptr->children[newptr->count] = last;
  newptr->keys[newptr->count++] = last->getMinimum();
  last->setParent(newptr);
  count = (internalSize + 1) / 2;
  return newptr;
} // split()

  
