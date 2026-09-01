// heap.cpp
// Duru Arda

#include "heap.h"
#include <stdexcept>
#include <utility> 
using namespace std;

static int parent(int i) { return (i - 1) / 2; }
static int left(int i)   { return 2 * i + 1; }
static int right(int i)  { return 2 * i + 2; }

static void bubbleUp(vector<int>& v, int i) {
  while (i > 0) {
    int p = parent(i);
    if (v[i] < v[p]) {
      std::swap(v[i], v[p]);
      i = p;
    } 
    else {
      break;
    }
  }
}

static void bubbleDown(vector<int>& v, int i) {
  int n = (int)v.size();
  while (true) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < n && v[l] < v[smallest]) smallest = l;
    if (r < n && v[r] < v[smallest]) smallest = r;

    if (smallest == i) break;
      swap(v[i], v[smallest]);
      i = smallest;
  }
}

Heap::Heap(vector<int>::iterator start, vector<int>::iterator end){
  for (auto it = start; it != end; ++it) {
    vdata.push_back(*it);
  }
  int n = (int)vdata.size();
  for (int i = (n / 2) - 1; i >= 0; --i) {
    bubbleDown(vdata, i);
  }
}

void Heap::push(int value){
  vdata.push_back(value);
  bubbleUp(vdata, (int)vdata.size() - 1);
}

void Heap::pop(){
  if (vdata.empty()) return;
  int last = (int)vdata.size() - 1;
  std::swap(vdata[0], vdata[last]);
  vdata.pop_back();
  if (!vdata.empty()) {
    bubbleDown(vdata, 0);
  }
}

int Heap::top(){
  if (vdata.empty()) {
    throw out_of_range("top() called on empty heap");
  }
  return vdata[0];
}

bool Heap::empty(){
  return vdata.empty();
}
    