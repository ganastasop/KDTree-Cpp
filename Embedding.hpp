#ifndef EMBEDDING_HPP
#define EMBEDDING_HPP

#include <string>
#include <vector>

class Embedding {
    private:
      std::string word;
      std::vector<double> v;  
      
    public:  
      Embedding(char* line);
      Embedding(const std::string& line);
      Embedding(const Embedding& e);
    
      std::string getWord() const;
      std::vector<double> getVector() const;
      int getDimensions() const;
    
      Embedding& operator = (const Embedding& e);
      
      Embedding operator + (const Embedding& e) const;
      Embedding operator - (const Embedding& e) const;
      double    operator * (const Embedding& e) const;
    
      double    operator ! () const;
      friend std::ostream& operator<<(std::ostream &stream, const Embedding& e);
    };

#endif