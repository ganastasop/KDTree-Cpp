#include "KDNode.hpp"
#include "Distance.hpp"
#include <queue>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

KDNode::KDNode(Embedding& E, int Split_axis, KDNode* Left, KDNode* Right, KDNode* Parent)
    : e(E), split_axis(Split_axis), left(Left), right(Right), parent(Parent) {}

KDNode::KDNode(const KDNode& node) 
    : e(node.getEmbedding()),
      split_axis(node.getSplit()),
      left((node.getLeft() == nullptr) ? nullptr : new KDNode(*node.getLeft())), 
      right((node.getRight() == nullptr) ? nullptr : new KDNode(*node.getRight())),
      parent(node.getParent())
{
    //left->setParent(this);
    //right->setParent(this);
}

KDNode::~KDNode() {
    delete left;
    delete right;
}

const Embedding& KDNode::getEmbedding() const {return e;}
int KDNode::getSplit() const {return split_axis;}
KDNode* KDNode::getLeft() const {return left;}
KDNode* KDNode::getRight() const {return right;}
KDNode* KDNode::getParent() const {return parent;}
void KDNode::setLeft(KDNode* node) {left = node;}
void KDNode::setRight(KDNode* node) {right = node;}
void KDNode::setParent(KDNode* node) {parent = node;}

void KDNode::getDistance(std::priority_queue <Distance>& pq, const Embedding& E, int k, int depth) {
    double sum = 0.0;
    std::vector<double> p = E.getVector();
    std::vector<double> q = e.getVector();
    for (size_t i = 0; i < p.size(); i++) {
        double diff = p[i] - q[i];
        sum += diff * diff;
    }
    Distance temp;
    temp.distance = std::sqrt(sum);
    temp.word = e.getWord();

    if (pq.size() < (size_t)k) {
        pq.push(temp);
        std::cout << "Adding: " << std::setprecision(5) << temp.distance << " [" << temp.word << "]\n";
    }
    else {
        if (temp.distance < pq.top().distance) {
            std::cout << "Removing: " << std::setprecision(5) << pq.top().distance << " [" << pq.top().word << "]\n";
            pq.pop();
            pq.push(temp);
            std::cout << "Adding: " << std::setprecision(5) << temp.distance << " [" << temp.word << "]\n";
        }
    }

    int axis = depth % e.getDimensions();

    if (left == nullptr && right == nullptr) {
        return;
    }
    else if (right == nullptr ){
        left->getDistance(pq, E, k, depth + 1);
    }
    else if (left == nullptr ){
        right->getDistance(pq, E, k, depth + 1);
    }
    else {
        if (q[axis] > p[axis]) {
            left->getDistance(pq, E, k, depth + 1);
            int difference = abs(q[axis] - p[axis]);
            if (difference < pq.top().distance) {
                right->getDistance(pq, E, k, depth + 1);
            }
        }
        else {
            right->getDistance(pq, E, k, depth + 1);
            int difference = abs(q[axis] - p[axis]);
            if (difference < pq.top().distance) {
                left->getDistance(pq, E, k, depth + 1);
            }
        }
    }
}