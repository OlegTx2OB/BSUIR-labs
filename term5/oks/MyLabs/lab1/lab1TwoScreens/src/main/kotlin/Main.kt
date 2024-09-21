import androidx.compose.material.MaterialTheme
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application
import androidx.compose.ui.window.rememberWindowState
import androidx.lifecycle.viewmodel.compose.viewModel
import theme.strComApp1
import theme.strComApp2
import view.MainScreen
import viewModel.MainViewModel

fun main() = application {
    val viewModel1: MainViewModel = MainViewModel()
    val viewModel2: MainViewModel = MainViewModel()

    Window(
        onCloseRequest = ::exitApplication,
        title = strComApp1,
        icon = painterResource("drawable/ic_app_logo.png"),
        state = rememberWindowState(width = 600.dp, height = 400.dp), // начальные размеры
    ) {
        // Устанавливаем минимальные размеры
        window.minimumSize = java.awt.Dimension(600.dp.value.toInt(), 400.dp.value.toInt())

        MaterialTheme {
            MainScreen(viewModel1) { oldText, newText ->
                if (viewModel1.onTextFieldTextChanged(oldText, newText)) {
                    viewModel2.getComSymbol()
                }
            }
        }
    }

    Window(
        onCloseRequest = ::exitApplication,
        title = strComApp2,
        icon = painterResource("drawable/ic_app_logo.png"),
        state = rememberWindowState(width = 600.dp, height = 400.dp), // начальные размеры
    ) {
        // Устанавливаем минимальные размеры
        window.minimumSize = java.awt.Dimension(600.dp.value.toInt(), 1200.dp.value.toInt())

        MaterialTheme {
            MainScreen(viewModel2) { oldText, newText ->
                if (viewModel2.onTextFieldTextChanged(oldText, newText)) {
                    viewModel1.getComSymbol()
                }
            }
        }
    }
}
