#pragma once

#ifndef T_BST_H
#define T_BST_H

#include "T_BSTN.h"
#include "T_Array.h"

template<typename K, typename V>
class T_BST
{
public:
    T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {} // constructor
    string getName() { return name; }
    int size() const { return num_entry; }
    bool empty() const { return num_entry == 0; }
    void clear();  // BST�� ���� �޸� ��ȯ�ϴ� �Լ�
    T_BSTN<K, V>* getRoot() { return _root; }
    T_BSTN<K, V>** getRootAddr() { return &_root; }
    T_Entry<K, V>& getRootEntry() { return _root->getEntry(); }
    T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp);  // BST�� ������ ����Ͽ� �޾ƿ� BSTN�� ����� �Լ� 
    void insertInOrder(const T_Entry<K, V> entry);  // ������ �°� insert
    void insertAndRebalance(T_Entry<K, V> e);  // ������ �°� insert �� rebalancing
    void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);  // ������ ũ�⿡ ���� ��� �湮
    void traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);  // subRoot ��� �켱 �湮
    void traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);  // subRoot ��带 ���߿� �湮
    T_BSTN<K, V>* searchBSTN(K k);
    T_Entry<K, V>& minEntry();
    T_Entry<K, V>& maxEntry();
    void fprint_with_Depth(ostream& fout);
    void fprint_inOrder(ostream& fout);
protected:
    T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot);
    T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot);
    T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e);
    T_BSTN<K, V>* _insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e);
    T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot);  // CurRoot�� NewRoot�� Rc�� �̵�
    T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot);  // CurRoot�� NewRoot�� Lc�� �̵�
    T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot);  // _rotate_LL -> _rotate_RR
    T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot);  // _rotate_RR -> _rotate_LL
    int _getHeight(T_BSTN<K, V>* pTN);  // Lc, Rc �� ���� height ��ȯ
    int _getHeightDiff(T_BSTN<K, V>* pTN);  // Lc height - Rc height
    T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN);  // height�� ���� BST balancing
    T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k);  // search key node
    void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth);
    void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout);
private:
    T_BSTN<K, V>* _root;  // pointer to the root
    int num_entry;  // number of tree nodes
    string name;
};

template<typename K, typename V>
void T_BST<K, V>::clear()
{
    while (num_entry != 0)
    {
        eraseBSTN(&_root);
    }
    delete _root;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pptoBeErased)
// remove BSTN considering balance of the BST
{
    T_BSTN<K, V>* newSubRoot, * temp, * w, * wlc;
    T_BSTN<K, V>* toBeErased;

    toBeErased = *pptoBeErased;
    if (toBeErased == NULL)
        return NULL;
    if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL))  // no child
    {
        newSubRoot = NULL;
    }
    else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL)) // only left child
    {
        newSubRoot = toBeErased->getpLc();
        newSubRoot->setpPr(toBeErased->getpPr());
    }
    else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL))  // only right child
    {
        newSubRoot = toBeErased->getpRc();
        newSubRoot->setpPr(toBeErased->getpPr());
    }
    else  // tree node to be deleted has both left child and right child
    {
        int heightDiff = _getHeightDiff(toBeErased);
        T_BSTN<K, V>* parDel = toBeErased->getpPr();
        T_BSTN<K, V>* lChild = toBeErased->getpLc();
        T_BSTN<K, V>* rChild = toBeErased->getpRc();
        T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs;
        T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd;
        if (heightDiff > 0)  // left subtree is higher, so put the ioPd in the place of the erased node
        {
            ioPd = _maxBSTN(lChild);  // in-order predecessor (ioPd)
            lcIoPd = ioPd->getpLc();
            parIoPd = ioPd->getpPr();
            newSubRoot = ioPd;
            if (ioPd->getpPr() != toBeErased)
            {
                newSubRoot->setpLc(lChild);
                parIoPd->setpRc(lcIoPd);
                if (lcIoPd != NULL)
                    lcIoPd->setpPr(parIoPd);
            }
            newSubRoot->setpRc(rChild);
            newSubRoot->setpPr(toBeErased->getpPr());
        }
        else
            // right subtree is higher, so put the ioSs in the place of the erased node
        {
            ioSs = _minBSTN(rChild); // in-order successor (ioSs)
            rcIoSs = ioSs->getpRc();
            parIoSs = ioSs->getpPr();
            newSubRoot = ioSs;
            if (ioSs->getpPr() != toBeErased)
            {
                newSubRoot->setpRc(rChild);
                parIoSs->setpLc(rcIoSs);
                if (rcIoSs != NULL)
                    rcIoSs->setpPr(parIoSs);
            }
            newSubRoot->setpLc(lChild);
            newSubRoot->setpPr(toBeErased->getpPr());
        }
        if (lChild != ioPd)
            lChild->setpPr(newSubRoot);
        if (rChild != ioSs)
            rChild->setpPr(newSubRoot);
    }
    if (toBeErased == _root)
        _root = newSubRoot;
    num_entry--; // decrement the number of entries in the BST
    free(toBeErased);
    *pptoBeErased = newSubRoot;
    return newSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> entry)
{
    T_BSTN<K, V>* newPos, ** pChildPos;
    T_BSTN<K, V>* pos;
    T_Entry<K, V> ent;

    if (pp == NULL)
    {
        cout << "Error in creation of BinarySearchTree :";
        cout << " address of the pointer to the Root Node is NULL \n!!";
        exit;
    }
    pos = *pp;
    if (pos == NULL)
    {
        pos = new T_BSTN<K, V>(entry);
        if (parenPos == NULL)
        {
            _root = pos;  // initialize the root node
        }
        pos->setpPr(parenPos);
        *pp = pos;
        num_entry++; // increment the number of elements

        return pos;
    }

    ent = pos->getEntry();
    if (entry < ent)
    {
        pChildPos = pos->getppLc();
        newPos = _insertInOrder(pChildPos, pos, entry);
        if (newPos != NULL)
            pos->setpLc(newPos);

        return NULL;  // only the leaf child is set correctly, while the intermediate node is skipped
    }
    else if (entry >= ent)
    {
        pChildPos = pos->getppRc();
        newPos = _insertInOrder(pChildPos, pos, entry);
        if (newPos != NULL)
            pos->setpRc(newPos);

        return NULL;  // only the leaf child is set correctly, while the intermediate node is skipped
    }
}

template<typename K, typename V>
void T_BST<K, V>::insertInOrder(const T_Entry<K, V> entry)
{
    _insertInOrder(&_root, NULL, entry);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_inOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
    T_BSTN<K, V>* pLc, * pRc;
    T_Entry<K, V> entry;
    V value;
    if (pos == NULL)
        return;
    pLc = pos->getpLc();
    pRc = pos->getpRc();
    traversal_inOrder(pLc, array_value);
    entry = pos->getEntry();
    value = entry.getValue();
    array_value.insertBack(value);
    traversal_inOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::
traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
    T_BSTN<K, V>* pLc, * pRc;
    T_Entry<K, V> entry;
    V value;

    if (pos == NULL)
        return;
    pLc = pos->getpLc();
    pRc = pos->getpRc();
    entry = pos->getEntry();
    value = entry.getValue();
    array_value.insertBack(value);
    traversal_preOrder(pLc, array_value);
    traversal_preOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
    T_BSTN<K, V>* pLc, * pRc;
    T_Entry<K, V> entry;
    V value;

    if (pos == NULL)
        return;
    pLc = pos->getpLc();
    pRc = pos->getpRc();
    traversal_postOrder(pLc, array_value);
    traversal_postOrder(pRc, array_value);
    entry = pos->getEntry();
    value = entry.getValue();
    array_value.insertBack(value);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
    K ent_k;
    T_BSTN<K, V>* pos_result = NULL;

    if (pos == NULL)
        return NULL;
    ent_k = pos->getKey();
    if (ent_k == k)
        pos_result = pos;  // given entry was found here !!
    else if (ent_k > k)
        pos_result = _searchBSTN(pos->getpLc(), k);
    else if (ent_k < k)
        pos_result = _searchBSTN(pos->getpRc(), k);
       
    return pos_result;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::searchBSTN(K key)
{
    T_BSTN<K, V>* pEntry;

    pEntry = _searchBSTN(_root, key);

    return pEntry;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)
{
    T_BSTN<K, V>* pos, * pLc;

    if ((subRoot == NULL) || (NULL == subRoot->getpLc()))
        return subRoot;
    pos = subRoot;
    while ((pos->getpLc()) != NULL)
        pos = pos->getpLc();

    return pos;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)
{
    T_BSTN<K, V>* pos, * pLc;

    if ((subRoot == NULL) || (NULL == subRoot->getpRc()))
        return subRoot;
    pos = subRoot;
    while ((pos->getpRc()) != NULL)
        pos = pos->getpRc();

    return pos;
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()
{
    T_BSTN<K, V>* pMin;

    pMin = _minBSTN(_root);

    return pMin->getEntry();
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
    T_BSTN<K, V>* pMax;

    pMax = _maxBSTN(_root);

    return pMax->getEntry();
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)
{
    T_BSTN<K, V>* pRc, * pLc;

    if ((pLc = pTN->getpLc()) != NULL)
        _fprint_inOrder(pLc, fout);
    fout << pTN->getEntry() << endl;
    if ((pRc = pTN->getpRc()) != NULL)
        _fprint_inOrder(pRc, fout);
}

template<typename K, typename V>
void T_BST<K, V>::fprint_inOrder(ostream& fout)
{
    T_BSTN<K, V>* root = getRoot();

    if (num_entry == 0)
    {
        fout << getName() << " is empty now !!" << endl;
        return;
    }
    _fprint_inOrder(root, fout);
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth)
{
    T_BSTN<K, V>* pRc, * pLc;
    T_Entry<K, V>* pEntry;

    if ((pRc = pTN->getpRc()) != NULL)
        _fprint_with_Depth(pRc, fout, depth + 1);
    for (int i = 0; i < depth; i++)
    {
        fout << "     ";
    }
    fout << pTN->getEntry() << endl;
    if ((pLc = pTN->getpLc()) != NULL)
        _fprint_with_Depth(pLc, fout, depth + 1);
}

template<typename K, typename V>
void T_BST<K, V>::fprint_with_Depth(ostream& fout)
{
    T_BSTN<K, V>* root = getRoot();

    if (num_entry == 0)
    {
        fout << getName() << " is empty now !!" << endl;
        return;
    }
    _fprint_with_Depth(root, fout, 0);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
    int heightDiff = 0;

    heightDiff = _getHeightDiff(*ppTN);
    if (heightDiff > 1)  // left subtree is higher
    {
        if (_getHeightDiff((*ppTN)->getpLc()) > 0)
            *ppTN = _rotate_LL(*ppTN);
        else
            *ppTN = _rotate_LR(*ppTN);
    }
    else if (heightDiff < -1)  // right subtree is higher
    {
        if (_getHeightDiff((*ppTN)->getpRc()) < 0)
            *ppTN = _rotate_RR(*ppTN);
        else
            *ppTN = _rotate_RL(*ppTN);
    }
    return *ppTN;
}

template<typename K, typename V>
void T_BST<K, V>::insertAndRebalance(T_Entry<K, V> entry)
{
    _insertAndRebalance(&_root, NULL, entry);
}
template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> entry)
{
    T_BSTN<K, V>* pTN, ** ppLc, ** ppRc;

    if (*ppTN == NULL)  // ���ο� Ʈ�� ����
    {
        pTN = new T_BSTN<K, V>(entry);
        *ppTN = pTN;
        if (pPr != NULL)  // if not root
            pTN->setpPr(pPr);
        (*ppTN)->setpLc(NULL);
        (*ppTN)->setpRc(NULL);
        num_entry++;

        return *ppTN;
    }

    T_Entry<K, V> bstn_entry;

    bstn_entry = (*ppTN)->getEntry();
    if (entry < bstn_entry)  // entry�� subroot�� ������ ������
    {
        ppLc = (*ppTN)->getppLc();
        pTN = _insertAndRebalance(ppLc, *ppTN, entry);  // subroot�� Lc�� subroot�� ��� insertAndRebalance
        if (ppTN != NULL)
        {
            (*ppTN)->setpLc(pTN);  // left childe�� ����
            *ppTN = _reBalance(ppTN);
        }
    }
    else // entry >= bstn_entry
    {
        ppRc = (*ppTN)->getppRc();
        pTN = _insertAndRebalance(ppRc, *ppTN, entry);
        if (ppTN != NULL)
        {
            (*ppTN)->setpRc(pTN);
            *ppTN = _reBalance(ppTN);
        }
    }
    return *ppTN;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)
{
    int height = 0;
    int height_Lc, height_Rc;

    if (pTN != NULL)
    {
        height_Lc = _getHeight(pTN->getpLc());
        height_Rc = _getHeight(pTN->getpRc());
        if (height_Lc > height_Rc)
            height = 1 + height_Lc;
        else
            height = 1 + height_Rc;
    }
    return height;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN)
{
    int heightDiff = 0;

    if (pTN == NULL)
        return 0;
    heightDiff = _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc());

    return heightDiff;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot) // CurRoot�� NewRoot�� Rc�� �̵�
{
    T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent;

    pCurParent = pCurSubRoot->getpPr(); // CurRoot�� Pr = pCurParent
    pNewSubRoot = pCurSubRoot->getpLc(); // CurRoot�� Lc = NewRoot
    pBR = pNewSubRoot->getpRc();  // NewRoot�� Rc = bR
    pCurSubRoot->setpLc(pBR);  // bR = CurRoot�� Lc
    if (pBR != NULL)  // CurRoot�� Lc !=  NULL
        pBR->setpPr(pCurSubRoot); // CurRoot�� Pr�� ����
    pNewSubRoot->setpRc(pCurSubRoot);  // NewRoot�� Rc = CurRoot
    pNewSubRoot->setpPr(pCurParent);  // NewRoot�� Pr = CurRoot�� ���� Pr
    pCurSubRoot->setpPr(pNewSubRoot);  // CurRoot�� Pr = NewRoot

    return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)  // CurRoot�� NewRoot�� Lc�� �̵�
{
    T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent;

    pCurParent = pCurSubRoot->getpPr();  // CurRoot�� Pr = pCurParent
    pNewSubRoot = pCurSubRoot->getpRc();  // CurRoot�� Rc = NewRoot
    pBL = pNewSubRoot->getpLc();  // NewRoot�� Lc = bL
    pCurSubRoot->setpRc(pBL);  // bL = CurRoot�� Rc
    if (pBL != NULL)  // CurRoot�� Rc !=  NULL
        pBL->setpPr(pCurSubRoot); // pBL�� �θ� ���� root���� ����
    pNewSubRoot->setpLc(pCurSubRoot);  // NewRoot�� Lc = CurRoot
    pNewSubRoot->setpPr(pCurParent);  // NewRoot�� Pr = CurRoot�� ���� Pr
    pCurSubRoot->setpPr(pNewSubRoot);  // CurRoot�� Pr = NewRoot

    return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)  // _rotate_RR -> _rotate_LL
{
    T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
    T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;

    pC = pCurSubRoot;  // pC = CurRoot
    pCurParent = pCurSubRoot->getpPr();  // pCurParent = CurRoot�� Pr
    pA = pC->getpLc();  // pA = CurRoot�� Lc
    pB = pA->getpRc();  // pB = pA�� Rc
    pBL = pB->getpLc();  // pBL = pB�� Lc
    pBR = pB->getpRc();  // pBR = pB�� Rc
    pSubRoot = _rotate_RR(pA);  // pA�� subRoot�� rotate_RR �� newRoot = pSubRoot
    pCurSubRoot->setpLc(pSubRoot);  // pSubRoot = CurRoot�� Lc
    pNewSubRoot = _rotate_LL(pC);  // pC�� subRoot�� rotate_LL �� newRoot = pNewSubRoot
    pNewSubRoot->setpPr(pCurParent);  // pNewSubRoot�� Pr = CurRoot�� ���� Pr
    pA->setpPr(pNewSubRoot);  // setPr with newSubRoot
    pC->setpPr(pNewSubRoot);  // setPr with newSubRoot
    if (pBL != NULL)
        pBL->setpPr(pA);
    if (pBR != NULL)
        pBR->setpPr(pC);

    return pNewSubRoot;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)  // _rotate_LL -> _rotate_RR
{
    T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
    T_BSTN<K, V>* pA, * pB, * pC, * pBL, * pBR;

    // _rotate_LR�� idea ����
    pA = pCurSubRoot;  // pC = CurRoot
    pCurParent = pCurSubRoot->getpPr();  // pCurParent = CurRoot�� Pr
    pC = pA->getpRc();  // pA = CurRoot�� Rc
    pB = pC->getpLc();  // pB = pA�� Lc
    pBL = pB->getpLc();  // pBL = pB�� Lc
    pBR = pB->getpRc();  // pBR = pB�� Rc
    pSubRoot = _rotate_LL(pC);  // pC�� subRoot�� rotate_LL �� newRoot = pSubRoot
    pCurSubRoot->setpRc(pSubRoot);  // pSubRoot = CurRoot�� Rc
    pNewSubRoot = _rotate_RR(pA);  // pA�� subRoot�� rotate_RR �� newRoot = pNewSubRoot
    pNewSubRoot->setpPr(pCurParent);  // pNewSubRoot�� Pr = CurRoot�� ���� Pr
    pA->setpPr(pNewSubRoot);  // setPr with newSubRoot
    pC->setpPr(pNewSubRoot);  // setPr with newSubRoot
    if (pBL != NULL) 
        pBL->setpPr(pA); 
    if (pBR != NULL) 
        pBR->setpPr(pC); 

    return pNewSubRoot;
}

#endif
