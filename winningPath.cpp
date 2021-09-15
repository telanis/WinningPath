/*
 Name: Tiana Sumaoang
 Description: Program prompts for a starting amount of stones
 and outputs guaranteed win paths for rock game
 Input: number of stones
 Output: Properly formatted guaranteed win paths
*/

#include <iostream>

//create tree node structure
template <typename Type>
struct binTreeNode{
    
    binTreeNode<Type> *left, *right;
    Type data;
    
};

/*
 function_identifier: builds left and right subtrees recursively
 parameters: binTreeNode<Type> *r (points to root), int rockAmount(num of rocks)
 return value: N/A
 */
template <typename Type>
void buildTree(binTreeNode<Type> * r, int rockAmount){
        
    
    if(rockAmount == 0)
        return;
    
    //create temp pointer
    binTreeNode<int> * t;
    
    //create left node
    r -> left = new binTreeNode<int>;
    t = r -> left;
    t -> data = rockAmount - 1;
    t -> left = t -> right = NULL;
    buildTree( t, rockAmount -1 );
    
    //create right node
    if( rockAmount > 1 ){
        r -> right = new binTreeNode<int>;
        t = r -> right;
        t -> data = rockAmount - 2;
        t -> left = t -> right = NULL;
        buildTree( t, rockAmount - 2 );
    }
        
}

/*
 function_identifier: deallocates the decision tree
 parameters: binTreeNode<Type> *r (points to root)
 return value: N/A
 */
template <typename Type>
void destroyTree(binTreeNode<Type> *r){
    
    if(!r)
        return;
    
    destroyTree(r -> left);
    delete r -> left;
    
    destroyTree(r -> right);
    delete r -> right;
    
    delete r;
    
}


/*
 function_identifier: determines if a win can be guaranteed
 parameters: binTreeNode<Type> *r, bool turn (turn variable)
 return value: true/false if a win can be guaranteed
 */
template <typename Type>
bool determineWinningPath(binTreeNode<Type> *r, bool turn){
    
    
    if( r -> data == 0 && turn == false )
        return true;
    else if( r -> data == 0 && turn == true)
        return false;
    
    //flip turn
    if( turn == false )
        turn = true;
    else
        turn = false;
    
    binTreeNode<int> * t, * t1;
    t = r -> right;
    t1 = r -> left;
    
    // if the right node is not null
    if( t != NULL ){
        
        //if both left and right are true
        if( determineWinningPath( t, turn ) == true && determineWinningPath(t1, turn) == true)
                return true;
        //if either left or right are true
        else if (determineWinningPath(t, turn) == true || determineWinningPath(t1, turn) == true){
            //if my turn, i can pick the right choice
            //turn was switched earlier for next value
            if(turn == false)
                return true;
            else
                return false;
        }
        //if neither left or right are true
        else
            return false;
    }
    
    // go down the left node to get to 0
    else{
    t = r -> left;
        if( determineWinningPath(t, turn) == true)
            return true;
    else
        return false;
    }
    
    
}


/*
 function_identifier: prints out the path to victory, calls determineWinningPath
 parameters: binTreeNode<Type> *r, bool turn, int level
 return value:
 */
template <typename Type>
void printWinningPath(binTreeNode<Type> *r, bool turn, int level){
    
    
    //flip turn
    if( turn == false )
        turn = true;
    else
        turn = false;
   
    
    binTreeNode<int> * t;
    t = r -> right;
    
    //check if right node is NULL
    if( t != NULL){
        
        
        //if right path has a guarantee win
        if( determineWinningPath( t, turn ) == true ){
            
            //handle indents
            for(int i = 0; i < level; i++)
                std::cout << "  ";
            
            //printing format
            std::cout << r -> data << ": ";
            if(turn == false)
                std::cout << "You selected 2 stones \n";
            else
                std::cout << "Opponent selected 2 stones \n";
            printWinningPath( t, turn, level + 1 );
        
        }
    }
    
    
    t = r -> left;
    if(t == NULL)
        return;
    
    //if left path has a guaranteed win
    if( determineWinningPath( t, turn ) == true ){
        
        //Printing format
        for(int i = 0; i < level; i++)
            std::cout << "  ";
        
        std::cout << r -> data << ": ";
        if(turn == false)
            std::cout << "You selected 1 stone \n";
        else
            std::cout << "Opponent selected 1 stone \n";
        
        printWinningPath( t, turn, level + 1);
        
    }
    else
        return;
        
}


/*
 function_identifier: main function prompts for an integer to denote starting num of rocks
 parameters: N/A
 return value: N/A
 */
int main() {

    //create root
    binTreeNode<int> * root;
    root = new binTreeNode<int>;
    root -> left = NULL;
    root -> right = NULL;
    root -> data = 0;
    int rockAmount;
    
    std::cout << "Enter the amount of stones to start the game: ";
    std::cin >> rockAmount;

    //check for valid input
    while(std::cin.fail() || rockAmount <= 0) {
        std::cout << "Please enter a valid amount: " << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cin >> rockAmount;
    }
    
    
    std::cout << std::endl;
    
    //There are no guaranteed path for amounts divisible by 3
    if(rockAmount % 3 == 0){
        std::cout << "There is no guaranteed path :c \n\n";
        return 0;
    }
    
    //build tree
    root -> data = rockAmount;
    buildTree(root, rockAmount);
    
    
    printWinningPath(root, true, 0);
    
    
    std::cout << std::endl;

    
    return 0;
}
