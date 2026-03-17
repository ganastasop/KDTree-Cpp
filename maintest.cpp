#include <iostream>
#include "Embedding.hpp"
#include "KDTree.hpp"
#include "Distance.hpp"

int main() {
    try {
        Embedding e1(std::string("word1,1.0,2.0,3.0"));
        Embedding e2(std::string("word2,4.0,5.0,6.0"));

        std::cout << "--- Embedding Operations ---" << std::endl;
        std::cout << "Addition (e1+e2): " << (e1 + e2);      
        std::cout << "Subtraction (e1-e2): " << (e1 - e2);   
        std::cout << "Magnitude of e1 (!e1): " << !e1 << std::endl; 
        std::cout << "Cosine Similarity (e1*e2): " << e1 * e2 << std::endl; 

        std::cout << "\n--- Tree Operations ---" << std::endl;
        KDTree tree1("test.csv");  
        KDTree tree2("test2.csv"); 

        std::cout << "Tree1 size: " << tree1.getSize() << std::endl;
        std::cout << "Tree2 size: " << tree2.getSize() << std::endl;

        tree1 += tree2;
        std::cout << "Merged Tree size: " << tree1.getSize() << std::endl;

        std::cout << "\n--- KNN Search ---" << std::endl;
        std::vector<Distance> neighbors = tree1.KNN_search(e1, 2); 
        for (const auto& d : neighbors) {
            std::cout << "Found: " << d.word << " with distance: " << d.distance << std::endl;
        }

    } catch (const InvalidFileException& e) {
        std::cerr << e.what();
    } catch (const InvalidDimensionsException& e) {
        std::cerr << e.what();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}