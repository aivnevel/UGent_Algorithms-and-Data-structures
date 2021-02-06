#ifndef BINTREE_H
#define BINTREE_H

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iostream>

class Node;

class BinaryTree : public std::unique_ptr<Node>
{
public:
    using std::unique_ptr<Node>::unique_ptr;
    using std::unique_ptr<Node>::operator=;
    friend std::ostream& operator<<(std::ostream& os, const BinaryTree &tree);
    
    bool build(std::vector<std::string> &questions, std::list<std::string> &animals, std::vector<std::map<std::string, bool>> answers);
    int height();
    double averageDepth();
    int numberOfLeaves();
    int numberOfSplits();

private:
    bool build(
        std::vector<std::string> &questions,
        std::vector<std::string>::iterator currentQuestion,
        std::list<std::string> &animals,
        std::vector<std::map<std::string, bool>>::iterator currentAnswers);

    std::ostream& print(std::ostream& os, int level, const std::string &prefix) const;
    
    int internalPathLength();
    
};

class Node
{
public:
    std::string value;;
    BinaryTree left, right;
};


bool BinaryTree::build(std::vector<std::string> &questions, std::list<std::string> &animals, std::vector<std::map<std::string, bool>> answers){
    return build(questions, questions.begin(), animals, answers.begin());
}

bool BinaryTree::build(
    std::vector<std::string> &questions,
    std::vector<std::string>::iterator currentQuestion,
    std::list<std::string> &animals,
    std::vector<std::map<std::string, bool>>::iterator currentAnswers){

    if (animals.size() == 1){
        // We are done, only one remaining animal, add a leaf
        *this = std::make_unique<Node>();
        (*this) -> value = *animals.begin();
        return true; // This branch is successful
    }
    
    else if (currentQuestion != questions.end()){
        // More than one animal remaining but luckily we have questions left.
        *this = std::make_unique<Node>(); // This will be an internal node

        (*this) -> value = *currentQuestion; // containing a question
      
        // Split the remaining animals based on this question
        std::list<std::string> animalsLeft;
        std::list<std::string> animalsRight;

        std::list<std::string>::iterator it= animals.begin();
        while (it != animals.end()){
            std::list<std::string>::iterator other = it;
            it++;
            if ((*currentAnswers)[*other]){
                animalsLeft.splice(animalsLeft.begin(), animals, other);
            }
            else{
                animalsRight.splice(animalsRight.begin(), animals, other);
            }
        }

        if (animalsLeft.size() == 0 || animalsRight.size() == 0){
            // One of the subtrees is empty, this was a useless question
            currentQuestion++;
            currentAnswers++;
            // try it again with the next question
            return build(questions, currentQuestion, (animalsLeft.size() == 0 ? animalsRight: animalsLeft), currentAnswers);            
        }
        else{
            // Ok, this was a useful question
            currentQuestion++;
            currentAnswers++;

            // Build the left and right tree recursively
            bool result = true;
            if (animalsLeft.size() > 0){
                result = (*this) -> left.build(questions, currentQuestion, animalsLeft, currentAnswers);
            }
            if (animalsRight.size() > 0){
                result &= (*this) -> right.build(questions, currentQuestion, animalsRight, currentAnswers);
            }

            return result;
        }        
    }
    else{
        // No questions left and more than one animal remaining.
        // We can not build the decision tree here
        std::cout << "Can not distinguish between ";
        for (auto it = animals.begin(); it != animals.end(); it++){
            std::cout << *it << ", ";
        }
        std::cout << std::endl;
        return false;
    }
}

int BinaryTree::height(){
    if (!*this){
        return 0;
    }
    return std::max((*this) -> left.height(), (*this) -> right.height())+1; 
}

double BinaryTree::averageDepth(){
    return (double)internalPathLength()/numberOfLeaves();
}

int BinaryTree::numberOfLeaves(){
    if (!((*this) -> left) && !((*this) -> right)){
        return 1;
    }
    else{
        int sum = 0;
        if ((*this) -> left){
            sum += (*this) -> left.numberOfLeaves();
        }
        if ((*this) -> right){
            sum += (*this) -> right.numberOfLeaves();
        }
        return sum;
    }
}

int BinaryTree::internalPathLength(){
    if (!*this){
        return 0;
    }
    int sum = 0;
    if ((*this) -> left){
        sum += (*this) -> left.numberOfLeaves() + (*this) -> left.internalPathLength();
    }
    if ((*this) -> right){
        sum += (*this) -> right.numberOfLeaves() + (*this) -> right.internalPathLength();
    }
    return sum;
}


int BinaryTree::numberOfSplits(){
    if (!((*this) -> left) && !((*this) -> right)){
        // this is a leave
        return 0;
    }
    // this is a split point
    int sum = 1;
    if ((*this) -> left){
        sum += (*this) -> left.numberOfSplits();
    }
    if ((*this) -> right){
        sum += (*this) -> right.numberOfSplits();
    }
    return sum;

}


std::ostream& operator<<(std::ostream& os, const BinaryTree &tree){
    os << tree -> value << std::endl;
    if (tree ->left){
        tree -> left.print(os, 0, "Y");
    }
    if (tree -> right){
        tree ->right.print(os, 0, "N");
    }
    return os;
}

std::ostream& BinaryTree::print(std::ostream& os, int level, const std::string &prefix) const{
    os << std::string(level, '\t') << "--" << prefix << "--> " <<(*this) -> value << std::endl;
    level++;
    if ((*this) -> left){
        (*this) -> left.print(os, level, "Y");
    }
    if ((*this) -> right){
        (*this) -> right.print(os, level, "N");
    }
    return os;
}



#endif