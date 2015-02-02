//Programmed by Edward Guo and Andy Pham
#include <iostream>
#include <climits>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
                   BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{
  values = new int[LSize];
}  // LeafNode()

void LeafNode::addToLeft(int value, int last)
{
  leftSibling->insert(values[0]);

  for(int i = 0; i < count - 1; i++)
    values[i] = values[i + 1];

  values[count - 1] = last;
  if(parent)
    parent->resetMinimum(this);
} // LeafNode::ToLeft)

void LeafNode::addToRight(int value, int last)
{
  rightSibling->insert(last);

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToRight()

void LeafNode::addToThis(int value)
{
  int i;

  for(i = count - 1; i >= 0 && values[i] > value; i--)
    values[i + 1] = values[i];

  values[i + 1] = value;
  count++;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
} // LeafNode::addToThis()


void LeafNode::addValue(int value, int &last)
{
  int i;

  if(value > values[count - 1])
    last = value;
  else
    {
      last = values[count - 1];

      for(i = count - 2; i >= 0 && values[i] > value; i--)
        values[i + 1] = values[i];
      // i may end up at -1
      values[i + 1] = value;
    }
} // LeafNode:: addValue()


int LeafNode::getMaximum()const
{
  if(count > 0)  // should always be the case
    return values[count - 1];
  else
    return INT_MAX;
} // getMaximum()


int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  int last;

  if(count < leafSize)
    {
      addToThis(value);
      return NULL;
    } // if room for value

  addValue(value, last);

  if(leftSibling && leftSibling->getCount() < leafSize)
    {
      addToLeft(value, last);
      return NULL;
    }
  else // left sibling full or non-existent
    if(rightSibling && rightSibling->getCount() < leafSize)
      {
        addToRight(value, last);
        return NULL;
      }
    else // both siblings full or non-existent
      return split(value, last);
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()


LeafNode* LeafNode::remove(int value)
{   // To be written by students
  this -> removeThis(value);
  //cout << "removing " << value << endl;
  //Condition checking after value removed, if array is above or equal to min value then ok, else handle conditions
  if (count >= (leafSize + 1)/2){
    return NULL;
  }else if (count < (leafSize+1)/2){
    //Looks left
    if (leftSibling != NULL) {
      //if can borrow
      if (leftSibling -> getCount() > (leafSize + 1)/2){
        this -> insert (leftSibling -> getMaximum());
        leftSibling->remove(leftSibling -> getMaximum()); //remove the value
        //cout << "removed left" << endl;
        return NULL;
      }else if (leftSibling -> getCount () <= (leafSize + 1)/2){    //merge
        //cout << "Merge Left"<< endl;
        for (int i = 0; i < count; i ++){
          leftSibling -> insert(values[i]);
        }
    	leftSibling -> setRightSibling(this -> rightSibling);//remap siblings
        return this; //returns non-NULL so parent knows to delete
      }
    } //end if
    else if (rightSibling != NULL) {
      //if can borrow
      if (rightSibling -> getCount() > (leafSize + 1)/2){
        this -> insert(rightSibling -> getMinimum());
        rightSibling->remove(rightSibling -> getMinimum()); //remove the value
        //cout << "removed right" << endl;
        return NULL;
      }else if(rightSibling -> getCount() <= (leafSize + 1)/2){
        //cout << "Merging Right" << endl;
        for (int i = 0; i < count; i ++){
          rightSibling -> insert(values[i]);
        }
    	rightSibling -> setLeftSibling (this -> leftSibling); //remap siblings
        //cout << "Here" << endl;
        return this; //returns non-NULL so parent knows to delete
      }//end inner else if
      return NULL;
    }//end else if
  } //outermost else if
  return NULL;
}//end LeafNode::remove()

void LeafNode::removeThis(int value){
  for (int i = 0; i < count; i++){
    if (value == values[i]){
      if (i == count - 1){         //if deleted value is at the end of the list
        count--;
      }//end if
      else{
        for (int j = i; j < count; j++){
          values[j] = values[j+1];
        }//end for
        count --;
      }//end else
    }//end value == values if
  }//end for
}//end removeThis

LeafNode* LeafNode::split(int value, int last)
{
  LeafNode *ptr = new LeafNode(leafSize, parent, this, rightSibling);

  if(rightSibling)
    rightSibling->setLeftSibling(ptr);

  rightSibling = ptr;

  for(int i = (leafSize + 1) / 2; i < leafSize; i++)
    ptr->values[ptr->count++] = values[i];

  ptr->values[ptr->count++] = last;
  count = (leafSize + 1) / 2;

  if(value == values[0] && parent)
    parent->resetMinimum(this);
  return ptr;
} // LeafNode::split()

    
