#include <iostream>
#include <vector>

using namespace std;

// 定义二叉树
typedef struct CSNode {
    int data;
    CSNode* left = NULL, * right = NULL;
}CSNode, * CSTree;

class DbTree {
private:
    CSNode* lastTree = NULL;  
    CSNode node;
    CSNode* tree = NULL;
    vector<CSNode> vct;

    void left(CSNode* currentTree = NULL);
    void center(CSNode* currentTree = NULL);
    void right(CSNode* currentTree = NULL);
public:
    DbTree(int x) {
        node.data = x;
        tree = &node;
    }
    void add(int x, CSNode* currentTree = NULL);
    bool remove(int x, CSNode* currentTree = NULL);
    void leftShow();
    void centerShow();
    void rightShow();
};

int main()
{
    DbTree dbTree(100);
    dbTree.add(50);
    dbTree.add(122);
    dbTree.add(60);
    dbTree.add(55);
    dbTree.add(65);
    dbTree.add(70);

    //cout << "left is :" << endl;
    //dbTree.leftShow();
    //cout << "rihgt is :" << endl;
    //dbTree.rightShow();
    //cout << "center is :" << endl;
    dbTree.centerShow();

    dbTree.remove(65);

    cout << "删除后" << endl;
    dbTree.centerShow();

    int i = 1;
    int j;
    while (i)
    {
        cin >> i;
        if (i == 1) {
            cin >> j;
            dbTree.add(j);
        }
        if (i == 2) {
            cin >> j;
            dbTree.remove(j);
        }
        if (i == 3)
        {
            cout << "显示一波" << endl;
            dbTree.centerShow();
        }
    }
}

void DbTree::add(int x, CSNode* currentTree) {
    if (currentTree == NULL)
        currentTree = &node;

    // 如果是首次添加添加，则将设为二插树头文件
    if (node.data == NULL)
        node.data = x;
    else {
        //tree = &node;
        // 如果比当前值小，在左边添加，负责在右边添加
        if (x < currentTree->data) {
            if (currentTree->left == NULL)
            {
                CSNode* lastTree;
                lastTree = currentTree;
                currentTree = new CSNode;
                currentTree->data = x;
                lastTree->left = currentTree;
            }
            else {
                currentTree = currentTree->left;
                add(x, currentTree);
            }
        }
        else {
            if (currentTree->right == NULL)
            {
                CSNode* lastTree;
                lastTree = currentTree;
                currentTree = new CSNode;
                currentTree->data = x;
                lastTree->right = currentTree;
            }
            else {
                currentTree = currentTree->right;
                add(x, currentTree);
            }
        }
    }
}

bool DbTree::remove(int x, CSNode* currentTree) {
    if (currentTree == NULL)
        currentTree = &node;

    // 二叉树为空
    if (node.data == NULL)
        return false;
    else {
        //tree = &node;
        if (x == currentTree->data) {
            // 删除当前树，并且如果有子二叉树，讲子二叉树重新排序
            if (currentTree->left != NULL && currentTree->right != NULL) {
                // 将父节点的替换的子节点方向指向子节点的右边子节点，子节点的左边子节点并到右边子节点的最左边
                if (lastTree->left == currentTree)
                    lastTree->left = currentTree->right;
                else
                    lastTree->right = currentTree->right;

                lastTree = currentTree->left;
                currentTree = currentTree->right;
                while (currentTree->left != NULL)
                {
                    currentTree = currentTree->left;
                }
                currentTree->left = lastTree;       // 将删除后的点的左下角点保存
            }
            else if (currentTree->left == NULL && currentTree->right == NULL) {
                if (lastTree->left == currentTree)
                    lastTree->left = NULL;
                else
                    lastTree->right = NULL;
            }
            else {
                // 将父的链接指向自己的子
                if (lastTree->left == currentTree)
                    if (currentTree->left != NULL)
                        lastTree->left = currentTree->left;
                    else
                        lastTree->left = currentTree->right;
                else
                    if (currentTree->left != NULL)
                        lastTree->right = currentTree->left;
                    else
                        lastTree->right = currentTree->right;
            }

            delete currentTree;

            return true;    // 返回执行成功，并且不继续一下循环
        }


        lastTree = currentTree;
        // 如果比当前值小，在左边添加，负责在右边添加
        if (x < currentTree->data) {
            if (currentTree->left == NULL)
            {
                return false;
            }
            else {
                currentTree = currentTree->left;
                remove(x, currentTree);
            }
        }
        else {
            if (currentTree->right == NULL)
            {
                return false;
            }
            else {
                currentTree = currentTree->right;
                remove(x, currentTree);
            }
        }
    }
}

void DbTree::left(CSNode* currentTree)
{
    cout << currentTree->data << endl;

    if (currentTree->left != NULL)
    {
        left(currentTree->left);
    }

    if (currentTree->right != NULL) {
        left(currentTree->right);
    }
}
void DbTree::leftShow() {
    left(&node);
}

/* 中序，左中右的检测，左边有值则将当前值加入对战，左边没有则将当前输出显示并查询右边，如果有则继续将其作为起始点同样的查询
 * 上面结束后从堆栈中取出继续同样操作（但左边的不用再处理因为已经执行），直到堆栈为空
 */
void DbTree::center(CSNode* currentTree)
{
    if (currentTree->left != NULL)
    {
        vct.push_back(*currentTree);
        center(currentTree->left);
    }
    else {
        //显示或输出当前的
        cout << currentTree->data << endl;
        // 并对右边进行检测
        if (currentTree->right != NULL) {
            center(currentTree->right);
        }
        else    // 负责对堆栈进行同样操作
        {
            if (vct.size() > 0) {
                currentTree = &vct.back();      // 返回最后一个变量
                vct.pop_back();
                currentTree->left = NULL;
                center(currentTree);
            }
        }
    }
}
void DbTree::centerShow()
{
    center(&node);
}

/* 输出顺序：左右中；
 */
void DbTree::right(CSNode* currentTree) {
    if (currentTree->left != NULL)
    {
        vct.push_back(*currentTree);
        right(currentTree->left);
    }
    else if (currentTree->right != NULL) {
        vct.push_back(*currentTree);
        right(currentTree->right);
    }
    else {
        cout << currentTree->data << endl;

        if (vct.size() > 0) {
            CSNode* tree = &vct.back();
            if (tree->right->data == currentTree->data)
                tree->right = NULL;

            currentTree = tree;      // 返回最后一个变量
            vct.pop_back();
            currentTree->left = NULL; 
            right(currentTree);
        }
    }
}
void DbTree::rightShow() {
    right(&node);
}
