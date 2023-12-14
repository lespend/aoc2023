#include "../lib/sw.h"
#include <assert.h>

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#define CARD_FORCE "23456789TJQKA"
#define CARD_FORCE2 "J23456789TQKA"
#define CARDS_NUM 1024

typedef struct {
  int chr;
  int count;
} Freq;

typedef enum {
  COMB_FIVE,
  COMB_FOUR,
  COMB_FULL_HOUSE,
  COMB_THREE,
  COMB_TWO_PAIR,
  COMB_ONE_PAIR,
  COMB_HIGH_CARD,
} Comb_Types;

typedef struct {
  sw *data;
  int rate;
  Comb_Types comb;
} Camel_Card;

int card_sym_to_int(char sym) {
  char *card_force = CARD_FORCE2;
  for (char *p = card_force; *p != '\0'; p++) {
    if (*p == sym) {
      return p - card_force;
    }
  }
  return -1;
}

void dump_freq(Freq *arr, int arr_size) {
  for (int i = 0; i < arr_size; i++) {
    printf("%c = %d\n", arr[i].chr, arr[i].count);
  }
}

void sort_freq(Freq *arr, int arr_size) {
  for (int i = 0; i < arr_size; i++) {
    for (int j = i + 1; j < arr_size; j++) {
      if (arr[i].count < arr[j].count) {
        Freq tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}

Comb_Types get_card_comb(sw *card) {
  Freq analyze[strlen(CARD_FORCE2)];
  int analyze_size = 0;
  for (int i = 0; i < card->length; i++) {
    int matched = 0;
    for (int j = 0; j < analyze_size; j++) {
      if (analyze[j].chr == card->data[i]) {
        matched = 1;
        analyze[j].count += 1;
        break;
      }
    }

    if (!matched) {
      analyze[analyze_size++] = (Freq){.chr = card->data[i], .count = 1};
    }
  }

  sort_freq(analyze, analyze_size);

  int joker_index = -1;
  int is_five_joker = 0;

  for (int i = 0; i < analyze_size; i++) {
    if (analyze[i].chr == 'J') {
      joker_index = i;
    }
  }

  if (joker_index == 0) {
    if (analyze[joker_index].count == 5) {
      is_five_joker = 1;
    } else {
      analyze[1].count += analyze[joker_index].count;
    }
  } else if (joker_index > 0) {
    analyze[0].count += analyze[joker_index].count;
  }

  if (!is_five_joker) {
    analyze[joker_index].count = 0;
  }

  sort_freq(analyze, analyze_size);

  if (analyze[0].count == 5) {
    return COMB_FIVE;
  } else if (analyze[0].count == 4) {
    return COMB_FOUR;
  } else if (analyze[0].count == 3 && analyze[1].count == 2) {
    return COMB_FULL_HOUSE;
  } else if (analyze[0].count == 3) {
    return COMB_THREE;
  } else if (analyze[0].count == 2 && analyze[1].count == 2) {
    return COMB_TWO_PAIR;
  } else if (analyze[0].count == 2) {
    return COMB_ONE_PAIR;
  } else {
    return COMB_HIGH_CARD;
  }

  dump_freq(analyze, analyze_size);
}

sw *comb_types_to_sw(Comb_Types type) {
  switch (type) {
  case COMB_FIVE:
    return sw_dup("COMB_FIVE");
  case COMB_FOUR:
    return sw_dup("COMB_FOUR");
  case COMB_FULL_HOUSE:
    return sw_dup("COMB_FULL_HOUSE");
  case COMB_THREE:
    return sw_dup("COMB_THREE");
  case COMB_TWO_PAIR:
    return sw_dup("COMB_TWO_PAIR");
  case COMB_ONE_PAIR:
    return sw_dup("COMB_ONE_PAIR");
  default:
    assert("comb_types_to_sw: incorrect type\n");
    break;
  }
  return sw_dup("");
}

// a > b: return 1
// a < b: return -1
// a == b: return 0
int compare_cards(Camel_Card a, Camel_Card b) {
  if (a.comb != b.comb) {
    if (a.comb < b.comb) {
      return 1;
    } else {
      return -1;
    }
  } else {
    for (int i = 0; i < a.data->length; i++) {
      int aweight = card_sym_to_int(a.data->data[i]);
      int bweight = card_sym_to_int(b.data->data[i]);
      if (aweight < bweight) {
        return -1;
      } else if (aweight > bweight) {
        return 1;
      }
    }

    return 0;
  }
}

void sort_cards(Camel_Card *arr, int arr_size) {
  for (int i = 0; i < arr_size; i++) {
    for (int j = i; j < arr_size; j++) {
      if (compare_cards(arr[i], arr[j]) == 1) {
        Camel_Card tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
      }
    }
  }
}

int main() {
  Camel_Card *cards = malloc(sizeof(Camel_Card) * CARDS_NUM);
  int cards_size = 0;
  sw *input = slurp_file("data2.txt");
  while (input->length > 0) {
    sw *line = sw_split(input, '\n');
    sw *card_data = sw_split(line, ' ');
    int rate = atoi(sw_split(line, ' ')->data);
    Comb_Types comb = get_card_comb(card_data);
    cards[cards_size++] =
        (Camel_Card){.data = card_data, .rate = rate, .comb = comb};
  }

  sort_cards(cards, cards_size);

  int rate_sum = 0;
  for (int i = 0; i < cards_size; i++) {
    sw *data = cards[i].data;
    sw *comb = comb_types_to_sw(cards[i].comb);
    printf("%.*s %.*s %d\n", data->length, data->data, comb->length, comb->data,
           i);
    rate_sum += cards[i].rate * (i + 1);
  }
  printf("Rate sum: %d\n", rate_sum);
  return 0;
}
