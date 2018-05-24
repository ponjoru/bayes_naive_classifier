/**
\file
\brief ������������ ���� � ��������� ������

������ ���� �������� �������� ������, �������������
��� ���������� ��������������� ������� ��� 
��������� �������� �������
*/
#pragma once

#ifndef STEM_H
#define STEM_H

#include <algorithm>
//#include "utilities.h"

template<typename T>
/** ����� ����������, �������� �� �������� �������� ����� �� ���� ������ �������� ��������
\param[in] value �������� ��������
\param[in] first ������ �������� ��� ���������
\param[in] second ������ �������� ��� ���������
\return True, ���� value �������� first ��� second, ����� False
*/
inline bool is_either(const T value, const T first, const T second)
{
	return (value == first || value == second);
}

namespace stemming
{
	/**
	\brief ������� ����� ��� ��������.
	\class stem

	\details ����� ��������� ��������������� �������, ����� ��� ���������� �������� RV, R1, R2,
	�����/�������� ���������/��������� �� ��������� �������� �����,
	��� ��������� �������� �������.
	*/
	template <typename string_typeT = std::wstring>
	class stem
	{
	public:
		/** �����������<br>
		��������� m_r1, m_r2, m_rv ���������������� ������
		*/
		stem() : m_r1(0), m_r2(0), m_rv(0) {}
	protected:
		
		/** �����, � ������� ���������� ��������� R1 �������. <br>
		������� ����� ����� ������� ��������� ��������-����������<br>
		��������� ������������ � ���� ������ m_r1.
		\param[in] text ����������� ������ �� �������� �����
		\param[in] vowel_list ����������� ��������� �� ������ ������� ����
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
		/** �����, � ������� ���������� ��������� R2 �������. <br>
		������� R1 ����� ������� ��������� ��������-����������<br>		
		��������� ������������ � ���� ������ m_r2.
		\param[in] text ����������� ������ �� �������� �����
		\param[in] vowel_list ����������� ��������� �� ������ ������� ����
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
		/** �����, � ������� ���������� ��������� RV �������. <br>
		������� ����� ����� ������ �������. ��� ����� ���� ������,
		���� ������� � ����� �����������.<br>
		��������� ������������ � ���� ������ m_rv.
		\param[in] text ����������� ������ �� �������� �����
		\param[in] vowel_list ����������� ��������� �� ������ ������� ����
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
		/** �����, � ������� ���������� ���������� ������� rv, r1 � r2
		\param[in] text ����������� ������ �� �������� �����
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ������ �������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ������� ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ����� ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� �������� � RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� ��������� �������� � RV - ������� ��� ������ ��������
		\return true, ���� ������� ������ � ������ �����<br>
		false, ���� ����� �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� R2 - ������� ��� ������ �������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� �������� �������� �� R2 - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� �������� �������� �� R2 - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� R2 - ������� ��� ������� ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� R2 - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� R2 - ������� ��� ����� ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� R2 - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� R2 - ������� ��� ������ ��������
		\return true, ���� ������� ������ � ������ ������� R2 � ��� ������<br>
		false, ���� ������� R2 �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ������ �������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ������� ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ����� ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ���� ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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

		/** ����� ��� �������� �������� �� RV - ������� ��� ������ ��������
		\return true, ���� ������� ������ � ������ ������� RV � ��� ������<br>
		false, ���� ������� RV �� �������� �������� ��� ���������� �������� � ����� < 1
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
		/** ����� ��� ��������� ���������� �������� ������� R1
		\return m_r1
		*/
		inline size_t get_r1() const
		{
			return m_r1;
		}

		/** ����� ��� ��������� ���������� �������� ������� R2
		\return m_r2
		*/
		inline size_t get_r2() const
		{
			return m_r2;
		}
		
		/** ����� ��� ��������� ���������� �������� ������� RV
		\return m_rv
		*/
		inline size_t get_rv() const
		{
			return m_rv;
		}
	
		/** �����, � ������� ���������� ����� �������� ��� ���� ��������
		*/
		void reset_r_values()
		{
			m_r1 = m_r2 = m_rv = 0;
		}
	private:
		size_t m_r1;///< ������ ������� r1 � �������� 
		size_t m_r2;///< ������ ������� r2 � ��������
		//only used for romance/russian languages
		size_t m_rv;///<������ ������� rv � ��������
	};
}

#endif 
