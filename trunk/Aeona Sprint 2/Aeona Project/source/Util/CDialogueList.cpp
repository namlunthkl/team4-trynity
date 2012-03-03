#include "StdAfx.h"
#include "CDialogueList.h"

// Dialogue List
tSpeechNode* CDialogueList::AddSpeechNode(string szName, string szSpeech)
{
	tSpeechNode* pSpeechNode = new tSpeechNode(szName, szSpeech);
	m_vpDialogue.push_back(pSpeechNode);
	return pSpeechNode;
}
void CDialogueList::Connect(string szSpeechA, unsigned int nOption, string szSpeechB)
{
	tSpeechNode* pSpeechA = nullptr;
	tSpeechNode* pSpeechB = nullptr;
	tOptionNode* pOption = nullptr;

	for(unsigned int i=0; i < m_vpDialogue.size(); ++i)
	{
		if(m_vpDialogue[i]->GetName() == szSpeechA)
		{
			pSpeechA = m_vpDialogue[i];
		}
		if(m_vpDialogue[i]->GetName() == szSpeechB)
		{
			pSpeechB = m_vpDialogue[i];
		}
	}

	if(pSpeechA)
		pOption = pSpeechA->GetOption(nOption);

	if(pOption && pSpeechB )
	{
		// CONNECT!
		pOption->SetNextSpeech(pSpeechB);
	}
}
tSpeechNode* CDialogueList::operator[](unsigned int uiIndex)
{
	if(uiIndex < m_vpDialogue.size())
		return m_vpDialogue[uiIndex];
	else
		return nullptr;
}
CDialogueList::~CDialogueList(void)
{
	for(unsigned int i=0; i < m_vpDialogue.size(); ++i)
	{
		delete m_vpDialogue[i];
		m_vpDialogue[i] = nullptr;
	}

	m_vpDialogue.clear();
}

// Speech Nodes
tSpeechNode::tSpeechNode(string szName, string szSpeech)
{
	m_szName = szName;
	m_szSpeech = szSpeech;
}
tSpeechNode& tSpeechNode::operator=(const tSpeechNode& p)
{
	m_szSpeech = p.m_szSpeech;
	
	for(unsigned int i=0; i < m_vpOptions.size(); ++i)
	{
		delete m_vpOptions[i];
		m_vpOptions[i] = nullptr;
	}

	m_vpOptions.clear();

	for(unsigned int i=0; i < p.m_vpOptions.size(); ++i)
	{
		m_vpOptions.push_back(p.m_vpOptions[i]);
	}

	return *this;
}
tOptionNode* tSpeechNode::GetOption(unsigned int uiIndex)
{
	if(uiIndex < m_vpOptions.size())
		return m_vpOptions[uiIndex];
	else
		return nullptr;
}
tSpeechNode::~tSpeechNode(void)
{
	for(unsigned int i=0; i < m_vpOptions.size(); ++i)
	{
		delete m_vpOptions[i];
		m_vpOptions[i] = nullptr;
	}

	m_vpOptions.clear();
}
tOptionNode* tSpeechNode::AddOption(string szOptionText)
{
	tOptionNode* pOptionNode = new tOptionNode(szOptionText);
	m_vpOptions.push_back(pOptionNode);
	return pOptionNode;
}

// Option Nodes
tOptionNode::tOptionNode(string szOptionText)
{
	m_szOptionText = szOptionText;
	m_pNextSpeech = 0;
}

