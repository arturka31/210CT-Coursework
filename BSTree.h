#pragma once

#include <string>
#include <vector>

class CBSTree
{
//Internal node class.
private:
    class CTreeNode
    {
        //Construction/Destruction
    public:
        CTreeNode(const std::string &word);
        ~CTreeNode();

        // Attributes
    public:
        std::string m_word;
        CTreeNode   *m_pLeftNode;
        CTreeNode   *m_pRightNode;
    };
// Construction/Destruction
public:
    CBSTree(const std::string &word_root);
    ~CBSTree();

//API
public:
    void AddNewWord(const std::string &word);
    int GetTotalWordCount(const std::string &word) const;
    void DeleteWord(const std::string &word);

// Internal operations
private:
    CTreeNode *Insert(CTreeNode *pCurNode, const std::string &word);
    CTreeNode *search(CTreeNode *pNode, int &nTimesAppeared, const std::string &word, bool &bFoundAtleastOne) const;
    CTreeNode *GatherNodesToDelete(CTreeNode *pNode, const std::string &word, std::vector<CTreeNode *> &nodes);
    CTreeNode *GetLeftMostLeaf(CTreeNode *pNode);
    void DeleteNodes(std::vector<CTreeNode *> &nodes);
    CTreeNode *DeleteNode(CTreeNode *pNode, const std::string &word, const bool bMultipleNodes);
    void ClearMemory(CTreeNode *pNode);

private:
    CTreeNode *m_pRoot;
};