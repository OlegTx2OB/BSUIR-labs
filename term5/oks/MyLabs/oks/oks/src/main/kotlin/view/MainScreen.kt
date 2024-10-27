package view

import androidx.compose.foundation.*
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
    val mainStateImpl = viewModel.MainStateImpl()

    Column(modifier = Modifier.fillMaxSize()) {
        Row(modifier = Modifier.weight(1f)) {
            Column(modifier = Modifier.weight(1f)) {
                InputBox(inputState = mainStateImpl.InputImpl())
            }
            Column(modifier = Modifier.weight(1f)) {
                OutputBox(outputState = mainStateImpl.OutputImpl())
            }
        }
        Row(modifier = Modifier.weight(1f)) {
            Column(modifier = Modifier.weight(1f)) {
                ControlBox(controlState = mainStateImpl.ControlImpl())
            }
            Column(modifier = Modifier.weight(1f)) {
                StateBox(statusState = mainStateImpl.StateImpl())
            }
        }
    }
}

@Composable
fun InputBox (inputState: MainViewModel.MainState.Input) {
    var text by remember { mutableStateOf("") }
    Column(
        modifier = Modifier.fillMaxSize().background(lightGreenBlue),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strInputBox, modifier = Modifier.padding(top = dp8), style = typography.h2)
        if (inputState.sIsInputTextFieldVisible.value) {
            TextField(
                value = text,
                onValueChange = {
                    text = inputState.onTextFieldValueChange(text, it)
                },
                textStyle = typography.h2,
                label = { Text(strEnterText, style = typography.h2) },
                placeholder = { Text(strEnterSomething, style = typography.h2) },
                singleLine = false,
                modifier = Modifier.background(Color.Transparent).padding(dp8).fillMaxSize(),
                colors = TextFieldDefaults.textFieldColors(
                    textColor = white,
                    focusedIndicatorColor = white,
                    unfocusedIndicatorColor = Color.Transparent,
                    focusedLabelColor = white,
                    unfocusedLabelColor = white,
                    cursorColor = white,
                )
            )
        } else {
            Text(strSetSenderCom, modifier = Modifier.padding(top = dp8, start = dp8, end = dp8), style = typography.h2)
        }
    }
}

@Composable
fun OutputBox(outputState: MainViewModel.MainState.Output) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightGrayGreen),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strOutputBox, modifier = Modifier.padding(top = dp8), style = typography.h2)
        if(outputState.sIsOutputTextFieldVisible.value) {
            val scrollState = rememberScrollState()
            Box(
                modifier = Modifier.padding(dp8).fillMaxSize().background(transparentBlack).verticalScroll(scrollState)
            ) {
                Text(
                    text = outputState.sOutputText.value,
                    modifier = Modifier.padding(dp8).fillMaxSize(),
                    overflow = TextOverflow.Clip,
                    style = typography.h2,
                )
            }
        } else {
            Text(strSetReceiverCom, modifier = Modifier.padding(top = dp8, start = dp8, end = dp8), style = typography.h2)
        }
    }
}

@Composable
fun ControlBox(controlState: MainViewModel.MainState.Control) {
    Column(
        modifier = Modifier.fillMaxSize().background(lightGreenGray),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strControlBox, modifier = Modifier.padding(top = dp8), style = typography.h2)
        ComPortComboBox(
            controlState.sSelectedSenderComName.value,
            controlState.sComList.value,
            controlState.sSenderComStateText.value,
            strTransmitterPortNumber
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
fun StateBox(statusState: MainViewModel.MainState.Status) {
    val scrollState = rememberScrollState()

    Column(
        modifier = Modifier.fillMaxSize().background(lightPeach),
        horizontalAlignment = Alignment.CenterHorizontally
    ) {
        Text(strStateBox, modifier = Modifier.padding(top = dp8), style = typography.h2)
        Column(
            modifier = Modifier.padding(dp8).fillMaxSize().verticalScroll(scrollState),
            horizontalAlignment = Alignment.CenterHorizontally
        ) {
            TextH3CenterPaddingTop2(text = strCurrentPackageStructure + statusState.sCurrentPackageString.value)
            TextH3CenterPaddingTop2(text = strBaudRate + statusState.sBaudRate.value)
            TextH3CenterPaddingTop2(text = strSymbolsTransmittedCount + statusState.sTransferredSymbolsCount.value)
            TextH3CenterPaddingTop2(text = strStopBits + statusState.sStopBits.value)
            TextH3CenterPaddingTop2(text = strDataBitsCount + statusState.sDataBits.value)
            TextH3CenterPaddingTop2(text = strTimeoutMode + statusState.sTimeoutMode.value)
            TextH3CenterPaddingTop2(text = strWriteTimeOut + statusState.sWriteTimeout.value)
            TextH3CenterPaddingTop2(text = strReadTimeOut + statusState.sReadTimeout.value)
            TextH3CenterPaddingTop2(text = strParity + statusState.sParity.value)
        }
    }
}

@Composable
fun TextH3CenterPaddingTop2(text: String) {
    Text(
        text = text,
        modifier = Modifier.padding(top = dp2),
        style = typography.h3,
        textAlign = TextAlign.Center
    )
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
    Row (modifier = Modifier.padding(top = dp8, start = dp8, end = dp8)) {
        ExposedDropdownMenuBox(
            expanded = expanded,
            onExpandedChange = { expanded = !expanded },
            modifier = Modifier.weight(2f),
        ) {
            TextField(
                value = selectedItem,
                textStyle = typography.h2,
                onValueChange = { },
                label = { Text(hint, style = typography.h3) },
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
            style = typography.h2,
            modifier = Modifier.weight(1f).padding(start = dp8)
        )
    }

}