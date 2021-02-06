#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <queue>
#include <chrono> 
#include <random>
#include <algorithm>
#include <string>

#include "hashfunctions.h"

/*
Reads all the files in "folder". Assumes that they are named 0.py, 1.py, ...
Returns a vector with for each file a set of of tokens in that file. 
Tokens are unique words or bigrams (two sequential words).
*/
std::vector<std::set<std::string>> readDatafiles(const char* folder){
    auto start = std::chrono::high_resolution_clock::now(); 

    std::vector<std::set<std::string>> contents;

    int i = 0;
    std::ifstream in(folder+std::to_string(i)+".py");

    while (in){
        std::string word;
        std::string previous = "";
        contents.push_back(std::set<std::string>());

        while (in){
            in >> word;
            contents[i].insert(word);

            previous = previous + " " + word;
            contents[i].insert(previous);

            previous = word;
        }

        i++;
        in = std::ifstream(folder+std::to_string(i)+".py");
    }

    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    std::cout << "Reading the data files took " << duration.count() << " ms" << std::endl; 

    return contents;
}


std::vector<std::set<int>> replaceWithUniqueId(const std::vector<std::set<std::string>> &input){
    auto start = std::chrono::high_resolution_clock::now(); 

    std::vector<std::set<int>> contents(input.size());
    std::map<std::string, int> mapping;

    for (int i=0; i< input.size(); i++){
        for (const std::string &word: input[i]){
            if (mapping.find(word) == mapping.end()){
                mapping[word] = mapping.size();
            }
            contents[i].insert(mapping[word]);
        }
    }

    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    std::cout << "Replacing words with IDs took " << duration.count() << " ms" << std::endl; 
    return contents;
}

template<unsigned int (*hashfunction) (const std::string&)>
std::vector<std::set<int>> replaceWithHash(const std::vector<std::set<std::string>> &input){
    auto start = std::chrono::high_resolution_clock::now(); 

    std::vector<std::set<int>> contents(input.size());

    for (int i=0; i< input.size(); i++){
        for (const std::string &word: input[i]){
            contents[i].insert(hashfunction(word));
        }
    }

    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    std::cout << "Replacing words with hash values took " << duration.count() << " ms" << std::endl; 
    return contents;
}

template<unsigned int (*hashfunction) (const std::string&)>
void findCollisions(const std::vector<std::set<std::string>> &input){
    std::map<unsigned int, std::string> mapping;
    for (auto &doc: input){
        for (std::string s:doc){
            unsigned int hash = hashfunction(s);
            if (mapping.find(hash) != mapping.end() && mapping[hash] != s){
                std::cout << "Collision found: \""<< s<< "\" and \"" << mapping[hash] << "\" both map to " << hashfunction(s) << std::endl;
            }
            else{
                mapping[hash] = s;
            }
        }
    }
}

template<typename T>
std::vector<std::priority_queue<std::pair<double, int>>> jaccard(const std::vector<std::set<T>> &contents){
    auto start = std::chrono::high_resolution_clock::now(); 

    std::vector<std::priority_queue<std::pair<double, int>>> similarities(contents.size());

    for (int i=0; i< contents.size(); i++){
        for (int j=i+1; j<contents.size();j++){
            double intersection = 0;
            
            for (auto kt = contents[i].begin(); kt != contents[i].end(); kt++){
                if (contents[j].find(*kt) != contents[j].end()){
                    intersection++;
                }
            }
            
            std::pair<double, int> result;
            result.first = intersection / (contents[i].size() + contents[j].size() - intersection);
            result.second = j;

            similarities[i].push(result);
            
        }
    }
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    std::cout << "Calculating the Jaccard index took " << duration.count() << " ms" << std::endl; 
    return similarities;
}

void showSummary(std::vector<std::priority_queue<std::pair<double, int>>> &similarities, double threshold){
    bool reported[similarities.size()] = {false};

    for (int i=0; i<similarities.size(); i++){
        std::cout << i << "\t";
        std::pair<double, int> r;
        while (!similarities[i].empty() && similarities[i].top().first > threshold){
            r = similarities[i].top();
            if (!reported[r.second]){
                std::cout << r.second << " (" << r.first << ") ";
                reported[r.second] = true;
            }
            
            similarities[i].pop();
        }
        std::cout << std::endl;
    }
}

std::vector<int> calculateSignature(const std::set<int> &contents, int k, const std::vector<int> &a, const std::vector<int> &b, int c){
    std::vector<int> hash(k);
    for (int hashfunction=0; hashfunction < k; hashfunction++){
        int minHash = -1;
        int minWord = -1;

        for (std::set<int>::iterator it= contents.begin(); it != contents.end(); it++){
            int hash = (a[hashfunction]* *it +b[hashfunction])%c;
            if (minHash < 0 || hash < minHash){
                minHash = hash;
                minWord = *it;
            }
        }
        hash[hashfunction] = minWord;
    }
    
    return hash;
}

void fillRandom(std::vector<int> &v, int max){
    static std::uniform_int_distribution<int> distribution(1, max);
    static std::default_random_engine generator;

    std::generate(v.begin(), v.end(), []() { return distribution(generator); });
}

std::vector<std::priority_queue<std::pair<double, int>>> minhashing(const std::vector<std::set<int>> &contents, int n){
    auto start = std::chrono::high_resolution_clock::now(); 
    std::vector<int> a(n);
    std::vector<int> b(n);
    
    fillRandom(a, contents.size());
    fillRandom(b, contents.size());
    int c = 409;

    std::vector<std::vector<int>> hashes(contents.size());
    for (int i=0; i< contents.size(); i++){
        hashes[i] = calculateSignature(contents[i], n, a, b, c);
    }

    std::vector<std::priority_queue<std::pair<double, int>>> similarities(contents.size());

    for (int i=0; i< contents.size(); i++){
        std::vector<int> hashI = hashes[i];

        for (int j=i+1; j<contents.size();j++){

            std::vector<int> hashJ = hashes[j];
            double match = 0;

            for (int k=0; k<n; k++){
                if (hashI[k] == hashJ[k]){
                    match++;
                }
            }

            std::pair<double, int> result;
            result.first = match/n;
            result.second = j;

            similarities[i].push(result);
            
        }
    }
    auto stop = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start); 
    std::cout << duration.count() << " ms" << std::endl; 
    return similarities;

}

int main() {
    std::vector<std::set<std::string>> contents = readDatafiles("src/quiz/");
    std::vector<std::set<int>> contentsId = replaceWithUniqueId(contents);

    //std::vector<std::set<int>> contentsId = replaceWithHash<worst_hash>(contents);
    //std::vector<std::set<int>> contentsId = replaceWithHash<jenkins_one_at_a_time_hash>(contents);

    findCollisions<good_hash>(contents);

    //std::vector<std::priority_queue<std::pair<double, int>>> similarities = jaccard<std::string>(contents);
    //std::vector<std::priority_queue<std::pair<double, int>>> similarities = jaccard<int>(contentsId);

    std::vector<std::priority_queue<std::pair<double, int>>> similarities = minhashing(contentsId, 100);
    showSummary(similarities, 0.75);

    return 0;
}