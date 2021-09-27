#include <list>
#include <algorithm>
#include <iostream>
#include "SuffixTree.h"

TSuffixTreeNode::~TSuffixTreeNode() {
    for (std::pair <char, TSuffixTreeNode *> node : Edges) {
        delete node.second;
    }
}

TSuffixTree::TSuffixTree(std::string& text, long long size) {
    Text = text;
    Size1 = size;
    Build();
    SetSuffixIndexByDFS(Root, 0);

    std::vector<int> substringStartIndex;
    DoTraversal(Root, 0, &LengthOfLCS, substringStartIndex);
    
    // Print LCS
    std::cout << LengthOfLCS << "\n";
    std::vector<std::string> ans;
    std::string temp;
    for (int i = 0; i < substringStartIndex.size();++i) {
        int k = 0;
        temp.clear();
        for (k = 0; k < LengthOfLCS; k++) {
            temp += Text[k + substringStartIndex[i]];
        }
        ans.push_back(temp);
    }
    std::sort(ans.begin(), ans.end());
    for(auto i:ans) {
        std::cout << i << "\n";
    }
}

void TSuffixTree::Build() {
    Size = Text.size();
    Root = NewNode(-1, std::make_shared<long long>(-1));
    ActiveTNode = Root; //First ActiveTNode will be root
    for (long long i = 0; i < Size; i++) {
        Extend(i);
    }
    
}

TNode* TSuffixTree::NewNode(long long start, std::shared_ptr<long long> End) {
    TNode* TNode = new TSuffixTreeNode;

    TNode->SuffixLink = Root;
    TNode->Start = start;
    TNode->End = End;
    return TNode;
}

long long TSuffixTree::EdgeLength(TNode* n) {
    if (n == Root) {
        return 0;
    }
    return *(n->End) - (n->Start) + 1;
}

long long TSuffixTree::WalkDown(TNode* currTNode) {
    if (ActiveLength >= EdgeLength(currTNode)) {
        ActiveEdge += EdgeLength(currTNode);
        ActiveLength -= EdgeLength(currTNode);
        ActiveTNode = currTNode;
        return 1;
    }
    return 0;
}

void TSuffixTree::Extend(long long pos)
{
    ++*LeafEnd;
    RemainingSuffixCount++;
    LastNewTNode = NULL;

    while (RemainingSuffixCount > 0) {

        if (ActiveLength == 0) {
            ActiveEdge = pos; 
        }

        if (!ActiveTNode->Edges[Text[ActiveEdge]]) {
            ActiveTNode->Edges[Text[ActiveEdge]] = NewNode(pos, LeafEnd);
            if (LastNewTNode != NULL) {
                LastNewTNode->SuffixLink = ActiveTNode;
                LastNewTNode = NULL;
            }
        }

        else {
            TNode* next = ActiveTNode->Edges[Text[ActiveEdge]];
            if (WalkDown(next)) { //Do walkdown
                continue;
            }

            if (Text[next->Start + ActiveLength] == Text[pos]) {
                if (LastNewTNode != NULL && ActiveTNode != Root) {
                    LastNewTNode->SuffixLink = ActiveTNode;
                    LastNewTNode = NULL;
                }
                ActiveLength++;
                break;
            }

            long long splitEnd = next->Start + ActiveLength - 1;
            TNode* split = NewNode(next->Start, std::make_shared<long long>(splitEnd));
            ActiveTNode->Edges[Text[ActiveEdge]] = split;

            split->Edges[Text[pos]] = NewNode(pos, LeafEnd);
            next->Start += ActiveLength;
            split->Edges[Text[next->Start]] = next;

            if (LastNewTNode != NULL) {
                LastNewTNode->SuffixLink = split;
            }

            LastNewTNode = split;
        }

        RemainingSuffixCount--;
        if (ActiveTNode == Root && ActiveLength > 0) {
            ActiveLength--;
            ActiveEdge = pos - RemainingSuffixCount + 1;
        }
        else if (ActiveTNode != Root) {
            ActiveTNode = ActiveTNode->SuffixLink;
        }
    }
}

void TSuffixTree::SetSuffixIndexByDFS(TNode* n, long long labelHeight) {
    if (n == NULL)  {
        return;
    }

    long long leaf = 1;
    for (auto child : n->Edges) {
        leaf = 0;
        SetSuffixIndexByDFS(child.second, labelHeight + EdgeLength(child.second));
    }
    if (leaf == 1) {
        n->SuffixIndex = Size - labelHeight;
    }
}

long long TSuffixTree::DoTraversal(TNode* n, long long labelHeight, long long* maxHeight, std::vector<int>& substringStartIndex) {
    if (n == NULL) {
        return 0;
    }
    long long ret = -1;
    if (n->SuffixIndex < 0) { //If it is long longernal TNode 
        for (auto child : n->Edges) {
            ret = DoTraversal(child.second, labelHeight + EdgeLength(child.second), maxHeight, substringStartIndex);
            if (n->SuffixIndex == -1) {
                n->SuffixIndex = ret;
            }
            else if ((n->SuffixIndex == -2 && ret == -3) || (n->SuffixIndex == -3 && ret == -2) || n->SuffixIndex == -4 || ret == -4) {
                n->SuffixIndex = -4;//Mark TNode as XY
                //Keep track of deepest TNode
                if (*maxHeight < labelHeight) {
                    *maxHeight = labelHeight;
                    substringStartIndex.clear();
                    substringStartIndex.push_back(*(n->End) - labelHeight + 1);
                }
                else if(*maxHeight == labelHeight && !substringStartIndex.empty() && substringStartIndex.back() != *(n->End) - labelHeight + 1) {
                    substringStartIndex.push_back(*(n->End) - labelHeight + 1);
                }
            }
        }
    }
    else if (n->SuffixIndex > -1 && n->SuffixIndex < Size1) { //suffix of X
        return -2;//Mark TNode as X
    }
    else if (n->SuffixIndex >= Size1) { //suffix of Y
        return -3;//Mark TNode as Y
    }
    return n->SuffixIndex;
}

TSuffixTree::~TSuffixTree() {
    delete Root;
}