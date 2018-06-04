/**
\file
\brief Заголовочный файл с описанием класса

Данный файл содержит описание класса, используемого
для реализации вспомогательных функция для 
алгоритма стеммера Портера
*/
#pragma once

#ifndef STEM_H
#define STEM_H

#include <algorithm>
//#include "utilities.h"

template<typename T>
/** Метод определяет, является ли заданное значение одним из двух других заданных значений
\param[in] value заданное значение
\param[in] first первое значение для сравнения
\param[in] second второе значение для сравнения
\return True, если value является first или second, иначе False
*/
inline bool is_either(const T value, const T first, const T second)
{
	return (value == first || value == second);
}

namespace stemming
{
	/**
	\brief Базовый класс для стеммера.
	\class stem

	\details Класс реализует вспомогательные функции, такие как нахождение областей RV, R1, R2,
	поиск/удаление окончаний/суффиксов из различных областей слова,
	для алгоритма стеммера Портера.
	*/
	template <typename string_typeT = std::wstring>
	class stem
	{
	public:
		/** Конструктор<br>
		Параметры m_r1, m_r2, m_rv инициализируются нулями
		*/
		stem() : m_r1(0), m_r2(0), m_rv(0) {}
	protected:
		
		/** Метод, в котором происходит выделение R1 области. <br>
		Область слова после первого сочетания “гласная-согласная”<br>
		Результат записывается в член класса m_r1.
		\param[in] text константная ссылка на исходное слово
		\param[in] vowel_list константный указатель на список гласных букв
		*/
		void find_r1(const string_typeT& text,
			const wchar_t* vowel_list)
		{
			//R1 is the region after the first consonant after the first vowel
			size_t start = text.find_first_of(vowel_list, 0);
			if (start == string_typeT::npos)
			{
				//we need at least need a vowel somewhere in the word
				m_r1 = text.length();
				return;
			}

			m_r1 = text.find_first_not_of(vowel_list, ++start);
			if (get_r1() == string_typeT::npos)
			{
				m_r1 = text.length();
			}
			else
			{
				++m_r1;
			}
		}
		/** Метод, в котором происходит выделение R2 области. <br>
		Область R1 после первого сочетания “гласная-согласная”<br>		
		Результат записывается в член класса m_r2.
		\param[in] text константная ссылка на исходное слово
		\param[in] vowel_list константный указатель на список гласных букв
		*/
		void find_r2(const string_typeT& text,
			const wchar_t* vowel_list)
		{
			size_t start = 0;
			//look for R2--not required for all criteria.
			//R2 is the region after the first consonant after the first vowel after R1
			if (get_r1() != text.length())
			{
				start = text.find_first_of(vowel_list, get_r1());
			}
			else
			{
				start = string_typeT::npos;
			}
			if (start != string_typeT::npos &&
				static_cast<int>(start) != static_cast<int>(text.length()) - 1)
			{
				m_r2 = text.find_first_not_of(vowel_list, ++start);
				if (get_r2() == string_typeT::npos)
				{
					m_r2 = text.length();
				}
				else
				{
					++m_r2;
				}
			}
			else
			{
				m_r2 = text.length();
			}
		}
		/** Метод, в котором происходит выделение RV области. <br>
		Область слова после первой гласной. Она может быть пустой,
		если гласные в слове отсутствуют.<br>
		Результат записывается в член класса m_rv.
		\param[in] text константная ссылка на исходное слово
		\param[in] vowel_list константный указатель на список гласных букв
		*/
		void find_russian_rv(const string_typeT& text,
			const wchar_t* vowel_list)
		{
			size_t start = text.find_first_of(vowel_list);
			if (start == string_typeT::npos)
			{
				//can't find first vowel
				m_rv = text.length();
				return;
			}
			else
			{
				m_rv = start + 1;
			}
		}
		/** Метод, в котором происходит обновление области rv, r1 и r2
		\param[in] text константная ссылка на исходное слово
		*/
		inline void update_r_sections(const string_typeT& text)
		{
			if (get_r1() > text.length())
			{
				m_r1 = text.length();
			}
			if (get_r2() > text.length())
			{
				m_r2 = text.length();
			}
			if (get_rv() > text.length())
			{
				m_rv = text.length();
			}
		}
		/** Метод для сравнения суффикса в RV - области для одного символа
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U)
		{
			if (text.length() < 1)
			{
				return false;
			}
			return (is_either<wchar_t>(text[text.length() - 1], suffix1L, suffix1U) &&
				(get_rv() <= text.length() - 1));
		}
		/** Метод для сравнения суффикса в RV - области для двух символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U)
		{
			if (text.length() < 2)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 2], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix2L, suffix2U)) &&
				(get_rv() <= text.length() - 2));
		}
		/** Метод для сравнения суффикса в RV - области для трех символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U)
		{
			if (text.length() < 3)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 3], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix3L, suffix3U)) &&
				(get_rv() <= text.length() - 3));
		}
		/** Метод для сравнения суффикса в RV - области для четырех символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U)
		{
			if (text.length() < 4)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 4], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix4L, suffix4U)) &&
				(get_rv() <= text.length() - 4));
		}
		/** Метод для сравнения суффикса в RV - области для пяти символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U)
		{
			if (text.length() < 5)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 5], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix5L, suffix5U)) &&
				(get_rv() <= text.length() - 5));
		}
		/** Метод для сравнения суффикса в RV - области для шести символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U)
		{
			if (text.length() < 6)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 6], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix6L, suffix6U)) &&
				(get_rv() <= text.length() - 6));
		}
		/** Метод для сравнения суффикса в RV - области для семи символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const wchar_t suffix7L, const wchar_t suffix7U)
		{
			if (text.length() < 7)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 7], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 6], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix6L, suffix6U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix7L, suffix7U)) &&
				(get_rv() <= text.length() - 7));
		}

		/** Метод для сравнения суффикса в RV - области для восьми символов
		\return true, если суффикс входит в состав слова<br>
		false, если слово не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool is_suffix_in_rv(const string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const wchar_t suffix7L, const wchar_t suffix7U,
			const wchar_t suffix8L, const wchar_t suffix8U)
		{
			if (text.length() < 8)
			{
				return false;
			}
			return ((is_either<wchar_t>(text[text.length() - 8], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 7], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 6], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix6L, suffix6U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix7L, suffix7U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix8L, suffix8U)) &&
				(get_rv() <= text.length() - 8));
		}

		/** Метод для удаления суффикса из R2 - области для одного символа
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const bool success_on_find = true)
		{
			if (text.length() < 1)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 1], suffix1L, suffix1U))
			{
				if (get_r2() <= text.length() - 1)
				{
					text.erase(text.length() - 1);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}
		/** Метод для удаления суффикса из R2 - области для двух символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/		
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const bool success_on_find = true)
		{
			if (text.length() < 2)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 2], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix2L, suffix2U))
			{
				if (get_r2() <= text.length() - 2)
				{
					text.erase(text.length() - 2);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}
		/** Метод для удаления суффикса из R2 - области для трех символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const bool success_on_find = true)
		{
			if (text.length() < 3)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 3], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix3L, suffix3U))
			{
				if (get_r2() <= text.length() - 3)
				{
					text.erase(text.length() - 3);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из R2 - области для четырех символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const bool success_on_find = true)
		{
			if (text.length() < 4)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 4], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix4L, suffix4U))
			{
				if (get_r2() <= text.length() - 4)
				{
					text.erase(text.length() - 4);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из R2 - области для пяти символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const bool success_on_find = true)
		{
			if (text.length() < 5)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 5], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix5L, suffix5U))
			{
				if (get_r2() <= text.length() - 5)
				{
					text.erase(text.length() - 5);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из R2 - области для шести символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const bool success_on_find = true)
		{
			if (text.length() < 6)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 6], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix6L, suffix6U))
			{
				if (get_r2() <= text.length() - 6)
				{
					text.erase(text.length() - 6);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из R2 - области для семи символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const wchar_t suffix7L, const wchar_t suffix7U,
			const bool success_on_find = true)
		{
			if (text.length() < 7)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 7], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 6], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix6L, suffix6U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix7L, suffix7U))
			{
				if (get_r2() <= text.length() - 7)
				{
					text.erase(text.length() - 7);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из R2 - области для восьми символов
		\return true, если суффикс входит в состав области R2 и был удален<br>
		false, если область R2 не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_r2(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const wchar_t suffix7L, const wchar_t suffix7U,
			const wchar_t suffix8L, const wchar_t suffix8U,
			const bool success_on_find = true)
		{
			if (text.length() < 8)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 8], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 7], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 6], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix6L, suffix6U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix7L, suffix7U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix8L, suffix8U))
			{
				if (get_r2() <= text.length() - 8)
				{
					text.erase(text.length() - 8);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для одного символа
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const bool success_on_find = true)
		{
			if (text.length() < 1)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 1], suffix1L, suffix1U))
			{
				if (get_rv() <= text.length() - 1)
				{
					text.erase(text.length() - 1);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для двух символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const bool success_on_find = true)
		{
			if (text.length() < 2)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 2], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix2L, suffix2U))
			{
				if (get_rv() <= text.length() - 2)
				{
					text.erase(text.length() - 2);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для трех символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const bool success_on_find = true)
		{
			if (text.length() < 3)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 3], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix3L, suffix3U))
			{
				if (get_rv() <= text.length() - 3)
				{
					text.erase(text.length() - 3);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для четырех символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const bool success_on_find = true)
		{
			if (text.length() < 4)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 4], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix4L, suffix4U))
			{
				if (get_rv() <= text.length() - 4)
				{
					text.erase(text.length() - 4);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для пяти символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const bool success_on_find = true)
		{
			if (text.length() < 5)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 5], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix5L, suffix5U))
			{
				if (get_rv() <= text.length() - 5)
				{
					text.erase(text.length() - 5);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для шести символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const bool success_on_find = true)
		{
			if (text.length() < 6)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 6], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix6L, suffix6U))
			{
				if (get_rv() <= text.length() - 6)
				{
					text.erase(text.length() - 6);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для семи символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const wchar_t suffix7L, const wchar_t suffix7U,
			const bool success_on_find = true)
		{
			if (text.length() < 7)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 7], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 6], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix6L, suffix6U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix7L, suffix7U))
			{
				if (get_rv() <= text.length() - 7)
				{
					text.erase(text.length() - 7);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		/** Метод для удаления суффикса из RV - области для восьми символов
		\return true, если суффикс входит в состав области RV и был удален<br>
		false, если область RV не содержит сфуффикс или количество символов в слове < 1
		*/
		inline bool delete_if_is_in_rv(string_typeT& text,
			const wchar_t suffix1L, const wchar_t suffix1U,
			const wchar_t suffix2L, const wchar_t suffix2U,
			const wchar_t suffix3L, const wchar_t suffix3U,
			const wchar_t suffix4L, const wchar_t suffix4U,
			const wchar_t suffix5L, const wchar_t suffix5U,
			const wchar_t suffix6L, const wchar_t suffix6U,
			const wchar_t suffix7L, const wchar_t suffix7U,
			const wchar_t suffix8L, const wchar_t suffix8U,
			const bool success_on_find = true)
		{
			if (text.length() < 8)
			{
				return false;
			}
			if (is_either<wchar_t>(text[text.length() - 8], suffix1L, suffix1U) &&
				is_either<wchar_t>(text[text.length() - 7], suffix2L, suffix2U) &&
				is_either<wchar_t>(text[text.length() - 6], suffix3L, suffix3U) &&
				is_either<wchar_t>(text[text.length() - 5], suffix4L, suffix4U) &&
				is_either<wchar_t>(text[text.length() - 4], suffix5L, suffix5U) &&
				is_either<wchar_t>(text[text.length() - 3], suffix6L, suffix6U) &&
				is_either<wchar_t>(text[text.length() - 2], suffix7L, suffix7U) &&
				is_either<wchar_t>(text[text.length() - 1], suffix8L, suffix8U))
			{
				if (get_rv() <= text.length() - 8)
				{
					text.erase(text.length() - 8);
					update_r_sections(text);
					return true;
				}
				return success_on_find;
			}
			else
			{
				return false;
			}
		}

		//----------------------------------------------------------
		/** Метод для получения количества символов области R1
		\return m_r1
		*/
		inline size_t get_r1() const
		{
			return m_r1;
		}

		/** Метод для получения количества символов области R2
		\return m_r2
		*/
		inline size_t get_r2() const
		{
			return m_r2;
		}
		
		/** Метод для получения количества символов области RV
		\return m_rv
		*/
		inline size_t get_rv() const
		{
			return m_rv;
		}
	
		/** Метод, в котором происходит сброс размеров для всех областей
		*/
		void reset_r_values()
		{
			m_r1 = m_r2 = m_rv = 0;
		}
	private:
		size_t m_r1;///< Размер области r1 в символах 
		size_t m_r2;///< Размер области r2 в символах
		//only used for romance/russian languages
		size_t m_rv;///<Размер области rv в символах
	};
}

#endif 
