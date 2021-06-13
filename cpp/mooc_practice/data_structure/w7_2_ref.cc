#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

#define CTree CNode

template <class Type> class CQueue {
public:
  CQueue(int iSize) : m_pHead(-1), m_pTail(-1) { m_arrQueue = new Type[iSize]; }
  ~CQueue() { delete[] m_arrQueue; }

public:
  void Push(Type value) { m_arrQueue[++m_pTail] = value; }
  void Pop() { m_pHead++; }

  bool IsEmpty() { return m_pHead == m_pTail; }
  Type GetFront() { return m_arrQueue[m_pHead + 1]; }
  int GetSize() { return m_pTail - m_pHead; }

  Type GetAt(int iIndex) { return m_arrQueue[iIndex + m_pHead + 1]; }

private:
  Type *m_arrQueue;
  int m_pHead, m_pTail;
};

template <class Type> class CNode {
public:
  CNode() { Clear(); }
  CNode(Type data, CNode<Type> *pParent = 0) : m_data(data) {
    Clear();
    m_pParent = pParent;
  }

public:
  void Clear() { m_pLeft = m_pRight = m_pParent = 0; }

public:
  Type m_data;
  CNode<Type> *m_pLeft, *m_pRight, *m_pParent;
};

void AddNode(CNode<char> *pRoot, char chTmp, int iTmp) {
  static CNode<char> *sta_pRoot = 0;
  static CNode<char> *sta_pNode = 0;
  if (sta_pRoot != pRoot)
    sta_pRoot = sta_pNode = pRoot;

  CNode<char> *pTmp;
  if (sta_pNode->m_pLeft == 0)
    pTmp = sta_pNode->m_pLeft = new CNode<char>(chTmp, sta_pNode);
  else
    pTmp = sta_pNode->m_pRight = new CNode<char>(chTmp, sta_pNode);

  if (iTmp == 0)
    sta_pNode = pTmp;
  else if (sta_pNode->m_pRight) {
    while (sta_pNode->m_pParent && sta_pNode->m_pParent->m_pRight)
      sta_pNode = sta_pNode->m_pParent;
    sta_pNode = sta_pNode->m_pParent;
  }
}

CQueue<void *> *OutputTree(CQueue<void *> *queTree) {
  CQueue<void *> *queResult = new CQueue<void *>(1000);

  for (int i = 1; i <= queTree->GetSize(); i++)
    // 下面这句是什么意思呢？慢慢看吧
    cout << ((CNode<char> *)(queTree->GetAt(queTree->GetSize() - i)))->m_data
         << ' ';

  CNode<char> *pThis;
  while (!queTree->IsEmpty()) {
    pThis = (CNode<char> *)(queTree->GetFront());
    queTree->Pop();

    pThis = pThis->m_pLeft;
    while (pThis) {
      if (pThis->m_data != '$')
        queResult->Push(pThis);
      pThis = pThis->m_pRight;
    }
  }

  return queResult;
}

int main() {
  int iNodeNum;
  cin >> iNodeNum;

  CTree<char> theTree('!');
  CQueue<void *> *queNode = new CQueue<void *>(1000);

  char chTmp;
  int iTmp;
  for (int i = 1; i <= iNodeNum; i++) {
    getchar();
    chTmp = getchar();
    iTmp = getchar() - '0';

    AddNode(&theTree, chTmp, iTmp);
  }

  queNode->Push(theTree.m_pLeft);
  while (queNode->IsEmpty() != true) {
    queNode = OutputTree(queNode);
  }

  return 0;
}