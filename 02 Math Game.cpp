#include <iostream>
using namespace std;

enum enOperationType { add = 1, sub = 2, mul = 3, Div = 4, mixOp = 5 };

enum enQuizLevelType { easyLevel = 1, mediumLevel = 2, hardLevel = 3, mixLevel = 4 };

struct stQuestion {
	int number1 = 0;
	int number2 = 0;
	enOperationType operationType;
	enQuizLevelType questionLevelType;
	int correctAnswer = 0;
	int playerAnswer = 0;
	bool answerResult = true;
};

struct stQuiz {
	stQuestion questionList[100];
	short numberQuiz = 0;
	enOperationType gameOpType;
	enQuizLevelType GameQuizLevelType;
	short numberOfWrongAnswer = 0;
	short numberOfRightAnswer = 0;
	bool isPass = true;
};

int randoNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}

enOperationType readOperator() {
	int choice;
	do {
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> choice;
	} while (choice < 1 || choice > 5);

	return (enOperationType)choice;
}

enQuizLevelType readLevel() {
	int choice;
	do {
		cout << "Enter Question level [1] Easy, [2] Medium, [3] Hard, [4] Mix ? ";
		cin >> choice;
	} while (choice < 1 || choice > 4);

	return (enQuizLevelType)choice;
}

int readManyNumberQuiz() {
	int number;
	do {
		cout << "How Many Question Do You Went? ";
		cin >> number;
	} while (number < 1 || number > 10);
	return number;
}

string operatorText(enOperationType op) {
	string operatorType[] = { "+", "-", "*", "/", "Mix" };

	return operatorType[op - 1];
}

string levelName(enQuizLevelType level) {
	string levelType[] = { "Easy", "Medium", "Hard", "Mix" };

	return levelType[level - 1];
}

int simpleCalcluter(int number1, int number2, enOperationType op) {
	switch (op) {
	case enOperationType::add:
		return number1 + number2;
	case enOperationType::sub:
		return number1 - number2;
	case enOperationType::mul:
		return number1 * number2;
	case enOperationType::Div:
		if (number1 == 0)
			return 0;
		return number1 / number2;
	default:
		return number1 + number2;
	}
}

stQuestion generateQuestion(enQuizLevelType levelType, enOperationType operationType) {
	stQuestion question;
	if (levelType == enQuizLevelType::mixLevel) {
		levelType = (enQuizLevelType)randoNumber(1, 3);
	}	
	if (operationType == enOperationType::mixOp) {
		operationType = (enOperationType)randoNumber(1, 4);
	}

	question.operationType = operationType;

	switch (levelType) {
	case enQuizLevelType::easyLevel:
		question.number1 = randoNumber(1, 10);
		question.number2 = randoNumber(1, 10);

		question.correctAnswer = simpleCalcluter(question.number1, question.number2, question.operationType);
		question.questionLevelType = levelType;

		return question;	

	case enQuizLevelType::mediumLevel:
			question.number1 = randoNumber(10, 50);
			question.number2 = randoNumber(10, 50);

			question.correctAnswer = simpleCalcluter(question.number1, question.number2, question.operationType);
			question.questionLevelType = levelType;

			return question;

	case enQuizLevelType::hardLevel:
		question.number1 = randoNumber(50, 100);
		question.number2 = randoNumber(50, 100);

		question.correctAnswer = simpleCalcluter(question.number1, question.number2, question.operationType);
		question.questionLevelType = levelType;

		return question;
	}
}

void genrateQuizzQuestion(stQuiz& quizz) {
	for (int question = 0; question < quizz.numberQuiz; question++) {
		quizz.questionList[question] = generateQuestion(quizz.GameQuizLevelType, quizz.gameOpType);
	}
}

void setScreenColor(bool isPass) {
	if (isPass)
		system("color 20");
	else
		system("color 40");
}

void printTheQuestion(stQuiz quizz, short numberOfQuiz) {
	cout << "\nQuestion [" << numberOfQuiz + 1 << '/' << quizz.numberQuiz << ']' << "\n\n";
	cout << quizz.questionList[numberOfQuiz].number1 << "\n";
	cout << quizz.questionList[numberOfQuiz].number2 << " ";
	cout << operatorText(quizz.questionList[numberOfQuiz].operationType) << "\n";
	cout << "------------\n";
}

int readQestion() {
	int number;
	cin >> number;
	return number;
}

void correctQuestionAnswer(stQuiz& quizz, short numberOfQuestion) {
	if (quizz.questionList[numberOfQuestion].correctAnswer != quizz.questionList[numberOfQuestion].playerAnswer) {
		cout << "Wrong Answer :-(\n";
		cout << "The right Answer is: ";
		cout << quizz.questionList[numberOfQuestion].correctAnswer << "\n\n";
		quizz.questionList[numberOfQuestion].answerResult = false;
		quizz.numberOfWrongAnswer++;
	}

	else {
		cout << "Right Answer :-)\n\n";
		quizz.questionList[numberOfQuestion].answerResult = true;
		quizz.numberOfRightAnswer++;
	}
	setScreenColor(quizz.questionList[numberOfQuestion].answerResult);
}

void askAndCorrectQuestionListAnswer(stQuiz& quizz) {
	for (int question = 0; question < quizz.numberQuiz; question++) {
		printTheQuestion(quizz, question);

		quizz.questionList[question].playerAnswer = readQestion();

		correctQuestionAnswer(quizz, question);
	}

	quizz.isPass = quizz.numberOfRightAnswer >= quizz.numberOfWrongAnswer;
}

string faceGame(bool ispass) {
	if (ispass)
		return "Pass :-)";

	return "fail :-(";
}

void printQuizResults(stQuiz quizz) {
	cout << "---------------------------\n";
	cout << "  final Result is " << faceGame(quizz.isPass) << "\n";
	cout << "---------------------------\n\n";
	cout << "Number Of Question     : " << quizz.numberQuiz << "\n";
	cout << "Question Level         : " << levelName(quizz.GameQuizLevelType) << "\n";
	cout << "opType                 : " << operatorText(quizz.gameOpType) << "\n";
	cout << "Number Of Right Answer : " << quizz.numberOfRightAnswer << "\n";
	cout << "Number Of Fail Answer  : " << quizz.numberOfWrongAnswer << "\n\n";
	setScreenColor(quizz.isPass);
	cout << "---------------------\n";
}

void playMathGame() {
	stQuiz quizz;
	quizz.numberQuiz = readManyNumberQuiz();
	quizz.GameQuizLevelType = readLevel();
	quizz.gameOpType = readOperator();

	genrateQuizzQuestion(quizz);
	askAndCorrectQuestionListAnswer(quizz);
	printQuizResults(quizz);
}


void resetScreen() {
	system("cls");
	system("color 07");
}

void startGame() {
	char doYouAgain = 'Y';
	do {
		resetScreen();
		playMathGame();

		cout << "Do You Want Play Again Y/N ? ";
		cin >> doYouAgain;

	} while (doYouAgain == 'y' || doYouAgain == 'Y');
}

int main() {
	srand((unsigned)time(NULL));

	startGame();

	return 0;
}