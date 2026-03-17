#ifndef KDNODE_HPP
#define KDNODE_HPP

#include "Embedding.hpp"
#include <queue>
#include <vector>
#include "Distance.hpp"

class KDNode {
private:
  Embedding e;
  int split_axis;
  KDNode* left;
  KDNode* right;
  KDNode* parent;
  
public:  
  KDNode(Embedding& e, int split_axis, KDNode* left, KDNode* right, KDNode* parent);
  KDNode(const KDNode& node);
  ~KDNode();

  const Embedding& getEmbedding() const;
  int getSplit() const;
  KDNode* getLeft() const;
  KDNode* getRight() const;
  KDNode* getParent() const;
  void setLeft(KDNode* node);
  void setRight(KDNode* node);
  void setParent(KDNode* node);

  void getDistance(std::priority_queue <Distance>& pq, const Embedding& e, int k, int depth);
};

#endif