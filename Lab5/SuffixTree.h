#pragma once
#include <vector>
#include <map>
#include <string>
#include <memory>

typedef long long ll;

struct TSuffixTreeNode {
    std::map <char, TSuffixTreeNode* > Edges;
    TSuffixTreeNode* SuffixLink;
    ll Start;
    std::shared_ptr<ll> End;
    ll SuffixIndex = -1;
    ~TSuffixTreeNode();
};

typedef struct TSuffixTreeNode TNode;

struct TSuffixTree {
    std::string Text;
    TNode* Root = NULL;

    TNode* LastNewTNode = NULL;
    TNode* ActiveTNode = NULL;

    ll ActiveEdge = -1;
    ll ActiveLength = 0;

    ll RemainingSuffixCount = 0;
    std::shared_ptr<ll> LeafEnd = std::make_shared<ll>(-1);
    ll Size = -1; //Length of input string
    ll Size1 = 0; //Size of 1st string
    ll LengthOfLCS = 0; // stores length of longest common substring 

    TSuffixTree(std::string& Text, ll size);
    TNode* NewNode(ll start,std::shared_ptr<ll> end);
    void Build();
    ll EdgeLength(TNode* n);
    ll WalkDown(TNode* currTNode);
    void Extend(ll pos);
    void SetSuffixIndexByDFS(TNode* n, ll labelHeight);
    ll DoTraversal(TNode* n, ll labelHeight, ll* maxHeight, std::vector<int>& substringStartIndex);
    ~TSuffixTree();
};