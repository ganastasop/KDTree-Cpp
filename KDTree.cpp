#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include "KDTree.hpp"
#include "Distance.hpp"
#include "InvalidFileException.hpp"
#include "InvalidDimensionsException.hpp"

KDTree::KDTree(const std::string filename) {
    try {
        std::vector<Embedding> embeddings = readVectors(filename);
        size = embeddings.size();
        sortAxis(embeddings, 0);
        int median = (size - 1) / 2;
        std::vector<Embedding> leftHalf(embeddings.begin(), embeddings.begin() + median);
        std::vector<Embedding> rightHalf(embeddings.begin() + median + 1, embeddings.end());
        root = new KDNode(embeddings[median], 0, insert(leftHalf, 1, root), insert(rightHalf, 1, root), nullptr);
    } catch (const InvalidFileException& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
    }
}

KDTree::KDTree(const KDTree& ht) {
    size = ht.getSize();
    this->root = new KDNode(*ht.root);
}

KDTree::~KDTree() {
    delete root;
}

std::vector<Distance> KDTree::KNN_search(const Embedding& e, int k) {
    std::priority_queue <Distance> pq;
    root->getDistance(pq, e, k, 0);
    std::vector <Distance> vec;
    for (int i = 0; i < k; i++) {
        vec.push_back(pq.top());
        pq.pop();
    }
    return vec;
}

KDTree& KDTree::operator = (const KDTree& tree) {
    delete root;
    root = new KDNode(*tree.getRoot());
    size = tree.getSize();
    return *this;
}

KDTree& KDTree::operator += (const KDTree& tree) {
    if (tree.getRoot()->getEmbedding().getVector().size() != root->getEmbedding().getVector().size()) {
        throw InvalidDimensionsException();
    }

    std::vector<Embedding> embeddings;
    toVector(root, embeddings);
    toVector(tree.root, embeddings);
    std::sort(embeddings.begin(), embeddings.end(), [](const Embedding& a, const Embedding& b) {
        return a.getWord() < b.getWord();
    });
    std::vector<int> toRemove;
    for (size_t i = 0; i < embeddings.size() - 1; i++) {
        if (embeddings[i].getWord() == embeddings[i+1].getWord()) {
            toRemove.push_back(i);
        }
    }
    for (int i = toRemove.size() - 1; i > -1; i--) {
        embeddings.erase(embeddings.begin() + toRemove[i]);
    }

    delete root;
    size = embeddings.size();
    sortAxis(embeddings, 0);
    int median = (size - 1) / 2;
    std::vector<Embedding> leftHalf(embeddings.begin(), embeddings.begin() + median);
    std::vector<Embedding> rightHalf(embeddings.begin() + median + 1, embeddings.end());
    root = new KDNode(embeddings[median], 0, insert(leftHalf, 1, root), insert(rightHalf, 1, root), nullptr);
    return *this;
}

KDTree KDTree::operator + (const KDTree& tree) const {
    KDTree result = *this;
    result += tree;
    return result;
}

std::ostream& operator<< (std::ostream& stream, const KDTree& t) {
    t.printPreorder(stream, t.root);
    return stream;
}

void KDTree::sortAxis(std::vector<Embedding>& vectors, int axis) const {
    std::sort(vectors.begin(), vectors.end(), [axis](const Embedding& a, const Embedding& b) {
        return a.getVector()[axis] < b.getVector()[axis];
    });
}

KDNode* KDTree::insert(std::vector<Embedding>& vectors, int depth, KDNode* parent) const {
    if (vectors.size() == 0) {
        return nullptr;
    }

    int axis = depth % vectors[0].getDimensions();
    int median = (vectors.size() - 1) / 2;
    if (vectors.size() > 1) {
        sortAxis(vectors, axis);
    }
    std::vector<Embedding> leftHalf(vectors.begin(), vectors.begin() + median);
    std::vector<Embedding> rightHalf(vectors.begin() + median + 1, vectors.end());
    KDNode* node = new KDNode(vectors[median], axis, nullptr, nullptr, parent);
    node->setLeft(insert(leftHalf, depth + 1, node));
    node->setRight(insert(rightHalf, depth + 1, node));
    return node;
}

KDNode* KDTree::getRoot() const {return root;}
int KDTree::getSize() const {return size;}

void KDTree::toVector(KDNode* root, std::vector<Embedding>& embeddings) const {
    if (root == nullptr) return;

    embeddings.push_back(root->getEmbedding());
    toVector(root->getLeft(), embeddings);
    toVector(root->getRight(), embeddings);
}

void KDTree::printPreorder(std::ostream& stream, KDNode* node) const {
    if (node == nullptr) return;

    stream << node->getEmbedding().getWord() << "\n";

    printPreorder(stream, node->getLeft());
    printPreorder(stream, node->getRight());
}