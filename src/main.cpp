// FuzzyLogic.cpp: определяет точку входа для приложения.
//

#include "../include/main.h"

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);

	auto a = FuzzyLogic::FuzzySet<float>(L"очень высокий", { {L"150", 0.0}, {L"170", 0.3}, {L"180", 0.5}, {L"190", 0.7}, {L"200", 1.0} });
	auto b = FuzzyLogic::FuzzySet<float>(L"здоровый", { {L"150", 0.4}, {L"170", 0.9}, {L"180", 1.0}, {L"190", 0.7}, {L"200", 0.2} });

	std::wcout << L"A = " << a << L'\n';
	std::wcout << L"B = " << b << L'\n';

	auto a_ = FuzzyLogic::FuzzySet<float>(L"средний", { {L"150", 0.3}, {L"170", 0.8}, {L"180", 1}, {L"190", 0.7}, {L"200", 0.5} });
	auto b_ = FuzzyLogic::compositionalRule(a, b, a_, L"более-менее");

	std::wcout << L"A' = " << a_ << L'\n';
	std::wcout << L"B' = " << b_ << L'\n';

	FuzzyLogic::printCompositionalRules(L"Если при росте {}см человек на {}% {} и на {}% {} и при этом {} рост {}%, то он {} здоровый на {}%.", a, b, a_, b_);

	auto mp_b_ = FuzzyLogic::modusPonensRule(a, b, a_, L"более-менее");
	FuzzyLogic::printModusPonensRule(L"Если человек {} и существует правило, что {} -> {}, то тогда он более-менее здоровый на {}%", a, b, a_, mp_b_);

  return 0;
}
