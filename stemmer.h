#pragma once

//#ifndef __RUSSIAN_STEM_H__
//#define __RUSSIAN_STEM_H__

#include "stemming.h"
///Namespace for stemming classes.
namespace stemming
{
	static const wchar_t RUSSIAN_VOWELS[] = { 0x0410, 0x0430, 0x0415, 0x0435, 0x0418, 0x0438,
		0x041E, 0x043E, 0x423, 0x0443, 0x042B, 0x044B,
		0x042D, 0x044D, 0x042E, 0x044E, 0x042F, 0x044F, 0 };

	static const wchar_t RUSSIAN_A_UPPER = 0x0410;
	static const wchar_t RUSSIAN_A_LOWER = 0x0430;

	static const wchar_t RUSSIAN_BE_UPPER = 0x0411;
	static const wchar_t RUSSIAN_BE_LOWER = 0x0431;

	static const wchar_t RUSSIAN_VE_UPPER = 0x0412;
	static const wchar_t RUSSIAN_VE_LOWER = 0x0432;

	static const wchar_t RUSSIAN_GHE_UPPER = 0x0413;
	static const wchar_t RUSSIAN_GHE_LOWER = 0x0433;

	static const wchar_t RUSSIAN_DE_UPPER = 0x0414;
	static const wchar_t RUSSIAN_DE_LOWER = 0x0434;

	static const wchar_t RUSSIAN_IE_UPPER = 0x0415;
	static const wchar_t RUSSIAN_IE_LOWER = 0x0435;

	static const wchar_t RUSSIAN_ZHE_UPPER = 0x0416;
	static const wchar_t RUSSIAN_ZHE_LOWER = 0x0436;

	static const wchar_t RUSSIAN_ZE_UPPER = 0x0417;
	static const wchar_t RUSSIAN_ZE_LOWER = 0x0437;

	static const wchar_t RUSSIAN_I_UPPER = 0x0418;
	static const wchar_t RUSSIAN_I_LOWER = 0x0438;

	static const wchar_t RUSSIAN_SHORT_I_UPPER = 0x0419;
	static const wchar_t RUSSIAN_SHORT_I_LOWER = 0x0439;

	static const wchar_t RUSSIAN_KA_UPPER = 0x041A;
	static const wchar_t RUSSIAN_KA_LOWER = 0x043A;

	static const wchar_t RUSSIAN_EL_UPPER = 0x041B;
	static const wchar_t RUSSIAN_EL_LOWER = 0x043B;

	static const wchar_t RUSSIAN_EM_UPPER = 0x041C;
	static const wchar_t RUSSIAN_EM_LOWER = 0x043C;

	static const wchar_t RUSSIAN_EN_UPPER = 0x041D;
	static const wchar_t RUSSIAN_EN_LOWER = 0x043D;

	static const wchar_t RUSSIAN_O_UPPER = 0x041E;
	static const wchar_t RUSSIAN_O_LOWER = 0x043E;

	static const wchar_t RUSSIAN_PE_UPPER = 0x041F;
	static const wchar_t RUSSIAN_PE_LOWER = 0x043F;

	static const wchar_t RUSSIAN_ER_UPPER = 0x0420;
	static const wchar_t RUSSIAN_ER_LOWER = 0x0440;

	static const wchar_t RUSSIAN_ES_UPPER = 0x0421;
	static const wchar_t RUSSIAN_ES_LOWER = 0x0441;

	static const wchar_t RUSSIAN_TE_UPPER = 0x0422;
	static const wchar_t RUSSIAN_TE_LOWER = 0x0442;

	static const wchar_t RUSSIAN_U_UPPER = 0x0423;
	static const wchar_t RUSSIAN_U_LOWER = 0x0443;

	static const wchar_t RUSSIAN_EF_UPPER = 0x0424;
	static const wchar_t RUSSIAN_EF_LOWER = 0x0444;

	static const wchar_t RUSSIAN_HA_UPPER = 0x0425;
	static const wchar_t RUSSIAN_HA_LOWER = 0x0445;

	static const wchar_t RUSSIAN_TSE_UPPER = 0x0426;
	static const wchar_t RUSSIAN_TSE_LOWER = 0x0446;

	static const wchar_t RUSSIAN_CHE_UPPER = 0x0427;
	static const wchar_t RUSSIAN_CHE_LOWER = 0x0447;

	static const wchar_t RUSSIAN_SHA_UPPER = 0x0428;
	static const wchar_t RUSSIAN_SHA_LOWER = 0x0448;

	static const wchar_t RUSSIAN_SHCHA_UPPER = 0x0429;
	static const wchar_t RUSSIAN_SHCHA_LOWER = 0x0449;

	static const wchar_t RUSSIAN_HARD_SIGN_UPPER = 0x042A;
	static const wchar_t RUSSIAN_HARD_SIGN_LOWER = 0x044A;

	static const wchar_t RUSSIAN_YERU_UPPER = 0x042B;
	static const wchar_t RUSSIAN_YERU_LOWER = 0x044B;

	static const wchar_t RUSSIAN_SOFT_SIGN_UPPER = 0x042C;
	static const wchar_t RUSSIAN_SOFT_SIGN_LOWER = 0x044C;

	static const wchar_t RUSSIAN_E_UPPER = 0x042D;
	static const wchar_t RUSSIAN_E_LOWER = 0x044D;

	static const wchar_t RUSSIAN_YU_UPPER = 0x042E;
	static const wchar_t RUSSIAN_YU_LOWER = 0x044E;

	static const wchar_t RUSSIAN_YA_UPPER = 0x042F;
	static const wchar_t RUSSIAN_YA_LOWER = 0x044F;

	/**
	\brief Стеммер Портера для русского языка.
	\par Возможные окончания слов:

	PERFECTIVE GERUND:
	- Группа 1: в, вши, вшись
	- Группа 2: ив, ивши, ившись, ыв, ывши, ывшись

	Окончаниям из группы 1 должна предшествовать буква а или я

	ADJECTIVE:
	- ее, ие, ые, ое, ими, ыми, ей, ий, ый, ой, ем, им, ым, ом, его, ого, ему, ому, их, ых, ую, юю, ая, яя, ою, ею.

	PARTICIPLE:
	- Группа 1: ем, нн, вш, ющ, щ
	- Группа 2: ивш, ывш, ующ

	Окончаниям из группы 1 должна предшествовать буква а или я

	VERB:
	- Группа 1: ла, на, ете, йте, ли, й, л, ем, н, ло, но, ет, ют, ны, ть, ешь, нно
	- Группа 2: ила, ыла, ена, ейте, уйте, ите, или, ыли, ей, уй, ил, ыл, им, ым, ен, ило, ыло, ено, ят, ует, уют, ит, ыт, ены, ить, ыть, ишь, ую, ю
	
	Окончаниям из группы 1 должна предшествовать буква а или я
	
	SUPERLATIVE:
	- ейш, ейше

	DERIVATIONAL:
	- ост, ость

	REFLEXIVE:
	- ся сь
	NOUN:
	- а, ев, ов, ие, ье, е, иями, ями, ами, еи, ии, и, ией, ей, ой, ий, й, иям, ям, ием, ем, ам, ом, о, у, ах, иях, ях, ы, ь, ию, ью, ю, ия, ья, я
	
	@par Алгоритм:

	<b>Шаг 1:</b>
	Найти окончание PERFECTIVE GERUND. Если оно существует — удалить его и завершить этот шаг.<br>
	Иначе, удаляем окончание REFLEXIVE (если оно существует)<br>
	Затем в следующем порядке пробуем удалить окончания:
		-# ADJECTIVAL,
		-# VERB,
		-# NOUN

	Как только одно из них найдено — шаг завершается.

	<b>Шаг 2:</b>

	Если слово оканчивается на и — удаляем и.

	<b>Шаг 3:</b>

	Если в R2 найдется окончание DERIVATIONAL — удаляем его.

	<b>Шаг 4:</b>

	Возможен один из трех вариантов:

	- если слово оканчивается на нн — удаляем последнюю букву
	- если слово оканчивается на SUPERLATIVE — удаляем его и снова удаляем последнюю букву, если слово оканчивается на нн
	- если слово оканчивается на ь — удаляем его

	*/
	template <typename string_typeT = std::wstring>
	/**
	\class russian_stem
	Класс, реализующий стеммер Портера для русского языка.
	*/
	class russian_stem : public stem<string_typeT>
	{
	public:
		//---------------------------------------------
		/**
		Метод находит области RV, R1, R2 и последовательно вызывает методы 
		step_1(string_typeT& text), step_2(string_typeT& text), 
		step_3(string_typeT& text), step_4(string_typeT& text).
		В результате работы метода, text будет содержать основу исходного слова
		\param[in,out] text входная строка для стемминга
		*/
		void operator()(string_typeT& text)
		{
			if (text.length() < 2)
			{
				return;
			}

			//reset internal data
			stem<string_typeT>::reset_r_values();

			stem<string_typeT>::find_r1(text, RUSSIAN_VOWELS);
			stem<string_typeT>::find_r2(text, RUSSIAN_VOWELS);
			stem<string_typeT>::find_russian_rv(text, RUSSIAN_VOWELS);

			//change 33rd letter ('&#x0451;') to '&#x0435;'
			for (size_t i = 0; i < text.length(); ++i)
			{
				if (text[i] == 0x0451)
				{
					text[i] = RUSSIAN_IE_LOWER;
				}
				else if (text[i] == 0x0401)
				{
					text[i] = RUSSIAN_IE_UPPER;
				}
			}

			step_1(text);
			step_2(text);
			step_3(text);
			step_4(text);
		}
	private:
		/** Метод, реализующий первый шаг алгоритма стеммера Портера
		\param[in] text ссылка на строку для стемминга
		*/
		void step_1(string_typeT& text)
		{
			//search for a perfect gerund
			//group 2
			if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
				RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
				RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
				RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
				RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
				RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
					RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
					RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
					RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
					RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
					RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false))
			{
				return;
			}
			//group 1
			else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
				RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
				RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
				RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
				RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER))
			{
				if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
					RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
					RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
					RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
					RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
					RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) ||
					stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
						RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
						RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
						RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
						RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
						RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER))
				{
					text.erase(text.end() - 5, text.end());
					stem<string_typeT>::update_r_sections(text);
					return;
				}
			}
			//group 2
			else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
				RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
				RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
				RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER,
					RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
					RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
					RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false))
			{
				return;
			}
			//group 1
			else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
				RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
				RUSSIAN_I_LOWER, RUSSIAN_I_UPPER))
			{
				if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER,
					RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
					RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
					RUSSIAN_I_LOWER, RUSSIAN_I_UPPER) ||
					stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
						RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER,
						RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
						RUSSIAN_I_LOWER, RUSSIAN_I_UPPER))
				{
					text.erase(text.end() - 3, text.end());
					stem<string_typeT>::update_r_sections(text);
					return;
				}
			}
			//group 2
			else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false))
			{
				return;
			}
			//group 1
			else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER))
			{
				if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER) ||
					stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER))
				{
					text.erase(text.end() - 1, text.end());
					stem<string_typeT>::update_r_sections(text);
					return;
				}
			}
			//reflexive
			if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false))
			{ /*NOOP*/
			}
			//adjectival
			if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_UPPER, RUSSIAN_YERU_LOWER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_GHE_LOWER, RUSSIAN_GHE_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_GHE_LOWER, RUSSIAN_GHE_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false))
			{
				//delete participles
				//group 2
				if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, false) ||
					stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, false) ||
					stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_SHCHA_LOWER, RUSSIAN_SHCHA_UPPER, false))
				{/*NOOP*/
				}
				//group 1
				else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER) ||
					stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER) ||
					stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER) ||
					stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_SHCHA_LOWER, RUSSIAN_SHCHA_UPPER))
				{
					if (text.length() >= 3 &&
						stem<string_typeT>::get_rv() <= text.length() - 3 &&
						(is_either<wchar_t>(text[text.length() - 3], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
							is_either<wchar_t>(text[text.length() - 3], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)))
					{
						text.erase(text.end() - 2, text.end());
						stem<string_typeT>::update_r_sections(text);
						return;
					}
				}
				else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_SHCHA_LOWER, RUSSIAN_SHCHA_UPPER))
				{
					if (text.length() >= 2 &&
						stem<string_typeT>::get_rv() <= text.length() - 2 &&
						(is_either<wchar_t>(text[text.length() - 2], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
							is_either<wchar_t>(text[text.length() - 2], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)))
					{
						text.erase(text.end() - 1, text.end());
						stem<string_typeT>::update_r_sections(text);
						return;
					}
				}
				return;
			}
			//verb
			//group 2
			else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||/*4*/
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false))
			{
				return;
			}
			//group 1
			if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER))
			{
				if (text.length() >= 4 &&
					stem<string_typeT>::get_rv() <= text.length() - 4 &&
					(is_either<wchar_t>(text[text.length() - 4], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
						is_either<wchar_t>(text[text.length() - 4], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)))
				{
					text.erase(text.end() - 3, text.end());
					stem<string_typeT>::update_r_sections(text);
					return;
				}
			}
			//group 2
			else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false))
			{
				return;
			}
			//group 1
			else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||/*2*/
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER))
			{
				if (text.length() >= 3 &&
					stem<string_typeT>::get_rv() <= text.length() - 3 &&
					(is_either<wchar_t>(text[text.length() - 3], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
						is_either<wchar_t>(text[text.length() - 3], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)))
				{
					text.erase(text.end() - 2, text.end());
					stem<string_typeT>::update_r_sections(text);
					return;
				}
			}
			if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER) ||/*1*/
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EL_LOWER, RUSSIAN_EL_UPPER) ||
				stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER))
			{
				if (text.length() >= 2 &&
					stem<string_typeT>::get_rv() <= text.length() - 2 &&
					(is_either<wchar_t>(text[text.length() - 2], RUSSIAN_A_LOWER, RUSSIAN_A_UPPER) ||
						is_either<wchar_t>(text[text.length() - 2], RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER)))
				{
					text.erase(text.end() - 1, text.end());
					stem<string_typeT>::update_r_sections(text);
					return;
				}
			}

			//noun
			if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER,
				RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER,
				RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER,
				RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_VE_LOWER, RUSSIAN_VE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_EM_LOWER, RUSSIAN_EM_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, RUSSIAN_HA_LOWER, RUSSIAN_HA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_LOWER, RUSSIAN_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_A_LOWER, RUSSIAN_A_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_U_LOWER, RUSSIAN_U_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YU_LOWER, RUSSIAN_YU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YA_LOWER, RUSSIAN_YA_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_YERU_LOWER, RUSSIAN_YERU_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER, false) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER, false))
			{
				return;
			}
		}
		/** Метод, реализующий втрой шаг алгоритма стеммера Портера
		\param[in] text ссылка на строку для стемминга
		*/
		void step_2(string_typeT& text)
		{
			stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_I_UPPER, RUSSIAN_I_LOWER);
		}
		/** Метод, реализующий третий шаг алгоритма стеммера Портера
		\param[in] text ссылка на строку для стемминга
		*/
		void step_3(string_typeT& text)
		{
			if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
				RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
				RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER,
				RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER))
			{
				stem<string_typeT>::delete_if_is_in_r2(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
					RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
					RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER,
					RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER);
			}
			else if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
				RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
				RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER))
			{
				stem<string_typeT>::delete_if_is_in_r2(text, RUSSIAN_O_LOWER, RUSSIAN_O_UPPER,
					RUSSIAN_ES_LOWER, RUSSIAN_ES_UPPER,
					RUSSIAN_TE_LOWER, RUSSIAN_TE_UPPER);
			}
		}
		/** Метод, реализующий четвертый шаг алгоритма стеммера Портера
		\param[in] text ссылка на строку для стемминга
		*/
		void step_4(string_typeT& text)
		{
			if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
				RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER))
			{
				text.erase(text.end() - 1, text.end());
				stem<string_typeT>::update_r_sections(text);
			}
			else if (stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
				RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER,
				RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER,
				RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER) ||
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_IE_LOWER, RUSSIAN_IE_UPPER,
					RUSSIAN_SHORT_I_LOWER, RUSSIAN_SHORT_I_UPPER,
					RUSSIAN_SHA_LOWER, RUSSIAN_SHA_UPPER))
			{
				if (stem<string_typeT>::is_suffix_in_rv(text, RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER,
					RUSSIAN_EN_LOWER, RUSSIAN_EN_UPPER))
				{
					text.erase(text.end() - 1, text.end());
					stem<string_typeT>::update_r_sections(text);
				}
			}
			else
			{
				stem<string_typeT>::delete_if_is_in_rv(text, RUSSIAN_SOFT_SIGN_LOWER, RUSSIAN_SOFT_SIGN_UPPER);
			}
		}
	};
}

/** @}*/

//#endif //__RUSSIAN_STEM_H__
