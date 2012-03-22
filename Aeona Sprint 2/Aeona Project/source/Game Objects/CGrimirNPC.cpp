
#include "StdAfx.h"
#include "CGrimirNPC.h"
#include "../Input Manager/CInputManager.h"
#include "../Game Objects/CPlayer.h"
#include "../StdAfx.h"
#include "../States/CGameplayState.h"

// Constructor
CGrimirNPC::CGrimirNPC(const char* szName, bool bActiveTalk, double dRange, int sndNPC,
	double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CNPC(szName, bActiveTalk, dRange, sndNPC, dPositionX, dPositionY, uiSpeed, nImageID, uiWidth, uiHeight, bActive, uiMaxHealth, uiAttackDamage)
{

	bHackToFixGrimir = true;
}

CGrimirNPC::~CGrimirNPC()
{
}

// Load NPC's speech
void CGrimirNPC::LoadText(char const * const szFilename)
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

	TiXmlElement* xDialogue = pRoot->FirstChildElement("Dialogue");
	if(!xDialogue)
		return;

	for(int i=0; i < 3; ++i)
	{
		// Temporary variables to store the data we'll read
		const char* szSpeechText = "";
		const char* szSpeechName = "";
		const char* szOptionText = "";
		const char* szOptionName = "";

		TiXmlElement* xSpeechNode = xDialogue->FirstChildElement("SpeechNode");

		if(!xSpeechNode)
			return;
		
		while(xSpeechNode)
		{
			// Read the speech node stuff
			szSpeechName = xSpeechNode->Attribute("name");
			szSpeechText = xSpeechNode->Attribute("text");
			tSpeechNode* pSpeechNode = m_GrimirDialogues[i].AddSpeechNode(szSpeechName,
				CGameplayState::GetInstance()->BreakDownStrings(szSpeechText, 50, 52));

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


		TiXmlElement* xConnection = xDialogue->FirstChildElement("Connection");
		while(xConnection)
		{
			szSpeechA = xConnection->Attribute("speechA");
			szSpeechB = xConnection->Attribute("speechB");
			xConnection->Attribute("option", &nOption);

			m_GrimirDialogues[i].Connect(szSpeechA, nOption - 1, szSpeechB);

			xConnection = xConnection->NextSiblingElement("Connection");
		}

		xDialogue = xDialogue->NextSiblingElement("Dialogue");
	}

	m_pCurrentDialogue = &m_GrimirDialogues[0];
	m_pCurrentSpeech = (*m_pCurrentDialogue)[0];
	m_nCurrentOption = 0;

}

// Common routines
void CGrimirNPC::Update(float fElapsedTime)
{
	CNPC::Update(fElapsedTime);
}

void CGrimirNPC::Render(void)
{
	CNPC::Render();
}

void CGrimirNPC::Input(void)
{
	if(CInputManager::GetInstance()->GetPressedA())
	{
		if(CPlayer::GetInstance()->HasFlower())
		{
			if(m_pCurrentDialogue == &m_GrimirDialogues[0])
			{
				if(GetCollisionRect().ContainsPoint(CPlayer::GetInstance()->GetInteractivePoint()))
				{
					if(CPlayer::GetInstance()->Lock())
					{
						m_pCurrentDialogue = &m_GrimirDialogues[1];
						m_pCurrentSpeech = (*m_pCurrentDialogue)[0];
						m_bTalk = true;
						CPlayer::GetInstance()->AcquireWeapon(CPlayer::WEAPON_SWORD);
						CPlayer::GetInstance()->CycleWeapon();
						//AUDIO->SFXPlaySound(AUDIO->SFXLoadSound("resource/sound/GetItem.wav"));
					}
				}
			}
			else
			{
				m_pCurrentDialogue = &m_GrimirDialogues[2];
			}
		}
		else
		{
			m_pCurrentDialogue = &m_GrimirDialogues[0];
		}
	}

	CNPC::Input();
}
