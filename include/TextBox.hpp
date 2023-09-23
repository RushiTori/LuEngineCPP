#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include "DrawableText.hpp"

class TextBox {
   private:
	const string alphabet;
	string content = "";
	int selectCursor = -1, writingCursor = 0;

   public:
	Rectangle body = (Rectangle){.x = 0, .y = 0, .width = 275, .height = 30};
	uint maxCharCount = 25;
	bool isActive = true, isFocused = false;

	TextBox() = delete;
	TextBox(float x, float y, float w, float h, uint maxCharCount_, const string& alphabet_);
	TextBox(const LVector& pos, float w, float h, uint maxCharCount_, const string& alphabet_);
	TextBox(const Rectangle& rec, uint maxCharCount_, const string& alphabet_);

	TextBox(const TextBox& other) = delete;

	void SetPos(const LVector& pos);
	void Move(const LVector& vel);
	void SetSizes(const LVector& sizes);
	void SetBody(const Rectangle& rec = (Rectangle){.x = 0, .y = 0, .width = 275, .height = 30});

	void TrySetContent(const string& str);

	string GetSelection() const;
	string GetContentStr() const;
	long GetContentInt(uint base) const;
	ulong GetContentUInt(uint base) const;
	float GetContentFloat() const;

	bool EraseSelection();

	void Update(const LVector& cursorPos = GetMousePosition());
	void Display() const;

   private:
	void MouseInteract(const LVector& mousePos);
	void EraseChars(uint eraseIdx, uint eraseCount);
	void AddChars(const string& str);

	void DisplayCursor() const;

   public:
	static const string ASCII_PRINTABLES;
	static const string LOWERCASE_ALPHABET;
	static const string UPPERCASE_ALPHABET;
	static const string WHOLE_ALPHABET;

	static const string DIGITS;
	static const string ONLY_DIGITS;
	static const string MATH_SYMBOLS;
	static const string MATHEXPR_SYMBOLS;
	static const string TEXT_SYMBOLS;
	static const string MISC_SYMBOLS;
	static const string ALL_SYMBOLS;
};

inline const string TextBox::ASCII_PRINTABLES =
	"!\"#$%&\'()*+,-./0123456789:.<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
inline const string TextBox::LOWERCASE_ALPHABET = " abcdefghijklmnopqrstuvwxyz";
inline const string TextBox::UPPERCASE_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
inline const string TextBox::WHOLE_ALPHABET = TextBox::LOWERCASE_ALPHABET + TextBox::UPPERCASE_ALPHABET;

inline const string TextBox::DIGITS = " 0123456789";
inline const string TextBox::ONLY_DIGITS = "0123456789";
inline const string TextBox::MATH_SYMBOLS = " ()+-/*^%.,\'";		   // character '\'' is there as a digit separator
inline const string TextBox::MATHEXPR_SYMBOLS = " <=>~()+-/*^%.,\'";  // character '\'' is there as a digit separator
inline const string TextBox::TEXT_SYMBOLS = " ,:;.?!-()\"\'`";
inline const string TextBox::MISC_SYMBOLS = "_|#$&@[]{}\\";
inline const string TextBox::ALL_SYMBOLS = TextBox::MATHEXPR_SYMBOLS + TextBox::TEXT_SYMBOLS + TextBox::MISC_SYMBOLS;

#endif	// TEXT_BOX_HPP
