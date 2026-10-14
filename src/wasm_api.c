#include <emscripten.h>
#include "deck.h"
#include "game.h"

EMSCRIPTEN_KEEPALIVE
int api_card_value(char val) {
    card_t c;
    c.val = val;
    return cardValue(c);
}