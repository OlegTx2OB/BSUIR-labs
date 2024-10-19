import androidx.compose.material.MaterialTheme
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application
import androidx.lifecycle.viewmodel.compose.viewModel
import theme.strAppName
import view.MainScreen

fun main() = application {
    Window(
        onCloseRequest = ::exitApplication,
        title = strAppName,
        icon = painterResource("drawable/ic_app_logo.png"),
    ) {
        MaterialTheme {
            MainScreen(viewModel())
        }
        window.minimumSize = java.awt.Dimension(700, 700)
    }
}