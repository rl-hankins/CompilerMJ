

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__

#include "macros.h"
#include "symbols.hpp"
SymTab tab; // symbol table
string name;


#include "Scanner.h"



class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const wchar_t *s);
	void Warning(int line, int col, const wchar_t *s);
	void Warning(const wchar_t *s);
	void Exception(const wchar_t *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_identifier=1,
		_integer=2,
		_float=3,
		_string=4,
		_macro=39
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const wchar_t* msg);

	void Cmm();
	void TypeSpecifier();
	void ArrayIndex();
	void Parameter();
	void Declaration();
	void Statement();
	void Expression();
	void OrExpression();
	void AndExpression();
	void RelationExpression();
	void SimpleExpression();
	void Term();
	void Factor();
	void Value();

	void Parse();

}; // end Parser



#endif

