#ifndef KDTREE_HPP
#define KDTREE_HPP

#include "KDNode.hpp"
#include "Distance.hpp"
#include <vector>
#include <string>

class KDTree {
private:
  int size;
  KDNode* root;
  
public:  
  KDTree(const std::string filename);
  KDTree(const KDTree &ht);
  ~KDTree();

  std::vector<Distance> KNN_search(const Embedding& e, int k);
  
  KDTree& operator = (const KDTree &tree);
  
  KDTree& operator += (const KDTree& tree);
  KDTree  operator +  (const KDTree& tree) const;
  
  friend std::ostream& operator<<(std::ostream &stream, const KDTree& t);

  void sortAxis(std::vector<Embedding>& vector, int axis) const;
  KDNode* insert(std::vector<Embedding>& vector, int depth, KDNode* parent) const;
  KDNode* getRoot() const;
  int getSize() const;
  void toVector(KDNode* root, std::vector<Embedding>& embeddings) const;
  void printPreorder(std::ostream& stream, KDNode* node) const;
};

#endif