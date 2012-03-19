////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNPC.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:13 AM
//    Purpose				:	NPC character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CNPC.h"
#include "CPlayer.h"
#include "../Input Manager/CInputManager.h"
#include "../Messaging/CEventSystem.h"
#include "../Messaging/CMessageSystem.h"
#include "../States/CGameplayState.h"

#define GAMEPLAY CGameplayState::GetInstance()

// Constructor
CNPC::CNPC(const char* szName, bool bActiveTalk, double dRange, int sndNPC,
	double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CBaseCharacter(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth, uiHeight, bActive, uiMaxHealth, uiAttackDamage)
{
	m_szName = szName;
	
	m_bActiveTalk = bActiveTalk;
	m_sndNPC = sndNPC;
	m_dRange = dRange;
	m_bTalk = false;
	m_szText = "";
	
	m_uiTextIndex = 0;
	m_dwTimeStamp = 0;
	
	m_pCurrentSpeech = nullptr;
	m_nCurrentOption = -1;

	m_pCurrentDialogue = nullptr;
}
CNPC::~CNPC()
{
	CEventSystem::GetInstance()->UnregisterFromEvent("destroyenemy",this);
}
// Load NPC's speech
void CNPC::LoadText(char const * const szFilename)
{
	// Create XML doc
	TiXmlDocument doc;
	// Try to load the file, and if it fails, return false
	if(!doc.LoadFile(szFilename))
		return;

	// Get a pointer to the root
	TiXmlElement* pRoot = doc.RootElement();
	// If that wasn't created properly too, get out of here
	if(!pRoot)
		return;

	// Temporary variables to store the data we'll read
	const char* szSpeechText = "";
	const char* szSpeechName = "";
	const char* szOptionText = "";
	const char* szOptionName = "";

	TiXmlElement* xSpeechNode = pRoot->FirstChildElement("SpeechNode");

	if(!xSpeechNode)
		return;

	while(xSpeechNode)
	{
		// Read the speech node stuff
		szSpeechName = xSpeechNode->Attribute("name");
		szSpeechText = xSpeechNode->Attribute("text");
		
		// Hacks for tests
		///string szEvent = xSpeechNode->Attribute("event");
		//////////////////

		tSpeechNode* pSpeechNode = m_Dialogue.AddSpeechNode(szSpeechName, GAMEPLAY->BreakDownStrings(szSpeechText, 50, 52));

		TiXmlElement* xOptionNode = xSpeechNode->FirstChildElement("Option");
		
		while(xOptionNode)
		{
			// Read the option stuff
			szOptionText = xOptionNode->Attribute("text");

			// Add the option to the node
			pSpeechNode->AddOption(szOptionText);

			xOptionNode = xOptionNode->NextSiblingElement("Option");
		}

		xSpeechNode = xSpeechNode->NextSiblingElement("SpeechNode");
	}

	
	const char* szSpeechA = "";
	const char* szSpeechB = "";
	int nOption = 0;


	TiXmlElement* xConnection = pRoot->FirstChildElement("Connection");
	while(xConnection)
	{
		szSpeechA = xConnection->Attribute("speechA");
		szSpeechB = xConnection->Attribute("speechB");
		xConnection->Attribute("option", &nOption);

		m_Dialogue.Connect(szSpeechA, nOption - 1, szSpeechB);

		xConnection = xConnection->NextSiblingElement("Connection");
	}

	m_pCurrentDialogue = &m_Dialogue;
	m_pCurrentSpeech = (*m_pCurrentDialogue)[0];
	m_nCurrentOption = 0;
}

// Common routines
void CNPC::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);

	if(m_bTalk)
	{
		if(timeGetTime() - m_dwTimeStamp > 50)
		{
			if(m_pCurrentSpeech)
			{
				if(m_uiTextIndex < m_pCurrentSpeech->GetText().size())
				{
					m_uiTextIndex++;
					m_dwTimeStamp = timeGetTime();
				}
			}
			else
			{
				if(m_uiTextIndex < m_szText.size())
				{
					m_uiTextIndex++;
					m_dwTimeStamp = timeGetTime();
				}
			}
		}
	}

	if(GetCollisionRect().ContainsPoint(CPlayer::GetInstance()->GetInteractivePoint()))
	{
		if(m_bActiveTalk)
			if(CPlayer::GetInstance()->Lock())
				m_bTalk = true;
	}
	else if(m_bTalk)
	{
		m_bTalk = false;
		m_uiTextIndex = 0;
		CPlayer::GetInstance()->Unlock();
		GAMEPLAY->SetMessageBox(false);
	}
}

void CNPC::Input(void)
{
	CBaseCharacter::Input();

	if(CInputManager::GetInstance()->GetPressedA())
	{
		if(!m_bTalk)
		{
			if(GetCollisionRect().ContainsPoint(CPlayer::GetInstance()->GetInteractivePoint()))
			{
				if(CPlayer::GetInstance()->Lock())
				{
					m_pCurrentSpeech = (*m_pCurrentDialogue)[0];
					m_bTalk = true;
					m_uiTextIndex = 0;
				}
			}
		}
		else
		{
			// If player pressed Enter and NPC has finished talking...
			if(m_uiTextIndex == m_pCurrentSpeech->GetText().size() && m_nCurrentOption != -1)
			{
				// ...and if player has selected an option to answer...
				if(m_pCurrentSpeech->GetOption(m_nCurrentOption))
				{
					// ...the NPC should get another speech to answer the player.
					m_pCurrentSpeech = m_pCurrentSpeech->GetOption(m_nCurrentOption)->GetNextSpeech();

					if(m_pCurrentSpeech == nullptr)
					{
						m_bTalk = false;
						CPlayer::GetInstance()->Unlock();
						GAMEPLAY->SetMessageBox(false);
					}
				}
				else
				{
					// If there's no option, just stop talking
					m_bTalk = false;
					CPlayer::GetInstance()->Unlock();
					GAMEPLAY->SetMessageBox(false);
				}
	
				m_uiTextIndex = 0;
			}
			// If player pressed Enter and NPC is talking
			// but he didn't finish talking yet, force him to finish
			else
				m_uiTextIndex = m_pCurrentSpeech->GetText().size();
		}
	}
		

	if(m_bTalk && CInputManager::GetInstance()->GetPressedB())
	{
		m_bTalk = false;
		CPlayer::GetInstance()->Unlock();
		GAMEPLAY->SetMessageBox(false);
		m_uiTextIndex = 0;
	}


	if(m_pCurrentSpeech)
	{
		if(m_uiTextIndex == m_pCurrentSpeech->GetText().size())
		{
			if(CInputManager::GetInstance()->GetPressedRight())
				m_nCurrentOption++;
			if(CInputManager::GetInstance()->GetPressedLeft())
				m_nCurrentOption--;

			if(m_nCurrentOption >= (int)m_pCurrentSpeech->GetNumberOfOptions())
				m_nCurrentOption = 0;
			else if(m_nCurrentOption < 0)
				m_nCurrentOption = m_pCurrentSpeech->GetNumberOfOptions() - 1;
		}
	}
}

void CNPC::Render(void)
{
	CBaseCharacter::Render();

	if(m_bTalk)
	{
		string textToDraw = "";

		if(!m_szText.empty())
		{
			for(unsigned int i=0; i < m_uiTextIndex; ++i)
				textToDraw += m_szText[i];
		}
		else
		{
			for(unsigned int i=0; i < m_uiTextIndex; ++i)
				textToDraw += m_pCurrentSpeech->GetText()[i];
		}

		tOptionNode* pCurrentOption = nullptr;
		if(m_pCurrentSpeech)
		{
			if(m_uiTextIndex == m_pCurrentSpeech->GetText().size() && m_nCurrentOption != -1)
				pCurrentOption = m_pCurrentSpeech->GetOption(m_nCurrentOption);
		}

		string szCurrentOption = "";
		if(pCurrentOption)
			szCurrentOption = pCurrentOption->GetText();

		GAMEPLAY->SetMessageBox(m_bTalk, m_szName, textToDraw, szCurrentOption);
	}
}
void CNPC::HandleEvent(CEvent* pEvent)
{
}