import androidx.compose.material.MaterialTheme
import androidx.compose.ui.res.painterResource
import androidx.compose.ui.window.Window
import androidx.compose.ui.window.application
import androidx.lifecycle.viewmodel.compose.viewModel
import view.MainScreen
import viewModel.MainViewModel

fun main() = application {
    val viewModel1: MainViewModel = viewModel()
    val viewModel2: MainViewModel = viewModel()

    Window(
        onCloseRequest = ::exitApplication,
        title = "COM ports",
        icon = painterResource("drawable/ic_app_logo.png")
    ) {
        MaterialTheme {
            MainScreen(viewModel1) { oldText, newText ->
                viewModel2.onTextFieldTextChanged(oldText, newText)
            }
        }
    }

    Window(
        onCloseRequest = ::exitApplication,
        title = "COM ports 2",
        icon = painterResource("drawable/ic_app_logo.png")
    ) {
        MaterialTheme {
            MainScreen(viewModel2) { oldText, newText ->
                viewModel2.onTextFieldTextChanged(oldText, newText)
            }
        }
    }
}
