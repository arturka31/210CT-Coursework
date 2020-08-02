#include "BSTree.h"

CBSTree::CBSTree(const std::string &word_root) 
{ 
    m_pRoot = new CTreeNode(word_root); 
}

CBSTree::~CBSTree() 
{ 
    ClearMemory(m_pRoot);
};

void CBSTree::AddNewWord(const std::string &word) 
{
    Insert(m_pRoot, word);
}

int CBSTree::GetTotalWordCount(const std::string &word) const
{
    int nCount = 0;
    bool bFoundAtleastOne = false;
    search(m_pRoot, nCount, word, bFoundAtleastOne);
    return nCount;
}

void CBSTree::DeleteWord(const std::string &word) 
{
    m_pRoot = DeleteNode(m_pRoot, word, true);
}

CBSTree::CTreeNode *CBSTree::Insert(CTreeNode *pCurNode, const std::string &word)
{
    if (!pCurNode)
    {
        pCurNode = new CTreeNode(word);
        return pCurNode;
    }

    if (word.compare(pCurNode->m_word) < 0) {
        pCurNode->m_pLeftNode = Insert(pCurNode->m_pLeftNode, word);
    }
    else {
        pCurNode->m_pRightNode = Insert(pCurNode->m_pRightNode, word);
    }

    return pCurNode;
}

CBSTree::CTreeNode *CBSTree::search(CTreeNode *pNode, int &nTimesAppeared, const std::string &word, bool &bFoundAtleastOne) const
{
    if (!pNode) {
        return pNode;
    }

    int nResult = pNode->m_word.compare(word);
    if (nResult == 0)
    {
        nTimesAppeared++;
        bFoundAtleastOne = true;
        return search(pNode->m_pRightNode, nTimesAppeared, word, bFoundAtleastOne);
    }

    // Only need to search to the left of the subtree by design until word is no longer found 
    // so by definition if found search can be ended.
    if (bFoundAtleastOne) {
        return nullptr;
    }

    if (nResult < 0) {
        return search(pNode->m_pRightNode, nTimesAppeared, word, bFoundAtleastOne);
    }

    return search(pNode->m_pLeftNode, nTimesAppeared, word, bFoundAtleastOne);
}

CBSTree::CTreeNode *CBSTree::GatherNodesToDelete(CTreeNode *pNode, const std::string &word, std::vector<CTreeNode *> &nodes)
{
    CTreeNode *pCurrent = pNode;

    while (pCurrent && pCurrent->m_pRightNode && pCurrent->m_pRightNode->m_word.compare(word) == 0)
    {
        nodes.push_back(pCurrent);
        pCurrent = pCurrent->m_pRightNode;
    }

    return pCurrent;
}

CBSTree::CTreeNode *CBSTree::GetLeftMostLeaf(CTreeNode *pNode)
{
    CTreeNode *pCurrent = pNode;
    while (pCurrent && pCurrent->m_pLeftNode) pCurrent = pCurrent->m_pLeftNode;
    return pCurrent;
}

void CBSTree::DeleteNodes(std::vector<CTreeNode *> &nodes)
{
    for (CTreeNode *pNode : nodes) {
        delete pNode;
    }
}

CBSTree::CTreeNode *CBSTree::DeleteNode(CTreeNode *pNode, const std::string &word, const bool bMultipleNodes)
{
    if (!pNode) return nullptr;
    const int nCmpResult = word.compare(pNode->m_word);
    if (nCmpResult < 0) pNode->m_pLeftNode = DeleteNode(pNode->m_pLeftNode, word, bMultipleNodes);
    else if (nCmpResult > 0) pNode->m_pRightNode = DeleteNode(pNode->m_pRightNode, word, bMultipleNodes);
    else
    {
        std::vector<CTreeNode *> nodes;
        CTreeNode *pLastSameWordNode = bMultipleNodes ? GatherNodesToDelete(pNode, word, nodes) : pNode;

        if (!pLastSameWordNode->m_pLeftNode)
        {
            CTreeNode *pRightNode = pLastSameWordNode->m_pRightNode;
            nodes.push_back(pLastSameWordNode);
            DeleteNodes(nodes);
            return pRightNode;
        }
        else if (!pLastSameWordNode->m_pLeftNode)
        {
            CTreeNode *pLeft = pLastSameWordNode->m_pLeftNode;
            nodes.push_back(pLastSameWordNode);
            DeleteNodes(nodes);
            return pLeft;
        }

        CTreeNode *pTempNode = GetLeftMostLeaf(pLastSameWordNode->m_pRightNode);
        pLastSameWordNode->m_word = pTempNode->m_word;
        pLastSameWordNode->m_pRightNode = DeleteNode(pLastSameWordNode->m_pRightNode, pTempNode->m_word, false);
        DeleteNodes(nodes);
        return pLastSameWordNode;
    }
    return pNode;
}

void CBSTree::ClearMemory(CTreeNode *pNode)
{
    if (!pNode) return;
    ClearMemory(pNode->m_pLeftNode);
    ClearMemory(pNode->m_pRightNode);
    delete pNode;
}

CBSTree::CTreeNode::CTreeNode(const std::string &word)
{
    m_word          = word;
    m_pLeftNode     = nullptr;
    m_pRightNode    = nullptr;
}

CBSTree::CTreeNode::~CTreeNode()
{

}