#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

//for playing sounds (did not work at least in C++ 98)
/*#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")*/

const int NUM_CHAMBERS = 6;
const int NUM_ITEMS = 4;

//stuff to add: dreaming, sound effects, save game

using namespace std;

bool isLetter(char c){
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return true;

    return false; 
}

char toLowerCase(char ch){
    if(ch >= 'A' && ch <= 'Z')
        ch+=' ';
        
    return ch;
}

void displayInvitation(){
	cout << "Dear Worker,\n\nYou have been randomly selected to become a Russian Roulette player. If you choose to accept this invitation you will receive special accomodation, fame, as well as $500 to commence your journey, not only amongst your peers but also throughout the country.\n\nFurther, success in each match merits a two thousand dollar reward ($2000) which may be accumulated over time in order to purchase your own manumission costing eight thousand dollars ($8000), a special reduction from the regular ten thousand dollars ($10000) only available for those who choose to participate in the games./n/nPlease contemplate this extraordinary offer carefully as you may opt out at any point in time even after deciding to take up this contract. However be cautioned that this deal may never reach you again if you decide to turn back.../n/nBest regards." << endl << endl << endl;
}

/*string poorFood[5]{
	"The food is cold.", "I don't want to eat.", "It's tasteless", "I feel nothing eating this.", "Whoever made this should eat my shit after I'm done."
};*/

string richFood[5]{
	"Eggs and steak for breakfast again? At least I'll be eating good before I die.", "They see us as subhuman; yet now they treat us as professional sports players.",
	"I can't go back to eating like I did before.", "I'll eat as much as I want. I might not live to see my next meal.", 
	"Three meals a day... buffet style. Why spend all this money on slaves who fight to the death? Why o I care? I can't complain... I just need to live."
};

void displaySecondMenu(){
	cout << "========== YOU ARE IN YOUR ROOM ==========" << endl << endl;
	cout << "1) View Invitation" << endl;
	cout << "2) Check Calendar" << endl;
	cout << "3) Send a letter" << endl;
	cout << "4) Play Russian Roulette" << endl;
	cout << "5) Eat" << endl;
	cout << "6) Purchase Freedom ($10,000)" << endl;
	cout << "7) View Your Current Standing With The Sponsors" << endl;
	cout << "8) Check Money" << endl;
	cout << "9) Quit Playing Russian Roulette (Exit Game)" << endl;
	cout << "Enter a valid number: ";
	 
}

void displayMainMenu(){

	cout << "========== RUSSIAN ROULETTE ==========" << endl << endl;
	cout << "NOTICE: ONCE YOU LEAVE THE PROGRAM OR YOUR CHARACTER DIES ALL PROGRESS WILL BE RESET. CHOOSING TO CONTINUE OR A NEW GAME MAKES NO DIFFERENCE CURRENTLY" << endl;
	cout << "1) Continue" << endl;
	cout << "2) New Game (WARNING: ALL PROGRESS WILL BE ERASED)" << endl;
	cout << "3) Enter 3 or any other number besides 1 or 2 to quit." << endl;
	cout << "WARNING: GAME MAY BREAK WITH UNEXPECTED INPUT SUCH AS PLACING LETTERS WHERE NUMBERS ARE SUPPOSED TO BE PLACED" << endl << endl;
	cout << "Enter a number: ";
}

bool useMGlass(bool cylinder[], int index){// cost = 1000
	if(cylinder[index] == 1)
		return true;
	else return false;	
}

void loadChamber(bool cylinder[], int numBullets){
	int randChamber;
	
	for(int i = numBullets; i > 0; i-=1){
		int randChamber = rand() % NUM_CHAMBERS;
		if(cylinder[randChamber] == true){
			int j = 0;
			while(j < NUM_CHAMBERS && cylinder[randChamber] == true)
				j+=1;
			cylinder[j] = true;
		}
		else cylinder[randChamber] = true;
		
		numBullets-=1;
	}
}

bool removeBullet(bool cylinder[], int numBullets){
	if(numBullets == 1)
		return false; //no more bullets to remove
			
	for(int i = 0; i < NUM_CHAMBERS; i+=1){
		if(cylinder[i] == true)
			cylinder[i] = false;
	}
	
	return true; //bullet was removed
}

void displayItemMenu(){
	cout << "1) Magnifying Glass - used to see into a narrow opening to verify if there is a round in the current chamber:" << setw(20) << "$1000" << endl;
	cout << "2) Cylinder Cycler - a device which is used to rapidly rotate the revolver's cylinder again:" << setw(20) << "$500" << endl;
	cout << "3) Pliers - used to reach into a chamber and remove one bullet from the cylinder: $750" << setw(20) << "$750" << endl;
	cout << "4) Handcuffs - a guard cuffs your enemy's hands behind their back, preventing them from acting for their turn:" << setw(20) << "$1500" << endl;
	cout << "Enter any other number to exit." << endl;
	cout << "Enter the corresponding number of the item you would like to purchase:" << endl << endl;
	
}

void displayBattleMenu(){
	cout << "What will you do?" << endl << endl;
	cout << "1) Shoot yourself" << endl;
	cout << "2) Shoot competitor" << endl;
	cout << "3) Buy item (items gets used immediately)" << endl << endl;
	cout << "Enter the corresponding number: ";
}

void displayCylinder(bool cylinder[]){//debug
	for(int i = 0; i < NUM_CHAMBERS; i+=1){
		if(cylinder[i] == 1)
			cout << "true\t";
		else cout << "false\t";
	}
	cout << endl << endl;
}

bool playRoulette(int &day, int &playerMoney, int &standing){
	bool cylinder[NUM_CHAMBERS] = {false, false, false, false, false, false};
	int numBullets = rand() % 4 + 1;
	int numItems = 4;
	bool enemyCanAct = true;
	bool playerCanAct = true;
	bool enemyCertainlyKills = false; //enemy used magnifying glass and there is a bullet in the currentChamber
	int decision;
	int currentChamber;
	//debug
	//playerMoney = 999999;

	int enemyMoney = playerMoney + (playerMoney * (day / 10));//initialize enemy money
	if(standing < 2){
		enemyMoney+=500 + (rand() % 200);
		cout << "A guard bumps your shoulder as you enter the room.\nGuard: \"Listen, slave. The sponsors have given your competitor money. Good luck!\", the guard laughs as you sit down to face your opponent." << endl << endl;
	}
	else if(standing >= 4){
		playerMoney+=700 + (rand() % 500);
		cout << "A guard bumps your shoulder as you enter the room.\nGuard: \"Listen. The sponsors have given you some money; your reputation seems quite high among them. Good luck!\" You sit down to face your opponent, feeling some strange hopefulness." << endl << endl;

	}
		
	if(day <= 6 && numBullets > 1)
		numBullets-=1;
	
	
	//load chamber once
	loadChamber(cylinder, numBullets);
	
	//get enemy's name
	string nameList[20] = {"Joe", "Jeff", "Knox", "Valeria", "Leroy", "Daniel", "Oriel", "Alvarez", "Tolstoy", "Gregory Orwell", "G.H. Wells", "Rob Greene", "Alexander", "Napoleon", "Clovis", "Uldren", "Pickethall", "Columbus", "Truman", "Reginald"};
	//choose a random name
	int randName = rand() % 20;
	if(randName <= 10){
		cout << "Your competitor is another worker called " << nameList[randName] << endl << endl;
	}
	
	else{
		cout << "Your competitor is a death row inmate called " << nameList[randName] << endl << endl; 
	}
	
	cout << "An announcement blares as you tremble in your seat: \"THE NUMBER OF BULLETS IS " << numBullets << "\"" << endl << endl;
	
	while(true){//game goes on until one party loses
	
		//displayCylinder(cylinder);//debug
		if(playerCanAct){
			currentChamber = rand() % NUM_CHAMBERS; //spin cylinder
			cout << "You spin the chamber. It is your turn... " << endl << endl;
			//PlaySound(TEXT("RevolverSpin.wav"), NULL, SND_FILENAME | SND_SYNC);
			displayBattleMenu();
			cin >> decision;
			bool playerTurn = true;
			while(playerTurn){
				
				if(decision == 1){
					cout << "You point the gun at yourself..." << endl << endl;
					playerTurn = false;//no longer player's turn
					
					if(cylinder[currentChamber]){
						cout << "The last thing you see is the flash of the barrel and your ears ring just a moment longer as you lose consciousness...\n\nYou died." << endl << endl;
						//PlaySound(TEXT("PistolShot.wav"), NULL, SND_FILENAME | SND_SYNC);
						return false; //lose
					}
					
					else{
						cout << "The gun fails to fire..." << endl << endl;
						//PlaySound(TEXT("GunJam.wav"), NULL, SND_FILENAME | SND_SYNC);
						playerTurn = false;
					}
				}
				
				else if(decision == 2){
					cout << "You point the gun at your competitor..." << endl << endl;
					if(cylinder[currentChamber]){
						cout << "You flinch as the gun fires. Your enemy's head dangles limply, their dull, glazed eyes pierce your soul...\n\nThe person sitting across from you is now dead." << endl << endl;	
						//PlaySound(TEXT("PistolShot.wav"), NULL, SND_FILENAME | SND_SYNC);
						standing+=1;
						day+=(rand() % 3);
						playerMoney+=2000;
						return true; //win
					}
					else{
						cout << "The gun fails to fire..." << endl << endl;
						playerTurn = false;//no longer player's turn
					}
				}
				
				else if(decision == 3){
					int itemDecision;
					displayItemMenu();
					cin >> itemDecision;
					
					switch(itemDecision){
				
						case 1:
							if(playerMoney < 1000){ //check if enemy has enough money
								cout << "You are too poor to afford this." << endl << endl;
								break;
							}
							else{
								playerMoney-=1000;
								if(useMGlass(cylinder, currentChamber)){
									cout << "There is a bullet in the current chamber." << endl << endl;
									break;
								}
								else{
									cout << "There is no bullet in the current chamber." << endl << endl;
								}
							}
					
						case 2:
							if(playerMoney < 500){
								cout << "You are too poor to afford this." << endl << endl;
								break;
							}
							else{
								playerMoney-=500;
								currentChamber = rand() % NUM_CHAMBERS; //spin cylinder
								break;
							}
					
						case 3:
							if(playerMoney < 750){
								cout << "You are too poor to afford this." << endl << endl;
								break;
							}
							else{
								bool removed = removeBullet(cylinder, numBullets);
								if(!removed){
									cout << "No more bullets to remove" << endl << endl;
									playerMoney+=750;
									break;
								}
							}
					
					case 4:
						if(playerMoney < 1500){
							cout << "You are too poor to afford this." << endl << endl;
							break;
						}
						else{
							playerMoney-=1500;
							enemyCanAct = false;
							break;
						}
					
					default: 
						break;
				}
				displayBattleMenu();
				cin >> decision;
					
			}
			else{
				cout << "Please enter a valid choice... There are guards watching..." << endl << endl;
			}
			displayBattleMenu();	
			}//end of player's turn
		}
		playerCanAct = true;
		
		int itemBought = rand() % NUM_ITEMS;
		int buyChance = rand() % 100;
		buyChance = buyChance + (day * 10);
		
		if(enemyCanAct){
		currentChamber = rand() % NUM_CHAMBERS; //spin cylinder
		cout << "Your opponent spins the chamber. It is their turn..." << endl << endl;
		//PlaySound(TEXT("RevolverSpin.wav"), NULL, SND_FILENAME | SND_SYNC);
		if(buyChance >= 80){
			switch(itemBought){
				
				case 1:
					if(enemyMoney < 1000) //check if enemy has enough money
						break;
					else{
						enemyMoney-=1000;
						enemyCertainlyKills = useMGlass(cylinder, currentChamber);
						break;
					}
					
				case 2:
					if(enemyMoney < 500)
						break;
					else{
						enemyMoney-=500;
						currentChamber = rand() % NUM_CHAMBERS; //spin cylinder
						break;
					}
					
				case 3:
					if(enemyMoney < 750)
						break;
					else{
						bool removed = removeBullet(cylinder, numBullets);
							if(!removed){
								cout << "No more bullets to remove" << endl << endl;
								enemyMoney+=750;
								break;
							}
					}
					
				case 4:
					if(enemyMoney < 1500)
						break;
					else{
						enemyMoney-=1500;
						playerCanAct = false;
						break;
					}
					
				default: 
					break;
			}
		}// enemy buys an item
		
		
			int enemyAction = (rand() % 100) + (day * (rand() % 2));
			enemyAction+=(20 * (enemyAction < 30));
			
			if(enemyAction >= 50 || enemyCertainlyKills){//shoot player
				cout << "The gun is pointed at you..." << endl << endl;
				if(cylinder[currentChamber]){
					cout << "The last thing you see is the flash of the barrel and your ears ring just a moment longer as you lose consciousness...\n\nYou die." << endl << endl;
					//PlaySound(TEXT("PistolShot.wav"), NULL, SND_FILENAME | SND_SYNC);
					return false; //lose
				}
				else{
					cout << "The gun fails to fire..." << endl << endl;
					//PlaySound(TEXT("GunJam.wav"), NULL, SND_FILENAME | SND_SYNC);
				}
					
			}
			
			else{
				cout << "Your competitor points the barrel at themself" << endl << endl;
				if(cylinder[currentChamber]){
					cout << "You flinch as the gun fires. Your enemy's head dangles limply, their dull, glazed eyes pierce your soul...\n\nThe person sitting across from you is now dead." << endl << endl;	
					//PlaySound(TEXT("PistolShot.wav"), NULL, SND_FILENAME | SND_SYNC);
					standing+=1;
					day+=(rand() % 3);
					playerMoney+=2000;
					return true; //win
					}
				}
			
			}
		enemyCanAct = true;
			
	}

}

bool replyChance(int currentStanding){
	int chance = rand() % 4;
	
	if(currentStanding >= 3){
		chance+=1;
	}
	
	else if(currentStanding >= 4){
		chance+=2;
	}
	
	if(chance >= 3){
		return true;	
	}
	
	else return false;
}

int sendLetter(string str, int currentStanding){
    
    const string cussList[] = {
    "ass", "asshole", "bastard", "bitch", "nazi", "crap", "cunt", "damn", "dick", "sociopath", "suck", "sucker",
    "psychopath", "fuck", "fucker", "goddamn", "hell", "jerk", "motherfucker", "piss", "prick",
    "pussy", "retard", "shit", "jackass", "twat", "wanker", "fuckers", "douchebag", "dipshit", "psycho",
    "jackass", "loser", "stupid", "idiot", "moron", "scumbag", "trash", "shithead", "evil", "fascist", "murder", "murderer", "murderers", "kill", "killers"
};

const int cussListLen = sizeof(cussList) / sizeof(cussList[0]);
    
    /*//initialize cussList (with a file containing cuss words
	for(int i = 0; i < MAX_LEN; i+=1){
    	cussList[i] = "placeholdercuss";
	}

	ifstream cussFile("CussWords.txt");

	int cussCount = 0;
	string cussWord;
	cussFile >> cussWord;

	while(cussWord != "$$$"){
		cussList[cussCount] = cussWord;
		cout << cussList[cussCount] << endl;
		cussCount+=1;
		cussFile >> cussWord;
	}

	int cussListLen = cussCount;
	cussFile.close();
    cout << cussListLen << endl;
    */
    
    int points = 60;
    int i = 0;
    int x;
    string sub;
    bool cussFound;
    
    if(currentStanding >= 4){
    	points+=10;
	}
    
    if(str.length() < 50){//check 1: is letter too short?
        points -= 30;
    }
    else if(str.length() < 20)
        points-=50;
        
    while(i < str.length()){//check 2: check letter after fullstop
         if(str.at(i) == '.' && i < str.length() - 1){
            int temp = i;
            
            while(!isLetter(str.at(temp)) && temp < str.length()){
                temp+=1;
            }
            if(temp == str.length())
                temp-=1;
                
            if(str.at(temp) >= 'a' && str.at(temp) <= 'z')
                points-=15;
        }
        
        i+=1;
    } 
    
    //convert contents of letter to lower case
    for(int t = 0; t < str.length(); t+=1)
            str.at(t) = toLowerCase(str.at(t));
        
    
    i = 0;
    
   while(i < str.length()){//check 3: contains cuss words?
        while(i < str.length() && !isLetter(str.at(i)))
              i+=1;
              
        cussFound = false;
        x = i;
        while(x < str.length() && isLetter(str.at(x)))
            x+=1;
        
        sub = str.substr(i, x - i);
          
        int j = 0;
        while(j < cussListLen && !cussFound){
            if(sub == cussList[j]){
               cussFound = true; 
               points-=50;
            }
            j+=1;
        }
        
        
        while(i < str.length() && isLetter(str.at(i)))
            i+=1;
    }
    
    i = 0;
    int a = 0;
    
    while(i < str.length()){//check 4: good punctuation?
        
        if(a <= 32){
            if(str.at(i) == ',' || str.at(i) == '\'' || str.at(i) == '\"' || str.at(i) == '.'){
                a = 0;
            }
        }
        else if(a >= 32){
            points-=15;
            a = 0;
        }
        
        i+=1;
        a+=1;
    }
    
    const string pleadingWords[] = {
        "beg", "begging", "begged", "begs", "plea", "pleading", "pleaded", "pleas", "please",
        "implore", "imploring", "implored", "implores", "beseech", "beseeching", "beseeched", "beseeches",
        "entreat", "entreating", "entreated", "entreats", "appeal", "appealing", "appealed", "appeals",
        "supplicate", "supplicating", "supplicated", "supplicates",
        "petition", "petitioning", "petitioned", "petitions",
        "pray", "praying", "prayed", "prays",
        "importune", "importuning", "importuned", "importunes",
        "solicit", "soliciting", "solicited", "solicits",
        "adjure", "adjourning", "adjured", "adjures",
        "bawl", "bawling", "bawled", "bawls",
        "cry", "crying", "cried", "cries",
        "entreaty", "supplication", "appeal", "request", "requesting",
        "ask", "asking", "asked", "asks",
        "demand", "demanding", "demanded", "demands",
        "importunity", "urgency", "urgency", "pleadingly",
        "earnest", "earnestly", "urgently", "urgency",
        "petitionary",
        "beseechingly", "imploringly", "entreatingly", "supplicatingly",
        "humble", "humbly", "urgent", "urgently",
        "crave", "craving", "craved", "craves",
        "solicitation", "solicitingly",
        "entreat", "entreatingly", "help", "helping", "helper", "helpless"
    };

    int pleadingWordsLen = sizeof(pleadingWords) / sizeof(pleadingWords[0]);
    i = 0;
    x = 0;
    bool pleadingWordFound = false;
    
    while(i < str.length()){//check 5: contains pleading words?
        while(i < str.length() && !isLetter(str.at(i)))
              i+=1;
              
        pleadingWordFound = false;
        x = i;
        while(x < str.length() && isLetter(str.at(x)))
            x+=1;
        
        sub = str.substr(i, x - i);
          
        int j = 0;
        while(j < pleadingWordsLen && !pleadingWordFound){
            if(sub == pleadingWords[j]){
               pleadingWordFound = true; 
               points+=5;
            }
            j+=1;
        }
        
        
        while(i < str.length() && isLetter(str.at(i)))
            i+=1;
    }
    
   cout << points << endl;
    
    if(points >= 80)
    	currentStanding+=1;
    	
    else if(points <= 40)
    	currentStanding-=1;
    
    //display replies
    bool replied = replyChance(currentStanding);
    
    string goodReplies[3] = {
		"Hello.\n\nWe are pleased to inform you that your next match will be sponsored.\n\nKind Regards.", "Greetings,\n\nGlad tidings as your sponsorhip has been accepted. This is a wonderful opportunity for you as a competitior.\n\nDo not disappoint us.", "Your salient reputation with us is duly noted and you have been selected for sponsorship in your next match.\n\nMay your death be delayed forever."
		
	};
    
    string neutralGoodReplies[3]{
    	"Hello.\n\nYour letter piqued our interest but we want to see better performance before we decide upon a sponsorship.\n\nRegards.", "Greetings,\n\nWe hope you are well. However, we want to see how well you perform before we consider sponsoring you.", "Good day,\n\nThere is still much you need to do for us to be able to sponsor you; but we wish the best odds for you\n\nGood luck."
	};
    
    string neutralReplies[3] = {
		"Hello.\n\nWe have received your letter; but please try to do more matches first.\n\nRegards.", "Greetings,\n\nWe have acknowledged your letter; yet your reputation leaves much to be desired.\n\nIncrease it.", "We have received your letter. Please participate in more matches before we consider sponsoring you.\n\nRegards."
	};
	
	string neutralBadReplies[3] = {
		"What a disgusting thing to say to us.\n\nIt would do you well to apologize or we will make you regret it if you keep up this behavior.", "It appears the slave is manifesting hubris. Perhaps you have been living comfortably too long? This is why your kind cannot be allowed so much comfort.\n\nReflect on this behavior or we will seek to rectify it ourselves... permanently", "After all the good you have been given? After we have pampered you with the best and raised your rank to that of a sportsman? How dare you,\n\nYou insolent whelp! How dare you write such an obnoxious letter to us?\n\nBe careful what you write, as the next time might be your last time writing to us..."
	};
	
	string badReplies[3] = {
		"It is clear from your letter that you have lost your senses but not so much as to become so inept as to be unable to importune us with such vulgar writing. Your opponent will certainly enjoy our help in ridding us of this source of unwanted emails.\n\nDo not contact us unless you are have a modicum of sense... and if you survive", "It is amazing what filth the subhuman betrays itself to be when under such dire circumstances. We will help your competitor in removing this filth from the face of the Earth.\n\nA pathetic creature such as yourself should never respond to us, unless it acknowledges its status fully for what it is.", "Disgusting writing from a disgusting creature. Your opponent will be helped in the next match and with any luck you perish.\n\nMay this letter be a portent of your impending doom..."
	};
    int chooseReply = rand() % 3;//choose a random email reply
    
    if(replied && currentStanding >= 4){// good reply received
    	cout << "You have received 1 new reply:\n\n";
    	cout << goodReplies[chooseReply] << endl << endl;
	}
	
	else if(replied && currentStanding <= 1){// bad reply received
    	cout << "You have received 1 new reply:\n\n";
    	cout << badReplies[chooseReply] << endl << endl;
	}
	
	else if(replied && points >= 80 && currentStanding >= 2 && currentStanding <= 4){// neutral-good replyreceived
    	cout << "You have received 1 new reply:\n\n";
    	cout << neutralGoodReplies[chooseReply] << endl << endl;
	}
	
	else if(replied && points <= 40 && currentStanding < 4 && currentStanding > 1){// neutral-bad reply received
		cout << "You have received 1 new reply\n\n";
		cout << neutralBadReplies[chooseReply] << endl << endl;
	}
	
	else{// neutral (automated) reply received
    	cout << "You have received 1 new reply:\n\n";
    	cout << "THIS IS AN AUTOMATED RESPONSE\n(In reality nobody has seen your letter and your standing has not been affected. However, you can participate in Russian Roulette matches to increase your chance of getting a reply.)" << endl << endl;
    	cout << neutralReplies[chooseReply] << endl << endl;
	}
    if(currentStanding < 0)
    	currentStanding = 0;
    	
    return currentStanding;
}

int main(){	
	
	srand(time(NULL));
	int choice;
	int secondChoice;
	int standing = 2;
	string email;
	bool alreadySentLetter = false;
	int day = 1;
	int numLetters = 0;
	int playerMoney = 500;
	bool isPlayerLiving = true;
	
	//main menu
	displayMainMenu();
	cin >> choice;
	cout << endl << endl << endl;
	
		if(choice == 1)
			displaySecondMenu();
		else if(choice == 2)
			displaySecondMenu();
		else{
			cout << "Game Over" << endl << endl;
			return 0;
		}
	
	//second menu
	cin >> secondChoice;
	while(true){
		int foodMessage = rand() % 5;
		if(secondChoice == 1)
			displayInvitation();
		else if(secondChoice == 2)
			cout << "It is day " << day << endl << endl;
		else if(secondChoice == 3 && numLetters < 3){
			cout << "Write a letter here: ";
			cin.clear();
			cin.ignore('\n', 100);
			getline(cin, email);
			standing = sendLetter(email, standing);
			numLetters+=1;
		}
		else if(secondChoice == 3 && numLetters >= 3)
			cout << "You are not allowed to send more letters" << endl << endl;
		else if(secondChoice == 4){
			isPlayerLiving = playRoulette(day, playerMoney, standing);
			if(isPlayerLiving){
				cout << "You wake up, more tired than before... How much more of this?" << endl;
				cout << "It is day " << day << endl << endl;
				numLetters = 0;
				displaySecondMenu();
			}
			else{
				return 0;
			}
		}
		
		else if(secondChoice == 5){
			cout << richFood[foodMessage] << endl;
		}
		
		else if(secondChoice == 6){
			if(playerMoney >= 8000){
				cout << "The fresh cool air soothes your face as you exit the workers' camp with your few belongings. Yet there you feel a knot in your stomach, not knowing what other fate this cruel world holds for you now..." << endl << endl;
				return 0;
			}	
			else
				cout << "You are too poor to afford this." << endl << endl;
		}
		else if(secondChoice == 7){
			cout << "Your current standing is " << standing << endl << endl;
		}
		else if(secondChoice == 8){
			cout << "You check the vault in your room: $" << playerMoney << endl << endl;
		}
		else if(secondChoice == 9){
			cout << "With a somber sigh, you take what you are allowed to and return to your old life of terrible, soul-crushing labor...\n\nGame Over" << endl << endl;
			return 0;
		}
		else{
			cout << "Please enter a valid option... The guards are watching..." << endl << endl;
			displaySecondMenu();
		}
		cout << "Enter a valid number: ";
		cin >> secondChoice;
	}
	return 0;
}

