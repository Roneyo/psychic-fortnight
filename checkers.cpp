
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#define WIDTH_COUNT 10
#define SPACE_CHAR '#'
#define ATEAM_CHAR 'a'
#define BTEAM_CHAR 'b'
using namespace std;

int i, j;
char unitBoard[10][10];
void showMap();
void initMap();
void playMap();
int map2int(char* pMap, int offset);
char* int2map(char* pMap, int direction);
int MoveSearch(char* pMap, char chFind, int nPrev, bool bKing);
void SearchPiece(char* pMap, char chFind, bool bKing);

int main(){
  int startChoice;

  int units;

  cout << "<<<<<<<<<Welcome to cppChecker, please choose one from followings.>>>>>>>>>" << endl;
  cout << "1. Start Game" << endl; //select 1 to start the game
  cout << "2. Exit" << endl; // select 2 to exit the program
  cin >> startChoice;

  if(startChoice == 1){
    initMap(); //it is a function that checker board for initialization
    showMap(); // it is a outline of checker board as well as locating units on the board.
    playMap();// it is a function that makes it playable.
  }
  if(startChoice == 2){
    cout << "Goodbye!" << endl;
  }
}


void showMap() // this outline consists of upper and lower parts. upper will be repeated through for loop.
{
  system("cls");
  for(i = 0; i < 10 ; i++){
    cout << endl;
    cout << "   |---+---+---+---+---+---+---+---+---+---|  " << endl;
    cout << setw(2) << i + 1 << " | ";   //side-number labelling
    for(j = 0; j < 10; j++){
      cout << unitBoard[i][j] << " | "; //not only dividing space but also give each space a location.

    }
  }
  cout << endl;
  cout << "   |---+---+---+---+---+---+---+---+---+---|  " << endl; // last line
  cout << "     a   b   c   d   e   f   g   h   i   j" << endl; // english labelling
}

void initMap(){  // loop for initialization, very first form of this checker program
  for(i = 0; i < 10; i++){
    char val;
    if(i >= 0 && i <= 3){
      val = 'b';  // unit b
    }
    else if(i >= 6 && i <= 9){
      val = 'a'; // unit a
    }
    else{
      val = '#'; // unit space
    }

    for (j = 0; j < 10; j++){
      if (i % 2 == 0){
        if (j % 2 == 0){
          unitBoard[i][j] = ' ';
        }
        else{
          unitBoard[i][j] = val;
        }
      }
      else{
        if (j % 2 == 0){
          unitBoard[i][j] = val;
        }
        else{
          unitBoard[i][j] = ' ';
        }
      }
    }
  }
}
void playMap(){ // function that allows user to make a move
  int playerChoice;
  bool gameSet = true;
  int count = 2;
  char player;
  while(gameSet) {

  cout << "choose your action." << endl;
  cout << "1. Make a move" << endl;
  cout << "2. Save" << endl; // saving current contents
  cout << "3. Exit" << endl;
  cin >> playerChoice;

  if(playerChoice == 2) {

  }

  if(playerChoice == 3) {
    exit(1);
  }
  if (playerChoice == 1) {

    int playerMove;
    int playerunitInt;
    char playerunitAlp;
    char opponent;

    if(count % 2 == 0) {
      player = ATEAM_CHAR;
      opponent = BTEAM_CHAR;
      cout << "player " << player << "'s turn" << endl;
    } else {
      player = BTEAM_CHAR;
      opponent = ATEAM_CHAR;
      cout << "player " << player << "'s turn" << endl;
    }

    cout << "chooose your unit(a space is required between a number and a LOWERCASE alphabet like '7 b', it is case sensitive.)" << endl;
    cin >> playerunitInt >> playerunitAlp; //  as the checker board has lowercase alphabet, i applied a limit
                                          // that user is only able to type lowercase alphabet.

    i = playerunitInt - 1; // converting number inputs into its actual 2d array location.

    switch(playerunitAlp) { // converting alphabet inputs into its actual 2d array location.
      case 'a':
        j = 0;
        break;

      case 'b':
        j = 1;
        break;

      case 'c':
        j = 2;
        break;

      case 'd':
        j = 3;
        break;

      case 'e':
        j = 4;
        break;

      case 'f':
        j = 5;
        break;

      case 'g':
        j = 6;
        break;

      case 'h':
        j = 7;
        break;

      case 'i':
        j = 8;
        break;

      case 'j':
        j = 9;
        break;

    }
    bool gameMove;
    if(unitBoard[i][j] == '#') {
      gameMove = false;
      cout << "that's just a space :^(" << endl;
    } else if(unitBoard[i][j] != player) {
      gameMove = false;
      cout << "that's not your unit :^(" << endl;
    }
     else {
      gameMove = true;
      count++;
    }


      while(gameMove){ //this is where user decides their move. following 4 choices are given below.
        SearchPiece(&unitBoard[i][j], opponent, false);

        cin >> playerMove;


      if(playerMove == 1) { //all moves are coded with some warnings, if a user attempts to move a unit
                            //to outside of the board, it will give warning message and let the user choose the right one
        if(j == 0){
          cout << "there is no space..." << endl;
          cout << " " << endl;
          count--;
          break;
        }
        if(unitBoard[i-1][j-1] == unitBoard[i][j]) {
          cout << "you can't leap over your unit" << endl;
          cout << " " << endl;
          count--;
          break;
        }
        if((unitBoard[i-1][j-1] == opponent) && (unitBoard[i-2][j-2] == SPACE_CHAR)) {

          int temp;

          temp = unitBoard[i][j];
          unitBoard[i][j] = unitBoard[i-2][j-2];
          unitBoard[i-2][j-2] = temp;
          unitBoard[i-1][j-1] = SPACE_CHAR;
          showMap();
          break;
        }
        if(unitBoard[i-1][j-1] == SPACE_CHAR) { // this is the part where unit changes as they move.
                                        // all other following moves are coded with the same structure
          int temp;

          temp = unitBoard[i][j];
          unitBoard[i][j] = unitBoard[i-1][j-1];
          unitBoard[i-1][j-1] = temp;
          showMap();
          break;
        }
      }
      if(playerMove == 2) {
        if(j == 9) {
          cout << "there is no space..." << endl;
          cout << " " << endl;
          count--;
          break;
        }
        if(unitBoard[i-1][j+1] == unitBoard[i][j]) {
          cout << "you can't leap over your unit" << endl;
          cout << " " << endl;
          count--;
          break;
        }
        if(unitBoard[i-1][j+1] == SPACE_CHAR) {
          int temp;

          temp = unitBoard[i][j];
          unitBoard[i][j] = unitBoard[i-1][j+1];
          unitBoard[i-1][j+1] = temp;
          showMap();
          break;
        }
      }
      if(playerMove == 3) {
        if(j == 0) {
          cout << "there is no space..." << endl;
          cout << " " << endl;
        }
        if(unitBoard[i+1][j-1] == unitBoard[i][j]) {
          cout << "you can't leap over your unit" << endl;
          cout << " " << endl;
        }
        if(unitBoard[i+1][j-1] == SPACE_CHAR) {
          int temp;

          temp = unitBoard[i][j];
          unitBoard[i][j] = unitBoard[i+1][j-1];
          unitBoard[i+1][j-1] = temp;
          showMap();
          break;
        }
      }
      if(playerMove == 4) {
        if(j == 9) {
          cout << "there is no space..." << endl;
          cout << " " << endl;
        }
        if(unitBoard[i+1][j+1] == unitBoard[i][j]) {
          cout << "you can't leap over your unit" << endl;
          cout << " " << endl;
        }
        if(unitBoard[i+1][j+1] == '#') {
          int temp;

          temp = unitBoard[i][j];
          unitBoard[i][j] = unitBoard[i+1][j+1];
          unitBoard[i+1][j+1] = temp;
          showMap();
          break;
        }
       }

    }

   }
  }
}
int map2int(char* pMap, int offset)
{
	return pMap[-(WIDTH_COUNT + 1) * offset]
		+ (pMap[-(WIDTH_COUNT - 1) * offset] << 8)
		+ (pMap[(WIDTH_COUNT - 1) * offset] << 16)
		+ (pMap[(WIDTH_COUNT + 1) * offset] << 24);
}
char* int2map(char* pMap, int direction)
{
  char* chRet = pMap;
	switch(direction)
	{
	case 0:
    chRet = &pMap[-(WIDTH_COUNT + 1) * 2];	// LEFT TOP
	case 1:
    chRet = &pMap[-(WIDTH_COUNT - 1) * 2];	// RIGHT TOP
	case 2:
    chRet = &pMap[(WIDTH_COUNT - 1) * 2];	// LEFT BOTTOM
	case 3:
    chRet = &pMap[(WIDTH_COUNT + 1) * 2];	// RIGHT BOTTOM
	}
  return chRet;
}
int MoveSearch(char* pMap, char chFind, int nPrev, bool bKing)
{
	int nResult = 0;

	// 1단
	int nStock = map2int(pMap, 1);
	char* chTemp = (char*)&nStock;
	char* chResult = (char*)&nResult;

	for (int i = 0; i < 4; i++)
	{
		// 이전 이동위치 제외
		if (i == nPrev) continue;

		// 공란검색 (1회성)
		if (nPrev == -1 && chTemp[i] == SPACE_CHAR)
		{
			chResult[i]++;

			// 공란일때 후진 제외
      if(!bKing) {
			switch (chFind)
			{
			case ATEAM_CHAR: chResult[0] = chResult[1] = 0; break;
			case BTEAM_CHAR: chResult[2] = chResult[3] = 0; break;
			}
		}
  }

		// 대상검색
		else if (chTemp[i] == chFind){
			chResult[i] += 2;
    }
	}

	// 2단
	nStock = map2int(pMap, 2);
	for (int i = 0; i < 4; i++)
	{
		// 1단이 공란 혹은 자신의 말일 경우 더 검색할 필요없음
		if (chResult[i] <= 1) {
      continue;
    }

		// 공란이 아니면 점프 불가
		if (chTemp[i] != SPACE_CHAR)
		{
			// 왕이 아니면 재귀탈출
			if (!bKing)
			{
				chResult[i] = 0;
				continue;
			}

			// 왕은 어느방향이던 상관없으나
			// 말을 1개 이상은 먹었을 경우 그 이후 같은선상의 임의장소로 이동
			// 먹지 않았을 경우 1칸만 이동
			// 여기에 해당 처리내용 작성요함



		}

		// 공란이므로 점프 가능함 재귀검사 실시
		int nSearch = MoveSearch(int2map(pMap, i), chFind, 3 - i, bKing);
		char* chSearch = (char*)&nSearch;

		// 제일 많이 갈 수 있는 방향을 얻음
		int nMax = 0;
		for (int j = 0; j < 4; j++) {
			if (chSearch[j] > nMax) {
				nMax = chSearch[j];
      }
    }
		for (int j = 0; j < 4; j++) {
			if (chSearch[j] == nMax) {
				chResult[j] += chSearch[j];
      }
    }
	}

	return nResult;
}

void SearchPiece(char* pMap, char chFind, bool bKing)
{
	int nSearch = MoveSearch(pMap, chFind, -1, bKing);
	char* chSearch = (char*)&nSearch;

	// 제일 많이 갈 수 있는 방향을 얻음
	int nMax = 0;
	for (int j = 0; j < 4; j++) {
		if (chSearch[j] > nMax) {
			nMax = chSearch[j];
    }
  }
	for (int j = 0; j < 4; j++) {
		if (chSearch[j] == nMax)
		{
			switch(j)
			{
			case 0: cout << "1. left up" << endl; break;
			case 1: cout << "2. right up" << endl; break;
			case 2: cout << "3. left down" << endl; break;
			case 3: cout << "4. right down" << endl; break;
			}
		}
  }
}
