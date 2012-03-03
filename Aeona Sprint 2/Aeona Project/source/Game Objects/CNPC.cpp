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

// Constructor
CNPC::CNPC(bool bActiveTalk, double dRange, int sndNPC, CBitmapFont* pFont,
	double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,
	unsigned int uiMaxHealth, unsigned int uiAttackDamage)
	: CBaseCharacter(dPositionX, dPositionY, uiSpeed, nImageID, uiWidth, uiHeight, bActive, uiMaxHealth, uiAttackDamage)
{
	m_bActiveTalk = bActiveTalk;
	m_sndNPC = sndNPC;
	m_dRange = dRange;
	m_bTalk = false;
	m_szText = "";
	m_pFont = pFont;
	m_uiTextIndex = 0;
	m_dwTimeStamp = 0;
	m_imgMsgBox = TEX_MNG->LoadTexture("resource/MessageBox.png");
	m_pCurrentSpeech = nullptr;
	m_nCurrentOption = -1;
}

// Load NPC's speech
void CNPC::LoadText(char* szFilename)
{
	//if(szFilename)
	//{
	//	// For now let's just set the text to this
	//	m_szText = szFilename;
	//	return;
	//}

	// Define dialogue data structure
	/*m_Dialogue.AddSpeechNode("Hi, I am a NPC. How are you?");
	m_pCurrentSpeech = m_Dialogue[0];

	tSpeechNode* answer = nullptr;
	
	m_Dialogue[0]->AddOption("I am fine, thanks.");
	m_nCurrentOption = 0;
	answer = m_Dialogue.AddSpeechNode("Cool. I am fine too.");
	m_Dialogue[0]->GetOption(0)->SetNextSpeech(answer);
	answer->AddOption("Nice to meet you")->SetNextSpeech(m_Dialogue.AddSpeechNode("Nice to meet you too."));
	answer->AddOption("I didn't ask.")->SetNextSpeech(m_Dialogue.AddSpeechNode("I don't like you."));
	
	m_Dialogue[0]->AddOption("I am bad");
	answer = m_Dialogue.AddSpeechNode("Really? What happened?");
	m_Dialogue[0]->GetOption(1)->SetNextSpeech(answer);
	answer->AddOption("A friend of mine died today.")->SetNextSpeech(m_Dialogue.AddSpeechNode("Oh, I'm sorry for you."));
	answer->AddOption("Why should I tell you?")->SetNextSpeech(m_Dialogue.AddSpeechNode("I don't care anyway..."));

	m_Dialogue[0]->AddOption("Shut up");
	answer = m_Dialogue.AddSpeechNode("That's not really polite.");
	m_Dialogue[0]->GetOption(2)->SetNextSpeech(answer);
	answer->AddOption("I was kidding...")->SetNextSpeech(m_Dialogue.AddSpeechNode("That was not funny, my friend."));
	answer->AddOption("Do I look like I care?")->SetNextSpeech(m_Dialogue.AddSpeechNode("Just get out of my way."));

*/




	// TODO: Read that XML file in the dialogue
	// data structure

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
		tSpeechNode* pSpeechNode = m_Dialogue.AddSpeechNode(szSpeechName, szSpeechText);

		TiXmlElement* xOptionNode = xSpeechNode->FirstChildElement("Option");
		if(!xOptionNode)
			return;

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

	m_pCurrentSpeech = m_Dialogue[0];
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

	// Get the distance between the player and the NPC
	double dDistance;
	dDistance = GetPosition().GetDistanceUntil(CPlayer::GetInstance()->GetPosition());

	if(dDistance < m_dRange)
	{
		if(m_bActiveTalk)
			m_bTalk = true;
	}
	else
	{
		m_bTalk = false;
		m_uiTextIndex = 0;
	}
}

void CNPC::Input(void)
{
	CBaseCharacter::Input();

	if(CInputManager::GetInstance()->GetPressedA())
	{
		if(m_bTalk)
		{
			// If NPC is talking and Enter is pressed, answer him
			if(m_uiTextIndex == m_pCurrentSpeech->GetText().size() && m_nCurrentOption != -1)
			{
				if(m_pCurrentSpeech->GetOption(m_nCurrentOption))
					m_pCurrentSpeech = m_pCurrentSpeech->GetOption(m_nCurrentOption)->GetNextSpeech();
				else
				{
					m_pCurrentSpeech = m_Dialogue[0];
					m_bTalk = false;
				}

				m_uiTextIndex = 0;
			}
		}
		// Else if NPC is not talking and he's a passive speaker, start the conversation
		else if(!m_bActiveTalk)
		{
			// Get the distance between the player and the NPC
			double dDistance;
			dDistance = GetPosition().GetDistanceUntil(CPlayer::GetInstance()->GetPosition());

			if(dDistance < m_dRange)
				m_bTalk = true;
			m_uiTextIndex = 0;
		}
	}

	if(m_bTalk && CInputManager::GetInstance()->GetPressedB())
	{
		m_bTalk = false;
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

			if(m_nCurrentOption >= m_pCurrentSpeech->GetNumberOfOptions())
				m_nCurrentOption = 0;
			else if(m_nCurrentOption < 0)
				m_nCurrentOption = m_pCurrentSpeech->GetNumberOfOptions() - 1;
		}
	}
}

void CNPC::Render(void)
{
	CBaseCharacter::Render();

	int nDrawLocationX;
	if(GAME->GetMapLocation() == 0)
		nDrawLocationX = 5;
	else
		nDrawLocationX = 105;


	if(m_bTalk)
	{
		char* textToDraw = new char[m_uiTextIndex + 1];

		if(!m_szText.empty())
		{
			for(int i=0; i < m_uiTextIndex; ++i)
				textToDraw[i] = m_szText[i];
			textToDraw[m_uiTextIndex] = '\0';
		}
		else
		{
			for(int i=0; i < m_uiTextIndex; ++i)
				textToDraw[i] = m_pCurrentSpeech->GetText()[i];
			textToDraw[m_uiTextIndex] = '\0';
		}

		if(m_pFont)
		{
			TEX_MNG->Draw(m_imgMsgBox, nDrawLocationX, 500);
			D3D->GetSprite()->Flush();

			m_pFont->Write(textToDraw, nDrawLocationX + 15, 510, D3DCOLOR_XRGB(255, 255, 255));

			if(m_pCurrentSpeech)
			{
				if(m_uiTextIndex == m_pCurrentSpeech->GetText().size() && m_nCurrentOption != -1)
				{
					tOptionNode* pCurrentOption = m_pCurrentSpeech->GetOption(m_nCurrentOption);
					// Render the current option
					if(m_pFont && pCurrentOption)
					{
						m_pFont->Write(pCurrentOption->GetText().c_str(), nDrawLocationX + 30, 550, D3DCOLOR_XRGB(255, 255, 255));
					}
				}
			}
		}

	}
}