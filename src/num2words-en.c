#include "num2words-en.h"
#include "string.h"

static const char* const JI_TWELVE[] = {
  "",
  "ichi ji",
  "ni ji",
  "san ji",
  "yo ji",
  "go ji",
  "roku ji",
  "shichi ji",
  "hachi ji",
  "kyu ji",
  "ju ji",
  "ju ichi ji",
  "ju ni ji"
};

static const char* const FUN_ONES[] = {
  "",
  "ippun",
  "ni fun",
  "san pun",
  "yon pun ",
  "go fun",
  "roppun",
  "nana fun",
  "happun",
  "kyu fun"
};

static const char* const FUN_TENS[] ={
  "",
  "juppun",
  "ni juppun",
  "san juppun",
  "yon juppun",
  "go juppun",
  "roku juppun",
  "nana juppun",
  "roku juppon",
  "kyu juppon"
};

static const char* const FUN_TENS_PRE[] = {
  "",
  "ju",
  "ni ju",
  "san ju",
  "yon ju",
  "go ju"
};

static size_t append_number(char* words, int num) {
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 0) {
    if (ones_val == 0) {
      strcat(words, FUN_TENS[tens_val]);
      len += strlen(FUN_TENS[tens_val]);
    }
    else {
      strcat(words, FUN_TENS_PRE[tens_val]);
      len += strlen(FUN_TENS_PRE[tens_val]);
    }
    strcat(words, "-");
    len += 1;
  }

  strcat(words, FUN_ONES[ones_val]);
  len += strlen(FUN_ONES[ones_val]);
  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}


void time_to_words(int hours, int minutes, char* words, size_t length) {

  size_t remaining = length;
  memset(words, 0, length);

  if (hours == 0 || hours == 12) {
    remaining -= append_string(words, remaining, JI_TWELVE[12]);
  } else {
    remaining -= append_string(words, remaining, JI_TWELVE[hours % 12]);
  }

  remaining -= append_string(words, remaining, "-");
  remaining -= append_number(words, minutes);
  remaining -= append_string(words, remaining, "-");
}

void time_to_3words(int hours, int minutes, char *line1, char *line2, char *line3, size_t length)
{
	char value[length];
	time_to_words(hours, minutes, value, length);
	
	memset(line1, 0, length);
	memset(line2, 0, length);
	memset(line3, 0, length);
	
	char *start = value;
	char *pch = strstr (start, "-");
	while (pch != NULL) {
		if (line1[0] == 0) {
			memcpy(line1, start, pch-start);
		}  else if (line2[0] == 0) {
			memcpy(line2, start, pch-start);
		} else if (line3[0] == 0) {
			memcpy(line3, start, pch-start);
		}
		start += pch-start+1;
		pch = strstr(start, "-");
	}
}
