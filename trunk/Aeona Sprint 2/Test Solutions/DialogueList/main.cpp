#include <iostream>
using namespace std;

#include "CDialogueList.h"

int main(void)
{
	CDialogueList dialogue;

	dialogue.AddSpeechNode("Hi, I'm a NPC. How are you?");
	
	tSpeechNode* answer = nullptr;
	
	dialogue[0]->AddOption("I'm fine, thanks.");
	answer = dialogue.AddSpeechNode("Cool. I'm fine too.");
	dialogue[0]->GetOption(0)->SetNextSpeech(answer);
	answer->AddOption("Nice to meet you")->SetNextSpeech(dialogue.AddSpeechNode("Nice to meet you too."));
	answer->AddOption("I didn't ask.")->SetNextSpeech(dialogue.AddSpeechNode("I don't like you."));
	
	dialogue[0]->AddOption("I'm bad.");
	answer = dialogue.AddSpeechNode("Really? What happened?");
	dialogue[0]->GetOption(1)->SetNextSpeech(answer);
	answer->AddOption("My best friend died today.")->SetNextSpeech(dialogue.AddSpeechNode("Oh, I'm sorry for you."));
	answer->AddOption("Why should I tell you?")->SetNextSpeech(dialogue.AddSpeechNode("I don't care anyway..."));

	dialogue[0]->AddOption("STFU.");
	answer = dialogue.AddSpeechNode("That's not really polite.");
	dialogue[0]->GetOption(2)->SetNextSpeech(answer);
	answer->AddOption("I was kidding...")->SetNextSpeech(dialogue.AddSpeechNode("That was not fun, my friend."));
	answer->AddOption("Do I look like I care?")->SetNextSpeech(dialogue.AddSpeechNode("Just get out of my way."));

	while(true)
	{
		tSpeechNode* pSpeech = dialogue[0];

		while(pSpeech)
		{
			system("cls");
			cout << pSpeech->GetText() << endl << endl;

			if(pSpeech->GetNumberOfOptions() == 0)
			{
				pSpeech = nullptr;
				break;
			}

			for(int i=0; i < pSpeech->GetNumberOfOptions(); ++i)
			{
				cout << i+1 << ") " << pSpeech->GetOption(i)->GetText() << endl;
			}

			int nChoice;
			cin >> nChoice;

			if(pSpeech->GetOption(nChoice - 1))
				pSpeech = pSpeech->GetOption(nChoice - 1)->GetNextSpeech();
			else
				pSpeech = nullptr;
		}


		system("pause");
	}


	return 0;
}