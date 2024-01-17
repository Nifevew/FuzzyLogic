#pragma once

#include <string>
#include <iostream>
#include <format>

#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/matrix.hpp"

#include "../include/FuzzySet.h"
#include "../include/FuzzyLogic.h"

namespace FuzzyLogic
{
	template<typename T>
	FuzzySet<T> compositionalRule(const FuzzySet<T>& a, const FuzzySet<T>& b, const FuzzySet<T>& a_, std::wstring name_set_b_)
	{
		auto x = generatingMatrixOfRelations(a.getUblasVectorValues(), b.getUblasVectorValues());
		auto x_ = convolutionMV(x, a_.getUblasVectorValues()); // TODO: проверить дополнительные копирования

		FuzzySet b_(name_set_b_, x_, a.getUblasVectorTerms());

		return b_;
	}

	template<typename T>
	void printCompositionalRules(std::wstring msg, const FuzzySet<T>& a, const FuzzySet<T>& b, const FuzzySet<T>& a_, const FuzzySet<T>& b_)
	{
		const auto terms = a.getUblasVectorTerms();

		const auto a_values = a.getUblasVectorValues();	
		const auto b_values = b.getUblasVectorValues();
		const auto a__values = a_.getUblasVectorValues();
		const auto b__values = b_.getUblasVectorValues();

		for (size_t i = 0; i < terms.size(); ++i)
			std::wcout << std::vformat(msg, std::make_wformat_args(terms(i), a[terms(i)] * 100, a.getName(), b[terms(i)] * 100, b.getName(), a_.getName(), a_[terms(i)] * 100, b_.getName(), b_[terms(i)] * 100)) << L'\n';
	}


	template<typename T>
	FuzzySet<T> modusPonensRule(const FuzzySet<T>& a, const FuzzySet<T>& b, const FuzzySet<T>& a_, std::wstring name_set_b_, std::function<T(T, T)> implication=FuzzyLogic::implicationByLotfiZadeh<T>)
	{
		using namespace boost::numeric;

		ublas::vector<T> impl = implicationV(a.getUblasVectorValues(), b.getUblasVectorValues(), implication);

		auto b_ = convolutionVV(a_.getUblasVectorValues(), impl);

		FuzzySet b_fs(L"более-менее", {b_}, {});

		return b_fs;
	}

	template<typename T>
	void printModusPonensRule(std::wstring msg, const FuzzySet<T>& a, const FuzzySet<T>& b, const FuzzySet<T>& a_, const FuzzySet<T>& b_)
	{
        // Если человек {} и существует правило, что {} -> {}, то тогда он более-менее здоровый на {}%
		std::wcout << std::vformat(msg, std::make_wformat_args(a_.getName(), a.getName(), b.getName(), b_.getUblasVectorValues()(0) * 100)) << L'\n';
	}

}