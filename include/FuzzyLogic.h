#pragma once

#include <string>
#include <sstream>
#include <iomanip>
#include <variant>

#include "boost/numeric/ublas/vector.hpp"
#include "boost/numeric/ublas/matrix.hpp"
#include "boost/numeric/ublas/io.hpp"

namespace FuzzyLogic
{
	template<typename T>
	inline T MIN(T u, T v)
	{
		return (u < v ? u : v);
	}

	template<typename T>
	inline T MAX(T u, T v)
	{
		return (u > v ? u : v);
	}

	template<typename T>
	inline T NOT(T u)
	{
		return 1 - u;
	}

	template<typename T>
	boost::numeric::ublas::matrix<T> generatingMatrixOfRelations(const boost::numeric::ublas::vector<T>& v, const boost::numeric::ublas::vector<T>& u)
	{
		using namespace boost::numeric;
		ublas::matrix<T> relations_matrix(u.size(), v.size()); // u - rows, v - cols

		for (size_t i = 0; i < u.size(); ++i)
			for (size_t j = 0; j < v.size(); ++j)
				relations_matrix(i, j) = MIN(u(i), v(j)); // TODO: swap i and j so as not to transpose the matrix later

		return ublas::trans(relations_matrix);
	}

	template<typename T>
	boost::numeric::ublas::matrix<T> convolutionMM(const boost::numeric::ublas::matrix<T>& v, const boost::numeric::ublas::matrix<T>& u)
	{
		using namespace boost::numeric;
		ublas::matrix<T> out_matrix{ ublas::zero_matrix<T>(u.size1(), v.size2()) }; // u - rows, v - cols

		for (size_t i = 0; i < u.size1(); ++i) // row u
		{
			for (size_t j = 0; j < v.size2(); ++j) // col v
			{
				for (size_t k = 0; k < v.size1(); ++k) // row v
				{
					out_matrix(i, j) = MAX(out_matrix(i, j), MIN(u(i, k), v(k, j)));
				}
			}
		}

		return out_matrix;
	}

	template<typename T>
	boost::numeric::ublas::vector<T> convolutionMV(const boost::numeric::ublas::matrix<T>& u, const boost::numeric::ublas::vector<T>& v)
	{
		using namespace boost::numeric;
		ublas::vector<T> out_vector{ ublas::zero_vector<T>(v.size()) }; // u - rows, v - cols

		for (size_t j = 0; j < u.size2(); ++j)
		{
			for (size_t i = 0; i < v.size(); ++i)
			{
				out_vector(j) = MAX(MIN(v(i), u(i, j)), out_vector(j));
			}
		}

		return out_vector;
	}

	template<typename T>
	boost::numeric::ublas::vector<T> convolutionVM(const boost::numeric::ublas::vector<T>& v, const boost::numeric::ublas::matrix<T>& u)
	{
		using namespace boost::numeric;
		ublas::vector<T> out_vector{ ublas::zero_vector<double>(v.size()) }; // u - rows, v - cols

		for (size_t j = 0; j < u.size2(); ++j)
		{
			for (size_t i = 0; i < v.size(); ++i)
			{
				out_vector(j) = MAX(MIN(v(i), u(i, j)), out_vector(j));
			}
		}

		return out_vector;
	}

	template<typename T>
	boost::numeric::ublas::vector<T> convolutionVV(const boost::numeric::ublas::vector<T>& u, const boost::numeric::ublas::vector<T>& v)
	{
		using namespace boost::numeric;
		T out = u(0);

		for (size_t j = 0; j < u.size(); ++j)
		{
			out = MAX(MIN(v(j), u(j)), out);
		}

		return out;
	}

	enum class ConvolutionType
	{
		kMM,
		kMV,
		kVM,
		kVV
	};

	template<typename T, FuzzyLogic::ConvolutionType ct>
	std::variant<boost::numeric::ublas::matrix<T>, boost::numeric::ublas::vector<T>, T> convolution(const std::variant<boost::numeric::ublas::matrix<T>, boost::numeric::ublas::vector<T>>& u, const std::variant<boost::numeric::ublas::matrix<T>, boost::numeric::ublas::vector<T>>& v)
	{
		using namespace boost::numeric;

		if constexpr (ct == ConvolutionType::kMM)
		{
			return convolutionMM(std::get<ublas::matrix<T>>(u), std::get<ublas::matrix<T>>(v));
		}
		else if constexpr (ct == ConvolutionType::kMV)
		{
			return convolutionMV(std::get<ublas::matrix<T>>(u), std::get<ublas::vector<T>>(v));
		}
		else if constexpr (ct == ConvolutionType::kVM)
		{
			return convolutionVM(std::get<ublas::vector<T>>(u), std::get<ublas::matrix<T>>(v));
		}
		else if constexpr (ct == ConvolutionType::kVV)
		{
			return convolutionVV(std::get<ublas::vector<T>>(u), std::get<ublas::vector<T>>(v));
		}
	}

	template<typename T>
	T implicationByLotfiZadeh(T v, T u)
	{
		return MAX(MIN(v, u), 1 - v);
	}

	template<typename T>
	T implicationByMamdani(T v, T u)
	{
		return MIN(v, u);
	}

	template<typename T>
	boost::numeric::ublas::vector<T> implicationV(boost::numeric::ublas::vector<T> v, boost::numeric::ublas::vector<T> u, std::function<T(T, T)> implication)
	{
		using namespace boost::numeric;
		ublas::vector<T> out_vector{ ublas::zero_vector<T>(u.size()) };

		for (size_t i = 0; i < out_vector.size(); ++i)
			out_vector(i) = implication(v(i), u(i));

		return out_vector;
	}
	

	template<typename T>
	std::wstring printMatrix(const boost::numeric::ublas::matrix<T>& matrix, unsigned short sing = 2)
	{
		std::wstringstream out;

		for (size_t i = 0; i < matrix.size1(); ++i)
		{
			for (size_t j = 0; j < matrix.size2(); ++j)
			{
				out << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(sing) << std::setw(sing + 4) << std::left << matrix(i, j);
			}
			out << '\n';
		}

		return out.str();
	}

	template<typename T>
	std::wstring printVector(const boost::numeric::ublas::vector<T>& vector, unsigned short sing = 2)
	{
		std::wstringstream out;

		for (size_t i = 0; i < vector.size(); ++i)
			out << std::setiosflags(std::ios::fixed | std::ios::showpoint) << std::setprecision(sing) << std::setw(sing + 4) << std::left << vector(i);

		return out.str();
	}
}