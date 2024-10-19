package util

import theme.FLAG_FOR_BITSTUFF

fun bitStuffSymbol(): Char {
    return if (FLAG_FOR_BITSTUFF.last() == '1') {
        '0'
    } else {
        '1'
    }
}