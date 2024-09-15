package view

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.material.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import theme.*
import viewModel.MainViewModel

@Composable
fun MainScreen(viewModel: MainViewModel) {
    Column(modifier = Modifier.fillMaxSize()) {
        Row(modifier = Modifier.weight(1f)) {
            Column(
                modifier = Modifier.weight(1f)
            ) {
                InputBox(viewModel)
            }
            Column(
                modifier = Modifier.weight(1f)
            ) {
                OutputBox(viewModel)
            }
        }
        Row(modifier = Modifier.weight(1f)) {
            Column(
                modifier = Modifier.weight(1f)
            ) {
                ControlBox(viewModel)
            }
            Column(
                modifier = Modifier.weight(1f)
            ) {
                StateBox(viewModel)
            }
        }
    }
}

@Composable
fun InputBox (viewModel: MainViewModel) {
    var text by remember { mutableStateOf("") }
    Column(
        modifier = Modifier.fillMaxSize().background(lightGreenBlue),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strInputBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        TextField(
            value = text,
            onValueChange = {
                viewModel.onTextFieldTextChanged(text, it)
                text = it
            },
            label = { Text(strEnterText, style = typography.h2) },
            placeholder = { Text(strEnterSomething, style = typography.h2) },
            singleLine = false,
            modifier = Modifier.background(Color.Transparent).padding(dp16).fillMaxSize(),
            colors = TextFieldDefaults.textFieldColors(
                textColor = white,
                focusedIndicatorColor = white,
                unfocusedIndicatorColor = Color.Transparent,
                focusedLabelColor = white,
                unfocusedLabelColor = white,
                cursorColor = white,
            )
        )

    }
}

@Composable
fun OutputBox(viewModel: MainViewModel) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightGrayGreen),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strOutputBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        Box(
            modifier = Modifier.padding(dp16).fillMaxSize().background(transparentBlack)
        ) {
            Text(
                text = viewModel.sOutputText.value,
                modifier = Modifier
                    .padding(dp16).fillMaxSize(),
                overflow = TextOverflow.Ellipsis,
                maxLines = 4,
                textAlign = TextAlign.Center,
                style = typography.h2,
            )
        }
    }
}

@Composable
fun ControlBox(viewModel: MainViewModel) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightGreenGray),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strControlBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        ComPortComboBox(
            viewModel.selectedSenderCom,
            viewModel.sSenderText,
            strSenderPortNumber
        ) { comName ->
            viewModel.setSelectedSenderCom(comName)
        }
        ComPortComboBox(
            viewModel.selectedReceiverCom,
            viewModel.sReceiverText,
            strReceiverPortNumber
        ) { comName ->
            viewModel.setSelectedReceiverCom(comName)
        }
    }
}

@Composable
fun StateBox(viewModel: MainViewModel) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightPeach),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strStateBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        Column(modifier = Modifier.padding(dp16).fillMaxSize()) {
            Text(
                text = strBaudRate + viewModel.sBaudRate.value,
                modifier = Modifier.weight(1f).padding(top = dp16),
                style = typography.h2,
                textAlign = TextAlign.Center
            )
            Text(
                text = strSymbolsTransferredCount + viewModel.sSymbolsCount.value,
                modifier = Modifier.weight(1f).padding(top = dp16),
                style = typography.h2,
                textAlign = TextAlign.Center
            )
        }
    }
}

@OptIn(ExperimentalMaterialApi::class)
@Composable
fun ComPortComboBox(
    selectedCom: State<String>,
    isPortOpenedText: State<String>,
    hint: String,
    callback: (port: String) -> Unit
) {
    var expanded by remember { mutableStateOf(false) }
    val comPorts = listOf("COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8")
    Row (modifier = Modifier.padding(top = dp16, start = dp16, end = dp16)) {
        ExposedDropdownMenuBox(
            expanded = expanded,
            onExpandedChange = { expanded = !expanded },
            modifier = Modifier.weight(2f),
        ) {
            TextField(
                value = selectedCom.value,
                onValueChange = { },
                label = { Text(hint, style = typography.h4) },
                readOnly = true,
                colors = TextFieldDefaults.textFieldColors(
                    textColor = white,
                    focusedIndicatorColor = white,
                    unfocusedIndicatorColor = Color.Transparent,
                    focusedLabelColor = white,
                    unfocusedLabelColor = white,
                    cursorColor = white,
                )
            )
            ExposedDropdownMenu(
                expanded = expanded,
                onDismissRequest = { expanded = false }
            ) {
                comPorts.forEach { port ->
                    DropdownMenuItem(
                        onClick = {
                            callback(port)
                            expanded = false
                        }
                    ) {
                        Text(port)
                    }
                }
            }
        }

        Text(
            text = isPortOpenedText.value,
            style = typography.h3,
            modifier = Modifier.weight(1f).padding(start = dp8)
        )
    }

}