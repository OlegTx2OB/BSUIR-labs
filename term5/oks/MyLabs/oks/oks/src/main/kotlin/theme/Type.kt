package theme

import androidx.compose.material.Typography
import androidx.compose.ui.text.TextStyle
import androidx.compose.ui.text.font.FontWeight

// Set of Material typography styles to start with
val typography = Typography(

    h1 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W600,
        fontSize = sp26,
    ),

    h2 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W500,
        fontSize = sp26,
    ),

    h3 = TextStyle(
        color = lightGray,
        fontWeight = FontWeight.W500,
        fontSize = sp18,
    ),
)