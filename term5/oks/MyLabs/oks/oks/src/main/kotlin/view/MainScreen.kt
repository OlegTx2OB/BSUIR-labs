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
import viewmodel.MainViewModel

@Composable
fun MainScreen(viewModel: MainViewModel) {
    Column(modifier = Modifier.fillMaxSize()) {
        Row(modifier = Modifier.weight(1f)) {
            Column(modifier = Modifier.weight(1f)) {
                InputBox(inputState = viewModel.InputStateImpl())
            }
            Column(modifier = Modifier.weight(1f)) {
                OutputBox(outputState = viewModel.OutputStateImpl())
            }
        }
        Row(modifier = Modifier.weight(1f)) {
            Column(modifier = Modifier.weight(1f)) {
                ControlBox(controlState = viewModel.ControlStateImpl())
            }
            Column(modifier = Modifier.weight(1f)) {
                StateBox(stateState = viewModel.StateStateImpl())
            }
        }
    }
}

@Composable
fun InputBox (inputState: MainViewModel.InputState) {
    var text by remember { mutableStateOf("") }
    Column(
        modifier = Modifier.fillMaxSize().background(lightGreenBlue),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strInputBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        TextField(
            value = text,
            onValueChange = {
                text = inputState.onTextFieldValueChange(text, it)
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
fun OutputBox(outputState: MainViewModel.OutputState) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightGrayGreen),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strOutputBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        Box(
            modifier = Modifier.padding(dp16).fillMaxSize().background(transparentBlack)
        ) {
            Text(
                text = outputState.sOutputText.value,
                modifier = Modifier.padding(dp16).fillMaxSize(),
                overflow = TextOverflow.Ellipsis,
                maxLines = 4,
                textAlign = TextAlign.Center,
                style = typography.h2,
            )
        }
    }
}

@Composable
fun ControlBox(controlState: MainViewModel.ControlState) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightGreenGray),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strControlBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        ComPortComboBox(
            controlState.sSelectedSenderComName.value,
            controlState.sComList.value,
            controlState.sSenderComStateText.value,
            strSenderPortNumber
        ) { comName ->
            controlState.setSelectedSenderCom(comName)
        }
        ComPortComboBox(
            controlState.sSelectedReceiverComName.value,
            controlState.sComList.value,
            controlState.sReceiverComStateText.value,
            strReceiverPortNumber
        ) { comName ->
            controlState.setSelectedReceiverCom(comName)
        }
    }
}

@Composable
fun StateBox(stateState: MainViewModel.StateState) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightPeach),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strStateBox, modifier = Modifier.padding(top = dp16), style = typography.h2)
        Column(modifier = Modifier.padding(dp16).fillMaxSize()) {
            Text(
                text = strBaudRate + stateState.sBaudRate.value,
                modifier = Modifier.weight(1f).padding(top = dp16),
                style = typography.h2,
                textAlign = TextAlign.Center
            )
            Text(
                text = strSymbolsTransferredCount + stateState.sSymbolsCount.value,
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
    selectedItem: String,
    dropDownMenuList: List<String>,
    isPortOpenedText: String,
    hint: String,
    callback: (port: String) -> Unit
) {
    var expanded by remember { mutableStateOf(false) }
    Row (modifier = Modifier.padding(top = dp16, start = dp16, end = dp16)) {
        ExposedDropdownMenuBox(
            expanded = expanded,
            onExpandedChange = { expanded = !expanded },
            modifier = Modifier.weight(2f),
        ) {
            TextField(
                value = selectedItem,
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
                onDismissRequest = { expanded = false },
            ) {
                dropDownMenuList.forEach { port ->
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
            text = isPortOpenedText,
            style = typography.h3,
            modifier = Modifier.weight(1f).padding(start = dp8)
        )
    }

}