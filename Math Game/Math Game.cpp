// Math Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enQuestionsLevel { Eazy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, OpMix = 5 };

struct stQuestion
{
    int Number1 = 0;
    int Number2 = 0;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};
struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionsLevel QuestionLevel;
    enOperationType OpType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = false;
};

string GetOpTypeSympol(enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return "+";
    case Sub:
        return "-";
    case Mul:
        return "*";
    case Div:
        return "/";
    default:
        return "Mix";
    }
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); //turn screen to Green
    else
    {
        system("color 4F"); //turn screen to Red
        cout << "\a";
    }
}

int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

short ReadHowManyQuestions()
{
    short NumberOfQuestion = 1;

    do
    {
        cout << "How Many Questions do you want to answer: \n";
        cin >> NumberOfQuestion;

    } while (NumberOfQuestion < 1 || NumberOfQuestion > 10);

    return NumberOfQuestion;
}

enQuestionsLevel ReadQuestionLevel()
{
    short Choice = 1;

    do
    {
        cout << "\nEnter Question Level [1] Eazy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 4);

    return (enQuestionsLevel)Choice;
}

enOperationType ReadOperationType()
{
    short Choice = 1;

    do
    {
        cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice > 5);

    return (enOperationType)Choice;
}

enOperationType GetRandomOperationType()
{
    int Op = RandomNumber(1, 4);
    return (enOperationType)Op;
}

int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mul:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);
    }

    if (OpType == enOperationType::OpMix)
    {
        OpType = GetRandomOperationType();
    }

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case Eazy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

        Question.QuestionLevel = QuestionLevel;
        return Question;

    case Med:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

        Question.QuestionLevel = QuestionLevel;
        return Question;

    case Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);

        Question.QuestionLevel = QuestionLevel;
        return Question;

    }
    return Question;
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void GenerateQuestionList(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OpType);
    }
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "[Question " << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << "  ";
    cout << GetOpTypeSympol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n-----------\n";
}

void handleAnswer(stQuizz& Quizz, short NumberOfQuestion)
{
    if (Quizz.QuestionList[NumberOfQuestion].PlayerAnswer != Quizz.QuestionList[NumberOfQuestion].CorrectAnswer)
    {
        Quizz.QuestionList[NumberOfQuestion].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;

        cout << "\nWrong Answer :-(\n";
        cout << "The correct answer is: " << Quizz.QuestionList[NumberOfQuestion].CorrectAnswer;
        cout << endl;
    }
    else
    {
        Quizz.QuestionList[NumberOfQuestion].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;

        cout << "\nRight Answer :-)\n";
    }
    cout << endl;

    SetScreenColor(Quizz.QuestionList[NumberOfQuestion].AnswerResult);
}

void AskAndCorrectQuetionsAnswer(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);

        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        handleAnswer(Quizz, QuestionNumber);
    }

    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultText(bool Pass)
{
    if (Pass)
        return "PASS :-)";
    else
        return "Fail :-(";
}

string GetQuestionLevelText(enQuestionsLevel QLevel)
{
    string arrQuestionsLevel[4] = {"Eazy", "Med", "Hard", "Mix"};
    return arrQuestionsLevel[QLevel - 1];
}

string GetOperationTypeText(enOperationType OpType)
{
    string arrOpType[5] = { "+", "-", "*", "/", "Mix" };
    return arrOpType[OpType - 1];
}

void FinalResult(stQuizz Quizz)
{
    cout << "\n__________________________\n";
    cout << "\n Final Result is " << GetFinalResultText(Quizz.IsPass);
    cout << "\n__________________________\n";

    cout << "\nNumber Of Questions   : " << Quizz.NumberOfQuestions;
    cout << "\nQuestions Level       : " << GetQuestionLevelText(Quizz.QuestionLevel);
    cout << "\nOperation Type        : " << GetOperationTypeText(Quizz.OpType);
    cout << "\nNumber Of Right Answer: " << Quizz.NumberOfRightAnswers;
    cout << "\nNumber Of Wrong Answer: " << Quizz.NumberOfWrongAnswers;

    cout << "\n__________________________\n";

    SetScreenColor(Quizz.IsPass);
}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOperationType();

    GenerateQuestionList(Quizz);
    AskAndCorrectQuetionsAnswer(Quizz);
    FinalResult(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();

        cout << endl << "Do you want play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
