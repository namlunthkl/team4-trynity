#ifndef C_DIALOGUE_LIST_H_
#define C_DIALOGUE_LIST_H_

class tSpeechNode;
class tOptionNode;

class CDialogueList
{
	vector<tSpeechNode*> m_vpDialogue;

public:
	tSpeechNode* AddSpeechNode(string szName, string szSpeech);
	tSpeechNode* operator[](unsigned int uiIndex);
	~CDialogueList(void);
	inline unsigned int GetNumberOfSpeechs(void) { return m_vpDialogue.size(); }
	void Connect(string szSpeechA, unsigned int nOption, string szSpeechB);
};

class tSpeechNode
{
	string m_szSpeech;
	string m_szName;
	vector<tOptionNode*> m_vpOptions;

public:
	tSpeechNode(string szName, string szSpeech);
	tSpeechNode& operator=(const tSpeechNode& p);
	~tSpeechNode(void);

	tOptionNode* AddOption(string szOptionText);
	tOptionNode* GetOption(unsigned int uiIndex);
	inline unsigned int GetNumberOfOptions(void) { return m_vpOptions.size(); }
	inline string GetText(void) { return m_szSpeech; }
	inline string GetName(void) { return m_szName; }
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