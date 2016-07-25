/*
 *  fifoarray.h
 *
 *  Base on queuearray.h
 *
 *  Library implementing a generic, dynamic queue (array version).
 *
 *  ---
 *
 *  Copyright (C) 2010  Efstathios Chatzikyriakidis (contact@efxa.org)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  ---
 *
 *  Version 1.0
 *
 *    2014-02-03  Brian Fletcher  <brian.jf.fletcher@gmail.com>
 *
 *      - added enqueue(), dequeue() and front().
 *
 *    2010-09-29  Efstathios Chatzikyriakidis  <contact@efxa.org>
 *
 *      - added resize(): for growing, shrinking the array size.
 *
 *    2010-09-25  Efstathios Chatzikyriakidis  <contact@efxa.org>
 *
 *      - added exit(), blink(): error reporting and handling methods.
 *
 *    2010-09-24  Alexander Brevig  <alexanderbrevig@gmail.com>
 *
 *      - added setPrinter(): indirectly reference a Serial object.
 *
 *    2010-09-20  Efstathios Chatzikyriakidis  <contact@efxa.org>
 *
 *      - initial release of the library.
 *
 *  ---
 *
 *  For the latest version see: http://www.arduino.cc/
 */

// header defining the interface of the source.
#ifndef __FIFOARRAY_H__
#define __FIFOARRAY_H__

// include Arduino basic header.
#include <Arduino.h>

// the definition of the queue class.
template<typename T>
class fifoArray {
  public:
    // init the queue (constructor).
    fifoArray ( T* i,const int _size);

    // clear the queue (destructor).
    ~fifoArray ();

    // // add an item to the queue.
    // bool enqueue (const T i);
    //
    // // remove an item from the queue.
    // T dequeue ();

    // push an item to the queue.
    bool push (const T i);

    // pop an item from the queue.
    T pop ();

    // get the front of the queue.
    T front () const;

    // get an item from the queue.
    T peek () const;

    // check if the queue is empty.
    bool isEmpty () const;

    // get the number of items in the queue.
    int count () const;

    // check if the queue is full.
    bool isFull () const;

  private:

    T * contents;    // the array of the queue.

    int size;        // the size of the queue.
    int items;       // the number of items of the queue.

    int head;        // the head of the queue.
    int tail;        // the tail of the queue.
};

// init the queue (constructor).
template<typename T>
fifoArray<T>::fifoArray ( T* i,const int _size) {
  contents = i;
  size = _size;       // set the size of queue to zero.
  items = 0;      // set the number of items of queue to zero.

  head = 0;       // set the head of the queue to zero.
  tail = 0;       // set the tail of the queue to zero.
}

// clear the queue (destructor).
template<typename T>
fifoArray<T>::~fifoArray () {

  contents = NULL; // set queue's array pointer to nowhere.

  size = 0;        // set the size of queue to zero.
  items = 0;       // set the number of items of queue to zero.

  head = 0;        // set the head of the queue to zero.
  tail = 0;        // set the tail of the queue to zero.
}

// add an item to the queue.
template<typename T>
bool fifoArray<T>::push (const T i) {
  // check if the queue is full.
  if (isFull ())
    return false;

  // store the item to the array.
  contents[tail++] = i;

  // wrap-around index.
  if (tail == size) tail = 0;

  // increase the items.
  items++;
  return true;
}
//
// // push an item to the queue.
// template<typename T>
// bool fifoArray<T>::push (const T i) {
//   return enqueue(i);
// }

// remove an item from the queue.
template<typename T>
T fifoArray<T>::pop () {
  // check if the queue is empty.
  if (isEmpty ())
    return NULL;

  // fetch the item from the array.
  T item = contents[head++];

  // decrease the items.
  items--;

  // wrap-around index.
  if (head == size) head = 0;

  // return the item from the array.
  return item;
}

// // pop an item from the queue.
// template<typename T>
// T fifoArray<T>::pop () {
//   return dequeue();
// }

// get the front of the queue.
template<typename T>
T fifoArray<T>::front () const {
  // check if the queue is empty.
  if (isEmpty ())
    return NULL;

  // get the item from the array.
  return contents[head];
}

// get an item from the queue.
template<typename T>
T fifoArray<T>::peek () const {
  return front();
}

// check if the queue is empty.
template<typename T>
bool fifoArray<T>::isEmpty () const {
  return items == 0;
}

// check if the queue is full.
template<typename T>
bool fifoArray<T>::isFull () const {
  return items == size;
}

// get the number of items in the queue.
template<typename T>
int fifoArray<T>::count () const {
  return items;
}

#endif // __FIFOARRAY_H__
