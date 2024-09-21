package theme

import androidx.compose.material.Typography
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight

val typography = Typography(
    h1 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W400,
        fontSize = sp100
    ),

    h2 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W500,
        fontSize = sp28,
    ),

    h3 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W500,
        fontSize = sp18,
    ),

    h4 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W500,
        fontSize = sp14,
    ),
)