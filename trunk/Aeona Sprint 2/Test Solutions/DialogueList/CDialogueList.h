#ifndef C_DIALOGUE_LIST_H_
#define C_DIALOGUE_LIST_H_

#include <vector>
using std::vector;
#include <string>
using std::string;

class tSpeechNode;
class tOptionNode;

class CDialogueList
{
	vector<tSpeechNode*> m_vpDialogue;

public:
	tSpeechNode* AddSpeechNode(string m_szSpeech);
	tSpeechNode* operator[](unsigned int uiIndex);
	~CDialogueList(void);
	inline unsigned int GetNumberOfSpeechs(void) { return m_vpDialogue.size(); }
};

class tSpeechNode
{
	string m_szSpeech;
	vector<tOptionNode*> m_vpOptions;

public:
	tSpeechNode(string szSpeech);
	tSpeechNode& operator=(const tSpeechNode& p);
	~tSpeechNode(void);

	tOptionNode* AddOption(string szOptionText);
	tOptionNode* GetOption(unsigned int uiIndex);
	inline unsigned int GetNumberOfOptions(void) { return m_vpOptions.size(); }
	inline string GetText(void) { return m_szSpeech; }
};

class tOptionNode
{
	string m_szOptionText;
	tSpeechNode* m_pNextSpeech;

public:
	tOptionNode(string szOptionText);
	inline void SetNextSpeech(tSpeechNode* pSpeechNode) { m_pNextSpeech = pSpeechNode; }
	inline tSpeechNode* GetNextSpeech(void) { return m_pNextSpeech; }
	inline string GetText(void) { return m_szOptionText; }
};



#endif // C_DIALOGUE_LIST_H_