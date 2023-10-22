﻿#pragma once

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
	FuzzySet<T> compositionalRule(const FuzzySet<T>& a, const FuzzySet<T>& b, const FuzzySet<T>& a_, std::wstring set_name_b_)
	{
		auto x = generatingMatrixOfRelations(a.getUblasVectorValues(), b.getUblasVectorValues());
		auto x_ = convolutionMV(x, a.getUblasVectorValues()); // TODO: проверить дополнительные копирования

		FuzzySet b_(set_name_b_, x_, a.getUblasVectorTerms());

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
}